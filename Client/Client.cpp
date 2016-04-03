#include "Client.h"
#include "lzz_RunStart.h"




int main(int argc, char* argv[])
{
//	lzz_RunStart *rs = new lzz_RunStart();
//	rs->Start();
//	lzz_HeartbeatThread *ht = new lzz_HeartbeatThread(rs->getSOCKET());
//	ht->Start();
//	char ActionCode[10];
//	while (lzz_Strcmp("close", ActionCode) != 0)
//	{
//		lzz_out << "输入close关闭程序" << lzz_endline;
//		lzz_in >> ActionCode;
//	}
//	delete ht;
//	delete rs;

	//lzz_out << "我收到一个推送包" << lzz_endline;
	lzz_ClientSocket *TcpSk = new lzz_ClientSocket();
	static_cast<lzz_ClientSocket*>(TcpSk)->TcpConnect(lzz_ServiceTcpPort, lzz_ServiceTcpIp);
	char data[20];

	while (true)
	{
		lzz_ZeroMemory(data, 20);
		lzz_in >> data;
		TcpSk->TcpSend(data, 20);
	}
	delete TcpSk;
	return 0;

}
