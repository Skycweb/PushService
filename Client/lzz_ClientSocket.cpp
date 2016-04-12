#include "lzz_ClientSocket.h"



lzz_ClientSocket::lzz_ClientSocket()
{
}

lzz_ClientSocket::lzz_ClientSocket(GUID userId)
{
	my_guid_ID = userId;
}

bool lzz_ClientSocket::TcpConnect(int port,char *pIp)
{
	sockClient = socket(AF_INET, SOCK_STREAM, 0);

	addrClt.sin_addr.S_un.S_addr = inet_addr(pIp);// inet_addr��IP��ַ�ӵ�����ʽת���������ֽڸ�ʽ���͡�
	addrClt.sin_family = AF_INET;
	addrClt.sin_port = htons(port);

	int back = connect(sockClient, reinterpret_cast<SOCKADDR*>(&addrClt), addrClt_len);//�ͻ����������������������
	if (back == SOCKET_ERROR)
	{
		lzz_out << "���ӷ�����ʧ��" << lzz_endline;
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
	lzz_ZeroMemory(&mysock, sizeof(mysock));  //��ʼ���ṹ��
	addrClt.sin_family = AF_INET;  //���õ�ַ����
	addrClt.sin_port = htons(port);  //���ö˿�
	addrClt.sin_addr.s_addr = inet_addr(pIp);  //���õ�ַ
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
	recvfrom(sockClient, static_cast<char*>(pData), len, 0, pAddress, &len);//from�յ��ͻ��˵�IP��Ϣ
}



lzz_ClientSocket::~lzz_ClientSocket()
{
		closesocket(sockClient);
}

GUID lzz_ClientSocket::getID() const
{
	return my_guid_ID;
}
