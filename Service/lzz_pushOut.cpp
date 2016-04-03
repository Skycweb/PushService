#include "lzz_pushOut.h"

lzz_pushOut::lzz_pushOut()
{
	//	isRun = lzz_nullptr;
	//	sk = lzz_nullptr;
	//	cl = lzz_nullptr;
	//	p_list = lzz_nullptr;
}

lzz_pushOut::lzz_pushOut(lzz_SocketInterface* s, lzz_ClientList* c)
{
	::lzz_pushOut();
	sk = s;
	cl = c;
}

void lzz_pushOut::SetConfig(lzz_SocketInterface* s, lzz_ClientList* c)
{
	sk = s;
	cl = c;
}

lzz_pushOut::~lzz_pushOut()
{
	if (isRun != lzz_nullptr)
		*isRun = false;
}

void lzz_pushOut::run()
{
	if (p_list == lzz_nullptr)
		p_list = lzz_Push::getList();
	bool runing = true;
	isRun = &runing;
	
	while (runing)
	{
		for (std::list<lzz_Push_Modle*>::iterator m = p_list->begin(); m != p_list->end(); ++m)
		{
			lzz_Push_Modle* modle = *m;
			if(modle->isUser)
			{
					lzz_UserModle* u = cl->GetClient((*modle).UserId);
					if (u != lzz_nullptr)
					{
						sk->UdpSend(&(modle->ActionId), 16, ActionType::PushAction, u->getAddr());
					}
			}
		}
		lzz_Thread::Sleep(10000);
	}
}

