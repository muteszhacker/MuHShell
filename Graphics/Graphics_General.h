/*Thông tin*********************************************************************
 *Tên tập tin	: Graphics_General.h
 *Mô tả			: Thư viên các hàm cơ bản của đồ họa console
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 29/09/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

#define IDM_EXIT 105

// Khai báo các kiểu dữ liệu
enum COLORS	{
	BLACK,  
	BLUE, 
	GREEN, 
	CYAN, 
	RED, 
	MAGENTA, 
	BROWN, 
	LIGHTGRAY, 
	DARKGRAY, 
	LIGHTBLUE, 
	LIGHTGREEN, 
	LIGHTCYAN, 
	LIGHTRED, 
	LIGHTMAGENTA, 
	YELLOW, 
	WHITE
};

enum CGA_COLORS	{
	CGA_LIGHTGREEN		=	1,  
	CGA_LIGHTRED		=	2,
	CGA_YELLOW			=	3,

	CGA_LIGHTCYAN		=	1,  
	CGA_LIGHTMAGENTA	=	2,
	CGA_WHITE			=	3,

	CGA_GREEN			=	1,  
	CGA_RED				=	2,
	CGA_BROWN			=	3,

	CGA_CYAN			=	1,  
	CGA_MAGENTA			=	2,
	CGA_LIGHTGRAY		=	3
};

enum EGA_COLORS	{
	EGA_BLACK			=	0,   
	EGA_BLUE			=	1, 
	EGA_GREEN			=	2, 
	EGA_CYAN			=	3, 
	EGA_RED				=	4, 
	EGA_MAGENTA			=	5, 
	EGA_BROWN			=	20, 
	EGA_LIGHTGRAY		=	7, 
	EGA_DARKGRAY		=	56,   
	EGA_LIGHTBLUE		=	57, 
	EGA_LIGHTGREEN		=	58, 
	EGA_LIGHTCYAN		=	59, 
	EGA_LIGHTRED		=	60, 
	EGA_LIGHTMAGENTA	=	61, 
	EGA_YELLOW			=	62, 
	EGA_WHITE			=	63
};

enum graphics_drivers	{ 
	DETECT, 
	CGA, 
	MCGA, 
	EGA, 
	EGA64, 
	EGAMONO, 
	IBM8514, 
	HERCMONO, 
	ATT400, 
	VGA, 
	PC3270, 
	CURRENT_DRIVER = -1
};

enum graphics_modes { 
	CGAC0		=	0,		/* 320x200 palette 0; 1 page*/
	CGAC1		=	1,		/* 320x200 palette 1; 1 page*/
	CGAC2		=	2,		/* 320x200 palette 2: 1 page*/
	CGAC3		=	463,	/* 320x200 palette 3; 1 page*/
	CGAHI		=	4,		/* 640x200 1 page*/
	MCGAC0		=	0,		/* 320x200 palette 0; 1 page*/
	MCGAC1		=	1,		/* 320x200 palette 1; 1 page*/
	MCGAC2		=	2,		/* 320x200 palette 2; 1 page*/
	MCGAC3		=	3,		/* 320x200 palette 3; 1 page*/
	MCGAMED		=	4,		/* 640x200 1 page*/
	MCGAHI		=	5,		/* 640x480 1 page*/
	EGALO		=	0,		/* 640x200 16 color 4 pages*/
	EGAHI		=	1,		/* 640x350 16 color 2 pages*/
	EGA64LO		=	0,		/* 640x200 16 color 1 page*/
	EGA64HI		=	1,		/* 640x350 4 color  1 page*/
	EGAMONOHI	=	0,		/* 640x350 64K on card, 1 page - 256K on card, 4 pages*/
	HERCMONOHI	=	0,		/* 720x348 2 pages*/
	ATT400C0	=	0,		/* 320x200 palette 0; 1 page*/
	ATT400C1	=	1,		/* 320x200 palette 1; 1 page*/
	ATT400C2	=	2,		/* 320x200 palette 2; 1 page*/
	ATT400C3	=	3,		/* 320x200 palette 3; 1 page*/
	ATT400MED	=	4,		/* 640x200 1 page*/
	ATT400HI	=	5,		/* 640x400 1 page*/
	VGALO		=	0,		/* 640x200 16 color 4 pages*/
	VGAMED		=	1,		/* 640x350 16 color 2 pages*/
	VGAHI		=	2,		/* 640x480 16 color 1 page*/
	PC3270HI	=	0,		/* 720x350 1 page*/
	IBM8514LO	=	0,		/* 640x480 256 colors*/
	IBM8514HI	=	1		/*1024x768 256 colors*/
};

enum graphics_errors	{
	grOk				=	0,
	grNoInitGraph		=	-1,
	grNotDetected		=	-2,
	grFileNotFound		=	-3,
	grInvalidDriver		=	-4,
	grNoLoadMem			=	-5,
	grNoScanMem			=	-6,
	grNoFloodMem		=	-7,
	grFontNotFound		=	-8,
	grNoFontMem			=	-9,
	grInvalidMode		=	-10,
	grError				=	-11,
	grIOerror			=	-12,
	grInvalidFont		=	-13,
	grInvalidFontNum	=	-14,
	grInvalidVersion	=	18
};

enum text_just	{
	LEFT_TEXT		=	0,
	CENTER_TEXT		=	1,
	RIGHT_TEXT		=	2,

	BOTTOM_TEXT		=	0,
	TOP_TEXT		=	2
};

//----------------------------------------------------------------------------//

// Khai báo các biến
int dosBiCount = 4;
unsigned char *dosScrBuf = NULL;
int wndW = 640, wndH = 480;
HDC memDC = NULL;
HWND hWnd = NULL;
HINSTANCE hInst;
char szWindowClass[255];
unsigned char dosPal[16][3];
COLORREF dosPal2[16];
int biCount = 24;
HBITMAP hBmp = NULL;
unsigned char *scrbuf = NULL;
int penW = 1;
COLORREF penColor, brushColor, textColor;
HPEN pen = NULL;
HBRUSH brush = NULL, hollowBrush = NULL;
int texthorzjus, textvertjus;
int dosMemMapping = 0;
int autoRedraw = 0;
unsigned char pattern[8];
BITMAPINFO bi;
HWND hConsoleWnd = NULL;
HANDLE hThread = NULL;
DWORD tid = 0;

//----------------------------------------------------------------------------//

// Khai báo các hàm
void Test();
BOOL InitDosGraphicsWindowInstance(HINSTANCE hInstance);
LRESULT CALLBACK DosGraphicsWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
ATOM RegisterDosGraphicsWindowClass(HINSTANCE hInstance);
void DosBufferToBitmapBuffer();
DWORD WINAPI DosGraphicsWindowThreadProc(LPVOID lpParameter);
void CreateDosGraphicsWindow(HINSTANCE hInstance);
void DestroyDosGraphicsWindow();
void BitmapBufferToDosBuffer();	// Chưa xong
void RedrawDosGraphicsWindow();
void EnableDosMemoryMapping(int flag);
void EnableAutoRedraw(int flag);
void ForceRedraw();
void cleardevice();
void initgraph(int *graphdriver, int *graphmode, const char *pathtodriver);
void detectgraph(int *graphdriver, int *graphmode);
void closegraph();
void *_graphgetmem(unsigned size);
int graphresult();
char *grapherrormsg(int errorcode);
void restorecrtmode();	//chưa xong
void clearviewport();	//chưa xong
void _graphfreemem(void  *ptr, unsigned size);	//chưa xong
void graphdefaults();	//chưa xong

//----------------------------------------------------------------------------//

/*Kiểm tra cửa sổ đồ họa*******************************************************/
void Test()	{
	dosBiCount = 8;
	
	for (int i=0; i<16; ++i)
		for (int j=0; j<20; ++j)
			for (int t=0; t<20; ++t)
				dosScrBuf[i * 20 + j + t * wndW] = i;

	Ellipse(memDC, 100, 100, 300, 250);
}/*Kết thúc hàm Test***********************************************************/

/*Khởi tạo cửa sổ đồ họa*******************************************************/
BOOL InitDosGraphicsWindowInstance(HINSTANCE hInstance)	{
	hInst = hInstance;

	hWnd = CreateWindow(szWindowClass, "DOS Graphics Emulator", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, wndW + 4, wndH + 30, NULL, NULL, hInstance, NULL, );

	if (hWnd == NULL)
		return FALSE;

	int i = 0, n = wndW * wndH;

	dosPal[i][0] = 0;	dosPal[i][1] = 0;	dosPal[i][2] = 0;	++i;
	dosPal[i][0] = 128;	dosPal[i][1] = 0;	dosPal[i][2] = 0;	++i;
	dosPal[i][0] = 0;	dosPal[i][1] = 128;	dosPal[i][2] = 0;	++i;
	dosPal[i][0] = 128;	dosPal[i][1] = 128;	dosPal[i][2] = 0;	++i;
	dosPal[i][0] = 0;	dosPal[i][1] = 0;	dosPal[i][2] = 128;	++i;
	dosPal[i][0] = 128;	dosPal[i][1] = 0;	dosPal[i][2] = 128;	++i;
	dosPal[i][0] = 0;	dosPal[i][1] = 128;	dosPal[i][2] = 128;	++i;
	dosPal[i][0] = 192;	dosPal[i][1] = 192;	dosPal[i][2] = 192;	++i;
	dosPal[i][0] = 128;	dosPal[i][1] = 128;	dosPal[i][2] = 128;	++i;
	dosPal[i][0] = 192;	dosPal[i][1] = 0;	dosPal[i][2] = 0;	++i;
	dosPal[i][0] = 0;	dosPal[i][1] = 255;	dosPal[i][2] = 0;	++i;
	dosPal[i][0] = 255;	dosPal[i][1] = 255;	dosPal[i][2] = 0;	++i;
	dosPal[i][0] = 0;	dosPal[i][1] = 0;	dosPal[i][2] = 255;	++i;
	dosPal[i][0] = 255;	dosPal[i][1] = 0;	dosPal[i][2] = 255;	++i;
	dosPal[i][0] = 0;	dosPal[i][1] = 255;	dosPal[i][2] = 255;	++i;
	dosPal[i][0] = 255;	dosPal[i][1] = 255;	dosPal[i][2] = 255;	++i;

	for (i=0; i<16; ++i)
		dosPal2[i] = RGB(dosPal[i][2], dosPal[i][1], dosPal[i][0]);

	dosBiCount = 4;
	dosScrBuf = new unsigned char [n + 1024];
	ZeroMemory(dosScrBuf, n);

	n = n * biCount / 8;

	ZeroMemory(&bi, sizeof(bi));
	bi.bmiHeader.biSize			=	sizeof(bi);
	bi.bmiHeader.biWidth		=	wndW;
	bi.bmiHeader.biHeight		=	-wndH;
	bi.bmiHeader.biPlanes		=	1;
	bi.bmiHeader.biBitCount		=	biCount;
	bi.bmiHeader.biCompression	=	BI_RGB;
	bi.bmiHeader.biSizeImage	=	n;

	memDC = CreateCompatibleDC(GetDC(hWnd));
	hBmp = CreateDIBSection(memDC, &bi, DIB_RGB_COLORS, (void **)&scrbuf, NULL, 0);
	SelectObject(memDC, hBmp);

	penW = 1;
	penColor = brushColor = textColor = RGB(255, 255, 255);
	pen = CreatePen(PS_SOLID, penW, penColor);
	brush = CreateSolidBrush(brushColor);

	LOGBRUSH lb;	

	lb.lbStyle	=	BS_HOLLOW;
	lb.lbColor	=	DIB_RGB_COLORS;
	lb.lbHatch	=	0;
	hollowBrush	=	CreateBrushIndirect(&lb);

	SelectObject(memDC, pen);
	SelectObject(memDC, brush);
	SetTextColor(memDC, textColor);

	texthorzjus = LEFT_TEXT;
	textvertjus = RIGHT_TEXT;

	dosMemMapping = 0;
	autoRedraw = 1;

	for (i=0; i<8; ++i)
		pattern[i] = 0xFF;

	//Test();

	SetTimer(hWnd, 0, 100, NULL);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return TRUE;
}/*Kết thúc hàm InitDosGraphicsWindowInstance**********************************/

/*Sao chép vùng đệm DOS và vùng đệm hình ảnh***********************************/
void DosBufferToBitmapBuffer()	{
	if (!dosMemMapping)
		return;

	long i, j = 0, n = wndW * wndH;

	switch (dosBiCount)	{
		case 8:
			for (i=0; i<n; i+=3)	{
				unsigned char num = dosScrBuf[i];
				scrbuf[++j] = dosPal[num][0];
				scrbuf[++j] = dosPal[num][1];
				scrbuf[++j] = dosPal[num][2];
			}
			break;

		default:
			n /= 2;
			for (i=0; i<n; ++i)	{
				unsigned char num = dosScrBuf[i];
				unsigned char numh = (unsigned char)(num >> 4);
				unsigned char numl = (unsigned char)(num & 0x0F);

				scrbuf[++j] = dosPal[numl][0];
				scrbuf[++j] = dosPal[numl][1];
				scrbuf[++j] = dosPal[numl][2];

				scrbuf[++j] = dosPal[numh][0];
				scrbuf[++j] = dosPal[numh][1];
				scrbuf[++j] = dosPal[numh][2];
			}
			break;
	}
}/*Kết thúc hàm DosBufferToBitmapBuffer****************************************/

/*Thiết lập cửa sổ*************************************************************/
LRESULT CALLBACK DosGraphicsWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)	{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;

	GetClientRect(hWnd, &rt);

	switch (message)	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 	

			switch (wmId)	{
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;

				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;

		case WM_TIMER:
			if (dosMemMapping)	{
				DosBufferToBitmapBuffer();		
				RedrawWindow(hWnd, &rt, NULL, RDW_INVALIDATE);
			}
			break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			BitBlt(hdc, 0, 0, wndW, wndH, memDC, 0, 0, SRCCOPY);
			EndPaint(hWnd, &ps);
			break;

		case WM_CLOSE:
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			SendMessage(hConsoleWnd, message, wParam, lParam);
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}/*Kết thúc hàm DosGraphicsWndProc*********************************************/

/*Đăng ký lớp cửa sổ***********************************************************/
ATOM RegisterDosGraphicsWindowClass(HINSTANCE hInstance)	{
	lstrcpy(szWindowClass, "DOSGraphicsWindowClass");

	WNDCLASSEX wcex;
	wcex.cbSize			=	sizeof(WNDCLASSEX); 
	wcex.style			=	CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	=	(WNDPROC)DosGraphicsWndProc;
	wcex.cbClsExtra		=	0;
	wcex.cbWndExtra		=	0;
	wcex.hInstance		=	hInstance;
	wcex.hIcon			=	NULL;
	wcex.hCursor		=	NULL;
	wcex.hbrBackground	=	NULL;
	wcex.lpszMenuName	=	NULL;
	wcex.lpszClassName	=	szWindowClass;
	wcex.hIconSm		=	NULL;

	return RegisterClassEx(&wcex);
}/*Kết thúc hàm RegisterDosGraphicsWindowClass*********************************/

/*Tạo luồng cửa sổ*************************************************************/
DWORD WINAPI DosGraphicsWindowThreadProc(LPVOID lpParameter)	{
	HINSTANCE hInstance = (HINSTANCE)lpParameter;

	MSG msg;

	RegisterDosGraphicsWindowClass(hInstance);

	if (!InitDosGraphicsWindowInstance(hInstance))	{
		return FALSE;
	}

	long pa = (long)GetProcAddress(GetModuleHandle("kernel32"), "GetConsoleWindow");

	_asm	{
		call pa
		mov hConsoleWnd, eax
	}

	while (GetMessage(&msg, NULL, 0, 0))	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DeleteObject(memDC);
	DeleteObject(hBmp);
	DeleteObject(pen);

	delete dosScrBuf;

	CloseHandle(hThread);
	hWnd = NULL;

	return msg.wParam;
}/*Kết thúc hàm DosGraphicsWindowThreadProc************************************/

/*Tạo cửa sổ đồ họa************************************************************/
void CreateDosGraphicsWindow(HINSTANCE hInstance)	{
	if (hWnd != NULL)
		return;

	hThread = CreateThread(NULL, 0, DosGraphicsWindowThreadProc, hInstance, 0, &tid);	

	while (hWnd == NULL)
		Sleep(100);
}/*Kết thúc hàm CreateDosGraphicsWindow****************************************/

/*Hủy cửa sổ đồ họa************************************************************/
void DestroyDosGraphicsWindow()	{
	DestroyWindow(hWnd);
	TerminateThread(hThread, 0);
	CloseHandle(hThread);
}/*Kết thúc hàm DestroyDosGraphicsWindow***************************************/

/*Sao chép vùng đệm đồ họa sang vùng đệm DOS***********************************/
void BitmapBufferToDosBuffer()	{
	if (!dosMemMapping)
		return;

	long n = wndW * wndH * biCount / 8;
	long i, j = 0;

	for (i=0; i<n; i+=3)	{

	}
}/*Kết thúc hàm BitmapBufferToDosBuffer****************************************/

/*Vẽ lại cửa sổ đồ họa*********************************************************/
void RedrawDosGraphicsWindow()	{
	if (!autoRedraw)
		return;

	RECT rt;
	GetClientRect(hWnd, &rt);
	RedrawWindow(hWnd, &rt, NULL, RDW_INVALIDATE);
	BitmapBufferToDosBuffer();
}/*Kết thúc hàm RedrawDosGraphicsWindow****************************************/

/*Cho phép đánh địa chỉ bộ nhớ DOS*********************************************/
void EnableDosMemoryMapping(int flag)	{
	dosMemMapping = flag;
}/*Kết thúc hàm EnableDosMemoryMapping*****************************************/

/*Cho phép vẽ lại tự động******************************************************/
void EnableAutoRedraw(int flag)	{
	autoRedraw = flag;
}/*Kết thúc hàm EnableAutoRedraw***********************************************/

/*Cấm vẽ lại*******************************************************************/
void ForceRedraw()	{
	int flag = autoRedraw;
	autoRedraw = 1;
	RedrawDosGraphicsWindow();
	autoRedraw = flag;
}/*Kết thúc hàm ForceRedraw****************************************************/

/*Giải phóng bộ nhớ đệm màn hình***********************************************/
void cleardevice()	{
	int n = wndW * wndH * 3;
	ZeroMemory(scrbuf, n);
	ForceRedraw();
}/*Kết thúc hàm cleardevice****************************************************/

/*Khởi tạo chế độ đồ họa*******************************************************/
void initgraph(int *graphdriver, int   *graphmode, const char  *pathtodriver)	{
	if (dosScrBuf != NULL)
		return;

	CreateDosGraphicsWindow(NULL);
}/*Kết thúc hàm initgraph******************************************************/

/*Dò loại thiết bị màn hình****************************************************/
void detectgraph(int  *graphdriver,int  *graphmode)	{
	(*graphmode) = EGALO;
	(*graphdriver) = EGA;
}/*Kết thúc hàm detectgraph****************************************************/

/*Đóng cửa sổ đồ họa***********************************************************/
void closegraph()	{
	DestroyDosGraphicsWindow();
}/*Kết thúc hàm closegraph*****************************************************/

/*Lấy kích thước bộ nhớ đệm màn hình*******************************************/
void * _graphgetmem(unsigned size)	{
	return dosScrBuf;
}/*Kết thúc hàm _graphgetmem***************************************************/

/*Trả về kết quả gọi chế đồ họa************************************************/
int graphresult()	{
	return grOk;
}/*Kết thúc hàm graphresult****************************************************/

/*Trả về thông báo về lỗi nếu có khi gọi chế độ đồ họa*************************/
char *grapherrormsg(int errorcode)	{
	return "No error";
}/*Kết thúc hàm grapherrormsg**************************************************/

/*Tạm thời trở về chế độ văn bản***********************************************/
void restorecrtmode()	{

}/*Kết thúc hàm restorecrtmode*************************************************/

/*Xóa vùng viewport************************************************************/
void clearviewport()	{

}/*Kết thúc hàm clearviewport**************************************************/

/*Giải phóng bộ nhớ đồ họa*****************************************************/
void _graphfreemem(void  *ptr, unsigned size)	{

}/*Kết thúc hàm _graphfreemem**************************************************/

/**/
void graphdefaults()	{

}/**/
