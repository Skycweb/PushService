/*
	聊天专用
*/

#ifndef _lzz_PushMsg_
#define  _lzz_PushMsg_


#include "../include/base.h"
#include "../include/lzz_Factory.h"
#include "lzz_UserModle.h"
#include "lzz_ServerSocket.h"
#include "../include/lzz_Thread.h"

class lzz_MsgSendNotice;
struct lzz_MsgModel
{
	GUID Id;//信息ID
	GUID SendUserId;//发送人ID
	GUID RecvUserId;//接收人ID
	int Len;//信息体长度
	char data[1024];//信息体
	volatile bool isUse;//当前地址可不可用
	time_t CreateTime;//创建的时间
};
typedef std::list<lzz_MsgModel*> msgList;
typedef std::list<lzz_MsgModel*>::iterator msgE;
class lzz_PushMsg : public lzz_Factory
{
private:
	static void* y_pVoid;//内存池指针
	static msgList y_msgList;//休息体列表
	static lzz_MsgSendNotice* y_Notice;//发送接收信息的通知
	static int y_msgCount;//休息总数
	lzz_MsgModel* y_SendMsgModel = lzz_nullptr;///发送信息记录model
	char *y_SendMsgBackCode;///返回状态,1表示正常,0表示失败
	lzz_ServerSocket *udpsk = new lzz_ServerSocket();
public:
	static msgList y_waitMsgList;//等代码发送的消息体
	lzz_PushMsg();
	virtual ~lzz_PushMsg();
	void Recv();//接收信息
	void Send();//转发信息
	void backFunction(int actionType) override;
	void onLoad() override;//载入函数
	

	void init(lzz_SocketInterface* _sk, lzz_ClientList* _cl, char* reqest, SOCKADDR* address) override;
};

class lzz_MsgSendNotice:public lzz_Thread
{
private:
	lzz_SocketInterface *sk = new lzz_ServerSocket();
	lzz_ClientList *cl = lzz_nullptr;
public:
	lzz_MsgSendNotice(lzz_ClientList* _cl);

	virtual ~lzz_MsgSendNotice();

	void run() override;

};
#endif