
git:
set environment variable:
GIT_SSL_NO_VERIFY=true


software required:
 > Borland C++ build 6


Build the software:
* [Linker Fatal Error] Fatal: Unable to open file 'PSAPI.LIB'
   > Project options->Directories/conditionals>Libarypath
     add ";$(BCB)\lib\Psdk"

