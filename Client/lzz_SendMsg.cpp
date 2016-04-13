#include "lzz_SendMsg.h"

lzz_SendMsg::lzz_SendMsg()
{
	isSend = false;
}

lzz_SendMsg::~lzz_SendMsg()
{
}

bool lzz_SendMsg::Recv(GUID MsgId, char* SendData, int DataLen)
{
	char isOk[1] = { 1 };
	lzz_SocketInterface *_sk = new lzz_ClientSocket();
	if (!((lzz_ClientSocket*)_sk)->TcpConnect(lzz_ServiceTcpPort, lzz_ServiceTcpIp))return false;
	char ff[16 + 1] = {0};
	ff[0] = 2;
	lzz_Memcpy(&ff[1], &MsgId, 16);
	_sk->TcpSend(ff, 17, ActionType::PushMsg);
	_sk->TcpRecv(SendData, DataLen);
	_sk->TcpSend(isOk, 1);
	lzz_Delete(_sk);
	return isOk[0] == 1;
}

bool lzz_SendMsg::Send(GUID RecvUserId, char* SendData, int DataLen)
{
	char isOk[1] = { 0 };
	lzz_SocketInterface *_sk = new lzz_ClientSocket();
	if (!((lzz_ClientSocket*)_sk)->TcpConnect(lzz_ServiceTcpPort, lzz_ServiceTcpIp))return false;
	char* ff = new char[16 + 16 + 1+4 + DataLen];
	ff[0] = 1;
	lzz_Memcpy(&ff[1], &lzz_UserId, 16);
	lzz_Memcpy(&ff[16 + 1], &RecvUserId, 16);
	lzz_Memcpy(&ff[16+1+16],&DataLen,4);
	lzz_Memcpy(&ff[16+16+1+4],SendData,DataLen);
	_sk->TcpSend(ff, DataLen + 1 + 16+16+4,ActionType::PushMsg);
	_sk->TcpRecv(isOk, 1);
	lzz_Delete(_sk);
	lzz_Deletes(ff);
	return isOk[0] == 1;
}

void lzz_SendMsg::onLoad()
{
	int len = *(int*)request;
	char *pstr = new char[len];
	GUID id = *(GUID*)&request[4];
	Recv(id, pstr, len);
	lzz_out << pstr << lzz_endline;
	lzz_Deletes(pstr);
}









