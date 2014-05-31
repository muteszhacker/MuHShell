/*Thông tin*********************************************************************
 *Tên tập tin	: Process.h
 *Mô tả			: Thư viên các hàm với tiến trình
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 29/09/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

#define MAX_PRC 8				//Số tiến trình tối đa Shell có thể quản lý

/*Định nghĩa kiểu dữ liệu mới**************************************************/
typedef struct	{
	char name[MAX_FILE_NAME_LEN];	//Tên tiến trình
	PROCESS_INFORMATION pi;			//Thông tin của tiến trình
	char location[MAX_PATH_LEN];	//Đường dẫn file thực thi
	bool running;					//Đánh dấu tiến trình đã được thực thi chưa
} PROCESS;

/*Khai báo biến toàn cục*******************************************************/
PROCESS prc[MAX_PRC];		//Mảng lưu thông tin các tiến trình Shell quản lý
int prc_count = 0;			//Số tiến trình Shell đang quản lý

/*Khai báo các hàm*************************************************************/
void Update_list();

void Cmd_exit(char *parameter);
void Cmd_kill(char *parameter);
void Cmd_list(char *parameter);
void Cmd_process(char *parameter);

/*Cập nhật trạng thái hoạt động của các tiến trình con đã được Shell gọi*******/
void Update_list()	{
	for (int i = 0; i < MAX_PRC; ++i)	{
		DWORD lpExitCode = 0;
		GetExitCodeProcess(prc[i].pi.hProcess, &lpExitCode);

		if (lpExitCode != STILL_ACTIVE && prc[i].running)	{
			prc[i].running = false;
			--prc_count;
		}
	}
}/*Kết thúc hàm Update_list****************************************************/

/*Command exec - Thực thi 1 tiến trình*****************************************/
void Cmd_exec(char *parameter)	{
	Update_list();

	/*Không cho thực hiện thêm tiến trình khi đã đạt số lượng tối đa*/
	int i;
	for (i = 0; i < MAX_PRC; ++i)
		if (!prc[i].running)	break;
	if (i == MAX_PRC)	{
		Error(4);
		return;
	}

	STARTUPINFO  si;
	PROCESS_INFORMATION    pi;

	/*Khởi tạo giá trị của mọi ô nhớ của khối nhớ dành cho tiến trình là 0*/
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	/*Khởi tạo tiến trình*/
	BOOL ok = CreateProcess(parameter, NULL, NULL, NULL, FALSE, 
		CREATE_NEW_CONSOLE,	NULL, NULL, &si, &pi);

	/*Đưa thông tin tiến trình vào CTDL quản lý tiến trình của Shell*/
	if (!ok)		Error(5);
	else	{
		strcpy_s(prc[i].name, parameter);
		prc[i].pi = pi;
		if (strlen(_getcwd(NULL, 0)) > MAX_PATH_LEN)	{
			strncpy_s(prc[i].location, _getcwd(NULL, 0), MAX_PATH_LEN-3);
			prc[i].location[MAX_PATH_LEN-4]='.';
			prc[i].location[MAX_PATH_LEN-3]='.';
			prc[i].location[MAX_PATH_LEN-2]='.';
			prc[i].location[MAX_PATH_LEN-1]='\0';
		}
		else	strcpy_s(prc[i].location, _getcwd(NULL, 0));
		prc[i].running = true;
		++prc_count;
	}
}/*Kết thúc hàm Cmd_exec*******************************************************/

/*Command kill - Kết thúc 1 tiến trình*****************************************/
void Cmd_kill(char *parameter)	{
	Update_list();

	/*Khi parameter rỗng*/
	if (parameter[0] == '\0')	{
		if (prc_count > 0)
			for (int i = 0; i < MAX_PRC; ++i)
				if (prc[i].running)	{
					TerminateProcess(prc[i].pi.hProcess, 0);
					CloseHandle(prc[i].pi.hProcess);
					CloseHandle(prc[i].pi.hThread);
					prc[i].running = false;
					--prc_count;
				}
		return;
	}

	bool found = false;
	int i;
	for (i = 0; i < MAX_PRC; ++i)
		if (!strcmp(prc[i].name, parameter))	{
			found = true;

			if (!prc[i].running)
				Error(8);
			else	{
				TerminateProcess(prc[i].pi.hProcess,  0);
				CloseHandle(prc[i].pi.hProcess);
				CloseHandle(prc[i].pi.hThread);
			}

			prc[i].running = false;
			--prc_count;
			break;
		}

	/*Báo lỗi khi không tìm thấy tiến trình*/
	if (i==MAX_PRC)		Error(5);
}/*Kết thúc hàm Cmd_kill*******************************************************/

/*Command list - Liệt kê các tiến trình được gọi bởi Shell*********************/
void Cmd_list(char *parameter)	{
	Update_list();
	
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	SetTextColor(6);

	if (prc_count == 0)
		cout << "Shell khong quan ly tien trinh nao.\n";
	else	{
		cout << "Co " << prc_count << " tien trinh Shell dang quan ly.\n";

		SetTextColor(2);
		printf("%-5s  ", "ID");
		SetTextColor(4);
		printf("%-40s ", "Tien trinh");
		SetTextColor(5);
		printf("%-32s\n\n", "Duong dan");

		for (int i = 0; i < MAX_PRC; ++i)
			if (prc[i].running)	{
				SetTextColor(2);
				printf("%-5d  ", i);
				SetTextColor(4);
				printf("%-40s ", prc[i].name);
				SetTextColor(5);
				printf("%s\n", prc[i].location);
			}
	}

	SetConsoleTextAttribute(hConsole, wAttributes);
}/*Kết thúc hàm Cmd_list*******************************************************/

/*Command process - Thực hiện các thao tác với tiến trình**********************/
void Cmd_process(char *parameter)	{
	char prc_name[MAX_FILE_NAME_LEN];
	char action[10];
	prc_name[0] = action[0] = '\0';

	if (parameter[0] == '-' && parameter[1] == '>')	{
		int i = 2;
		while (parameter[i] == ' ')
			++i;

		int j = 0;
		while (parameter[i] != '\0')
			action[j++] = parameter[i++];
		action[j] = '\0';

		if (!strcmp(action, "list"))
			Cmd_list("\0");
		return;
	}

	if (!Trim(parameter, prc_name, action, 0))			
		return;

	if (!strcmp(action, "create"))
		Cmd_exec(prc_name);
	else if (!strcmp(action, "kill"))
		Cmd_kill(prc_name);
}/*Kết thúc hàm Cmd_process****************************************************/
