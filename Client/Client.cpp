#include "Client.h"
#include "lzz_RunStart.h"




int main(int argc, char* argv[])
{
	lzz_out << "1or2" << lzz_endline;
	char ty[1];
	lzz_in >> ty;
	GUID _RecvUserId;
	if(ty[0] == 49)
	{
		lzz_STR_2_GUID(L"{AB78C729-3A7A-4172-8BCF-2C9D72A46481}", &lzz_UserId);
		lzz_STR_2_GUID(L"{75825370-4171-42BD-8C93-3A0C5F6F14D1}", &_RecvUserId);
	}
	else
	{
		lzz_STR_2_GUID(L"{75825370-4171-42BD-8C93-3A0C5F6F14D1}", &lzz_UserId);
		lzz_STR_2_GUID(L"{AB78C729-3A7A-4172-8BCF-2C9D72A46481}", &_RecvUserId);
	}
	//lzz_NewGuid(&lzz_UserId);
	lzz_out << "UserId：" << lzz_GuidToString(lzz_UserId) << lzz_endline;
	//lzz_in >> id;
	//GUID userId;

	lzz_RunStart *rs = new lzz_RunStart();
	lzz_HeartbeatThread *ht = new lzz_HeartbeatThread(rs->getSOCKET());
	ht->Start();
	rs->Start();
	lzz_SendMsg * msg = new lzz_SendMsg();
	char ActionCode[10];
	
	while (lzz_Strcmp("close", ActionCode) != 0)
	{
		lzz_out << "请输入发送的信息：" << lzz_endline;
		char msgData[200] = {0};
		lzz_in >> msgData;
		msg->Send(_RecvUserId, msgData, 200);
//		lzz_out << "输入close关闭程序"  << lzz_endline;
//		lzz_in >> ActionCode;
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
