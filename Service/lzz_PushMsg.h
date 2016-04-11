/*
	����ר��
*/
#pragma once
#include "../include/base.h"
#include "../include/lzz_Factory.h"
#include <list>
#include "lzz_UserModle.h"


struct lzz_MsgModel
{
	GUID Id;//��ϢID
	GUID SendUserId;//������ID
	GUID RecvUserId;//������ID
	int Len;//��Ϣ�峤��
	char data[1024];//��Ϣ��
	volatile bool isUse;//��ǰ��ַ�ɲ�����
	time_t CreateTime;//������ʱ��
};
typedef std::list<lzz_MsgModel*> msgList;
typedef std::list<lzz_MsgModel*>::iterator msgE;
class lzz_PushMsg : public lzz_Factory
{
private:
	static void* y_pVoid;//�ڴ��ָ��
	static msgList y_msgList;//��Ϣ���б�
	static int y_msgCount;//��Ϣ����
	char y_SendMsgBackCode[1] = { 0 };///����״̬,1��ʾ����,0��ʾʧ��
	lzz_MsgModel* y_SendMsgModel = lzz_nullptr;///������Ϣ��¼model
public:
	lzz_PushMsg();
	void Recv();//������Ϣ
	void Send();//ת����Ϣ

	void backFunction(int actionType) override;
	void onLoad() override;//���뺯��
};


