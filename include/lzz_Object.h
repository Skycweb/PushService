#pragma once
#include "base.h"

class lzz_Object
{
public:
	lzz_Object();
	void * operator new(size_t size);
	void operator delete(void *p);
	void * operator new[](size_t size);
	void operator delete[](void *p);
	virtual ~lzz_Object();
};


