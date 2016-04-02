#ifndef LZZ_TCPRECV_H
#define LZZ_TCPRECV_H

#include "../include/lzz_Thread.h"
#include "../include/lzz_SocketInterface.h";
#include "lzz_TcpRecvAction.h"

class lzz_TcpRecv : public lzz_Thread
{
    public:
        lzz_TcpRecv(lzz_SocketInterface *s);
        virtual ~lzz_TcpRecv();
        /** @brief (one liner)
          *
          * 开线程运行的函数
          */
        void run() override;
		lzz_TcpRecvAction* getAction();
    private:
		lzz_TcpRecvAction tcpAction[20];
		lzz_SocketInterface *sk;
        bool* isRun = lzz_nullptr;
};

#endif // LZZ_TCPRECV_H
