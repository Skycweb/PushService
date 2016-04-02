#include "Client.h"
#include "lzz_RunStart.h"
#include "../include/base.h"



int main(int argc, char* argv[])
{
	lzz_RunStart *rs = new lzz_RunStart();
	rs->Start();
	lzz_HeartbeatThread *ht = new lzz_HeartbeatThread(rs->getSOCKET());
	ht->Start();
	char ActionCode[10];
	while (lzz_Strcmp("close", ActionCode) != 0)
	{
		lzz_out << "ÊäÈëclose¹Ø±Õ³ÌÐò" << lzz_endline;
		lzz_in >> ActionCode;
	}
	delete ht;
	delete rs;

}
