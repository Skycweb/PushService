#include "lzz_ClientList.h"



bool operator < (GUID l, GUID r){
	return lzz_Memcmp(&r,&l,sizeof(GUID)) > 0;
}

bool lzz_ClientList::addMap(GUID key, lzz_UserModle *ip)
{
	std::pair< std::map< GUID, lzz_UserModle* >::iterator, bool > ret = list.insert(std::pair<GUID, lzz_UserModle*>(key, ip));
	if(ret.second)
	{
		return true;
	}
	list[key] = ip;
	return true;
}

lzz_UserModle *lzz_ClientList::FindMap(GUID key)
{
	std::map<GUID, lzz_UserModle*>::iterator it = list.find(key);
	if (it != list.end())
		return it->second;
	else
		return lzz_nullptr;
}


lzz_ClientList::lzz_ClientList()
{
}

bool lzz_ClientList::SaveClient(GUID key, lzz_UserModle *ip)
{
	return addMap(key, ip);
}

lzz_UserModle* lzz_ClientList::GetClient(GUID key)
{
	return FindMap(key);
}

lzz_ClientList::~lzz_ClientList()
{
}

size_t lzz_ClientList::GetCount()
{
	return list.size();
}
