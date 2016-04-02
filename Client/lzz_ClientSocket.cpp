#include "lzz_ClientSocket.h"



lzz_ClientSocket::lzz_ClientSocket()
{
	lzz_STR_2_GUID(L"{74B0E245-EA33-4869-8DE3-B5A51E1E1C7D}", &my_guid_ID);
}

bool lzz_ClientSocket::TcpConnect(int port,char *pIp)
{
	sockClient = socket(AF_INET, SOCK_STREAM, 0);

	addrClt.sin_addr.S_un.S_addr = inet_addr(pIp);// inet_addr将IP地址从点数格式转换成网络字节格式整型。
	addrClt.sin_family = AF_INET;
	addrClt.sin_port = htons(port);

	int back = connect(sockClient, reinterpret_cast<SOCKADDR*>(&addrClt), sizeof(SOCKADDR));//客户机向服务器发出连接请求
	if (back == 0)
	{
		lzz_out << "连接服务器失败" << lzz_endline;
		return false;
	}
	return true;
}

bool lzz_ClientSocket::TcpSend(void* pData, int len)
{
	return send(sockClient, static_cast<char*>(pData), len, 0) == len;
}

bool lzz_ClientSocket::TcpRecv(void* pData, int len)
{
	for (int i = 0; i < len; i++)
	{
		int state = recv(sockClient, static_cast<char*>(pData) + i, 1, 0);
		if (state <= 0)
		{
			return false;
		}
	}
	return true;
}

bool lzz_ClientSocket::TcpSend(void* pData, int len, ActionType at)
{
	char *s = new char[len + 8];
	lzz_ZeroMemory(s, len + 8);
	lzz_Memcpy(&(s[0]), &at, 4);
	lzz_Memcpy(&(s[4]), &len, 4);
	lzz_Memcpy(&(s[8]), pData, len);
	int state = send(sockClient, s, len + 8, 0);
	lzz_Deletes(s);
	return state > 0;
}

void lzz_ClientSocket::UdpSend(void* pData, int len, ActionType at, SOCKADDR* pAddress)
{

}

bool lzz_ClientSocket::UdpBind(char* pIp, int port)
{
	
	struct sockaddr_in mysock;
	lzz_ZeroMemory(&mysock, sizeof(mysock));  //初始化结构体
	addrClt.sin_family = AF_INET;  //设置地址家族
	addrClt.sin_port = htons(port);  //设置端口
	addrClt.sin_addr.s_addr = inet_addr(pIp);  //设置地址
	return (sockClient = socket(AF_INET, SOCK_DGRAM, 0)) > 0;
}

void lzz_ClientSocket::UdpSend(void* pData, int len, ActionType at)
{
	char *s = new char[len+8];
	lzz_ZeroMemory(s, len+8);
	lzz_Memcpy(&(s[0]), &at, 4);
	lzz_Memcpy(&(s[4]), &len, 4);
	lzz_Memcpy(&(s[8]), pData, len);
	sendto(sockClient, s, len + 8, 0, reinterpret_cast<SOCKADDR*>(&addrClt), sizeof(SOCKADDR));
	lzz_Deletes(s);
}

void lzz_ClientSocket::UdpRecv(void *pData, int len, SOCKADDR* pAddress)
{
	recvfrom(sockClient, static_cast<char*>(pData), len, 0, pAddress, &len);//from收到客户端的IP信息
}



lzz_ClientSocket::~lzz_ClientSocket()
{
	shutdown(sockClient, 2);
	sockClient = 0;
}

GUID lzz_ClientSocket::getID() const
{
	return my_guid_ID;
}
