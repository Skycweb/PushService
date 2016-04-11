#include "lzz_PushMsg.h"

void* lzz_PushMsg::y_pVoid = lzz_nullptr;
msgList lzz_PushMsg::y_msgList;
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
}


void lzz_PushMsg::Recv()
{
	lzz_MsgModel* model = lzz_nullptr;
	time_t newTime = time(0);
	for (msgE i = y_msgList.begin(); i != y_msgList.end();i++)
	{
		model = *i;
		if (model->isUse)
			break;
		else if(model->CreateTime - newTime > 1000*60*1)
		{
			lzz_UserModle* uModel = cl->GetClient(model->RecvUserId);
			if (uModel != lzz_nullptr)
			{
				lzz_ServerSocket *udpsk = new lzz_ServerSocket();
				udpsk->UdpSend(&model->Id, 16, ActionType::PushMsg, uModel->getAddr());
				lzz_Delete(udpsk);
			}
		}
	}
	if(model != lzz_nullptr)
	{
		lzz_NewGuid(&model->Id);
		lzz_Memcpy(&model->SendUserId, &request[1], 16);
		lzz_Memcpy(&model->RecvUserId, &request[1+16], 16);
		lzz_Memcpy(&model->Len, &request[1 + 16 + 16], 16);
		lzz_Memcpy(&model->data, &request[1 + 16 + 16+4], model->Len);
		model->CreateTime = time(0);
		lzz_UserModle* uModel = cl->GetClient(model->RecvUserId);
		if(uModel != lzz_nullptr)
		{
			lzz_ServerSocket *udpsk = new lzz_ServerSocket();
			udpsk->UdpSend(&model->Id, 16, ActionType::PushMsg, uModel->getAddr());
			lzz_Delete(udpsk);
		}
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
		if (model->isUse && model->Id == id)
		{
			y_SendMsgModel = model;
			respone = new char[model->Len + 4];
			lzz_Memcpy(respone, &model->Len, 4);
			lzz_Memcpy(&respone[4],model->data, model->Len);
			sk->TcpSend(request, model->Len + 4,this,1);
		}
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
	}
}

void lzz_PushMsg::onLoad()
{
	char type = request[1];
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
