#pragma once
#include "../include/base.h"
class lzz_UserModle
{
private:
	 SOCKADDR addr;
public:
	lzz_UserModle();
	void setAddr(SOCKADDR *);
	SOCKADDR* getAddr();
	~lzz_UserModle();
};

