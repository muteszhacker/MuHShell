/*Thông tin*********************************************************************
 *Tên tập tin	: Graphics_Set.h
 *Mô tả			: Thư viên các hàm thiết đặt thuộc tính đồ họa
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 29/09/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

#define HORIZ_DIR 0
#define VERT_DIR 1
#define USER_CHAR_SIZE 0

// Khai báo các kiểu dữ liệu
enum putimage_ops	{ 
	COPY_PUT, 
	XOR_PUT, 
	OR_PUT, 
	AND_PUT, 
	NOT_PUT 
};

//----------------------------------------------------------------------------//

// Khai báo các biến
void setbkcolor(int color);
void setcolor(int color);
unsigned setgraphbufsize(unsigned bufsize);
void setgraphmode(int mode);
void setlinestyle(int linestyle, unsigned upattern, int thickness);
void setwritemode(int mode);
void settextjustify(int horiz, int vert);
void setpalette(int colornum, int color);	//chưa xong
void setrgbpalette(int colornum, int red, int green, int blue);	//chưa xong
void settextstyle(int font, int direction, int charsize);	//chưa xong
void setusercharsize(int multx, int divx, int multy, int divy);	//chưa xong
void setviewport(int left, int top, int right, int bottom, int clip);	//chưa xong
void setvisualpage(int page);	//chưa xong
void setactivepage(int page);	//chưa xong
void setallpalette(const struct palettetype  *palette);	//chưa xong
void setaspectratio(int xasp, int yasp);	//chưa xong
void setfillpattern(const char  *upattern, int color);	//chưa xong
void setfillstyle(int pattern, int color);	//chưa xong

//----------------------------------------------------------------------------//

/*Thiết lập màu nền************************************************************/
void setbkcolor(int color)	{
	SetBkColor(memDC,GetPalColor(color));
}/*Kết thúc hàm setbkcolor*****************************************************/

/*Thiết lập màu vẽ hiện tại****************************************************/
void setcolor(int color)	{
	penColor = GetPalColor(color);
	HPEN newpen = CreatePen(PS_SOLID,1,penColor);
	SelectObject(memDC,newpen);
	DeleteObject(pen);
	pen = newpen;
}/*Kết thúc hàm setcolor*******************************************************/

/*Đặt kích thước vùng đệm đồ họa để quét và tô*********************************/
unsigned setgraphbufsize(unsigned bufsize)	{
	return bufsize;
}/*Kết thúc hàm setgraphbufsize************************************************/

/*Đặt chế độ đồ họa và xóa màn hình********************************************/
void setgraphmode(int mode)	{
	cleardevice();
	ShowWindow(hWnd,SW_SHOW);
}/*Kết thúc hàm setgraphmode***************************************************/

/*Đặt kiểu nét vẽ**************************************************************/
void setlinestyle(int linestyle, unsigned upattern, int thickness)	{
	int ps = PS_SOLID;

	switch (linestyle)	{
	case DOTTED_LINE:
		ps = PS_DOT;
		break;

	case CENTER_LINE:
		ps = PS_DASHDOT;
		break;

	case DASHED_LINE:
		ps = PS_DASH;
		break;

	}

	HPEN newpen = CreatePen(ps,thickness,penColor);
	SelectObject(memDC,newpen);
	DeleteObject(pen);
	pen = newpen;
}/*Kết thúc hàm setlinestyle***************************************************/

/*Đặt chế độ căn lề cho hàm outtext và outtextxy*******************************/
void settextjustify(int horiz, int vert)	{
	texthorzjus = horiz;
	textvertjus = vert;
}/*Kết thúc hàm settextjustify*************************************************/

/*Thay đổi chế độ ghi ra màn hình**********************************************/
void setwritemode(int mode)	{
	int ropmode;

	switch (mode)	{
	case XOR_PUT:
		ropmode = R2_XORPEN;
		break;

	case OR_PUT:
		ropmode = R2_MERGEPEN;
		break;

	case AND_PUT:
		ropmode = R2_MASKPEN;
		break;

	case NOT_PUT:
		ropmode = R2_NOT;
		break;

	default:
		ropmode = R2_COPYPEN;
		break;
	}

	SetROP2(memDC,ropmode);
}/*Kết thúc hàm setwritemode***************************************************/

/*Chọn trang đồ họa hoạt động hiện thời****************************************/
void setactivepage(int page)	{

}/*Kết thúc hàm setactivepage**************************************************/

/*Thay đổi toàn bộ bảng mầu****************************************************/
void setallpalette(const struct palettetype *palette)	{

}/*Kết thúc hàm setallpalette**************************************************/

/*Đặt tỉ lệ tương quan ngang dọc***********************************************/
void setaspectratio( int xasp, int yasp )	{

}/*Kết thúc hàm setaspectratio*************************************************/

/*Đặt mẫu tô do người dùng định nghĩa******************************************/
void setfillpattern(const char  *upattern, int color)	{

}/*Kết thúc hàm setfillpattern*************************************************/

/*Đặt mẫu và mầu tô************************************************************/
void setfillstyle(int pattern, int color)	{

}/*Kết thúc hàm setfillstyle***************************************************/

/*THay đổi giá trị bảng mầu****************************************************/
void setpalette(int colornum, int color)	{

}/*Kết thúc hàm setpalette*****************************************************/

/*Thay đổi giá trị bảng mầu cho vỉ mạch IBM8514 và VGA*************************/
void setrgbpalette(int colornum, int red, int green, int blue)	{

}/*Kết thúc hàm setrgbpalette**************************************************/

/*Thiết lập font, hướng, kích thước viết chữ đồ họa****************************/
void settextstyle(int font, int direction, int charsize)	{

}/*Kết thúc hàm settextstyle***************************************************/

/*Thiết lập kích thước, độ rộng, chiều cao các font vector*********************/
void setusercharsize(int multx, int divx, int multy, int divy)	{

}/*Kết thúc hàm setusercharsize************************************************/

/*Thiết lập khung nhìn đồ họa**************************************************/
void setviewport(int left, int top, int right, int bottom, int clip)	{

}/*Kết thúc hàm setviewport****************************************************/

/*Thiết lập số trang nhìn******************************************************/
void setvisualpage(int page)	{

}/*Kết thúc hàm setvisualpage**************************************************/