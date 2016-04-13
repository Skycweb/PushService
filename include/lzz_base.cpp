#include "base.h"

GUID lzz_UserId;


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

std::string lzz_GuidToString(const GUID &guid)
{
	char buf[64] = { 0 };
#ifdef __GNUC__
	snprintf(
#else // MSVC
	_snprintf_s(
#endif
		buf,
		sizeof(buf),
		"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	return std::string(buf);
}
