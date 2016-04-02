#include "lzz_Object.h"

lzz_Object::lzz_Object()
{
}

void* lzz_Object::operator new(size_t size)
{
	void* p = malloc(size); // Replace this with alternative allocator
	if (p != lzz_nullptr)
	{
		lzz_ZeroMemory(p, size);
	}
	return (p);
}

void lzz_Object::operator delete(void* p)
{
	if (p != lzz_nullptr)
		free(p);
	p = lzz_nullptr;
}

void* lzz_Object::operator new [](size_t size)
{
	void* p = malloc(size); // Replace this with alternative allocator
	if (p != lzz_nullptr)
	{
		lzz_ZeroMemory(p, size);
	}
	return (p);
}

void lzz_Object::operator delete [](void* p)
{
	if (p != lzz_nullptr)
		free(p);
	p = lzz_nullptr;
}

lzz_Object::~lzz_Object()
{
}

