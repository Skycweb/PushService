#include "lzz_PushMsg.h"

void* lzz_PushMsg::y_pVoid = lzz_nullptr;
msgList lzz_PushMsg::y_msgList;
lzz_MsgSendNotice* lzz_PushMsg::y_Notice = lzz_nullptr;
msgList lzz_PushMsg::y_waitMsgList;
int lzz_PushMsg::y_msgCount = 100000;

lzz_PushMsg::lzz_PushMsg()
{
	if(y_pVoid == lzz_nullptr)
	{
		y_pVoid = malloc(sizeof(lzz_MsgModel)*y_msgCount);
		if(y_pVoid != lzz_nullptr)
		{
				for (int i = 0; i < y_msgCount; i++)
				{
					lzz_MsgModel* p = reinterpret_cast<lzz_MsgModel*>(static_cast<char*>(y_pVoid) + i*sizeof(lzz_MsgModel));
					y_msgList.push_back(p);
				}
		}
	}
	y_SendMsgBackCode = new char[1];
	udpsk->UdpBind(5648);
}
lzz_PushMsg::~lzz_PushMsg()
{
	lzz_Delete(y_SendMsgBackCode);
	lzz_Delete(udpsk);
}


void lzz_PushMsg::Recv()
{
	lzz_MsgModel* model = lzz_nullptr;
	time_t newTime = time(0);
	for (msgE i = y_msgList.begin(); i != y_msgList.end(); i++)
	{
		model = *i;
		if (model->isUse)
		{
			model->isUse = false;
			break;
		}
		if (model->CreateTime - newTime > 1000 * 60 * 1)
		{
			lzz_UserModle* uModel = cl->GetClient(model->RecvUserId);
			if (uModel != lzz_nullptr)
			{
				y_waitMsgList.push_front(model);
			}
		}
	}
	if (model != lzz_nullptr)
	{
		lzz_NewGuid(&model->Id);
		lzz_Memcpy(&model->SendUserId, &request[1], 16);
		lzz_Memcpy(&model->RecvUserId, &request[1 + 16], 16);
		lzz_Memcpy(&model->Len, &request[1 + 16 + 16], 16);
		lzz_Memcpy(&model->data, &request[1 + 16 + 16 + 4], model->Len);
		model->CreateTime = time(0);
		lzz_UserModle* uModel = cl->GetClient(model->RecvUserId);
		if (uModel != lzz_nullptr)
		{
			char dt[20];
			lzz_Memcpy(dt, &model->Len, 4);
			lzz_Memcpy(&dt[4], &model->Id, 16);
			udpsk->UdpSend(dt, 20, ActionType::PushMsg, uModel->getAddr());
		}
		sk->TcpSend(new char{ 1 }, 1, this, 3);
	}
}
 
void lzz_PushMsg::Send()
{
	GUID id = *(GUID*)&request[1];
	y_SendMsgModel = lzz_nullptr;
	lzz_MsgModel* model = lzz_nullptr;
	for (msgE i = y_msgList.begin(); i != y_msgList.end(); i++)
	{
		model = *i;
		if (!model->isUse && model->Id == id)
		{
			y_SendMsgModel = model;
			respone = new char[model->Len];
			lzz_Memcpy(respone, model->data, model->Len);
			sk->TcpSend(respone, model->Len, this, 1);
			break;
		}
	}
}
void lzz_PushMsg::init(lzz_SocketInterface* _sk, lzz_ClientList* _cl, char* reqest, SOCKADDR* address)
{
	lzz_Factory::init(_sk, _cl, reqest, address);
	if (y_Notice == lzz_nullptr)
	{
		y_Notice = new lzz_MsgSendNotice(_cl);
		y_Notice->Start();
	}
}

void lzz_PushMsg::backFunction(int actionType)
{
	switch(actionType)
	{
	case 1:
		if(sk->y_pIo->bytesSend != sk->y_pIo->databuff.len)
		{
			sk->TcpSend(&(sk->y_pIo->databuff.buf[sk->y_pIo->bytesSend]), sk->y_pIo->databuff.len - sk->y_pIo->bytesSend,this,1);
		}
		else
		{
			lzz_Delete(respone);
			sk->TcpRecv(y_SendMsgBackCode, 1, this, 2);
		}
		break;
	case 2:
		if(y_SendMsgBackCode[0] == 1)
		{
			lzz_ZeroMemory(y_SendMsgModel, sizeof(lzz_MsgModel));
			y_SendMsgModel->isUse = true;
		}
		break;
	case 3:
		//lzz_Delete(sk->y_pIo->factory);
		break;
	}
}

void lzz_PushMsg::onLoad()
{
	char type = request[0];
	switch(type)
	{
		case 1:
			Recv();
			break;
		case 2:
			Send();
			break;
	}
}

lzz_MsgSendNotice::lzz_MsgSendNotice(lzz_ClientList* _cl)
{
	cl = _cl;
}
lzz_MsgSendNotice::~lzz_MsgSendNotice()
{
	
}


void lzz_MsgSendNotice::run()
{
	bool run = true;
	lzz_ServerSocket *udpsk = new lzz_ServerSocket();
	udpsk->UdpBind(8025);
	char data[20];
	while(run)
	{
		if (lzz_PushMsg::y_waitMsgList.empty())continue;
		lzz_MsgModel* model = lzz_PushMsg::y_waitMsgList.front();
		if (!model->isUse) {
			lzz_UserModle* uModel = cl->GetClient(model->RecvUserId);
			if (uModel != lzz_nullptr)
			{
				lzz_Memcpy(data, &model->Len, 4);
				lzz_Memcpy(&data[4], &model->Id, 16);
				udpsk->UdpSend(data, 20, ActionType::PushMsg, uModel->getAddr());
			}
		}else
		{
			lzz_PushMsg::y_waitMsgList.remove(model);
		}
	}
	lzz_Delete(udpsk);
}
