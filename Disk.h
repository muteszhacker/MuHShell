/*Thông tin*********************************************************************
 *Tên tập tin	: Disk.h
 *Mô tả			: Thư viên các hàm với ổ đĩa
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 29/09/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

/*Định nghĩa kiểu dữ liệu mới**************************************************/
struct	{
	unsigned char active;
	unsigned char BgHdr;
	unsigned short  BgSctCyl;
	unsigned char Sys;
	unsigned char EndHdr;
	unsigned short EndSctCyl;
	unsigned long addr;
	unsigned long size;
}	Tab[4];

/*Khai báo các hàm*************************************************************/
void Print_Table(BYTE Buf[]);
void Cmd_MBR(char *parameter);

/*In bảng phân chương**********************************************************/
void Print_Table(BYTE Buf[])	{
	int i;  
	memcpy(Tab, &Buf[446], 4*16);

	cout << " +--------+-----+-----+-----+-----+-----+-----+-----+------------+------------+\n";
	cout << " |        |     Bat dau     |     |    Ket  thuc    |  Dia  chi  |     So     |\n";
	cout << " |Tich cuc+-----+-----+-----+ SYS +-----+-----+-----+            |            |\n";
	cout << " |        |  H  |  C  |  S  |     |  H  |  C  |  S  | Sector dau |   Sector   |\n";
	cout << " +--------+-----+-----+-----+-----+-----+-----+-----+------------+------------+\n";

	for(i=0; i < 4; ++i )	{
		if (Tab[i].active == 0x00)
			cout << " |  KHONG |";
		else if (Tab[i].active == 0x80)
			cout << " |   CO   |";
		printf(" %3d |", Tab[i].BgHdr);
		printf("%4d |", (Tab[i].BgSctCyl >>8) + ((Tab[i].BgSctCyl & 0x00C0)<<2));
		printf("% 4d |", Tab[i].BgSctCyl & 0x003F);
		printf("  %02X |", Tab[i].Sys);
		printf("%4d |", Tab[i].EndHdr);
		printf("%4d |", (Tab[i].EndSctCyl >>8) + ((Tab[i].EndSctCyl & 0x00C0)<<2));
		printf("%4d |", Tab[i].EndSctCyl & 0x003F);
		
		printf(" %10d |", Tab[i].addr);
		printf(" %10d |", Tab[i].size);
		printf("\n");
	}
	cout << " +--------+-----+-----+-----+-----+-----+-----+-----+------------+------------+\n";
}/*Kết thúc hàm Print_Table****************************************************/

/*Command MBR - Đọc bảng phân chương*******************************************/
void Cmd_MBR(char *parameter)	{
	if (parameter[0] != '\0')	{
		Error(13);
		return;
	}

	HANDLE hDevice;              
	BYTE Buf[512];
	DWORD byteread;
	int i;
	unsigned __int64 pos;
	LONG Lp, Hp;	

	hDevice = CreateFile(TEXT("\\\\.\\PhysicalDrive0"), GENERIC_READ, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	if (hDevice == INVALID_HANDLE_VALUE)
		Error(17);
	else	{
		cout << "Bang phan chuong:\n";
		ReadFile(hDevice, Buf, 512, &byteread, NULL);
		for(i=446; i<512; ++i)	{
			printf("  %02X ", Buf[i]);
			if ((i-445)%16 == 0)
				cout << "\n";
		}

		cout << "\n\n\n";
		Print_Table(Buf);
		cout << "\n\nBang phan chuong mo rong:\n";

		//Thay doi vi tri con tro file
		pos = Tab[1].addr;
		pos *=512;
		Lp = pos & 0xFFFFFFFF;
		Hp = pos >> 32;

		//Doc, dua ra và giai ma ext_partition	
		SetFilePointer(hDevice, Lp, &Hp, FILE_BEGIN);
		ReadFile(hDevice, Buf, 512, &byteread, NULL);
		for(i=446; i<512; ++i)	{
			printf("  %02X ", Buf[i]);
			if ((i-445)%16 == 0)
				cout << "\n";
		}
		printf("\n\n\n");
		Print_Table(Buf);
		CloseHandle(hDevice);
	}
}/*Kết thúc hàm Cmd_MBR********************************************************/
