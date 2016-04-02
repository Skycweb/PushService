#pragma once
#include "lzz_ClientSocket.h"
#include "../include/lzz_Thread.h"

class lzz_HeartbeatThread:public lzz_Thread
{
private:
	GUID guid_id;//前端为一ID
	bool *is_close_b_ = nullptr;//是否关闭
	lzz_ClientSocket *sk = nullptr;//连接
public:
	lzz_HeartbeatThread(lzz_ClientSocket *s);
	virtual ~lzz_HeartbeatThread();

	void Close() override;
	void run() override;
};

