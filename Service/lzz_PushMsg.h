/*
	����ר��
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
	static lzz_MsgSendNotice* y_Notice;//���ͽ�����Ϣ��֪ͨ
	static int y_msgCount;//��Ϣ����
	lzz_MsgModel* y_SendMsgModel = lzz_nullptr;///������Ϣ��¼model
	char *y_SendMsgBackCode;///����״̬,1��ʾ����,0��ʾʧ��
	lzz_ServerSocket *udpsk = new lzz_ServerSocket();
public:
	static msgList y_waitMsgList;//�ȴ��뷢�͵���Ϣ��
	lzz_PushMsg();
	virtual ~lzz_PushMsg();
	void Recv();//������Ϣ
	void Send();//ת����Ϣ
	void backFunction(int actionType) override;
	void onLoad() override;//���뺯��
	

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