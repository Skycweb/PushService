#include "lzz_TcpRecv.h"
#include "lzz_TcpRecvAction.h"

lzz_TcpRecv::lzz_TcpRecv(lzz_SocketInterface* s)

lzz_ClientList* lzz_TcpRecv::cl = lzz_nullptr;


lzz_TcpRecv::lzz_TcpRecv(lzz_SocketInterface* s, lzz_ClientList* _cl)
{
	sk = s;

	if (cl != lzz_nullptr)
		cl = _cl;
}

lzz_TcpRecv::~lzz_TcpRecv()
{
	*isRun = false;
	if(isRun != lzz_nullptr)
		*isRun = false;
}

void lzz_TcpRecv::run()
{
//	lzz_out << "进入等待接入" << lzz_endline;
	//	lzz_out << "进入等待接入" << lzz_endline;
	bool _Run = true;
	isRun = &_Run;
	SOCKET _socket;
	SOCKADDR address;
	lzz_ZeroMemory(&_socket,sizeof(SOCKET));
	HANDLE completionPort;
	completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, lzz_nullptr, 0, 0);
	if (completionPort == lzz_nullptr)
	{
		std::cout << "CreateIoCompletionPort failed. Error:" << GetLastError() << std::endl;
		return;
	}
	SYSTEM_INFO mySysInfo;
	GetSystemInfo(&mySysInfo);

	// 创建 2 * CPU核数 + 1 个线程
	DWORD threadID;
	for (DWORD i = 0; i < (mySysInfo.dwNumberOfProcessors * 2 + 1); ++i)
	{
		HANDLE threadHandle;
		threadHandle = CreateThread(lzz_nullptr, 0, ServerWorkThread, completionPort, 0, &threadID);
		if (threadHandle == lzz_nullptr)
		{
			std::cout << "CreateThread failed. Error:" << GetLastError() << std::endl;
			return;
		}

		CloseHandle(threadHandle);
	}
	while (_Run)
	{
		sk->Accept(&_socket, &address);
		if (_socket == INVALID_SOCKET)
			break;
//		lzz_out << "收到一个连接接入" << lzz_endline;
		lzz_TcpRecvAction* a = getAction();
		if (a != lzz_nullptr) {
			a->SetSKOCKET(&_socket);
			a->Start();
		lzz_LPPER_HANDLE_DATA socket = new lzz_PER_HANDLE_DATA;
		socket->socket = _socket;
		lzz_LPPER_IO_OPERATION_DATA pIoData = new lzz_PER_IO_OPERATEION_DATA;

		lzz_out << "收到一个连接接入" << lzz_endline;
		if (CreateIoCompletionPort((HANDLE)_socket, completionPort, (ULONG_PTR)socket, 0) == lzz_nullptr)
		{
			std::cout << "CreateIoCompletionPort failed. Error:" << GetLastError() << std::endl;
			return;
		}
		if (WSARecv(_socket, &(pIoData->databuff), 1, &(pIoData->bytesRecv), 0, &(pIoData->overlapped), lzz_nullptr) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != ERROR_IO_PENDING)
			{
				std::cout << "WSARecv() failed. Error:" << GetLastError() << std::endl;
				//return;
			}
			else
			{
				std::cout << "WSARecv() io pending" << std::endl;
				//return;
			}
		}
	}
	isRun = lzz_nullptr;
}

lzz_TcpRecvAction* lzz_TcpRecv::getAction()
DWORD lzz_TcpRecv::ServerWorkThread(LPVOID CompletionPortID)
{
	int len = 0;
	lzz_ARRAY_LEN(tcpAction, len);
	for (int i = 0; i < len;i++)

	GUID id;
	lzz_NewGuid(&id);
	HANDLE complationPort = (HANDLE)CompletionPortID;
	DWORD bytesTransferred;
	lzz_LPPER_HANDLE_DATA pHandleData = lzz_nullptr;
	lzz_LPPER_IO_OPERATION_DATA pIoData = lzz_nullptr;
	DWORD sendBytes = 0;
	DWORD recvBytes = 0;
	DWORD flags;

	while (1)
	{
		if (tcpAction[i].isOk)
		if (GetQueuedCompletionStatus(complationPort, &bytesTransferred, (PULONG_PTR)&pHandleData, (LPOVERLAPPED *)&pIoData, INFINITE) == 0)

		{
			tcpAction[i].isOk = false;
			return &(tcpAction[i]);
			std::cout << "GetQueuedCompletionStatus failed. Error:" << GetLastError() << std::endl;
			return 0;
		}
		if (i == len-1)
			i = 0;
		lzz_out << "工作者:" << lzz_GuidToString(id) << lzz_endline;
		// 检查数据是否已经传输完了
		if (bytesTransferred == 0)
		{
			std::cout << " Start closing socket..." << std::endl;
			if (CloseHandle((HANDLE)pHandleData->socket) == SOCKET_ERROR)
			{
				std::cout << "Close socket failed. Error:" << GetLastError() << std::endl;
				return 0;
			}
			lzz_Delete(pHandleData);
			lzz_Delete(pIoData);
			continue;
		}

		// 检查管道里是否有数据
		if (pIoData->bytesRecv == 0)
		{
			pIoData->bytesRecv = bytesTransferred;
			pIoData->bytesSend = 0;
		}
		else
		{
			pIoData->bytesSend += bytesTransferred;
		}
		if(pIoData->factory != lzz_nullptr)
		{
			pIoData->factory->backFunction(pIoData->ActionType);
			continue;
		}
		int DataLen = *((int*)&pIoData->databuff.buf[4]);
		ActionType type = *(ActionType*)pIoData->databuff.buf;
		char* p_str = lzz_nullptr;
		p_str = new char[DataLen];
		lzz_Memcpy(p_str, &pIoData->databuff.buf[8], DataLen);
		lzz_SocketInterface * _interface_sk = new lzz_ServerSocket(&pHandleData->socket,pHandleData,pIoData);
		if (_interface_sk == lzz_nullptr) continue;
		lzz_Factory* f = lzz_nullptr;
		switch (type)
		{
		case _ActionType::PushAction: //添加推送
			f = new lzz_Push();
			break;
		case ActionType::PushMsg:
			f = new lzz_PushMsg();
			break;
		default: break;
		}
		if (f != lzz_nullptr)
		{
			f->init(_interface_sk, cl, p_str, nullptr);
			f->onLoad();
			f->BindView();
		}
		pIoData->factory = f;
		// 数据没有发完，继续发送
		//		if (pIoData->bytesRecv > pIoData->bytesSend)
		//		{
		//			ZeroMemory(&(pIoData->overlapped), sizeof(OVERLAPPED));
		//			pIoData->databuff.buf = pIoData->buffer + pIoData->bytesSend;
		//			pIoData->databuff.len = pIoData->bytesRecv - pIoData->bytesSend;
		//
		//			// 发送数据出去
		//			if (WSASend(pHandleData->socket, &(pIoData->databuff), 1, &sendBytes, 0, &(pIoData->overlapped), lzz_nullptr) == SOCKET_ERROR)
		//			{
		//				if (WSAGetLastError() != ERROR_IO_PENDING)
		//				{
		//					std::cout << "WSASend() failed. Error:" << GetLastError() << std::endl;
		//					//return 0;
		//				}
		//				else
		//				{
		//					std::cout << "WSASend() failed. io pending. Error:" << GetLastError() << std::endl;
		//					//return 0;
		//				}
		//			}
		//
		//			std::cout << "Send " << pIoData->buffer  << std::endl;
		//
		//		}
		//		else
		//		{
		//			pIoData->bytesRecv = 0;
		//			flags = 0;
		//
		//			ZeroMemory(&(pIoData->overlapped), sizeof(OVERLAPPED));
		//			pIoData->databuff.len = DataBuffSize;
		//			pIoData->databuff.buf = pIoData->buffer;
		//
		//			if (WSARecv(pHandleData->socket, &(pIoData->databuff), 1, &recvBytes, &flags, &(pIoData->overlapped), lzz_nullptr) == SOCKET_ERROR)
		//			{
		//				if (WSAGetLastError() != ERROR_IO_PENDING)
		//				{
		//					std::cout << "WSARecv() failed. Error:" << GetLastError() << std::endl;
		//					//return 0;
		//				}
		//				else
		//				{
		//					std::cout << "WSARecv() io pending" << std::endl;
		//					//return 0;
		//				}
		//			}
		//		}
	}
	return lzz_nullptr;
}
