#include "../include/base.h"
#include "lzz_StartServer.h"

using namespace std;

int main() {
    lzz_StartServer *ss = new lzz_StartServer();
    ss->Start();
	lzz_out << "Enter \"close\" to close the program" << lzz_endline;
    char ActionCode[10];
    while(lzz_Strcmp("close",ActionCode) != 0)
    {
        lzz_in >> ActionCode;
    }
    lzz_Delete(ss);
	
    return 0;
}
