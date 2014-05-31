/*Thông tin*********************************************************************
 *Tên tập tin	: Shell.h
 *Mô tả			: Thư viện chứa một số thông tin cơ bản về Shell
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 29/09/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

#include <iostream>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <direct.h>
#include <io.h>
#include <time.h>
#include <PowrProf.h>

#include <string>
#include <fstream>
#include <unordered_map>
#include <cstdint>
#include <algorithm>
#include <math.h>

#define MAX_CMD 24										   //Số loại lệnh tối đa
#define MAX_CMD_LEN 128							 //Độ dài tối đa của lệnh đầy đủ
#define MAX_CMD_NAME_LEN 12							//Độ dài tối đa của tên lệnh
#define MAX_PAR_LEN MAX_CMD_LEN - MAX_CMD_NAME_LEN	 //Độ dài tối đa của tham số

using namespace std;

/*Định nghĩa kiểu dữ liệu mới**************************************************/
typedef struct	{
	char name[MAX_CMD_NAME_LEN];									  //Tên lệnh
} COMMAND;

/*Khai báo biến toàn cục*******************************************************/
COMMAND list_cmd[] = {
	"about", "attribute", "batch", "chdir", "clear", "color", "copy", "decrypt", 
	"delete", "encrypt", "enum", "exit", "graph", "help", "hexview", "MBR", 
	"monoff", "move", "process", "rename", "system", "textsize", "textview", 
	"time"
};

/*Khai báo các hàm*************************************************************/
bool Trim(char *parameter, char *source, char *destination, int option);
bool Analyze(char *cmd, char *name, char *parameter);
void Implement(char *cmd);
void Start_Shell();

/*Kết thúc khai báo************************************************************/
