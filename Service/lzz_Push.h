#pragma once
#include "../include/lzz_Factory.h"
#include "lzz_Push_Modle.h"
#include <list>


class lzz_Push : public lzz_Factory
{
private:
	static std::list<lzz_Push_Modle*> _list;
	static void* p_lzz_Push_Modle;
	static int count;//�����Խ��ն��ٸ�����
	static volatile bool isInitialization;//��ʼ��
	static volatile bool read;//��ȡ��
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



