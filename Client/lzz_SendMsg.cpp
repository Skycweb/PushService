#include "lzz_SendMsg.h"

lzz_SendMsg::lzz_SendMsg()
{
	isSend = ((lzz_ClientSocket*)sk)->TcpConnect(lzz_ServiceTcpPort, lzz_ServiceTcpIp);
}

lzz_SendMsg::~lzz_SendMsg()
{
	lzz_Delete(sk);
}

bool lzz_SendMsg::Recv(GUID MsgId, char* SendData, int DataLen)
{
	char isOk[1] = { 1 };
	lzz_SocketInterface *sk = new lzz_ClientSocket();
	if (!((lzz_ClientSocket*)sk)->TcpConnect(lzz_ServiceTcpPort, lzz_ServiceTcpIp))return false;
	char ff[16 + 1] = {0};
	ff[0] = 2;
	lzz_Memcpy(&ff[1], &MsgId, 16);
	sk->TcpSend(ff, 17, ActionType::PushMsg);
	sk->TcpRecv(SendData, DataLen);
	sk->TcpSend(isOk, 1);
	lzz_Delete(sk);
	return isOk[0] == 1;
}

bool lzz_SendMsg::Send(GUID RecvUserId, char* SendData, int DataLen)
{
	char isOk[1] = { 0 };
	lzz_SocketInterface *sk = new lzz_ClientSocket();
	if (!((lzz_ClientSocket*)sk)->TcpConnect(lzz_ServiceTcpPort, lzz_ServiceTcpIp))return false;
	char* ff = new char[16 + 16 + 1 + DataLen];
	ff[0] = 1;
	lzz_Memcpy(&ff[1], &lzz_UserId, 16);
	lzz_Memcpy(&ff[16 + 1], &RecvUserId, 16);
	lzz_Memcpy(&ff[16+1+16],&DataLen,4);
	lzz_Memcpy(&ff[16+16+1+4],SendData,DataLen);
	sk->TcpSend(ff, DataLen + 11 + 16,ActionType::PushMsg);
	lzz_Deletes(ff);
	sk->TcpRecv(isOk, 1);
	lzz_Delete(sk);
	return isOk[0] == 1;
}

void lzz_SendMsg::onLoad()
{
	
}









