//#include "lzz_WinService.h"
//#include "lzz_StartServer.h"
//
////定义全局函数变量
//void Init();
//BOOL IsInstalled();
//BOOL Install();
//BOOL Uninstall();
//void LogEvent(LPCTSTR pszFormat, ...);
//void WINAPI ServiceMain();
//void WINAPI ServiceStrl(DWORD dwOpcode);
//TCHAR szServiceName[] = _T("UJ平台推送服务系统");
//BOOL bInstall;
//SERVICE_STATUS_HANDLE hServiceStatus;
//SERVICE_STATUS status;
//DWORD dwThreadID;
//lzz_StartServer *ss = new lzz_StartServer();
//
//int APIENTRY WinMain(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR     lpCmdLine,
//	int       nCmdShow)
//{
//	Init();
//	dwThreadID = ::GetCurrentThreadId();
//
//	SERVICE_TABLE_ENTRY st[] =
//	{
//		{ szServiceName, reinterpret_cast<LPSERVICE_MAIN_FUNCTION>(ServiceMain) },
//		{ lzz_nullptr, lzz_nullptr }
//	};
//	if (strcmp(lpCmdLine, "/install") == 0)
//	{
//		Install();
//	}
//	else if (strcmp(lpCmdLine, "/uninstall") == 0)
//	{
//		Uninstall();
//	}
//	else
//	{
//		if (!::StartServiceCtrlDispatcher(st))
//		{
//			LogEvent(_T("注册服务Main入口出错"));
//		}
//	}
//	return 0;
//}
////*********************************************************
////Functiopn:			Init
////Description:			初始化
////Calls:				main		
////			<author>niying <time>2006-8-10		<version>		<desc>
////*********************************************************
//void Init()
//{
//	hServiceStatus = lzz_nullptr;
//	status.dwServiceType = SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
//	status.dwCurrentState = SERVICE_START_PENDING;
//	status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
//	status.dwWin32ExitCode = 0;
//	status.dwServiceSpecificExitCode = 0;
//	status.dwCheckPoint = 0;
//	status.dwWaitHint = 0;
//}
//
////*********************************************************
////Functiopn:			ServiceMain
////Description:			服务主函数，这在里进行控制对服务控制的注册
////			<author>niying <time>2006-8-10		<version>		<desc>
////*********************************************************
//void WINAPI ServiceMain()
//{
//	// Register the control request handler
//	status.dwCurrentState = SERVICE_START_PENDING;
//	status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
//
//	//注册服务控制
//	hServiceStatus = RegisterServiceCtrlHandler(szServiceName, ServiceStrl);
//	if (hServiceStatus == lzz_nullptr)
//	{
//		LogEvent(_T("Handler not installed"));
//		return;
//	}
//	SetServiceStatus(hServiceStatus, &status);
//
//	status.dwWin32ExitCode = S_OK;
//	status.dwCheckPoint = 0;
//	status.dwWaitHint = 0;
//	status.dwCurrentState = SERVICE_RUNNING;
//	SetServiceStatus(hServiceStatus, &status);
//
//	//模拟服务的运行。应用时将主要任务放于此即可
//	//可在此写上服务需要执行的代码，一般为死循环
//	
//	ss->Start();
////	WinServerRun = true;
////	while (WinServerRun)
////	{
////		lzz_Thread::Sleep(1000);
////	}
//	
////	status.dwCurrentState = SERVICE_STOPPED;
////	SetServiceStatus(hServiceStatus, &status);
////	OutputDebugString(_T("服务已经停止"));
//}
//
////*********************************************************
////Functiopn:			ServiceStrl
////Description:			服务控制主函数，这里实现对服务的控制，
////						当在服务管理器上停止或其它操作时，将会运行此处代码
////Calls:
////Called By:
////Table Accessed:
////Table Updated:
////Input:				dwOpcode：控制服务的状态
////Output:
////Return:
////Others:
////History:
////			<author>niying <time>2006-8-10		<version>		<desc>
////*********************************************************
//void WINAPI ServiceStrl(DWORD dwOpcode)
//{
//	switch (dwOpcode)
//	{
//	case SERVICE_CONTROL_STOP:
//		lzz_Delete(ss);
//		status.dwCurrentState = SERVICE_STOP_PENDING;
//		SetServiceStatus(hServiceStatus, &status);
//		PostThreadMessage(dwThreadID, WM_CLOSE, 0, 0);
//		break;
//	case SERVICE_CONTROL_PAUSE:
//		break;
//	case SERVICE_CONTROL_CONTINUE:
//		break;
//	case SERVICE_CONTROL_INTERROGATE:
//		break;
//	case SERVICE_CONTROL_SHUTDOWN:
//		break;
//	default:
//		LogEvent(_T("未知的服务传回参数"));
//		OutputDebugString(_T("未知的服务传回参数"));
//	}
//}
////*********************************************************
////Functiopn:			IsInstalled
////Description:			判断服务是否已经被安装
////			<author>niying <time>2006-8-10		<version>		<desc>
////*********************************************************
//BOOL IsInstalled()
//{
//	BOOL bResult = FALSE;
//
//	//打开服务控制管理器
//	SC_HANDLE hSCM = ::OpenSCManager(lzz_nullptr, lzz_nullptr, SC_MANAGER_ALL_ACCESS);
//
//	if (hSCM != lzz_nullptr)
//	{
//		//打开服务
//		SC_HANDLE hService = ::OpenService(hSCM, szServiceName, SERVICE_QUERY_CONFIG);
//		if (hService != lzz_nullptr)
//		{
//			bResult = TRUE;
//			::CloseServiceHandle(hService);
//		}
//		::CloseServiceHandle(hSCM);
//	}
//	return bResult;
//}
//
////*********************************************************
////Functiopn:			Install
////Description:			安装服务函数
////			<author>niying <time>2006-8-10		<version>		<desc>
////*********************************************************
//BOOL Install()
//{
//	if (IsInstalled())
//		return TRUE;
//
//	//打开服务控制管理器
//	SC_HANDLE hSCM = ::OpenSCManager(lzz_nullptr, lzz_nullptr, SC_MANAGER_ALL_ACCESS);
//	if (hSCM == lzz_nullptr)
//	{
//		MessageBox(lzz_nullptr, _T("Couldn't open service manager"), szServiceName, MB_OK);
//		return FALSE;
//	}
//
//	// Get the executable file path
//	TCHAR szFilePath[MAX_PATH];
//	::GetModuleFileName(lzz_nullptr, szFilePath, MAX_PATH);
//
//	//创建服务
//	SC_HANDLE hService = ::CreateService(hSCM, szServiceName, szServiceName,
//		SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
//		szFilePath, lzz_nullptr, lzz_nullptr, _T(""), lzz_nullptr, lzz_nullptr);
//
//	if (hService == lzz_nullptr)
//	{
//		::CloseServiceHandle(hSCM);
//		MessageBox(lzz_nullptr, _T("Couldn't create service"), szServiceName, MB_OK);
//		return FALSE;
//	}
//
//	::CloseServiceHandle(hService);
//	::CloseServiceHandle(hSCM);
//	return TRUE;
//}
//
////*********************************************************
////Functiopn:			Uninstall
////Description:			删除服务函数
////			<author>niying <time>2006-8-10		<version>		<desc>
////*********************************************************
//BOOL Uninstall()
//{
//	if (!IsInstalled())
//		return TRUE;
//
//	SC_HANDLE hSCM = ::OpenSCManager(lzz_nullptr, lzz_nullptr, SC_MANAGER_ALL_ACCESS);
//
//	if (hSCM == lzz_nullptr)
//	{
//		MessageBox(lzz_nullptr, _T("Couldn't open service manager"), szServiceName, MB_OK);
//		return FALSE;
//	}
//
//	SC_HANDLE hService = ::OpenService(hSCM, szServiceName, SERVICE_STOP | DELETE);
//
//	if (hService == lzz_nullptr)
//	{
//		::CloseServiceHandle(hSCM);
//		MessageBox(lzz_nullptr, _T("Couldn't open service"), szServiceName, MB_OK);
//		return FALSE;
//	}
//	SERVICE_STATUS status;
//	::ControlService(hService, SERVICE_CONTROL_STOP, &status);
//
//	//删除服务
//	BOOL bDelete = ::DeleteService(hService);
//	::CloseServiceHandle(hService);
//	::CloseServiceHandle(hSCM);
//
//	if (bDelete)
//		return TRUE;
//
//	LogEvent(_T("Service could not be deleted"));
//	return FALSE;
//}
//
////*********************************************************
////Functiopn:			LogEvent
////Description:			记录服务事件
////			<author>niying <time>2006-8-10		<version>		<desc>
////*********************************************************
//void LogEvent(LPCTSTR pFormat, ...)
//{
//	TCHAR    chMsg[256];
//	HANDLE  hEventSource;
//	LPTSTR  lpszStrings[1];
//	va_list pArg;
//
//	va_start(pArg, pFormat);
//	vsprintf_s(chMsg, pFormat, pArg);
//	va_end(pArg);
//
//	lpszStrings[0] = chMsg;
//
//	hEventSource = RegisterEventSource(lzz_nullptr, szServiceName);
//	if (hEventSource != lzz_nullptr)
//	{
//		ReportEvent(hEventSource, EVENTLOG_INFORMATION_TYPE, 0, 0, lzz_nullptr, 1, 0, (LPCTSTR*)&lpszStrings[0], lzz_nullptr);
//		DeregisterEventSource(hEventSource);
//	}
//}