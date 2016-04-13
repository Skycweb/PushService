#include "lzz_UserModle.h"


lzz_UserModle::lzz_UserModle()
{
	clientType = lzz_ClientType::None;
}

lzz_UserModle::lzz_UserModle(lzz_ClientType* ct, SOCKADDR* userAddress)
{
	clientType = *ct;
	addr = *userAddress;
}

void lzz_UserModle::setAddr(SOCKADDR* v_sockaddr)
{
	addr = *v_sockaddr;
}

void lzz_UserModle::setClientType(lzz_ClientType* ct)
{
	clientType = *ct;
}

SOCKADDR* lzz_UserModle::getAddr()
 {
	return &addr;
}

lzz_UserModle::~lzz_UserModle()
{

}
