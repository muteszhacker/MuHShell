/*Thông tin*********************************************************************
 *Tên tập tin	: Graphics_Others.h
 *Mô tả			: Thư viên các hàm khác của đồ họa console
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 29/09/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

/*Khai báo các hàm*************************************************************/
void moverel(int dx, int dy);
void moveto(int x, int y);
void outtext(const char  *textstring);
void outtextxy(int x, int y, const char  *textstring);
int textheight(const char  *textstring);
int textwidth(const char  *textstring);
unsigned imagesize(int left, int top, int right, int bottom);
void getimage(int left, int top, int right, int bottom, void  *bitmap);	//chưa xong
void putimage(int left, int top, const void  *bitmap, int op);	//chưa xong

//--------------------------------------------------------------------------//

/*Dịch chuyển vị trí hiện tại tới vị trí mới theo tọa độ tương đối*************/
void moverel(int dx, int dy)	{
	POINT pnt;
	GetCurrentPos(&pnt);
	MoveToEx(memDC,pnt.x + dx,pnt.y + dy,NULL);
}/*Kết túc hàm moverel*********************************************************/

/*Dịch chuyển vị trí hiện tại tới điểm (x, y)**********************************/
void moveto(int x, int y)	{
	MoveToEx(memDC,x,y,NULL);
}/*Kết thúc hàm moveto*********************************************************/

/*Viết ra dòng văn bản tại vị trí hiện tại*************************************/
void outtext(const char *s)	{
	POINT pnt;
	GetCurrentPos(&pnt);
	outtextxy(pnt.x,pnt.y,s);
}/*Kết thúc hàm outtext********************************************************/

/*Viết ra dòng văn bản tại vị trí (x, y)***************************************/
void outtextxy(int x, int y, const char *s)	{
	int mode = SetBkMode(memDC,TRANSPARENT);
	int x2 = x, y2 = y;
	SIZE size;

	GetTextSize(s,&size);

	switch (texthorzjus)	{
	case RIGHT_TEXT:
		x2 -= size.cx;
		break;

	case CENTER_TEXT:
		x2 -= (size.cx / 2);
		break;
	}

	switch (textvertjus)	{
	case LEFT_TEXT:
		y2 -= size.cy;
		break;

	case CENTER_TEXT:
		y2 -= (size.cy / 2);
		break;
	}

	TextOut(memDC,x2,y2,s,lstrlen(s));
	SetBkMode(memDC,mode);
	RedrawDosGraphicsWindow();
}/*Kết thúc hàm outtextxy******************************************************/

/*Trả lại sô byte cần để cất một vùng chữ nhật trên màn hình đồ họa************/
unsigned imagesize(int left, int top, int right, int bottom)	{
	return ((right - left) * (bottom - top) / (8 / dosBiCount));
}/*Kết thúc hàm imagesize******************************************************/

/*Trả lại độ cao của xâu chữ tính theo pixel***********************************/
int textheight(const char  *s)	{
	SIZE size;
	GetTextSize(s,&size);
	return size.cy;
}/*Kết thúc hàm textheight*****************************************************/

/*Trả lại độ rộng của xâu chữ tính theo pixel**********************************/
int textwidth(const char  *s)	{
	SIZE size;
	GetTextSize(s,&size);
	return size.cx;
}/*Kết thúc hàm textwidth******************************************************/

/*Cất ảnh bit vào bộ nhớ đệm***************************************************/
void getimage(int left, int top, int right, int bottom, void  *bitmap)	{

}/*Kết thúc hàm getimage*******************************************************/

/*Nạp hình ảnh bit vào màn hình************************************************/
void putimage(int left, int top, const void  *bitmap, int op)	{

}/*Kết thúc hàm putimage*******************************************************/
