/*Thông tin*********************************************************************
 *Tên tập tin	: Graphics_Drawing.h
 *Mô tả			: Thư viên các hàm vẽ hình trong console
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 29/09/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

#define PI 3.14159265358979
#define M_PI 3.14159265358979

// Khai báo các hàm
void putpixel(int x, int y, int color);
void arc(int x, int y, int stangle, int endangle,int radius);
void bar(int left, int top, int right, int bottom);
void bar3d(int left, int top, int right, int bottom, int depth, int topflag);
void circle(int x, int y, int radius);
void drawpoly(int numpoints, const int  *polypoints);
void ellipse(int x, int y, int stangle, int endangle, int xradius, int yradius);
void fillellipse( int x, int y, int xradius, int yradius );
void fillpoly(int numpoints, const int  *polypoints);
void floodfill(int x, int y, int border);
void line(int x1, int y1, int x2, int y2);
void linerel(int dx, int dy);
void lineto(int x, int y);
void rectangle(int left, int top, int right, int bottom);
void pieslice(int x, int y, int stangle, int endangle, int radius);	//chưa xong
void sector( int X, int Y, int StAngle, int EndAngle, int XRadius, int YRadius );	//chưa xong

//----------------------------------------------------------------------------//

/*Vẽ điểm ảnh tại (x, y)*******************************************************/
void putpixel(int x, int y, int color)	{
	int i = (y * wndW + x) * 3;
	int num = GetPalColor(color);
	unsigned char *p = (unsigned char *)&num;

	scrbuf[++i] = p[2];
	scrbuf[++i] = p[1];
	scrbuf[++i] = p[0];

	RedrawDosGraphicsWindow();
}/*Kết thúc hàm putpixel*******************************************************/

/*Vẽ cung tròn có tọa độ tâm, góc bắt đầu, góc kết thúc, tọa độ tâm, bán kính**/
void arc(int x, int y, int stangle, int endangle, int radius)	{
	double rad;		
	int x1, y1, x2, y2;
	POINT pnt;

	rad = stangle * PI / 180.0;
	x1 = (int)(x + radius * cos(rad));
	y1 = (int)(y - radius * sin(rad));

	rad = endangle * PI / 180.0;
	x2 = (int)(x + radius * cos(rad));
	y2 = (int)(y - radius * sin(rad));

	int ad = SetArcDirection(memDC, AD_COUNTERCLOCKWISE);
	MoveToEx(memDC, x1, y1, &pnt);
	Arc(memDC, x - radius, y - radius, x + radius, y + radius, x1, y1, x2, y2);	
	MoveToEx(memDC, pnt.x, pnt.y, NULL);
	SetArcDirection(memDC, ad);

	RedrawDosGraphicsWindow();
}/*Kết thúc hàm arc************************************************************/

/*Vẽ hình chữ nhật có tô bên trong bằng mầu tô và kiểu tô hiện tại*************/
void bar(int left, int top, int right, int bottom)	{
	Rectangle(memDC, left, top, right, bottom);
	RedrawDosGraphicsWindow();
}/*Kết thúc hàm bả*************************************************************/

/*Vẽ hình hộp chữ nhật có tô bên trong bằng mầu tô và kiểu tô hiện tại*********/
void bar3d(int left, int top, int right, int bottom, int depth, int topflag)	{
	bar(left, top, right, bottom);
	line(right, bottom - 1, right + depth, bottom - depth);
	line(right + depth, bottom - depth, right + depth, top - depth);
	if (topflag)	{
		line(right + depth, top - depth, right - 1, top + 1);
		line(right + depth, top - depth, left + depth, top - depth);
		line(left + depth, top - depth,left,top);
	}

	RedrawDosGraphicsWindow();
}/*Kết thúc hàm bar3d***********************************************************/

/*Vẽ hình tròn******************************************************************/
void circle(int x, int y, int radius)	{
	SelectObject(memDC,hollowBrush);
	Ellipse(memDC, x - radius, y - radius, x + radius, y + radius);
	SelectObject(memDC, brush);
	RedrawDosGraphicsWindow();
}/*Kết thúc hàm circle**********************************************************/

/*Vẽ đa giác*******************************************************************/
void drawpoly(int numpoints, const int *polypoints)	{
	int n = numpoints, j = 0;
	POINT *pnt = new POINT [n];

	for (int i=0; i<n; ++i)	{
		pnt[i].x = polypoints[++j];
		pnt[i].y = polypoints[++j];
	}

	SelectObject(memDC, hollowBrush);
	Polygon(memDC, pnt, n);
	SelectObject(memDC, brush);

	delete pnt;

	RedrawDosGraphicsWindow();
}/*Kết thúc hàm drawpoly*******************************************************/

/*Vẽ hình elip*****************************************************************/
void ellipse(int x, int y, int stangle, int endangle, int xradius, int yradius)	{
	double rad;
	int x1, y1, x2, y2;
	POINT pnt;

	rad = stangle * PI / 180.0;
	x1 = (int)(x + xradius * cos(rad));
	y1 = (int)(y - yradius * sin(rad));

	rad = endangle * PI / 180.0;
	x2 = (int)(x + xradius * cos(rad));
	y2 = (int)(y - yradius * sin(rad));

	int ad = SetArcDirection(memDC, AD_COUNTERCLOCKWISE);
	MoveToEx(memDC, x1, y1, &pnt);
	Arc(memDC, x - xradius, y - yradius, x + xradius, y + yradius, x1, y1, x2, y2);	
	MoveToEx(memDC, pnt.x, pnt.y, NULL);
	SetArcDirection(memDC, ad);

	RedrawDosGraphicsWindow();
}/*Kết thúc hàm ellipse********************************************************/

/*Vẽ hình ellipse có tô********************************************************/
void fillellipse( int x, int y, int xradius, int yradius )	{
	Ellipse(memDC, x - xradius, y - yradius, x + xradius, y + yradius);
	RedrawDosGraphicsWindow();
}/*Kết thúc hàm fillellipse****************************************************/

/*Vẽ hình đa giác có tô********************************************************/
void fillpoly(int numpoints, const int  *polypoints)	{
	int n = numpoints, j = 0;
	POINT *pnt = new POINT [n];

	for (int i=0; i<n; ++i)	{
		pnt[i].x = polypoints[++j];
		pnt[i].y = polypoints[++j];
	}

	Polygon(memDC, pnt, n);

	delete pnt;

	RedrawDosGraphicsWindow();
}/*Kết thúc hàm fillpoly*******************************************************/

/*Tô miền bị chặn dùng mẫu tô và mầu tô hiện tại*******************************/
void floodfill(int x, int y, int border)	{
	UINT style;

	if (border)
		style = FLOODFILLBORDER;
	else
		style = FLOODFILLSURFACE;

	ExtFloodFill(memDC, x, y, penColor, style);
	RedrawDosGraphicsWindow();
}/*Kết thúc hàm floodfill******************************************************/

/*Vẽ đường thẳng***************************************************************/
void line(int x1, int y1, int x2, int y2)	{
	POINT pnt;

	MoveToEx(memDC,x1,y1,&pnt);
	LineTo(memDC,x2,y2);
	MoveToEx(memDC,pnt.x,pnt.y,NULL);

	RedrawDosGraphicsWindow();
}/*Kết thúc hàm line***********************************************************/

/*Vẽ đường thẳng với khoảng cách tương đối*************************************/
void linerel(int dx, int dy)	{
	POINT pnt;
	GetCurrentPos(&pnt);
	LineTo(memDC,pnt.x + dx,pnt.y + dy);

	RedrawDosGraphicsWindow();
}/*Kết thúc hàm linerel********************************************************/

/*Vẽ đường thảng từ điểm hiện tại tới điểm (x, y)******************************/
void lineto(int x, int y)	{
	LineTo(memDC,x,y);
	RedrawDosGraphicsWindow();
}/*Kết thucs hàm lineto********************************************************/

/*Vẽ hình chữ nhật*************************************************************/
void rectangle(int left, int top, int right, int bottom)	{
	SelectObject(memDC,hollowBrush);
	Rectangle(memDC,left,top,right,bottom);
	SelectObject(memDC,brush);
	RedrawDosGraphicsWindow();
}/*Kết thúc hàm rectangle******************************************************/

/*Vẽ một miếng bánh tròn*******************************************************/
void pieslice(int x, int y, int stangle, int endangle, int radius)	{

}/*Kết thúc hàm pieslice*******************************************************/

/*Vẽ và tô một miếng cung hình elip********************************************/
void sector(int X, int Y, int StAngle, int EndAngle, int XRadius, int YRadius)	{

}/*Kết thúc hàm sector*********************************************************/
