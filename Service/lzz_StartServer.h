#pragma once
#include "lzz_ServerSocket.h"
#include "lzz_RecvThread.h"
#include "../include/lzz_ClientList.h"
#include "lzz_TcpRecv.h"
#include "lzz_pushOut.h"

class lzz_StartServer
{
private:
	lzz_SocketInterface *sk = new lzz_ServerSocket();//创建SOCKET
	lzz_SocketInterface *skTcp = new lzz_ServerSocket();//创建SOCKET
	lzz_ClientList *cl = new lzz_ClientList();//访问者列表
	lzz_RecvThread *rt = new lzz_RecvThread(sk,cl);
	lzz_TcpRecv *tcp = new lzz_TcpRecv(skTcp);
	lzz_pushOut *pushOut = new lzz_pushOut(sk, cl);
public:
	lzz_StartServer();
	void Start() const;
	virtual ~lzz_StartServer();
};

