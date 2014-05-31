/*Thông tin*********************************************************************
 *Tên tập tin	: Time.h
 *Mô tả			: Thư viên các hàm với thời gian
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 29/09/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

/*Khai báo các hàm*************************************************************/
void Cmd_time(char *parameter);

/*Command time - Hiển thị ngày giờ hệ thống************************************/
void Cmd_time(char *parameter)	{
	char *Vdays[] = {	"Thu Hai", "Thu Ba", "Thu Tu", "Thu Nam",
						"Thu Sau", "Thu Bay", "Chu Nhat"};
	char *days[] = {	"Monday", "Tuesday", "Wednesday", "Thursday", 
						"Friday", "Saturday", "Sunday"};
	char *Vmont[] = {	"1", "2", "3", "4", "5", "6", "7", "8",
						"9", "10", "11", "12"							};
	char *mont[]= {		"January", "February", "March", "April", 
						"May", "June", "July", "August", 
						"September", "October", "November", "December"	};

	int i, nday, nyear;
	char bufr[40], cmon[10], cday[10], ctime[10];
	
	time_t lt = time(NULL);
	struct tm *ptr = localtime(&lt);

	strcpy_s(bufr, asctime(ptr));
	sscanf(bufr, "%s %s %d %s %d", cday, cmon, &nday, ctime, &nyear);

	ctime[strlen(ctime)-3] = '\0';
	for (i=0; i<7; ++i)
		if (!strncmp(days[i], cday, 3))
			break;
	strcpy_s(cday, Vdays[i]);

	for (i=0; i<12; i++)
		if (!strncmp(mont[i], cmon, 3))
			break;
	strcpy_s(cmon, Vmont[i]);
	
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	SetTextColor(6);

	cout << ctime << ", " << cday << ", ngay " << nday << "/" << cmon << "/" 
		 << nyear << ".\n";

	SetConsoleTextAttribute(hConsole, wAttributes);
}/*Kết thúc hàm Cmd_time*******************************************************/
