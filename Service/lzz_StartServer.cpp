#include "lzz_StartServer.h"


lzz_StartServer::lzz_StartServer()
{
}

void lzz_StartServer::Start() const
{
	static_cast<lzz_ServerSocket*>(sk)->UdpBind(8024);
	static_cast<lzz_ServerSocket*>(skTcp)->TcpBind(8023);
	tcp->Start();
	rt->Start();
	pushOut->Start();
}

lzz_StartServer::~lzz_StartServer()
{
	lzz_Delete(pushOut);
	lzz_Delete(rt);
	lzz_Delete(tcp);
	lzz_Delete(sk);
	lzz_Delete(skTcp);
	lzz_Delete(cl);
}
