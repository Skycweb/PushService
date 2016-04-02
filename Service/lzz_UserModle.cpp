#include "lzz_UserModle.h"
#include "../include/base.h"


lzz_UserModle::lzz_UserModle()
{
}

void lzz_UserModle::setAddr(SOCKADDR* v_sockaddr)
{
	lzz_Memcpy(&(this->addr), v_sockaddr, sizeof(SOCKADDR));
}

SOCKADDR* lzz_UserModle::getAddr()
{
	return &addr;
}

lzz_UserModle::~lzz_UserModle()
{
}
