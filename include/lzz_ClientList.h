#pragma once
#include "base.h"
#include <winsock.h>
#include <map>
#include "../Service/lzz_UserModle.h"

class lzz_ClientList
{
private:
	std::map<GUID, lzz_UserModle*> list;
	bool addMap(GUID, lzz_UserModle*);
	GUID *y_empty;
	lzz_UserModle* FindMap(GUID);
public:
	lzz_ClientList();
	bool SaveClient(GUID, lzz_UserModle*);
	lzz_UserModle* GetClient(GUID);
	virtual ~lzz_ClientList();
	size_t GetCount();
};

