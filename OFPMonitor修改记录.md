#服务器列表保存域名(2021.01.24)

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
	  ***但是处理来着服务器的信息时, 通过 ServerList::incomingMessage 调用的 getServer(String address) 获得一个IP并在 ServerList 的 list 里查找, 因此0号元素必须提供IP.***
	  *需要修改 Server 的构造函数, ServerList::addServer()方法。*
	+ 使用 Server 时, 它的IP地址和端口被直接使用. getServerByID()方法只发生在 OFPMonitorModel.cpp 的 OFPMonitorModel::onQueryTimer 函数里.
	  因此*使用域名的Server仍然应当存储IP和端口. *由此看来, *域名解析最好发生在 Server 创建之前*.
		+ ***ServerList 添加 getIPFromDomainName(String) 方法, 将域名转化为IP.***
		+ ***需要添加头文件和声明 resolv 函数. 这部分还可以再精修.***
	+ Server的保存
	  关闭程序时, Server对象的IP被记录.
	  程序通过当前的 ServerList 通过遍历, 向配置文件写入服务器信息. 对每一个server调用 Server::createSettingsFileEntry() 方法, 通过 Server::getGamespyAddress()方法录入IP.
	  *因为调用的是 Server 方法, 因此Server需要有域名的成员.*
	  *使用域名的Server, 应当录入域名. 需要一个方法判定 Server 对象是否使用域名. 需要特殊的标识表明录入的是域名.*
		+ ***使用域名的情况下，记录server对象的ip，并在ip之前追加字符'|'.***
	+ ServerList的更新(Server的读取)
		+ 开启程序时, Server对象被读取.
		  readSettings方法使用 StringSplitter 分割字符串. ***利用字符'|', 将域名特殊处理.***
			+ ***注意, split要求前后有其他字符才行. 这里普通地在'|'前加一个单词 domain.***
			+ ***不知为何, SubString和Pos的效率特别低. 所以还是使用 StringSplitter 来处理.***
		  readSettings方法使用 addServer(ServerConfigEntry) 添加 Server 对象. *调整这个函数.*
		+ 手动添加Server.
		  TWINDOW_SETTINGS::BUTTON_SERVERS_ADDClick 处理 Server 的手动添加. 它解析域名并使用 addServer 方法.
+ Server的调整
	+ ***Server 增加成员 bool isDomainName, 初始化为false. 增加成员 String DomainName 和方法 getDomainName(). ***
	  ***改写全部非默认构造函数, 添加 bool 和 String 默认参数, 用于 isDomainName 与 domainName 的赋值.***
	  ***设置方法 checkDomainName(), 读取 isDomainName 的值.***
+ addServer的调整
##addServer的修改
要在 OFPMonitorModel 里同步修改, 因为 OFPMonitorModel 通过 ServerList\* 调用同名方法.
+ addServer(ServerConfigEntry)
	+ 增加参数为(ServerConfigEntry entry, String domainName)的重载.
		+ AddObject 的0号参数记录域名.
		+ new Server的最后一个参数是true.
+ addServer(String)
	+ 增加参数为(String address, String domainName, bool isDomainName)的重载.
		+ AddObject 的0号参数记录域名.
		+ new Server的最后一个参数是true.
###removeServer的修改
由于 TStringList\* list 要求保存IP地址，因此不用特别处理。一个时期内，从域名解析得到的IP是相同的。就算运行期间IP发生了突变，下次启动程序时也就ok了。


+ 引理: 关于【Server的读取】, 根据 ServerList 的 getServerByID 成员函数来看, 调用了 ServerList 的 getServer(int) 函数. 该函数返回一个指向 Server 对象的指针, 这个指针是从 this->list->Objects[index] 通过 (Server\*) 转换得到的.

+ 引理: TWINDOW_SETTINGS 的 updateServerEditorList 函数 使用 list<int> 容器 allServers, 通过 OFPMonitorModel::getAllMatchingServers 函数, 记录 srv->getServerID().
	+ 问题: 在主界面中, 通过什么来刷新服务器列表呢?
+ 引理: 根据 getGamespyPort() 方法, 确定服务器的IP读取只发生在 OFPMonitorModel.cpp 的 OFPMonitorModel::onQueryTimer 函数里.
+ 提示: *根据 getGamePort() 方法, form_main.cpp 里调用它, 于软件左上角显示端口(及密码/插件: 是/否).*
##bug
+ 添加的服务器, 不会被显示在主页. 应该是IP的问题.
	+ 前述关于 ServerList::incomingMessage 的部分, 要求 ServerList 的 TStringList\* list 保存IP地址. 事实上修改后的 Server 对象已经有保存域名的成员了, 无需在list里保存.
+ (已解决|spilt要求关键字前后都有字符.) 域名会被保存, 但第二次打开时, 这个域名会被视作无效而不加入serverList, 程序关闭时无法被保存.



#2.01版本支持(2020.02.07)
为令程序支持2.01版本, fork源码并进行改动.
##游戏的版本探测
+ FileVersion::getOFPVersion.
	+ 游戏的版本检测 detected version 调用 getOFPVersion. 它通过 majorVersion, buildVersion, 经 IntToStr 转为字符串相加后再转回整数的结果，对2.01版本会返回21。*需要补上字符0.*
	+ 在"允许进入的服务器"的环节，由 OFPMonitorModel::getMatchingGame 通过 Game::checkIfCorrectGame 函数进行版本号大小校验时, 进行比较的版本也是 getOFPVersion的返回值.
	+ ***FileVersion::getOFPVersion()函数体内, 利用三目运算符, 为 buildVersion 小于10的情形追加一个字符 "0". 注意BCB6里String类首字母S要大写. ***
+ 服务器的Version:
  即主界面显示的201/201.
	+ 版本号的值是 LABEL_SERVERINFO_VERSION_VALUE, 它是 server 对象的 getRequiredVersion() 和 getActualVersion() 成员函数返回值直接转成字符串.
	+ 看起来, 从服务器获得的返回值是没有问题的. 无需修改.
##增设2.01的版本入口
将已经弃置不用的OFP:CWC改为ARMA:R即可. 这里只需要做一些关键字替换.
+ Operation Flashpoint: Cold War Crisis
  替换为 Arma: Resistance
	+ 文件 Form_Settings.dfm, OFPMonitorDefinitions.h
+ OperationFlashpoint.exe
  替换为ArmAResistance.exe
	+ 文件OFPMonitorDefinitions.h
##隐藏1.96版本
+ 游戏程序路径设置
  setting选项卡里隐藏配置1.96的部分.
	+ TWINDOW_SETTINGS::updateGames() 函数体内, 直接在 groupBox->visible 赋值处, 对1.96设置一个检测和隐藏.
	+ CHECKBOX_OFPRES 的隐藏, 需要在 Form_Settings.dfm 里直接对 object CHECKBOX_OFPRES 设置 visible = false.
	+ (2020.01.26更新) 将3个 LABEL_..._DETECTEDVERSION的起始位置左移20像素(345).
+ 服务器列表显示过滤
  利用已有的filter即可, 手动强制硬编码1.96的过滤.
	+ ServerFilterResult Server::checkFilter(ServerFilter \*filter) 内添加一个关于版本的判断
##自动启动游戏
getAppTitleByGameId 的返回结果，主要在于 GameControl.cpp 文件里。涉及到变量 offset1, 它是 WriteProcessMemory 的第二个参数 lpBaseAddress. 姑且先直接用1.99的值，测试可行.  
关键字大概是 获取进程的内存首地址. getAppTitleByGameId 定义于 OFPMonitorDefinitions.h 里, case ARMARES 的输出应当和进程名一致, 不可以有冒号，而且是大小写敏感的, 必须要写ArmA.
顺带把 OFPCWC, OFP:CWC 做一下关键字替换（全字匹配）。注意和上面 OFPMonitorDefinitions.h 里，case ARMARES 的输出不要冲突
##中文语言支持
简体字语言支持: 基于马哈鱼编辑过的文档进行再次编辑。
##程序基本外观(图标,标题)修改
+ 图标: 不是代码文件而是BCB对project的设置. Project Options Application. 
+ Title: OFPMonitor.cpp 里对 Application->Title = "OFPMonitor " + fv->getFullVersion()做修改. cpp, bpr, res文件名要自己手动改.
+ 版本号: Project Options Version Info里修改. 只改动OFPMonitor.bpr的版本没用，它只影响右键点击图标后的信息。修改版本为1.7.4.1，增加备注，修改产品名和内部名.
+ 其他操作记录:
	+ OFPMonitor.tds文件：剪切掉。不是编译程序所必需的，大概是中间产物
	+ OFPMonitor 关键字替换. 目的是修改标题, 但源码放在同名的一个子目录下, 这里利用全词匹配查找零散的 OFPMonitor 单字, 以及查找 \ofpmonitor\ 并临时更名.
	+ (2020.01.26) Form_Info.dfm 添加窗口高度和说明文本.
##遗留问题
+ 在进程里和OFPMonitor仍然识别为相同的程序
	+ 自动启动游戏, 也使用和1.99相同的 lpBaseAddress 值.
+ 右下角托盘图标还是原有的. 找不到这个图标从何处被调用. 可能封装在组件里?


#环境准备(2020.02.07)
##安装C++ Builder 6（以下简称BCB6）
已预备安装包。中英文均可。安装时使用一次keygen，初次运行时再使用一次（注册）。
##安装BCB6可用的Indy10控件
+ Indy10资源: 来自https://download.csdn.net/download/gdhuman/5334614, 通过CSDN代下获得资源，于QQ邮箱接收。
+ Indy10清理: 按照链接 https://bbs.csdn.net/topics/200083490, 或所下载的Indy.v10.1.6.Full.Source.Delphi.BCB目录下ccrun.com.txt及indy10安装提示.txt所记录的方式, 执行清理.
+ Indy10安装: 清理后就可以执行. 通过Indy.v10.1.6.Full.Source.Delphi.BCB\Lib\Fullc6.Indy10.bat生成完整的C6目录, 然后将C6目录复制到BCB6目录下Project里.
	+ （这步只是简化Component: Install packages而已，不是必须的）.
	+ 还有两篇相关文章 https://blog.csdn.net/sczyq/article/details/663538, https://blog.csdn.net/9527/article/details/1343234, 但这里没用上. 估计它们的内容在下载源里已处理.
+ Indy10添加: 2个组件. 这步在win10系统无法执行，需要在虚拟机XP系统里添加（使用虚拟机的提示源于https://bbs.csdn.net/topics/391854138 ）
+ 文件放置
	+ Project Options里include和lib仍然需要使用OFPMonitor\vcl_components\bin\Indy10_5161_BCB6.rar内相应的include与lib目录.
		+ 它们可以在BCB6里手动指定，也可以解压后合并到OFPMonitor.bpr所在目录下的include及lib目录
			+ 比如，将这三个子目录存储到 BCB\Project\Indy\ 同时 project Options 的 directions/conditionals 选项卡也增设这个路径.
				+ 增加 include 和lib 的路径, 例如 $(BCB)\Projects\Indy10\include (及lib). 也可手动复制文件到已设置的路径里.
+ 组件添加: 从OFPMonitor\vcl_components里加载CoolTrayIcon.bpl