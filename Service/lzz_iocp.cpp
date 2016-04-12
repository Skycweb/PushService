///************************************************************************
//
//FileName:iocp.cpp
//Author	:eliteYang
//http://www.cppfans.org
//
//************************************************************************/
//
//#include "lzz_iocp.h"
//
//using namespace std;
//DWORD WINAPI ServerWorkThread(LPVOID CompletionPortID);
//
//void main()
//{
//
//	SOCKET acceptSocket;
//	HANDLE completionPort;
//	LPPER_HANDLE_DATA pHandleData;
//	LPPER_IO_OPERATION_DATA pIoData;
//	DWORD recvBytes;
//	DWORD flags;
//
//	WSADATA wsaData;
//	DWORD ret;
//	if (ret = WSAStartup(0x0202, &wsaData) != 0)
//	{
//		std::cout << "WSAStartup failed. Error:" << ret << std::endl;
//		return;
//	}
//
//	completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, lzz_nullptr, 0, 0);
//	if (completionPort == lzz_nullptr)
//	{
//		std::cout << "CreateIoCompletionPort failed. Error:" << GetLastError() << std::endl;
//		return;
//	}
//
//	SYSTEM_INFO mySysInfo;
//	GetSystemInfo(&mySysInfo);
//
//	// 创建 2 * CPU核数 + 1 个线程
//	DWORD threadID;
//	for (DWORD i = 0; i < (mySysInfo.dwNumberOfProcessors * 2 + 1); ++i)
//	{
//		HANDLE threadHandle;
//		threadHandle = CreateThread(lzz_nullptr, 0, ServerWorkThread, completionPort, 0, &threadID);
//		if (threadHandle == lzz_nullptr)
//		{
//			std::cout << "CreateThread failed. Error:" << GetLastError() << std::endl;
//			return;
//		}
//
//		CloseHandle(threadHandle);
//	}
//
//	// 启动一个监听socket
//	SOCKET listenSocket = WSASocketW(AF_INET, SOCK_STREAM, 0, lzz_nullptr, 0, WSA_FLAG_OVERLAPPED);
//	if (listenSocket == INVALID_SOCKET)
//	{
//		std::cout << " WSASocket( listenSocket ) failed. Error:" << GetLastError() << std::endl;
//		return;
//	}
//
//	SOCKADDR_IN internetAddr;
//	internetAddr.sin_family = AF_INET;
//	internetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//	internetAddr.sin_port = htons(DefaultPort);
//
//	// 绑定监听端口
//	if (bind(listenSocket, (PSOCKADDR)&internetAddr, sizeof(internetAddr)) == SOCKET_ERROR)
//	{
//		std::cout << "Bind failed. Error:" << GetLastError() << std::endl;
//		return;
//	}
//
//	if (listen(listenSocket, 5) == SOCKET_ERROR)
//	{
//		std::cout << "listen failed. Error:" << GetLastError() << std::endl;
//		return;
//	}
//
//	// 开始死循环，处理数据
//	while (1)
//	{
//		acceptSocket = WSAAccept(listenSocket, lzz_nullptr, lzz_nullptr, lzz_nullptr, 0);
//		lzz_out << "Socket:" << acceptSocket << lzz_endline;
//		if (acceptSocket == SOCKET_ERROR)
//		{
//			std::cout << "WSAAccept failed. Error:" << GetLastError() << std::endl;
//			return;
//		}
//		pHandleData = (LPPER_HANDLE_DATA)GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA));
//		if (pHandleData == lzz_nullptr)
//		{
//			std::cout << "GlobalAlloc( HandleData ) failed. Error:" << GetLastError() << std::endl;
//			return;
//		}
//		
//		pHandleData->socket = acceptSocket;
//		if (CreateIoCompletionPort((HANDLE)acceptSocket, completionPort, (ULONG_PTR)pHandleData, 0) == lzz_nullptr)
//		{
//			std::cout << "CreateIoCompletionPort failed. Error:" << GetLastError() << std::endl;
//			return;
//		}
//
//		pIoData = (LPPER_IO_OPERATION_DATA)GlobalAlloc(GPTR, sizeof(PER_IO_OPERATEION_DATA));
//		if (pIoData == lzz_nullptr)
//		{
//			std::cout << "GlobalAlloc( IoData ) failed. Error:" << GetLastError() << std::endl;
//			return;
//		}
//		lzz_NewGuid(&(pIoData->id));
//		ZeroMemory(&(pIoData->overlapped), sizeof(pIoData->overlapped));
//		pIoData->bytesSend = 0;
//		pIoData->bytesRecv = 0;
//		pIoData->databuff.len = DataBuffSize;
//		pIoData->databuff.buf = pIoData->buffer;
//
//		flags = 0;
//		lzz_out << "上下文:" << lzz_GuidToString(pIoData->id) << lzz_endline;
//		if (WSARecv(acceptSocket, &(pIoData->databuff), 1, &recvBytes, &flags, &(pIoData->overlapped), lzz_nullptr) == SOCKET_ERROR)
//		{
//			if (WSAGetLastError() != ERROR_IO_PENDING)
//			{
//				std::cout << "WSARecv() failed. Error:" << GetLastError() << std::endl;
//				//return;
//			}
//			else
//			{
//				std::cout << "WSARecv() io pending" << std::endl;
//				//return;
//			}
//		}
//	}
//}
//
//DWORD WINAPI ServerWorkThread(LPVOID CompletionPortID)
//{
//	GUID id;
//	lzz_NewGuid(&id);
//	HANDLE complationPort = (HANDLE)CompletionPortID;
//	DWORD bytesTransferred;
//	LPPER_HANDLE_DATA pHandleData = lzz_nullptr;
//	LPPER_IO_OPERATION_DATA pIoData = lzz_nullptr;
//	DWORD sendBytes = 0;
//	DWORD recvBytes = 0;
//	DWORD flags;
//	
//	while (1)
//	{
//		
//		if (GetQueuedCompletionStatus(complationPort, &bytesTransferred, (PULONG_PTR)&pHandleData, (LPOVERLAPPED *)&pIoData, INFINITE) == 0)
//		{
//			std::cout << "GetQueuedCompletionStatus failed. Error:" << GetLastError() << std::endl;
//			return 0;
//		}
//		lzz_out << "工作者:" << lzz_GuidToString(id) << lzz_endline;
//		lzz_out << "上下文:" << lzz_GuidToString(pIoData->id) << lzz_endline;
//		// 检查数据是否已经传输完了
//		if (bytesTransferred == 0)
//		{
//			std::cout << " Start closing socket..." << std::endl;
//			if (CloseHandle((HANDLE)pHandleData->socket) == SOCKET_ERROR)
//			{
//				std::cout << "Close socket failed. Error:" << GetLastError() << std::endl;
//				return 0;
//			}
//
//			GlobalFree(pHandleData);
//			GlobalFree(pIoData);
//			continue;
//		}
//
//		// 检查管道里是否有数据
//		if (pIoData->bytesRecv == 0)
//		{
//			pIoData->bytesRecv = bytesTransferred;
//			pIoData->bytesSend = 0;
//		}
//		else
//		{
//			pIoData->bytesSend += bytesTransferred;
//		}
//		for (int i = 0;i < pIoData->bytesRecv;i++)
//			lzz_out << pIoData->databuff.buf[i];
//		lzz_out << lzz_endline;
//
//		// 数据没有发完，继续发送
////		if (pIoData->bytesRecv > pIoData->bytesSend)
////		{
////			ZeroMemory(&(pIoData->overlapped), sizeof(OVERLAPPED));
////			pIoData->databuff.buf = pIoData->buffer + pIoData->bytesSend;
////			pIoData->databuff.len = pIoData->bytesRecv - pIoData->bytesSend;
////
////			// 发送数据出去
////			if (WSASend(pHandleData->socket, &(pIoData->databuff), 1, &sendBytes, 0, &(pIoData->overlapped), lzz_nullptr) == SOCKET_ERROR)
////			{
////				if (WSAGetLastError() != ERROR_IO_PENDING)
////				{
////					std::cout << "WSASend() failed. Error:" << GetLastError() << std::endl;
////					//return 0;
////				}
////				else
////				{
////					std::cout << "WSASend() failed. io pending. Error:" << GetLastError() << std::endl;
////					//return 0;
////				}
////			}
////
////			std::cout << "Send " << pIoData->buffer  << std::endl;
////
////		}
////		else
////		{
////			pIoData->bytesRecv = 0;
////			flags = 0;
////
////			ZeroMemory(&(pIoData->overlapped), sizeof(OVERLAPPED));
////			pIoData->databuff.len = DataBuffSize;
////			pIoData->databuff.buf = pIoData->buffer;
////
////			if (WSARecv(pHandleData->socket, &(pIoData->databuff), 1, &recvBytes, &flags, &(pIoData->overlapped), lzz_nullptr) == SOCKET_ERROR)
////			{
////				if (WSAGetLastError() != ERROR_IO_PENDING)
////				{
////					std::cout << "WSARecv() failed. Error:" << GetLastError() << std::endl;
////					//return 0;
////				}
////				else
////				{
////					std::cout << "WSARecv() io pending" << std::endl;
////					//return 0;
////				}
////			}
////		}
//	}
//}