#ifndef LZZ_TCPRECVACTION_H
#define LZZ_TCPRECVACTION_H

#include "../include/lzz_Thread.h"
#include "../include/lzz_Factory.h"


class lzz_TcpRecvAction : public lzz_Thread
{
    public:
		lzz_TcpRecvAction();
        lzz_TcpRecvAction(SOCKET *);
		void SetSKOCKET(SOCKET *);
        virtual ~lzz_TcpRecvAction();

	void Start() override;
	void run() override;
	volatile bool isOk = true;
    private:
        SOCKET _sk = 0;
        int socket_len_int = sizeof(SOCKET);
        lzz_Factory* action = lzz_nullptr;
		bool *isRun = lzz_nullptr;
		bool _Start = true;
};

#endif // LZZ_TCPRECVACTION_H
