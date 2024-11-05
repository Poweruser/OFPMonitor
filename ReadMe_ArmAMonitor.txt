ArmAMonitor.exe made by IF, modified basing on OFPMonitor 1.7.4.0.
New released files:
"ArmaMonitor.exe" - the product,
"ArmaMonitor.ini" - the profile,
"OFPM_Chinese_Simplified.lang" - modified Chinese Language files.

=============================Features=============================
Supporting Game Version: 
OFP:CWC and OFP:RES are removed and not supported.
ArmA: Resistance (2.01 OFP by [4RTech]) is added and supported.

Automation:
ArmA: Resistance (2.01 OFP by [4RTech]) is added and supported.

Server List:
Servers whose version less than 1.99 won't be displayed in ArmAMonitor.

Program Name:
Rename to ArmaMonitor.exe.

Icon:
Using the icon of ArmA: Resistance. However unable to edit the icon display in tray thus remain the icon of OFP.


==================Personal Notes About Compiling==================
1. Prepare the OS: Windows XP in a virtual machine.
2. Setup Borland C++ build 6(BCB6) there.
3. Uninstall/Remove all elements of Indy in BCB6.
4. Install Indy10 for BCB6(I used the Indy10.1.6)
5. Install the CoolTrayIcon from "\OFPMonitor\vcl_components\bin\CoolTrayIcon.bpl"
6. Decompress the "\OFPMonitor\vcl_components\bin\Indy10_5161_BCB6.rar", add newly created folders "include" and "lib" into BCB6's Project Options(or integrate these 2 folders whth same-name folders located in "\OFPMonitor\", and they'll be used automatically by BCB6 when compiling OFPMonitor).
7. Open OFPMonitor.bpr by BCB6, and Make/Build the program(Ctrl+F9). If succeed, there'll be about 2 warnings but 0 error. The product OFPMonitor.exe can be tested by moving it into "\Monitor\required_dlls\".
*. I neither set GIT_SSL_NO_VERIFY environment variable nor added ";$(BCB)\lib\Psdk" as "readme.txt" suggested.


======================Modifications in Detail=====================
Supporting 2.01 Game:
Simply renaming those OFP:CWC, Cold war crisis and the identification of executable file(Operation Flashpoint) can make it "looks" supporting 2.01.
The version which is detected from EXE and used for judging the permission to join a server is gained by the function "getOFPVersion", which will return "21" for ArmA:Resistance without modification. The "getOFPVersion" is defined in FileVersion.cpp. The edited function will add a "0" in the middle if the buildVersion of game is less than 10.
2.01 needs to be added into Automation as well. In "GameControl.cpp" the program using the return value of the function "getAppTitleByGameId" defined in OFPMonitorDefinitions.h. Notice that the comparison of process's title and the function's return value is cASe-seNsItiVE, thus in the String function "getAppTitleByGameId" the return value for 2.01 should be "ArmA Resistance" but not "Arma Resistance". There're still many lower-case "Arma Resistance" in other files remain not replaced by "ArmA Resistance" but they won't cause problems in this first version ArmaMonitor 1.7.4.1.

Unsupporting 1.96 Game:
In the function "updateGames" defined in Form_Settings.cpp, the groupbox->Visible is always false if (i == OFPRES), which means never displaying the second part of the page. The second check box is hided by adding the "visible" member to "CHECKBOX_OFPRES" defined in Form_Settings.dfm and set it "false".

Server List:
In the function "checkFilter" defined in Server.cpp, a condition about server's version(the "actver" member) is added to filter 1.96 servers.

Program's information:
They should be edited in "*.bpr" and "*.cpp" files by directly editing or by BCB6, to change the icon, program name, etc.