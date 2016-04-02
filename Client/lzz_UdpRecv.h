#pragma once
#include "lzz_ClientSocket.h"
#include "../include/lzz_Thread.h"

class lzz_UdpRecv :
	public lzz_Thread
{
public:
	lzz_UdpRecv();
	virtual ~lzz_UdpRecv();

	void run() override;
private:
	lzz_ClientSocket *sk = nullptr;
	
};

