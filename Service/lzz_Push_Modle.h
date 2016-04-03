#pragma once
#include "../include/base.h"


struct lzz_Push_Modle
{
public:
	GUID UserId;//要推送的会员ID
	volatile char* data = lzz_nullptr;//推送的数据
	volatile int DataLen = 0;
	GUID ActionId;
	volatile bool isUser = false;//是否在使用
};
