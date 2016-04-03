#pragma once
#include "../include/base.h"
namespace ClientType {
	enum lzz_ClientType_
	{
		  None = 0 //无法识别的前端
		, IOS = 1//苹果手机
		, Android = 2//安卓手机
	};
}

typedef ClientType::lzz_ClientType_ lzz_ClientType;//重新定义枚举类型
class lzz_UserModle
{
private:
	 SOCKADDR addr;
	 lzz_ClientType clientType;
public:
	lzz_UserModle();
	lzz_UserModle(lzz_ClientType *ct,SOCKADDR* userAddress);
	void setAddr(SOCKADDR *);
	void setClientType(lzz_ClientType *ct);
	SOCKADDR* getAddr();
	~lzz_UserModle();
};

