#include "lzz_Push.h"



lzz_Push::lzz_Push()
{

}

void lzz_Push::onLoad()
{
	lzz_out << "我收到一个推送包" << lzz_endline;
	static_cast<lzz_ClientSocket*>(TcpSk)->TcpConnect(lzz_ServiceTcpPort,lzz_ServiceTcpIp);
	pushType pt = _pushType::Delete;
	char d[16 + 4];
	lzz_Memcpy(d, request, 16);
	lzz_Memcpy(&(d[16]), &pt, 4);
	TcpSk->TcpSend(d,20, ActionType::PushAction);
	int _len = 0;
	if (TcpSk->TcpRecv(reinterpret_cast<char*>(&_len), 4)) {
		lzz_out << "内容长度：" << _len << lzz_endline;
		if (_len == 0)
		{
			lzz_out << "我收到一个没有内容的推送包" << lzz_endline;
			return;
		}
		char *data = new char[_len + 1];
		lzz_ZeroMemory(data, _len + 1);
		if (TcpSk->TcpRecv(data, _len))
		{
			lzz_out << data << lzz_endline;
		}
	}
	TcpSk->TcpSend(new char[1]{ 1 }, 1);
}

lzz_Push::~lzz_Push()
{
	lzz_Delete(TcpSk);
}
