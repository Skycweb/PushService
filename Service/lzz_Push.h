#pragma once
#include "../include/lzz_Factory.h"
#include "lzz_Push_Modle.h"
#include <list>


class lzz_Push : public lzz_Factory
{
private:
	static std::list<lzz_Push_Modle*> _list;
	static void* p_lzz_Push_Modle;
	static int count;//最多可以接收多少个推送
	static volatile bool isInitialization;//初始化
	static volatile bool read;//读取锁
public:
	lzz_Push();
	static void AddModle(GUID, char*,int);
	static void DeleteModle(GUID, lzz_SocketInterface*);
	static void lock();
	static void unlock();
	void onLoad() override;
	virtual ~lzz_Push();
	static std::list<lzz_Push_Modle*> *getList();
};



