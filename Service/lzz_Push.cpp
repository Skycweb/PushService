#include "lzz_Push.h"
#include "../include/lzz_Thread.h"


std::list<lzz_Push_Modle*>* lzz_Push::getList()
{
	return &_list;
}


std::list<lzz_Push_Modle*> lzz_Push::_list;
volatile bool lzz_Push::read = false;//读取锁
void* lzz_Push::p_lzz_Push_Modle = lzz_nullptr;
int lzz_Push::count = 1000;//最多可以接收多少个推送

lzz_Push::lzz_Push()
{
	if(p_lzz_Push_Modle == lzz_nullptr)
	{
		p_lzz_Push_Modle = malloc(sizeof(lzz_Push_Modle)*count);
		if (p_lzz_Push_Modle != lzz_nullptr) {
			lzz_ZeroMemory(p_lzz_Push_Modle, sizeof(lzz_Push_Modle)*count);
			for (int i = 0; i < count;i++)
			{
				lzz_Push_Modle* p = reinterpret_cast<lzz_Push_Modle*>(static_cast<char*>(p_lzz_Push_Modle) + i*sizeof(lzz_Push_Modle));
				_list.push_back(p);
			}
			lzz_out << "初始化" << count << "个推送成功" << lzz_endline;
		}
	}
}

void lzz_Push::AddModle(GUID userId, char* data,int len)
{
	
 	lzz_Push_Modle mo;
	mo.UserId = userId;
	mo.data = data;
	mo.DataLen = len;
	mo.isUser = true;
    lzz_NewGuid(&(mo.ActionId));
	for (std::list<lzz_Push_Modle*>::iterator i = _list.begin(); i != _list.end(); ++i)
	{
		lzz_Push_Modle* m = *i;
		if (m->isUser == false)
		{
			lzz_Memcpy(m, &mo, sizeof(lzz_Push_Modle));
			break;
		}
	}
	lzz_out << "增加好友通知推送一个" << lzz_endline;
}

void lzz_Push::DeleteModle(GUID ActionId,lzz_SocketInterface* sk)
{
	for (std::list<lzz_Push_Modle*>::iterator m = _list.begin(); m != _list.end(); ++m)
	{
		lzz_Push_Modle* i = *m;
		if(i->ActionId == ActionId)
		{
			int len = i->DataLen;
			if(sk->TcpSend(reinterpret_cast<char*>(&len), 4))
			{
				if(sk->TcpSend(const_cast<char*>(i->data), i->DataLen))
				{
					char d[1] = { 0 };
					if (sk->TcpRecv(d, 1) && d[0] == 1)
					{
						lzz_Deletes(i->data);
						lzz_out << "我删除了内存地址:" << (void*)i->data << lzz_endline;
						lzz_ZeroMemory(i, sizeof(lzz_Push_Modle));
					}
				}
			}
			break;
		}

	}
}

void lzz_Push::lock()
{
	
	while(!read)
	{
		lzz_Thread::Sleep(1);
	}
	if (read)read = false;
}

void lzz_Push::unlock()
{
	read = true;
}

void lzz_Push::onLoad()
{
	GUID guid;
	lzz_Memcpy(&guid, request, sizeof(GUID));
	pushType pt = *reinterpret_cast<pushType*>(&request[16]);
	if (pt == Add)
	{
		
		int len = 0;
		if (sk == lzz_nullptr)return;
		if (!(sk->TcpRecv(&len, 4)))return;
		if (len == 0)return;
		char* d = new char[len];
		lzz_out << "d内存地址:" << static_cast<void*>(d) << lzz_endline;
		if (sk->TcpRecv(d, len))
		{
			AddModle(guid, d, len);
			sk->TcpSend(new char[1]{ 1 }, 1);
		}
	}
	else if (pt == Delete)
	{
		DeleteModle(guid,sk);
	}
}


lzz_Push::~lzz_Push()
{
}

