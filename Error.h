/*Thông tin*********************************************************************
 *Tên tập tin	: Error.h
 *Mô tả			: Thư viện thông tin lỗi
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 29/09/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

/*Khai báo các hàm*************************************************************/
void SetTextColor_2(HANDLE hConsole, WORD wAttributes, int color);
void Error(unsigned int i);

/*Thiết lập màu chữ************************************************************/
void SetTextColor_2(HANDLE hConsole, WORD wAttributes, int color)	{
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsole, wAttributes);
}/*Kết thúc hàm SetTextColor***************************************************/

/*In ra thông tin lỗi**********************************************************/
void Error(unsigned int i)	{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;

	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;

	SetTextColor_2(hConsole, wAttributes, 6);

	switch (i)	{
		case 0	:	cout << "Loi: Tap tin khong ton tai.\n";
					break;
		case 1	:	cout << "Loi: Khong phai tap tin batch.\n";
					break;
		case 2	:	cout << "Loi: Duong dan khong dung hoac khong duoc phap "
						 << "truy cap.\n";
					break;
		case 3	:	cout <<	"Loi: Loi tim kiem.\n";
					break;
		case 4	:	cout << "Loi: Shell khong the quan ly them tien trinh.\n";
					break;
		case 5	:	cout << "Loi: Tap tin khong ton tai hoac "
						 << "khong phai tap tin thuc thi.\n";
					break;
		case 6	:	cout << "Loi: Khong co lenh nay.\n";
					break;
		case 7	:	cout << "Loi: Khong co mau nay.\n";
					break;
		case 8	:	cout << "Loi: Tien trinh dang khong hoat dong.\n";
					break;
		case 9	:	cout << "Loi: Khong co che do nay.\n";
					break;
		case 10	:	cout << "Loi: Khong the xoa vi tap tin nay la tap tin chi "
						<< "doc.\n";
					break;
		case 11	:	cout << "Loi: Khong the sao chep vi o thu muc dich da "
						 << "ton tai tap tin nay va tap tin nay la tap tin chi"
						 << "doc.\n";
					break;
		case 12	:	cout << "Loi: Khong the di chuyen vi o thu muc dich da "
						<< "ton tai tap tin nay va tap tin nay la tap tin chi"
						<< "doc.\n";
					break;
		case 13	:	cout << "Loi: Sai cau truc lenh.\n";
					break;
		case 14	:	cout << "Loi: Trung ten voi tap tin/thu muc da ton tai.\n";
					break;
		case 15	:	cout << "Loi: Khong co thuoc tinh nay.\n";
					break;
		case 16	:	cout << "Loi: Khong co co chu nay.\n";
					break;
		case 17	:	cout << "Loi: Khong the truy cap o cung.\n";
					break;
		case 18	:	cout << "Loi: Tap tin dang duoc su dung hoac khong the "
						 << "truy cap.\n";
					break;
	}

	SetConsoleTextAttribute(hConsole, wAttributes);
}/*Kết thúc hàm Error**********************************************************/
