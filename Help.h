/*Thông tin*********************************************************************
 *Tên tập tin	: Help.h
 *Mô tả			: Thư viện các hàm trợ giúp thông tin về Shell
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 29/09/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

/*Khai báo các hàm*************************************************************/
void Help_about();
void Help_attribute();
void Help_batch();
void Help_chdir();
void Help_clear();
void Help_color();
void Help_copy();
void Help_decrypt();
void Help_delete();
void Help_encrypt();
void Help_enum();
void Help_exit();
void Help_graph();
void Help_help();
void Help_hexview();
void Help_MBR();
void Help_monoff();
void Help_move();
void Help_process();
void Help_rename();
void Help_system();
void Help_textsize();
void Help_textview();
void Help_time();

void Cmd_about(char *parameter);
void Cmd_help(char *parameter);

/*Trợ giúp lệnh about**********************************************************/
void Help_about()	{
	SetTextColor(2);
	printf("%-60s", "about");
	SetTextColor(4);
	printf("%-88s\n", "Gioi thieu ve chuong trinh.");
}/*Kết thúc hàm Help_about*****************************************************/

/*Trợ giúp lệnh attribute******************************************************/
void Help_attribute()	{
	SetTextColor(2);
	printf("%-60s", "attribute <Ten tap tin> -> <Thuoc tinh>");
	SetTextColor(4);
	printf("%-88s", "Them (+) hoac bo (-) thuoc tinh tap tin voi <Thuoc tinh> la: +/-archive, +/-hidden,");
	printf("%-60s%-88s\n", "\0", "normal, +/-read only.");
}/*Kết thúc hàm Help_attribute*************************************************/

/*Trợ giúp lệnh batch**********************************************************/
void Help_batch()	{
	SetTextColor(2);
	printf("%-60s", "batch <Ten tap tin>");
	SetTextColor(4);
	printf("%-88s\n", "Thuc thi cac lenh trong tap tin *.mbt.");
}/*Kết thúc hàm Help_batch*****************************************************/

/*Trợ giúp lệnh chdir**********************************************************/
void Help_chdir()	{
	SetTextColor(2);
	printf("%-60s", "chdir <Duong dan>");
	SetTextColor(4);
	printf("%-88s", "Thay doi thu muc hien hanh, neu chuyen den thu muc con thi chi can nhap ten thu muc,");
	printf("%-60s%-88s\n", "\0", "neu muon tro ve thu muc cha thi go <Duong dan> la ..");
}/*Kết thúc hàm Help_chdir*****************************************************/

/*Trợ giúp lệnh clear**********************************************************/
void Help_clear()	{
	SetTextColor(2);
	printf("%-60s", "clear");
	SetTextColor(4);
	printf("%-88s\n", "Xoa trang man hinh Shell.");
}/*Kết thúc hàm Help_clear*****************************************************/

/*Trợ giúp lệnh color**********************************************************/
void Help_color()	{
	SetTextColor(2);
	printf("%-60s", "color <Doi tuong> -> <Mau>");
	SetTextColor(4);
	printf("%-88s", "Thay doi mau nen cua dong chu neu <Doi tuong> la background, mau cua dong chu neu");
	printf("%-60s%-88s\n", "\0", "<Doi tuong> la text.");
}/*Kết thúc hàm Help_color*****************************************************/

/*Trợ giúp lệnh copy***********************************************************/
void Help_copy()	{
	SetTextColor(2);
	printf("%-60s", "copy <Ten tap tin> -> <Duong dan thu muc dich>");
	SetTextColor(4);
	printf("%-88s\n", "Sao chep tap tin toi thu muc xac dinh.");
}/*Kết thúc hàm Help_copy******************************************************/

/*Trợ giúp lệnh decrypt********************************************************/
void Help_decrypt()	{
	SetTextColor(2);
	printf("%-60s", "decrypt <Ten tap tin da ma hoa> -> <Ten tap tin goc>");
	SetTextColor(4);
	printf("%-88s\n", "Giai ma tap tin da ma hoa dung lenh encrypt.");
}/*Kết thúc hàm Help_decrypt***************************************************/

/*Trợ giúp lệnh delete*********************************************************/
void Help_delete()	{
	SetTextColor(2);
	printf("%-60s", "delete <Ten tap tin>");
	SetTextColor(4);
	printf("%-88s\n", "Xoa tap tin.");
}/*Kết thúc hàm Help_delete****************************************************/

/*Trợ giúp lệnh encrypt********************************************************/
void Help_encrypt()	{
	SetTextColor(2);
	printf("%-60s", "encrypt <Ten tap tin goc> -> <Ten tap tin ma hoa>");
	SetTextColor(4);
	printf("%-88s\n", "Ma hoa tap tin, dung lenh decrypt de giai ma.");
}/*Kết thúc hàm Help_encrypt***************************************************/

/*Trợ giúp lệnh enum***********************************************************/
void Help_enum()	{
	SetTextColor(2);
	printf("%-60s", "enum <Tu khoa>");
	SetTextColor(4);
	printf("%-88s", "Liet ke tat ca cac tap tin va thu muc con cua thu muc hien hanh co ten chua <Tu khoa>");
	printf("%-60s%-88s\n", "\0", "neu muon liet ke tat ca thi <Tu khoa> de trong.");
}/*Kết thúc hàm Help_enum******************************************************/

/*Trợ giúp lệnh exit***********************************************************/
void Help_exit()	{
	SetTextColor(2);
	printf("%-60s", "exit");
	SetTextColor(4);
	printf("%-88s\n", "Ket thuc Shell.");
}/*Kết thúc hàm Help_exit******************************************************/

/*Trợ giúp lệnh graph**********************************************************/
void Help_graph()	{
	SetTextColor(2);
	printf("%-60s", "graph <Thuat toan> -> <Thu muc chua ket qua>");
	SetTextColor(4);
	printf("%-88s", "Chay thuat toan voi hang loat file trong thu muc hien hanh va xuat ra thu muc chi dinh.");
	printf("%-60s%-88s\n", "\0", "<Thuat toan> la BFS, DFS, Topo, Dijkstra, Prim, Cover, Indep, Max_Indep.");
}/*Kết thúc hàm Help_graph*****************************************************/

/*Trợ giúp lệnh help***********************************************************/
void Help_help()	{
	SetTextColor(2);
	printf("%-60s", "help <Ten lenh>");
	SetTextColor(4);
	printf("%-88s\n", "Tra cuu chuc nang cua lenh, neu <Ten lenh> rong thi hien thi thong tin tat ca cac lenh.");
}/*Kết thúc hàm Help_help******************************************************/

/*Trợ giúp lệnh hexview********************************************************/
void Help_hexview()	{
	SetTextColor(2);
	printf("%-60s", "hexview <Ten tap tin>");
	SetTextColor(4);
	printf("%-88s\n", "Hien thi noi dung tap tin duoi dang hex.");
}/*Kết thúc hàm Help_hexview***************************************************/

/*Trợ giúp lệnh MBR************************************************************/
void Help_MBR()	{
	SetTextColor(2);
	printf("%-60s", "MBR");
	SetTextColor(4);
	printf("%-88s\n", "Doc bang phan chuong.");
}/*Kết thúc hàm Help_MBR*******************************************************/

/*Trợ giúp lệnh monoff*********************************************************/
void Help_monoff()	{
	SetTextColor(2);
	printf("%-60s", "monoff");
	SetTextColor(4);
	printf("%-88s\n", "Tat man hinh, nhan phim bat ky de quay tro lai.");
}/*Kết thúc hàm Help_monoff****************************************************/

/*Trợ giúp lệnh move***********************************************************/
void Help_move()	{
	SetTextColor(2);
	printf("%-60s", "move <Ten tap tin> -> <Duong dan thu muc dich>");
	SetTextColor(4);
	printf("%-88s\n", "Di chuyen tap tin toi thu muc xac dinh.");
}/*Kết thúc hàm Help_move******************************************************/

/*Trợ giúp lệnh process********************************************************/
void Help_process()	{
	SetTextColor(2);
	printf("%-60s", "process <Ten tien trinh> -> <Hanh dong>");
	SetTextColor(4);
	printf("%-88s", "Thuc hien cac thao tac voi tien trinh voi <Hanh dong> la create, kill, list. <Hanh dong>");
	printf("%-60s%-88s\n", "\0", "list khong can <Ten tien trinh>.");
}/*Kết thúc hàm Help_process***************************************************/

/*Trợ giúp lệnh rename*********************************************************/
void Help_rename()	{
	SetTextColor(2);
	printf("%-60s", "rename <Ten cu> -> <Ten moi>");
	SetTextColor(4);
	printf("%-88s\n", "Doi ten tap tin.");
}/*Kết thúc hàm Help_rename****************************************************/

/*Trợ giúp lệnh system*********************************************************/
void Help_system()	{
	SetTextColor(2);
	printf("%-60s", "system <Che do>");
	SetTextColor(4);
	printf("%-88s\n", "Cho phep log off, stand by, hibernate, shut down hay reboot may tinh.");
}/*Kết thúc hàm Help_system****************************************************/

/*Trợ giúp lệnh textsize*******************************************************/
void Help_textsize()	{
	SetTextColor(2);
	printf("%-60s", "textsize <Co>");
	SetTextColor(4);
	printf("%-88s\n", "Thay doi co chu voi <co> la: small, medium (mac dinh), big.");
}/*Kết thúc hàm Help_textsize**************************************************/

/*Trợ giúp lệnh textview*******************************************************/
void Help_textview()	{
	SetTextColor(2);
	printf("%-60s", "textview <Ten tap tin van ban>");
	SetTextColor(4);
	printf("%-88s\n", "Hien thi noi dung tap tin van ban ASCII.");
}/*Kết thúc hàm Help_textview**************************************************/

/*Trợ giúp lệnh time***********************************************************/
void Help_time()	{
	SetTextColor(2);
	printf("%-60s", "time");
	SetTextColor(4);
	printf("%-88s\n", "Hien thi ngay, gio he thong.");
}/*Kết thúc hàm Help_time******************************************************/

typedef void (*Help)();
Help hlp_ptr[] = {
	Help_about, Help_attribute, Help_batch, Help_chdir, Help_clear, Help_color, 
	Help_copy, Help_decrypt, Help_delete, Help_encrypt, Help_enum, Help_exit, 
	Help_graph, Help_help, Help_hexview, Help_MBR, Help_monoff, Help_move, 
	Help_process, Help_rename, Help_system, Help_textsize, Help_textview, 
	Help_time
};

/*Command about - Giới thiệu về Shell******************************************/
void Cmd_about(char *parameter)	{
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;

	SetTextColor(2);
	cout << "Phan mem  :";
	SetTextColor(4);
	cout << " MuH Shell\n";

	SetTextColor(2);
	cout << "Phien ban :";
	SetTextColor(4);
	cout << " 6.0, thang 9 nam 2012\n";
	
	SetTextColor(2);
	cout << "Tac gia   :";
	SetTextColor(4);
	cout << " Vu Van Hiep\n";
	
	SetTextColor(2);
	cout << "Lop       :";
	SetTextColor(4);
	cout << " Cong nghe thong tin 2 - K55\n";
	
	SetTextColor(2);
	cout << "Truong    :";
	SetTextColor(4);
	cout << " Dai hoc Bach Khoa Ha Noi\n";

	SetConsoleTextAttribute(hConsole, wAttributes);
}/*Kết thúc hàm Cmd_about******************************************************/

/*Command help - Trợ giúp về Shell*********************************************/
void Cmd_help(char *parameter)	{
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;

	/*Khi không có tham số*/
	if (parameter[0] == '\0')	{
		SetTextColor(6);
		cout << "Shell nay ho tro " << MAX_CMD << " lenh:\n\n";
		for (int i = 0; i < MAX_CMD; ++i)
			hlp_ptr[i]();
	}
	else	{
		for (int i = 0; i < MAX_CMD; )	{
			if (!strcmp(list_cmd[i].name, parameter))	{
				hlp_ptr[i]();
				break;
			}
			if ((++i) == MAX_CMD)		Error(6);
		}
	}

	SetConsoleTextAttribute(hConsole, wAttributes);
}/*Kết thúc hàm Cmd_help*******************************************************/
