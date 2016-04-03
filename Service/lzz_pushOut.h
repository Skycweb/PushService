#pragma once
#include "../Service/lzz_Push.h"
#include "../include/lzz_Thread.h"


class lzz_pushOut :
	public lzz_Thread
{

public:
	lzz_pushOut();
	lzz_pushOut(lzz_SocketInterface *,lzz_ClientList*);
	void SetConfig(lzz_SocketInterface *,lzz_ClientList*);
	virtual ~lzz_pushOut();
	void run() override;
private:
	bool *isRun = lzz_nullptr;
	lzz_SocketInterface *sk = lzz_nullptr;
	lzz_ClientList *cl = lzz_nullptr;
	std::list<lzz_Push_Modle*>* p_list = lzz_nullptr;
};

