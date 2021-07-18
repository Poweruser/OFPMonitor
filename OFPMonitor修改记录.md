#服务器列表保存域名
2021.01.24
##域名的解析
+ 引理1
  域名的解析只发生在添加服务器时.
	+ 文件 Form_Settings 定义了类 TWINDOW_SETTINGS. 成员函数 BUTTON_SERVERS_ADDClick 执行域名的解析与服务器列表的添加.
##对象的结构
+ 引理2
  类 TWINDOW_SETTINGS 有数据成员 OFPMonitorModel \*ofpm.
  类 OFPMonitorModel 有数据成员 ServerList \*servers. OFPMonitorModel 还有一些成员函数, 通过成员 servers 调用 ServerList 的同名成员函数.
  类 ServerList 有数据成员 TStringList \*list. 它使用 AddObject 方法插入一个对象(2个参数, 参数0是字符串, 参数1是(TObject\*)指针, 指向一个 new Server 对象).
  类 Server 有数据成员 serverID (往 ServerList 添加新 Server 对象时计数的索引)与方法 getServerByID(), 成员 ip 及方法 getIP(), 成员 gamespyport 及方法 getGamespyPort()等. 此外, 还有方法 getServerID(), getGamespyAddress()等.
  
##服务器信息的读写
从配置文件\*.ini入手找线索.  
程序关闭时, 于 ArmaMonitor.cpp 末尾, 调用 WINDOW_MAIN->saveSettings() 方法向配置文件写入信息.  
程序启动时, 通过 ServerList::readSettings 读取信息. 读取的信息被逐行分析, 通过 StringSplitter 对象的 split 方法(结合 Count 方法) 处理记录的服务器.  
*对程序的改写, 需要让 serverlist 中使用域名的服务器, 以域名的形式写入和读取.*  
##ServerList的存储方式及Server的结构
+ ServerList的存储方式分析
	+ ServerList 使用成员 TStringList \*list 存储 Server 对象. 它使用 AddObject 方法添加元素, 参数为(字符串, \* Server对象).
	  *0号参数用于list内的查找. 原设置中它使用IP地址, 从这个角度来说用域名也有同样的效果.*
	  *需要修改 Server 的构造函数, ServerList::addServer()方法。*
	+ 使用 Server 时, 它的IP地址和端口被直接使用. getServerByID()方法只发生在 OFPMonitorModel.cpp 的 OFPMonitorModel::onQueryTimer 函数里.
	  因此*使用域名的Server仍然应当存储IP和端口. *由此看来, *域名解析最好发生在 Server 创建之前*.
		+ ***ServerList 添加 getIPFromDomainName(String) 方法, 将域名转化为IP.***
	+ Server的保存
	  关闭程序时, Server对象的IP被记录.
	  程序通过当前的 ServerList 通过遍历, 向配置文件写入服务器信息. 对每一个server调用 Server::createSettingsFileEntry() 方法, 通过 Server::getGamespyAddress()方法录入IP.
	  *因为调用的是 Server 方法, 因此Server需要有域名的成员.*
	  *使用域名的Server, 应当录入域名. 需要一个方法判定 Server 对象是否使用域名. 需要特殊的标识表明录入的是域名.*
		+ ***使用域名的情况下，记录server对象的ip，并在ip之前追加字符'|'.***
	+ ServerList的更新(Server的读取)
		+ 开启程序时, Server对象被读取.
		  readSettings方法使用 StringSplitter 分割字符串. ***利用字符'|', 将域名特殊处理.
		  readSettings方法使用 addServer(ServerConfigEntry) 添加 Server 对象. *调整这个函数.*
		+ 手动添加Server.
		  TWINDOW_SETTINGS::BUTTON_SERVERS_ADDClick 处理 Server 的手动添加. 它解析域名并使用 addServer 方法.
+ Server的调整
	+ ***Server 增加成员 bool isDomainName, 初始化为false. 增加成员 String DomainName 和方法 getDomainName(). ***
	  ***改写全部非默认构造函数, 添加 bool 和 String 默认参数, 用于 isDomainName 与 domainName 的赋值.***
	  ***设置方法 checkDomainName(), 读取 isDomainName 的值.***
+ addServer的调整
##addServer的修改
+ addServer(ServerConfigEntry)
	+ 增加参数为(ServerConfigEntry entry, String domainName)的重载.
		+ AddObject 的0号参数记录域名.
		+ new Server的最后一个参数是true.
+ addServer(String)
	+ 增加参数为(String address, String domainName, bool isDomainName)的重载.
		+ AddObject 的0号参数记录域名.
		+ new Server的最后一个参数是true.


+ 引理: 关于【Server的读取】, 根据 ServerList 的 getServerByID 成员函数来看, 调用了 ServerList 的 getServer(int) 函数. 该函数返回一个指向 Server 对象的指针, 这个指针是从 this->list->Objects[index] 通过 (Server\*) 转换得到的.

+ 引理: TWINDOW_SETTINGS 的 updateServerEditorList 函数 使用 list<int> 容器 allServers, 通过 OFPMonitorModel::getAllMatchingServers 函数, 记录 srv->getServerID().
	+ 问题: 在主界面中, 通过什么来刷新服务器列表呢?
+ 引理: 根据 getGamespyPort() 方法, 确定服务器的IP读取只发生在 OFPMonitorModel.cpp 的 OFPMonitorModel::onQueryTimer 函数里.
+ 提示: *根据 getGamePort() 方法, form_main.cpp 里调用它, 于软件左上角显示端口(及密码/插件: 是/否).*


##思路
+ 需要使用一种方法添加域名 domainName 而非IP. 从函数重载来说, 添加一个逻辑值比较好. 缺省为false, 函数体内 if false 则调用 添加address 的函数.
+ 当获取服务器时, 检查 isDomainName, 如果为true, 则按照域名解析的方式获取服务器.
##操作
+ addServer函数:
	+ OFPMonitorModel 里, 增加函数 void addServer(String address, String domainName, bool isDomainName), 调用 ServerList 的同名成员函数.
	+ ServerList 里, 增加一个重载函数 bool ServerList::addServer(String address, String domainName, bool isDomainName);
		+ 这个函数通过传入的address记录ip和端口, 同时记录域名 domainName 并将server对象的 isDomainName 标注为true.
			+ 此时server记录了域名解析得到的当前ip与端口, 之后可以持续直接使用.
			+ **读取server的新信息时, 要如何从域名解析IP? 从ini的记录里找找线索.**

+ TWINDOW_SETTINGS::BUTTON_SERVERS_ADDClick函数:
	+ value 为域名的分支, 调用 this->ofpm->addServer(true, value);
	
+ **removeServer**