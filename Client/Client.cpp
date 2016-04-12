#include "Client.h"
#include "lzz_RunStart.h"




int main(int argc, char* argv[])
{
	lzz_NewGuid(&lzz_UserId);
	lzz_out << "UserId：" << lzz_GuidToString(lzz_UserId) << lzz_endline;
	//lzz_in >> id;
	//GUID userId;
	//int len = MultiByteToWideChar(CP_ACP, 0, id, -1, NULL, 0);
	//wchar_t *w_string = new wchar_t[len];
	//memset(w_string, 0, sizeof(wchar_t)*len);
	//MultiByteToWideChar(CP_ACP, 0, id, -1, w_string, len);
	//lzz_STR_2_GUID(w_string, &userId);

	lzz_RunStart *rs = new lzz_RunStart(lzz_UserId);
	rs->Start();
	lzz_HeartbeatThread *ht = new lzz_HeartbeatThread(rs->getSOCKET());
	ht->Start();
	char ActionCode[10];
	while (lzz_Strcmp("close", ActionCode) != 0)
	{
		lzz_out << "输入close关闭程序" << lzz_endline;
		lzz_in >> ActionCode;
	}
	delete ht;
	delete rs;

//	lzz_out << "10个字符串" << lzz_endline;
//	char tt[10];
//	lzz_in >> tt;
//
//		lzz_ClientSocket *TcpSk = new lzz_ClientSocket();
//		static_cast<lzz_ClientSocket*>(TcpSk)->TcpConnect(lzz_ServiceTcpPort, lzz_ServiceTcpIp);
//	while (true)
//	{	
//
//
////		lzz_out << "传递出去的数据是：";
////		for (int i = 0; i < 10; i++)
////			lzz_out << int(tt[i]) << " ";
////		lzz_out << lzz_endline;
//		TcpSk->TcpSend(tt, 10);
////		lzz_ZeroMemory(tt, 10);
//
//		lzz_in >> tt;
//		
//	}
//		delete TcpSk;	
	return 0;

}
