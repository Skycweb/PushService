#pragma once
#include "../include/lzz_Factory.h"
#include "../Client/lzz_ClientSocket.h"

class lzz_Push :
	public lzz_Factory
{
public:
	lzz_Push();

	void onLoad() override;
	virtual ~lzz_Push();
private:
	lzz_SocketInterface *TcpSk = new lzz_ClientSocket();
};

