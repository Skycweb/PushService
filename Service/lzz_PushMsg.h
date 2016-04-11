/*
	聊天专用
*/
#pragma once
#include "../include/base.h"
#include "../include/lzz_Factory.h"
#include <list>
#include "lzz_UserModle.h"


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
	static int y_msgCount;//休息总数
	char y_SendMsgBackCode[1] = { 0 };///返回状态,1表示正常,0表示失败
	lzz_MsgModel* y_SendMsgModel = lzz_nullptr;///发送信息记录model
public:
	lzz_PushMsg();
	void Recv();//接收信息
	void Send();//转发信息

	void backFunction(int actionType) override;
	void onLoad() override;//载入函数
};


