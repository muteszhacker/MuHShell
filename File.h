#define MAX_FILE_NAME_LEN 40	//Độ dài tối đa của tên tập tin
#define MAX_PATH_LEN 32			//Độ dài tối đa của đường dẫn
#define BUF_SIZE 512

char Hex_digit[] = "0123456789ABCDEF";

void Bin_Hex_View(unsigned char ch);
void Text_Hex_View(unsigned char ch);
unsigned long Get_File_Size(char *file_name);

void Cmd_chdir(char *parameter);
void Cmd_batch(char *parameter);
void Cmd_enum(char *parameter);
void Cmd_delete(char *parameter);
void Cmd_copy(char *parameter);
void Cmd_move(char *parameter);
void Cmd_rename(char *parameter);
void Cmd_attribute(char *parameter);
void Cmd_hexview(char *parameter);
void Cmd_hexview_2(char *parameter);
void Cmd_textview(char *parameter);

/*In dưới dạng mã hex**********************************************************/
void Bin_Hex_View(unsigned char ch)	{
	cout << "  " << Hex_digit[ch>>4] << Hex_digit[ch%16];
}/*Kết thúc hàm Bin_Hex_Word***************************************************/

/*In ký tự dưới dạng mã hex****************************************************/
void Text_Hex_View(unsigned char ch)	{
	if (ch==KEY_ENTER)
		cout << "\n";
	else if (ch>31 && ch<256 && ch!=KEY_DELETE)	{
		cout << "  " << Hex_digit[ch>>4] << Hex_digit[ch%16];
	}
}/*Kết thúc hàm Hex_Word*******************************************************/

/*Lấy kích thước file**********************************************************/
unsigned long Get_File_Size(char *file_name)	{
	FILE *f = fopen (file_name, "rb");

	if (f)	{
		fseek(f, 0L, SEEK_END);
		unsigned long size = ftell(f);
		fclose(f);
		return size;
	}
	else	{
		cout << "Loi: Tap tin khong ton tai.\n";
		return 0;
	}
}/*Kết thúc hàm Get_File_Size**************************************************/

/*Command chdir - Thay đổi thư mục hiện hành***********************************/
void Cmd_chdir(char *parameter)	{
	if (_chdir(parameter))
		Error(2);
}/*Kết thúc hàm Cmd_chdir******************************************************/

/*Command batch - Thực thi các lệnh viết trong file *.mbt**********************/
void Cmd_batch(char *parameter)	{
	FILE *f = fopen(parameter, "r");
	if (!f)		Error(0);
	else	{
		/*Kiểm tra parameter có là tên tập tin .mbt không*/
		size_t le = strlen(parameter);
		if (!(parameter[le-4]=='.' && parameter[le-3]=='m' &&
			parameter[le-2]=='b' && parameter[le-1]=='t'	))	{
				Error(1);
				fclose(f);
				return;
		}

		char cmd[MAX_CMD_LEN];

		/*Đọc và thực thi từng dòng lệnh*/
		while (!feof(f))	{
			fgets(cmd, MAX_CMD_LEN, f);

			/*Xóa kí tự \r ở cuối xâu nhập từ file*/
			if (!feof(f))	{
				le = strlen(cmd);
				cmd[le - 1]='\0';
			}

			cout << "\n-> " << cmd << "\n";

			Implement(cmd);
		}

		fclose(f);
	}
}/*Kết thúc hàm Cmd_batch******************************************************/

/*Command enum - Liệt kê tất cả các file và thư mục con của thư mục hiện hành**/
void Cmd_enum(char *parameter)	{
	_finddata_t file_info;
	intptr_t search_handle = _findfirst("*.*", &file_info);
	int counter = 0;

	if (search_handle == -1)		Error(3);
	else	{
		GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
		WORD wAttributes = screen_buffer_info.wAttributes;

		SetTextColor(2);
		printf("%-90s\t\t", "Ten file, thu muc");
		SetTextColor(4);
		printf("%-10s\t", "  Kich co");
		SetTextColor(5);
		printf("%-30s\n\n", "Thuoc tinh");

		do	{
			if (parameter[0]!='\0')	{
				bool match = false;
				size_t le1 = strlen(file_info.name), le2 = strlen(parameter);

				for (size_t i=0; i<le1; ++i)	{
					size_t j=0;

					if (file_info.name[i]==parameter[0] && i<=le1-le2)	{
						for (j=1; j<le2; ++j)
							if (file_info.name[i+j]!=parameter[j])
								break;

						if (j==le2)	{
							match=true;
							break;
						}
					}
				}
				if (!match)		continue;
			}

			if (!strcmp(file_info.name, ".") || !strcmp(file_info.name, ".."))
				continue;
			else	++counter;

			/*In tên file, nếu tên quá dài thì chỉ hiển thị một phần*/
			SetTextColor(2);
			if (strlen(file_info.name) >= MAX_FILE_NAME_LEN)	{
				char name_disp[MAX_FILE_NAME_LEN];

				strncpy_s(name_disp, file_info.name, MAX_FILE_NAME_LEN - 4);
				name_disp[MAX_FILE_NAME_LEN-4]='.';
				name_disp[MAX_FILE_NAME_LEN-3]='.';
				name_disp[MAX_FILE_NAME_LEN-2]='.';
				name_disp[MAX_FILE_NAME_LEN-1]='\0';

				printf("%-90s\t\t", name_disp);
			}
			else	printf("%-90s\t\t", file_info.name);

			/*In các kích thước file, với thư mục thì để trống*/
			SetTextColor(4);
			if (file_info.attrib & _A_SUBDIR)
				printf("%-10s\t", "\0");
			else	{
				int count=0;
				float size = (float)file_info.size;

				/*Đổi đơn vị*/
				while (size > 1024)	{
					++count;
					size = size / 1024;
				}
				switch (count)	{
				case 0	:	printf("%4.0f byte \t", size);
					break;
				case 1	:	printf("%6.2f KB \t", size);
					break;
				case 2	:	printf("%6.2f MB \t", size);
					break;
				case 3	:	printf("%6.2f GB \t", size);
					break;
				case 4	:	printf("%6.2f TB \t", size);
					break;
				}
			}

			/*In ra các thuộc tính file*/
			SetTextColor(5);
			if (file_info.attrib & _A_SUBDIR)
				cout << "Thu muc";
			else	cout << "Tap tin";
			if (file_info.attrib & _A_SYSTEM)
				cout << " he thong,";
			if (file_info.attrib & _A_HIDDEN)
				cout << " an,";
			if (file_info.attrib & _A_RDONLY)
				cout << " chi doc";
			cout << "\n";
		} while(!_findnext(search_handle, &file_info));

		SetTextColor(6);
		if (counter)
			cout << "\nCo " << counter << " khoan muc.\n";
		else	cout << "\nKhong co khoan muc nao.\n";

		_findclose(search_handle);

		SetConsoleTextAttribute(hConsole, wAttributes);
	}
}/*Kết thúc hàm Cmd_enum*******************************************************/

/*Xóa tập tin******************************************************************/
void Cmd_delete(char *parameter)	{
	if (remove(parameter))	{
		long err_id = GetLastError();

		if (err_id == ERROR_ACCESS_DENIED)
			Error(10);
		else	Error(0);
	}
}/*Kết thúc hàm Cmd_delete*****************************************************/

/*Sao chép tập tin*************************************************************/
void Cmd_copy(char *parameter)	{
	char source[MAX_FILE_NAME_LEN];
	char destination[MAX_CMD_LEN - MAX_FILE_NAME_LEN - 10];
	source[0] = destination[0] = '\0';

	if (!Trim(parameter, source, destination, 1))
		return;

	if (!CopyFile(source, destination, FALSE))	{
		long err_id = GetLastError();

		if (err_id == ERROR_FILE_NOT_FOUND)
			Error(0);

		else if (err_id == ERROR_ACCESS_DENIED)
			Error(11);
	}
}/*Kết thúc hàm Cmd_copy*******************************************************/

/*Di chuyển tập tin************************************************************/
void Cmd_move(char *parameter)	{
	char source[MAX_FILE_NAME_LEN];
	char destination[MAX_CMD_LEN - MAX_FILE_NAME_LEN - 10];
	source[0] = destination[0] = '\0';

	if (!Trim(parameter, source, destination, 1))
		return;

	if (!MoveFile(source, destination))	{
		long err_id = GetLastError();

		if (err_id == ERROR_FILE_NOT_FOUND)
			Error(0);

		else if (err_id == ERROR_ALREADY_EXISTS)
			Error(12);
	}
}/*Kết thúc hàm Cmd_move*******************************************************/

/*Đổi tên tập tin**************************************************************/
void Cmd_rename(char *parameter)	{
	char old_name[MAX_FILE_NAME_LEN];
	char new_name[MAX_FILE_NAME_LEN];
	old_name[0] = new_name[0] = '\0';

	if (!Trim(parameter, old_name, new_name, 0))
		return;

	if (rename(old_name, new_name))	{
		long err_id = GetLastError();

		printf("%d\n", err_id);
		if (err_id == ERROR_ALREADY_EXISTS)
			Error(14);
		else if (err_id == ERROR_FILE_NOT_FOUND)
			Error(0);
	}
}/*Kết thúc hàm Cmd_rename*****************************************************/

/*Thêm hoặc bỏ thuộc tính file*************************************************/
void Cmd_attribute(char *parameter)	{
	char file_name[MAX_FILE_NAME_LEN];
	char attribute[10];
	file_name[0] = attribute[0] = '\0';

	if (!Trim(parameter, file_name, attribute, 0))
		return;

	if (attribute[0] == '+')	{
		if (!strcmp(attribute, "+archive"))
			SetFileAttributes(file_name, GetFileAttributes(file_name) | FILE_ATTRIBUTE_ARCHIVE);
		else if (!strcmp(attribute, "+hidden"))
			SetFileAttributes(file_name, GetFileAttributes(file_name) | FILE_ATTRIBUTE_HIDDEN);
		else if (!strcmp(attribute, "+read only"))
			SetFileAttributes(file_name, GetFileAttributes(file_name) | FILE_ATTRIBUTE_READONLY);
	}
	else if (attribute[0] == '-')	{
		if (!strcmp(attribute, "-archive"))
			SetFileAttributes(file_name, GetFileAttributes(file_name) & ~(FILE_ATTRIBUTE_ARCHIVE));
		else if (!strcmp(attribute, "-hidden"))
			SetFileAttributes(file_name, GetFileAttributes(file_name) & ~(FILE_ATTRIBUTE_HIDDEN));
		else if (!strcmp(attribute, "-read only"))
			SetFileAttributes(file_name, GetFileAttributes(file_name) & ~(FILE_ATTRIBUTE_READONLY));
	}
	else if (!strcmp(attribute, "normal"))
		SetFileAttributes(file_name, FILE_ATTRIBUTE_NORMAL);
	else	Error(15);
}/*Kết thúc hàm Cmd_attrib*****************************************************/

/*Đọc và hiển thị nội dung tập tin dưới dạng hex*******************************/
void Cmd_hexview(char *parameter)	{
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;

	SetTextColor(6);
	FILE *f = fopen(parameter, "rb");
	if (!f)	{
		Error(0);
		SetConsoleTextAttribute(hConsole, wAttributes);
		return;
	}
	
	unsigned char i;
	while ((fread(&i, sizeof(unsigned char), 1, f)), !feof(f))
		Bin_Hex_View(i);

	cout << "\n";

	fclose(f);

	SetConsoleTextAttribute(hConsole, wAttributes);
}/*Kết thúc hàm hexview********************************************************/

/*Đọc và hiển thị nội dung tập tin dưới dạng hex dùng hàm Windows**************/
void Cmd_hexview_2(char *parameter)	{
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;

	HANDLE hDisk = CreateFile(parameter, GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, 0, NULL);

	if (hDisk == INVALID_HANDLE_VALUE)
		Error(0);
	else	{
		unsigned long size = Get_File_Size(parameter);
		BYTE *Buf = new BYTE[size];
		DWORD* byteread = new DWORD;

		ReadFile(hDisk, Buf, size, byteread, NULL);
		for(unsigned long i=0; i<size; ++i)
			printf("%02X   ", Buf[i]);
		CloseHandle(hDisk);
	}

	SetConsoleTextAttribute(hConsole, wAttributes);
}/*Kết thúc hàm hexview********************************************************/

/*Đọc và hiển thị nội dung tập tin văn bản*************************************/
void Cmd_textview(char *parameter)	{
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;

	if (parameter[0] != '\0')	{
		FILE *f = fopen(parameter, "rb");
		if (!f)	{
			Error(0);
			SetConsoleTextAttribute(hConsole, wAttributes);
			return;
		}

		SetTextColor(6);
		cout << "Tap tin: ";
		SetTextColor(2);
		cout << parameter << "\n";

		SetTextColor(7);
		for (int j = 1; j<=148; ++j)
			cout << '-';

		SetTextColor(6);
		unsigned char i;
		while ((fread(&i, sizeof(unsigned char), 1, f)), !feof(f))	{
			if (i==KEY_ENTER)
				cout << "\n";
			else if ( (i>31 && i<256) || (i=='\t'))	{
				cout << i;
			}
		}

		fclose(f);

		SetConsoleTextAttribute(hConsole, wAttributes);
		
		cout << "\n";
		for (int j = 1; j<=148; ++j)
			cout << '-';
	}
	else	{
		// Tìm tất cả các file .out trong thu muc hien hanh
		_finddata_t file_info;
		intptr_t search_handle = _findfirst("*.*", &file_info);
		uint16_t counter = 0;

		if (search_handle == -1)		Error(3);
		else	{
			GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
			WORD wAttributes = screen_buffer_info.wAttributes;

			do	{
				if (!strcmp(file_info.name, ".") || !strcmp(file_info.name, ".."))
					continue;

				SetTextColor(6);
				cout << "Tap tin: ";
				SetTextColor(2);
				cout << file_info.name << "\n";
				
				FILE *f = fopen(file_info.name, "rb");

				if (!f)	{
					Error(18);
					continue;
				}

				SetTextColor(7);
				for (int j = 1; j<=148; ++j)
					cout << '-';

				SetTextColor(6);
				unsigned char i;
				while ((fread(&i, sizeof(unsigned char), 1, f)), !feof(f))	{
					if (i==KEY_ENTER)
						cout << "\n";
					else if ( (i>31 && i<256) || (i=='\t'))	{
						cout << i;
					}
				}

				fclose(f);

				SetConsoleTextAttribute(hConsole, wAttributes);
	
				cout << "\n";
				for (int j = 1; j<=148; ++j)
					cout << '-';

			} while (!_findnext(search_handle, &file_info));
		}
	}
}/*Kết thúc hàm textview*******************************************************/
