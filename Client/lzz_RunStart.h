#pragma once
#include "../include/base.h"
#include "lzz_ClientSocket.h"
#include "../include/lzz_Thread.h"
#include "../include/lzz_Factory.h"
#include "lzz_push.h"
class lzz_RunStart :
	public lzz_Thread
{
public:
	lzz_RunStart();
	lzz_ClientSocket *getSOCKET();
	void run() override;
	virtual ~lzz_RunStart();
private:
	bool *isRun = nullptr;//运行开关
	lzz_ClientSocket *sk = new lzz_ClientSocket();
};

