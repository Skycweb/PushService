#include "lzz_Heartbeat.h"

lzz_Heartbeat::~lzz_Heartbeat()
{
}

void lzz_Heartbeat::onLoad()
{
	lzz_out << "收到来自：" << inet_ntoa(((SOCKADDR_IN*)&(this->address_sockaddr_))->sin_addr) <<":"<< ((SOCKADDR_IN*)&(this->address_sockaddr_))->sin_port << "的心跳包,系统当前连接数："<< cl->GetCount() << lzz_endline;
	GUID guid;
	lzz_Memcpy(&guid, request, 16);
	lzz_UserModle *userModle = cl->GetClient(guid);
	if(!userModle)
	{
		userModle = new lzz_UserModle();
		userModle->setAddr(&(this->address_sockaddr_));
		cl->SaveClient(guid, userModle);
	}
	else
	{
		userModle->setAddr(&(this->address_sockaddr_));
	}
}
