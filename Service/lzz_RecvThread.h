#pragma once
#include "../include/lzz_Thread.h"
#include "../include/lzz_SocketInterface.h"
#include "../include/lzz_ClientList.h"

class lzz_RecvThread: public lzz_Thread
{
private:
	lzz_SocketInterface *sk;//全局SOCKET
	lzz_ClientList *cl;//全局访问者
	bool *isRun;//是否运行
public:
	lzz_RecvThread(lzz_SocketInterface*,lzz_ClientList*);
	~lzz_RecvThread() override;
	void run() override;

	void Close() override;
};
