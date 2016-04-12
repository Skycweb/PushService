#pragma once
#include "../include/lzz_SocketInterface.h"

#pragma comment(lib,"ws2_32.lib")




class lzz_ClientSocket:public lzz_SocketInterface
{
private:
	SOCKET sockClient = 0;
	WSADATA wsa;
	SOCKADDR_IN addrClt;
	int addrClt_len = sizeof(SOCKADDR_IN);
	GUID my_guid_ID = {0};
public:
	lzz_ClientSocket();
	lzz_ClientSocket(GUID);
	//�󶨶˿�
	bool TcpConnect(int port, char *pIp);
	//������Ϣ
	bool TcpSend(void *pData, int len) override;
	//������Ϣ
	bool TcpRecv(void *pData, int len) override;

	bool TcpSend(void* pData, int len, ActionType a) override;
	void UdpSend(void* pData, int len, ActionType at, SOCKADDR* pAddress) override;
	bool UdpBind(char *pIp,int port);
	//������Ϣ
	void UdpSend(void *pData, int len,ActionType at) override;
	//������Ϣ
	void UdpRecv(void *pData, int len, SOCKADDR *pAddress) override;
	virtual ~lzz_ClientSocket();
	/*����ID*/
	GUID getID() const;
};

