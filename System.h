/*Thông tin*********************************************************************
 *Tên tập tin	: System.h
 *Mô tả			: Thư viên các hàm thay đổi trạng thái hệ thống
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 29/09/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

/*Định nghĩa kiểu dữ liệu mới**************************************************/
typedef enum _SHUTDOWN_ACTION {
	Shut_down = 0,
	Reboot
} SHUTDOWN_ACTION, *PSHUTDOWN_ACTION;

typedef VOID(WINAPI *pAddr)(IN SHUTDOWN_ACTION SdAction);

/*Khai báo các hàm*************************************************************/
BOOL EnablePriv(LPCSTR lpszPriv);
BOOL QuickShutdown(SHUTDOWN_ACTION opt);
void Cmd_system(char *parameter);
void Cmd_exit(char *parameter);
void Cmd_monoff(char *parameter);

/*Tiến hành các hoạt động chuẩn bị cho shut down hoặc reboot máy tính**********/
BOOL EnablePriv(LPCSTR lpszPriv)	{
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tkprivs;
	ZeroMemory(&tkprivs, sizeof(tkprivs));

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return FALSE;

	if (!LookupPrivilegeValue(NULL, lpszPriv, &luid))	{
		CloseHandle(hToken);
		return FALSE;
	}

	tkprivs.PrivilegeCount = 1;
	tkprivs.Privileges[0].Luid = luid;
	tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL);
	CloseHandle(hToken);
	return bRet;
}/*Kết thúc hàm EnablePriv*****************************************************/

/*Shut down hoặc reboot máy tính***********************************************/
BOOL QuickShutdown(SHUTDOWN_ACTION opt)	{
	HINSTANCE ntdll = LoadLibrary("ntdll.dll");
	if(ntdll)	{
		pAddr NtShutdownSystem;
		NtShutdownSystem = (pAddr)GetProcAddress(ntdll, "NtShutdownSystem");

		if(NtShutdownSystem){
			EnablePriv(SE_SHUTDOWN_NAME);
			NtShutdownSystem(opt);
			return TRUE;
		}
	}
	return FALSE;
}/*Kết thúc hàm QuickShutdown**************************************************/

/*Log off, stand by, hibernate, shutdown hay reboot máy tinh*******************/
void Cmd_system(char *parameter)	{
	if (!strcmp(parameter, "log off"))
		ExitWindowsEx(EWX_LOGOFF, 0);

	else if (!strcmp(parameter, "stand by"))
		SetSystemPowerState(TRUE, FALSE);
	
	else if (!strcmp(parameter, "hibernate"))
		SetSystemPowerState(FALSE, FALSE);
	
	else if (!strcmp(parameter, "shut down"))
		QuickShutdown(Shut_down);
	
	else if (!strcmp(parameter, "reboot"))
		QuickShutdown(Reboot);
	
	else	Error(9);
}/*Kết thúc hàm Cmd_system*****************************************************/

/*Command exit - Kết thúc Shell************************************************/
void Cmd_exit(char *parameter)	{
	if (parameter[0] == '\0')
		exit(0);
	else	Error(13);
}/*Kết thúc hàm Cmd_exit*******************************************************/

/*Command monoff - Tắt màn hình************************************************/
void Cmd_monoff(char *parameter)	{
	if (parameter[0] == '\0')
		SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);
	else	Error(13);
}/*Kết thúc hàm Cmd_monoff*****************************************************/
