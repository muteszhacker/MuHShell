/*Thông tin*********************************************************************
 *Tên tập tin	: main.cpp
 *Mô tả			: Chương trình Shell đơn giản
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 10/10/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

#include "Shell.h"
#include "Error.h"

#include "Console.h"
#include "Help.h"
#include "System.h"
#include "Graphics.h"
#include "Time.h"
#include "File.h"
#include "Process.h"
#include "Huffman.h"
#include "Disk.h"
#include "Graph.h"

/*Khai báo các biến toàn cục***************************************************/
typedef void (*Command)(char *parameter);
Command func_ptr[] = {
	Cmd_about, Cmd_attribute, Cmd_batch, Cmd_chdir, Cmd_clear, Cmd_color, 
	Cmd_copy, Cmd_decrypt, Cmd_delete, Cmd_encrypt, Cmd_enum, Cmd_exit, 
	Cmd_graph, Cmd_help, Cmd_hexview, Cmd_MBR, Cmd_monoff, Cmd_move, 
	Cmd_process, Cmd_rename, Cmd_system, Cmd_textsize, Cmd_textview, Cmd_time
};
/*Kết thúc khai báo************************************************************/

/*Chương trình chính***********************************************************/
int main()	{
	Start_Shell();

	return 0;
}/*Kết thúc hàm main***********************************************************/

/*Nhận diện tên 2 tham số******************************************************/
bool Trim(char *parameter, char *source, char *destination, int option)	{
	if (parameter[0] == '\0' || (parameter[0] == '-' && parameter[1] == '>'))	{
		Error(13);
		return false;
	}

	size_t le = strlen(parameter), i;
	for (i=0; i<le-2; ++i)
		if (parameter[i] == '-' && parameter[i+1] == '>')
			break;
	if (i == le-2 || le == 0)	{
		Error(13);
		return false;
	}
	
	/*Nhận diện tham số nguồn*/
	i=0;
	while ( !(	parameter[i] == ' '	&&	parameter[i+1] == '-' 
		&&	parameter[i+2] == '>' && parameter[i+3] == ' ' ) )		{
			source[i] = parameter[i];
			++i;
	}
	source[i] = '\0';

	/*Loại bỏ dấu cách thừa*/
	int j = strlen(source) - 1;
	while (source[j] == ' ')	{
		source[j] = '\0';
		--j;
		if (source[j] != ' ')
			break;
	}

	/*Bỏ qua dấu cách thừa*/
	i = i+4;
	while (parameter[i] == ' ')
		++i;

	/*Nhận diện tham số đích*/
	j = 0;
	while (parameter[i] != '\0')	{
		destination[j] = parameter[i];
		++i;
		++j;
	}

	if (option == 1)	{
		/*Thêm dấu '\' nếu gõ thiếu*/
		if (destination[j-1] != '\\')	{
			destination[j] = '\\';
			destination[++j] = '\0';
		}
		else	destination[j]='\0';

		/*Thêm tên file để tạo đường dẫn đầy đủ*/
		int k=0;
		while (source[k]!='\0')	{
			destination[j] = source[k];
			++j;
			++k;
		}
	}

	destination[j] = '\0';

	if (parameter[0] == '-' && parameter[1] == '>')	{
		Error(13);
		return false;
	}

	return true;
}/*Kết thúc hàm Trim***********************************************************/

/*Nhận diện tên lệnh và tham số************************************************/
bool Analyze(char *cmd, char *name, char *parameter)	{
	int i = 0;
	parameter[0] = '\0';

	/*Nhận diện tên lệnh*/
	name[0] = '\0';
	while (cmd[i] != ' ')	{
		name[i] = cmd[ i++ ];

		/*Loại ngay những lệnh có độ dài tên quá quy định*/
		if (i == MAX_CMD_NAME_LEN)	{
			Error(6);
			return false;
		}

		/*Trường hợp lệnh không có tham số*/
		if (cmd[i] == '\0')	{
			name[i] = '\0';
			return true;
		}
	}
	name[i] = '\0';

	/*Bỏ qua những khoảng trống thừa giữa tên lệnh và tham số*/
	do	++i;
	while (cmd[i] == ' ');

	/*Nhận diện tham số*/
	int j = 0;
	while (cmd[i] != '\0')	{
		parameter[ j++ ] = cmd[ i++ ];
		if (i == MAX_CMD_LEN)		break;
	}
	parameter[j] = '\0';

	return true;
}/*Kết thúc hàm Analyze********************************************************/

/*Thực thi lệnh****************************************************************/
void Implement(char *cmd)	{
	char name[MAX_CMD_NAME_LEN], parameter[MAX_PAR_LEN];

	if (!Analyze(cmd, name, parameter))
		return;

	/*Kiểm tra tên lệnh có phù hợp*/
	int i;
	for (i = 0; i < MAX_CMD; ++i)
		if (!strcmp(name, list_cmd[i].name))	{
			func_ptr[i](parameter);
			break;
		}

	if (i == MAX_CMD)
		Error(6);
}/*Kết thúc hàm Implement******************************************************/

/*Bắt đầu thực thi Shell*******************************************************/
void Start_Shell()	{
	SetConsoleTitleA("MuH SHELL 6.0");						//Đặt tiêu đề cửa sổ
	SetScreenBufferSize(148, 3000);				  //Đặt kích thước buffer cửa sổ
	SetWindowCo(62, 40, 1230, 660);				//Đặt tọa độ 4 góc cửa sổ cửa sổ
	Cmd_clear("\0");										//Xóa trắng màn hình

	SetTextColor(6);
	cout << "\t\t\t\t\t\t\t\t\tMuH SHELL 6.0\n"
		 << "\t\t\t\t\t\t\t Go lenh ";
	SetTextColor(7);
	cout <<	"help";
	SetTextColor(6);
	cout << " de xem thong tin ve cac lenh\n";
	SetTextColor(7);

	char cmd[MAX_CMD_LEN];
	while (true)	{
		GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
		WORD wAttributes = screen_buffer_info.wAttributes;
		SetTextColor(3);

		cout << "\nMUH-> " << _getcwd(NULL, 0) << " -> ";

		SetConsoleTextAttribute(hConsole, wAttributes);

		/*Chỉ nhận đến số ký tự tối đa*/
		fflush(stdin);
		fgets(cmd, MAX_CMD_LEN + 1, stdin);
		size_t le = strlen(cmd);
		cmd[le - 1] = '\0';

		if (cmd[0] != '\0')
			Implement(cmd);
	}
}/*Kết thúc hàm Start_Shell****************************************************/

/*Kết thúc chương trình********************************************************/