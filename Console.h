/*Thông tin*********************************************************************
 *Tên tập tin	: Console.h
 *Mô tả			: Thư viên các hàm với console
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 29/09/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

#define MAX_COLOR 16									 //Số mầu chữ/nền tối đa

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 115
#define KEY_RIGHT 116
#define KEY_ENTER 13
#define KEY_ESCAPE 27
#define KEY_BACKSPACE 8
#define KEY_DELETE 127

/*Định nghĩa kiểu dữ liệu mới**************************************************/
typedef struct	{
	char name[13];
} COLOR;

/*Khai báo biến toàn cục*******************************************************/
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
COLOR color_list[MAX_COLOR] = {	
	"black", "blue", "green", "aqua", "red", "purple", "yellow", "white", 
	"gray", "light blue", "light green", "light aqua", "light red", 
	"light purple", "light yellow", "bright white"	
};

/*Khai báo các hàm*************************************************************/
void NoCursorType();

void SetBKColor(int color);
void SetTextColor(int color);
void SetScreenBufferSize(int width, int height);
void SetWindowCo(int left, int top, int right, int bottom);

void Gotoxy(int x, int y);
int WhereX();
int WhereY();

void PutChar(char ch, int left, int top);
char* GetPassword(size_t length, int left, int top);
void PrintMenuItem(	char* items[], char* format, int left, int top, int index, 
																bool select);
void PrintInput(char *format, int value);
int Menu(char* items[], int nItem, int left, int top);
int Is_color(char *parameter);

void Cmd_clear(char *parameter);
void Cmd_color(char *parameter);
void Cmd_textsize(char *parameter);

/*Không hiện con trỏ màn hình**************************************************/
void NoCursorType()	{
	CONSOLE_CURSOR_INFO Info;

	Info.bVisible = FALSE;
	Info.dwSize = 20;
	
	SetConsoleCursorInfo (hConsole, &Info);
}/*Kết thúc hàm NoCursorType***************************************************/

/*Thiết lập màu nền************************************************************/
void SetBKColor(int color)	{
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsole, wAttributes);
}/*Kết thúc hàm SetBKColor*****************************************************/

/*Thiết lập màu chữ************************************************************/
void SetTextColor(int color)	{
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsole, wAttributes);
}/*Kết thúc hàm SetTextColor***************************************************/

/*Thiết lập kích thước cửa sổ**************************************************/
void SetScreenBufferSize(int width, int height)	{
	COORD coord = {width, height};
	SetConsoleScreenBufferSize(hConsole, coord);

	SMALL_RECT conWin = {0, 0, width, height};
	SetConsoleWindowInfo(hConsole, true, &conWin);
}/*Kết thúc hàm SetScreenSize**************************************************/

/*Đặt tọa độ 4 góc của cửa sổ console******************************************/
void SetWindowCo(int left, int top, int right, int bottom)	{
	MoveWindow(GetConsoleWindow(), left, top, right, bottom, true);
}/*Kết thúc hàm SetWindowPosition**********************************************/

/*Di chuyển con trỏ màn hình đến tọa độ (x, y)*********************************/
void Gotoxy(int x, int y)	{
	COORD pos = {x, y};
	SetConsoleCursorPosition(hConsole , pos);
}/*Kết thúc hàm Gotoxy*********************************************************/

/*Hoành độ của con trỏ màn hình************************************************/
int WhereX()	{
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.X;
}/*Kết thúc hàm WhereX*********************************************************/

/*Tung độ của con trỏ màn hình*************************************************/
int WhereY()	{
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.Y;
}/*Kết thúc hàm WhereX*********************************************************/

/*In ký tự ch vào tọa độ (left, top)*******************************************/
void PutChar(char ch, int left, int top)	{
	if (top == -1)	{
		GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
		left = screen_buffer_info.dwCursorPosition.X;
		top = screen_buffer_info.dwCursorPosition.Y;
	}

	COORD coord = {left, top};
	DWORD cCharsWritten;
	FillConsoleOutputCharacterA(hConsole, ch, 1, coord, &cCharsWritten);
}/*Kết thúc hàm PutChar********************************************************/

/*Nhập mật khẩu với độ dài tối đa length ở tọa độ (left, top)******************/
char* GetPassword(size_t length, int left, int top)	{
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;

	Gotoxy(left, top);

	char* pass = new char[length + 1];
	char ch = 0;
	memset(pass, 0, length + 1);
	fflush(stdin);
	while (ch != KEY_ENTER)
	{
		fflush(stdin);
		ch = _getch();

		if (ch <= 0)
			_getch();							//Loại bỏ kí các tự điều khiển
		else if (ch > 31 && ch < 127)	{		//Các kí tự ASCII in được
			if (strlen(pass) < length)	{		//Nếu chuỗi chưa đầy
				cout << "*";
				pass[strlen(pass)] = ch;
			}
		}
		else if (ch == KEY_BACKSPACE)			//Xóa một kí tự
			if (pass[0])	{					//Nếu chuỗi khác rỗng
				pass[strlen(pass) - 1] = 0;		//Xoá kí tự cuối cùng của chuỗi
				Gotoxy(WhereX() - 1, WhereY());
				PutChar(' ', WhereX() - 1, WhereY());
			}
	}

	fflush(stdin);
	SetConsoleTextAttribute(hConsole, wAttributes);

	return pass;
}/*Kết thúc hàm GetPassword****************************************************/

/*In menu**********************************************************************/
void PrintMenuItem(	char* items[], char* format, int left, int top, int index, 
	bool select)	{
		int wAttributes = screen_buffer_info.wAttributes;

		if (select)
			SetBKColor(3);

		Gotoxy(left, top + index + 1);
		printf(format, items[index]);

		if (select)
			SetConsoleTextAttribute(hConsole, (WORD)wAttributes);
}/*Kết thúc hàm PrintMenuItem**************************************************/

/*In một số trong vùng nhập dữ liệu********************************************/
void PrintInput(char *format, int value)	{
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;

	SetBKColor(3);
	printf(format, value);
	
	SetConsoleTextAttribute(hConsole, wAttributes);
}/*Kết thúc hàm Print_Input****************************************************/

/*Tương tác với các item trong menu********************************************/
int Menu(char* items[], int nItem, int left, int top)	{
	if (left == -1)
		left = WhereX();
	if (top == -1)
		top = WhereY();

	size_t maxLen = 0;
	for (int i = 0; i <= nItem; ++i)
		if (strlen(items[i]) > maxLen)
			maxLen = strlen(items[i]);

	char format[12] = "%-";
	char sLen[10];
	_itoa_s(maxLen, sLen, 10);
	strcat_s(format, sLen);

	for (int i = 2; i < 12 ; ++i)
		if (format[i] == '\0')	{
			format[i] = 's';
			format[i+1] = '\0';
			break;
		}

	Gotoxy(left, top);
	cout << items[0] << "\n";

	PrintMenuItem(items, format, left, top, 1, true);
	for (int i = 2; i <= nItem; ++i)
		PrintMenuItem(items, format, left, top, i, false);

	Gotoxy(left, top + nItem + 3);
	cout << "Select: ";
	int xSelect = WhereX(), ySelect = WhereY();

	int selectItem = 1, lastSelectItem = nItem, PressClock = 0;
	while (1)	{
		if (selectItem != lastSelectItem)	{
			PrintMenuItem(items, format, left, top, lastSelectItem, false);
			PrintMenuItem(items, format, left, top, selectItem, true);
			lastSelectItem = selectItem;
			Gotoxy(xSelect, ySelect);
			PrintInput("%2d",selectItem);
			Gotoxy(xSelect + 1, ySelect);
		}

		char key = (char)_getch();
		if (key < 0)	{
			key = _getch();
			if (key == KEY_UP)	{
				--selectItem;
				if (!selectItem)
					selectItem = nItem;
			}
			else if (key == KEY_DOWN)	{
				++selectItem;
			if (selectItem > nItem)
				selectItem = 1;
			}
		}
		else if (key == KEY_ESCAPE || key == KEY_BACKSPACE)
			selectItem = nItem;
		else if (key == KEY_ENTER)
			return selectItem;
		else	{
			if (isdigit(key))	{
				int num = key - '0', ck = clock();

				if (nItem > 9 && ck - PressClock < 300)	{
					selectItem *= 10;
					selectItem += num;
					if (selectItem > nItem)
						selectItem = num;
				}
				else	selectItem = num;

				PressClock = ck;

				if (selectItem < 1 || selectItem > nItem)
						selectItem = lastSelectItem;
			}
		}
	}

	return 0;
}

/*Kiểm tra parameter có phải là tên màu không**********************************/
int Is_color(char *parameter)	{
	for (int i=0; i<MAX_COLOR; ++i)
		if (!strcmp(color_list[i].name, parameter))
			return i;
	return -1;
}/*Kết thúc hàm Is_color*******************************************************/

/*Xóa màn hình console*********************************************************/
void Cmd_clear(char *parameter)	{
	if (parameter[0] != '\0')	{
		Error(13);
		return;
	}

	COORD Home = {0, 0};
	DWORD dummy;
	DWORD size = screen_buffer_info.dwSize.X * screen_buffer_info.dwSize.Y;

	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	FillConsoleOutputCharacter(hConsole, ' ', size, Home, &dummy);
	SetConsoleCursorPosition(hConsole, Home);
	FillConsoleOutputAttribute(hConsole, 7, size, Home, &dummy);
}/*Kết thúc hàm Cmd_clear******************************************************/

/*Thay đổi màu chữ, màu nền chữ************************************************/
void Cmd_color(char *parameter)	{
	char object[11];
	char color[10];
	object[0] = color[0] = '\0';

	if (!Trim(parameter, object, color, 0))
		return;

	int i = Is_color(color);
	if (i==-1)	{
		Error(7);
		return;
	}
	else if (!strcmp(object, "background"))
		SetBKColor(i);
	else if (!strcmp(object, "text"))
		SetTextColor(i);
}/*Kết thúc hàm Cmd_color******************************************************/

/*Thay đổi cỡ chữ**************************************************************/
void Cmd_textsize(char *parameter)	{
	typedef BOOL (WINAPI *PSetConsoleFont)(HANDLE, DWORD);
	typedef DWORD (WINAPI *PGetNumberOfConsoleFonts)();

	PSetConsoleFont pSetConsoleFont = NULL;
	PGetNumberOfConsoleFonts pGetNumberOfConsoleFonts  = NULL;

	HMODULE hKernel = GetModuleHandleA("kernel32");
	pSetConsoleFont = (PSetConsoleFont)GetProcAddress(hKernel, 
		"SetConsoleFont");
	pGetNumberOfConsoleFonts = (PGetNumberOfConsoleFonts)
		GetProcAddress(hKernel, "GetNumberOfConsoleFonts");

	if (!strcmp(parameter, "small"))
		pSetConsoleFont(hConsole, 1);
	else if (!strcmp(parameter, "medium"))	{
		pSetConsoleFont(hConsole, 6);
		SetWindowCo(62, 40, 1230, 660);
	}
	else if (!strcmp(parameter, "big"))	{
		pSetConsoleFont(hConsole, 8);
		SetWindowCo(62, 40, 1223, 660);
	}
	else	Error(16);
}/*Kết thúc hàm Cmd_textsize***************************************************/
