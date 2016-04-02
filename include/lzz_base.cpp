#include "base.h"

void lzz_STR_2_GUID(wchar_t* buf, GUID* guid)
{

	CLSIDFromString(buf, guid);
}


void* operator new(size_t size)
{
	void* p = malloc(size); // Replace this with alternative allocator
	if (p != lzz_nullptr)
	{
		lzz_ZeroMemory(p, size);
	}
	return (p);
}

void operator delete(void* p)
{
	if (p != lzz_nullptr)
		free(p);
	p = lzz_nullptr;
}

void* operator new [](size_t size)
{
	void* p = malloc(size); // Replace this with alternative allocator
	if (p != lzz_nullptr)
	{
		lzz_ZeroMemory(p, size);
	}
	return (p);
}

void operator delete [](void* p)
{
	if (p != lzz_nullptr)
		free(p);
	p = lzz_nullptr;
}

