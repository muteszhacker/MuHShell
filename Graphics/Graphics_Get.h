/*Thông tin*********************************************************************
 *Tên tập tin	: Graphics_Get.h
 *Mô tả			: Thư viên các hàm lấy thuộc tính đồ họa
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 29/09/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

#define MAXCOLORS 15

// Khai báo các kiểu dữ liệu
enum line_styles	{
	SOLID_LINE		=	0,
	DOTTED_LINE		=	1,
	CENTER_LINE		=	2,
	DASHED_LINE		=	3,
	USERBIT_LINE	=	4  
};

enum line_widths	{
	NORM_WIDTH	=	1,
	THICK_WIDTH	=	3,
};

enum font_names	{
	DEFAULT_FONT		=	0, 
	TRIPLEX_FONT		=	1, 
	SMALL_FONT			=	2, 
	SANS_SERIF_FONT		=	3, 
	GOTHIC_FONT			=	4, 
	SCRIPT_FONT			=	5, 
	SIMPLEX_FONT		=	6, 
	TRIPLEX_SCR_FONT	=	7, 
	COMPLEX_FONT		=	8, 
	EUROPEAN_FONT		=	9, 
	BOLD_FONT			=	10 
};

enum fill_patterns	{     
	EMPTY_FILL, 
	SOLID_FILL, 
	LINE_FILL, 
	LTSLASH_FILL, 
	SLASH_FILL,   
	BKSLASH_FILL, 
	LTBKSLASH_FILL, 
	HATCH_FILL, 
	XHATCH_FILL, 
	INTERLEAVE_FILL, 
	WIDE_DOT_FILL, 
	CLOSE_DOT_FILL, 
	USER_FILL 
};

struct pointtype	{
	int x, y;
};

struct arccoordstype	{
	int x, y;
	int xstart, ystart, xend, yend;
};

struct palettetype	{
	unsigned char size;
	signed char colors[MAXCOLORS + 1];
};

struct fillsettingstype	{
	int pattern;
	int color;
};

struct linesettingstype	{
	int linestyle;
	unsigned upattern;
	int thickness;
};

struct textsettingstype	{
	int font;
	int direction;
	int charsize;
	int horiz;
	int vert;
};

struct viewporttype	{
	int left, top, right, bottom;
	int clip;
};

//----------------------------------------------------------------------------//

// Khai báo các biến
arccoordstype arccoord;
palettetype defpaltype;

//----------------------------------------------------------------------------//

// Khai báo các hàm
int GetDosPalColor(COLORREF cr);
COLORREF GetPalColor(int cl);
void GetCurrentPos(POINT *p);
int getx();
int gety();
void GetTextSize(const char *s, SIZE *psize);
void getarccoords(struct arccoordstype  *arccoords);
void getaspectratio(int  *xasp, int  *yasp);
int getbkcolor();
int getcolor();
struct palettetype *getdefaultpalette();
char * getdrivername();
void getfillpattern(char  *pattern);
void getfillsettings(struct fillsettingstype  *fillinfo);
int getgraphmode();
void getlinesettings(struct linesettingstype  *lineinfo);
int getmaxcolor();
int getmaxmode();
int getmaxx();
int getmaxy();
char * getmodename( int mode_number );
void getmoderange(int graphdriver, int  *lomode, int  *himode);
unsigned getpixel(int x, int y);
void getpalette(struct palettetype  *palette);
int getpalettesize();
void gettextsettings(struct textsettingstype  *texttypeinfo);	//chưa xong
void getviewsettings(struct viewporttype  *viewport);	//chưa xong

//----------------------------------------------------------------------------//

/*Lấy bảng màu DOS*************************************************************/
int GetDosPalColor(COLORREF cr)	{
	for (int i=0; i<16; ++i)
		if (dosPal2[i] == cr)
			return i;

	return 0;
}/*Kết thúc hàm GetDosPalColor*************************************************/

/*Trả về bảng màu hiện tại*****************************************************/
COLORREF GetPalColor(int cl)	{
	return dosPal2[cl];
}/*Kết thúc hàm GetPalColor****************************************************/

/*Lấy vị trí hiện tại của con trỏ đồ họa***************************************/
void GetCurrentPos(POINT *p)	{
	MoveToEx(memDC, 0, 0, p);
	MoveToEx(memDC, p->x, p->y, NULL);
}/*Kết thúc hàm GetCurrentPos**************************************************/

/*Lấy hoành độ hiện tại********************************************************/
int getx()	{
	POINT pnt;
	GetCurrentPos(&pnt);
	return pnt.x;
}/*Kết thúc hàm getx***********************************************************/

/*Lấy tung độ hiện tại*********************************************************/
int gety()	{
	POINT pnt;
	GetCurrentPos(&pnt);
	return pnt.y;
}/*Kết thúc hàm gety***********************************************************/

/*Lấy cỡ chữ*******************************************************************/
void GetTextSize(const char *s, SIZE *psize)	{
	GetTextExtentPoint32(memDC,s,lstrlen(s),psize);
}/*Kết thúc hàm GetTextSize****************************************************/

/*Nhận lại tọa độ để vẽ cung***************************************************/
void getarccoords(struct arccoordstype  *p)	{
	memmove(p, &arccoord, sizeof(arccoordstype));
}/*Kết thúc hàm getarccoords***************************************************/

/*Đặt lại tỉ lệ tương quan ngang dọc*******************************************/
void getaspectratio(int *xasp, int *yasp)	{
	(*xasp) = (*yasp) = 10000;
}/*Kết thúc hàm getaspectratio*************************************************/

/*Lấy màu nền hiện tại*********************************************************/
int getbkcolor()	{
	COLORREF cr = GetBkColor(memDC);
	return GetDosPalColor(cr);
}/*Kết thúc hàm getbkcolor*****************************************************/

/*Lấy màu vẽ hiện tại**********************************************************/
int getcolor()	{
	return GetDosPalColor(penColor);
}/*Kết thúc hàm getcolor*******************************************************/

/*Lấy bảng màu ngầm định*******************************************************/
struct palettetype * getdefaultpalette()	{
	return (&defpaltype);
}/**/

/*Lấy tên vỉ mạch đồ họa*******************************************************/
char *getdrivername()	{
	return "EGAVGA";
}/*Kết thúc hàm getdrivername**************************************************/

/*Lấy mẫu tô*******************************************************************/
void getfillpattern(char *p)	{
	for (int i=0; i<8; ++i)
		p[i] = (char)pattern[i];
}/*Kết thúc hàm getfillpattern*************************************************/

/*Lấy mẫu tô được thiết lập mới nhất*******************************************/
void getfillsettings(struct fillsettingstype  *fillinfo)	{
	fillinfo->color = GetDosPalColor(brushColor);
	fillinfo->pattern = SOLID_FILL;
}/*Kết thúc hàm getfillsettings************************************************/

/*Lấy chế độ đồ họa hiện tại***************************************************/
int getgraphmode()	{
	return EGALO;
}/*Kết thúc hàm getgraphmode***************************************************/

/*Lấy kiểu vẽ, nét vẽ, độ dày nét vẽ*******************************************/
void getlinesettings(struct linesettingstype  *lineinfo)	{
	lineinfo -> linestyle = SOLID_LINE;
	lineinfo -> thickness = 1;
	lineinfo -> upattern = 255;
}/*Kết hàm getlinesettings*****************************************************/

/*Lấy số màu tối đa của chế độ đồ họa hiện thời********************************/
int getmaxcolor()	{
	return 16;
}/*Kết thúc hàm getmaxcolor****************************************************/

/*Lấy số chế độ hiển thị cao nhất**********************************************/
int getmaxmode()	{
	return 5;
}/*Kết thúc hàm getmaxmode*****************************************************/

/*Lấy độ phân giải ngang*******************************************************/
int getmaxx()	{
	return wndW;
}/*Kết thúc hàm getmaxx********************************************************/

/*Lấy độ phân giải dọc*********************************************************/
int getmaxy()	{
	return wndH;
}/*Kết thúc hàm getmaxy********************************************************/

/*Lấy tên chế độ đò họa**s*****************************************************/
char *getmodename(int mode_number)	{
	return "EGALO";
}/*Kết thúc hàm getmodename****************************************************/

/*Lấy chế độ nhỏ nhất và lớn nhất của vỉ mạch**********************************/
void getmoderange(int graphdriver, int  *lomode, int  *himode)	{
	(*lomode) = 1;
	(*himode) = 5;
}/*Kết thúc hàm getmoderange***************************************************/

/*Lấy màu ở vị trí (x, y)******************************************************/
unsigned getpixel(int x, int y)	{
	return 0;
}/*Kết thúc hàm getpixel*******************************************************/

/*Lấy giá trị bảng màu*********************************************************/
void getpalette(struct palettetype *pal)	{
	pal->size = 16;
	for (int i=0;i<16;++i)
		pal->colors[i] = i;
}/*Kết thúc hàm getpalette*****************************************************/

/*Lấy kích thước bẳng màu******************************************************/
int getpalettesize()	{
	return 16;
}/*Kết thúc hàm getpalettesize*************************************************/

/*Lấy kiểu chữ, hướng viết, kích thước chữ*************************************/
void gettextsettings(struct textsettingstype  *texttypeinfo)	{

}/*Kết thúc hàm gettextsettings************************************************/

/*Lấy thông tin  về khung nhìn và các tham số**********************************/
void getviewsettings(struct viewporttype  *viewport)	{

}/*Kết thúc hàm getviewsettings************************************************/
