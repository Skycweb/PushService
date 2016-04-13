#ifndef LZZ_TCPRECV_H
#define LZZ_TCPRECV_H

#include "../include/lzz_Thread.h"
#include "../include/lzz_SocketInterface.h";
#include "lzz_TcpRecvAction.h"

#include "lzz_Push.h"
#include "lzz_PushMsg.h"

class lzz_TcpRecv : public lzz_Thread
{
    public:
        lzz_TcpRecv(lzz_SocketInterface *s,lzz_ClientList *_cl);
        virtual ~lzz_TcpRecv();
        /** @brief (one liner)
          *
          * 开线程运行的函数
          */
        void run() override;
		//工作者函数
		static DWORD WINAPI ServerWorkThread(LPVOID CompletionPortID);
    private:
		lzz_TcpRecvAction tcpAction[20];
		lzz_SocketInterface *sk;
        bool* isRun = lzz_nullptr;
		static lzz_ClientList* cl;
};

#endif // LZZ_TCPRECV_H
