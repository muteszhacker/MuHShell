/*Thông tin*********************************************************************
 *Tên tập tin	: Huffman.h
 *Mô tả			: Thư viên các hàm mã hóa tập tin bằng mã Huffman
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 29/09/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

#define MAX_CHAR 256

/*Định nghĩa kiểu dữ liệu mới**************************************************/
typedef struct Node	{
    unsigned char character;
    unsigned long frequency;
    Node *left, *right;
} node;

/*Khai báo các biến toàn cục***************************************************/
unsigned char DayBit = 0;							  //Day Cac Bit Chuan Bi Ghi
int SoBit = 0;										//Bit danh dau trong day bit
unsigned long foutLen = 0;								//Do dai mac dinh bang 0

/*Khai báo các hàm*************************************************************/
void Count_char(char *source, unsigned long *Ratio, unsigned long &FLen);
void Insertion_Sort(node *TL[MAX_CHAR]);
void Find_First_Position(int &first, node *TL[MAX_CHAR]);
void Make_Huffman_Tree(node *&root, unsigned long *Ratio);
void Tranverse(node *root);

void Make_Code_Table(node *root, char Bang[MAX_CHAR][MAX_CHAR], int VT, 
	unsigned char Tam[MAX_CHAR]);
void Write_char_and_freq(unsigned long *Ratio, FILE *fout, unsigned char &SKT);
void Write_bit(unsigned char Bit, FILE *fout);
void Write_char(char Bang[MAX_CHAR][MAX_CHAR], unsigned char KT, FILE *fout);

void Read_Ratio(unsigned long *Ratio, FILE *fin);
void Decode_byte(node *root, node *&T, unsigned char MangBit, FILE *fout, 
	unsigned char SBit);
void Decode_bit(node *root, node *&T, unsigned char bit, FILE *fout);

void Cmd_encrypt(char *parameter);
void Cmd_decrypt(char *parameter);

/*Đếm tổng số ký tự và số ký tự mỗi loại***************************************/
void Count_char(char *source, unsigned long *Ratio, unsigned long &FLen)	{
	FILE *f = fopen(source, "rt");

	while (!feof(f))	{
		++Ratio[fgetc(f)];
		++FLen;
	}

	fclose(f);
}/*Kết thúc hàm Count_char*****************************************************/

/*Sắp xếp mảng theo tần suất***************************************************/
void Insertion_Sort(node *TL[MAX_CHAR])	{  
	node temp;
	int j;

	for (int i=2; i<MAX_CHAR; ++i)	{
		temp = *TL[i];
		j = i-1;
		while (TL[j]->frequency > temp.frequency && j > 0)	{
			*TL[j+1] = *TL[j];
			--j;
		}
		*TL[j+1] = temp;
	}
}/*Kết thúc hàm Insertion_Sort*************************************************/

/*Tìm vị trí đầu của mảng đã sắp xếp*******************************************/
void Find_First_Position(int &first, node *TL[MAX_CHAR])	{
	for (first=1; TL[first]->frequency==0 && first<MAX_CHAR; ++first);
}/*Kết thúc hàm Find_First_Position********************************************/

/*Dựng cây Huffman*************************************************************/
void Make_Huffman_Tree(node *&root, unsigned long *Ratio)	{
	node *TL[MAX_CHAR] = {NULL};

	for (int i=0; i<MAX_CHAR; ++i)	{
		TL[i] = new node;
		TL[i]->character = i;
		TL[i]->frequency = Ratio[i];
		TL[i]->left = NULL;
		TL[i]->right = NULL;
	}					//Tao ra mang bien dong de xay cay bang cach thay doi lk

	Insertion_Sort(TL);

	int first;										//Tim VT dau cua mang da sx
	Find_First_Position(first, TL);

	//Xay Cay Huffman
	node *Tam = NULL;

	//Khi chi co 1 loai ktu
	if (first == MAX_CHAR-1)	{
		Tam = new node;
		*Tam = *TL[MAX_CHAR-1];
		TL[MAX_CHAR-1]->character = 0;
		TL[MAX_CHAR-1]->frequency = 0;
		TL[MAX_CHAR-1]->left = Tam;
	}

	while (first < MAX_CHAR-1)	{
		Tam = new node;
		Tam->character = 0;
		Tam->frequency = TL[first]->frequency + TL[first+1]->frequency;
		Tam->left = TL[first];
		Tam->right = TL[first+1];

		TL[first] = new node;				   //Tao node 0 o ben trai de cho SX
		TL[first]->character = 0;
		TL[first]->frequency = 0;  

		TL[first+1] = Tam;							   //Gan Tam vao pt ben trai
		Insertion_Sort(TL);
		first++;
	}

	root = TL[first];
	for (int i=0; i< first; ++i)
		delete TL[i];
}/*Kết thúc hàm Make_Huffman_Tree**********************************************/

/*Duyệt cây thứ tự NLR*********************************************************/
void Tranverse(node *root)	{
	if (root)	{
		Tranverse(root->left);
		Tranverse(root->right);
	}
}/*Kết thúc hàm Tranverse******************************************************/

/*Tạo bảng mã Huffman**********************************************************/
void Make_Code_Table(node *root, char Bang[MAX_CHAR][MAX_CHAR], int VT, 
	unsigned char Tam[MAX_CHAR])	{  
	if (root)	{
		if (root->character)	{  
			for(int i=1; i<=VT; ++i)
				Bang[root->character][i] = Tam[i];
			Bang[root->character][0] = VT;
		}

		//Duyệt nhánh trái
		Tam[++VT] = 0;
		Make_Code_Table(root->left, Bang, VT, Tam);

		//Duyệt nhánh phải
		Tam[VT] = 1;
		Make_Code_Table(root->right, Bang, VT, Tam);
		--VT;
	}
}/*Kết thúc hàm Make_Code_Table************************************************/

/*Ghi số loại ký tự xuất hiện và từng ký tự và tần suất tương ứng**************/
void Write_char_and_freq(unsigned long *Ratio, FILE *fout, unsigned char &SKT){
	SKT = 0;						// Số lượng ký tự ASCII xuất hiện trong file
	int i;

	for (i=0; i<MAX_CHAR; ++i)
		if (Ratio[i])
			SKT++ ;

	cout << "\nSo KT Trong Bang Ma ASCII: "<< int(SKT) << "\n";
	fputc(SKT, fout);

	for (i=0; i<MAX_CHAR; ++i)
		if (Ratio[i])	{  
			fputc(char(i), fout);
			fwrite(&Ratio[i], sizeof(unsigned long), 1, fout);    
		}
}/*Kết thúc hàm Write_char_and_freq********************************************/

/*Ghi từng bit*****************************************************************/
void Write_bit(unsigned char Bit, FILE *fout)	{  
	DayBit <<= 1;
	DayBit |= Bit;
	if (++SoBit == 8)	{  
		foutLen++;
		fputc(DayBit, fout);
		SoBit = 0;
	}
}/*Kết thúc hàm Write_bit******************************************************/

/*Ghi ký tự********************************************************************/
void Write_char(char Bang[MAX_CHAR][MAX_CHAR], unsigned char KT, FILE *fout)	{
	int SBit = Bang[KT][0];

	for (int i=1; i<=SBit; ++i)
		Write_bit(Bang[KT][i], fout);
}/*Kết thúc hàm Write_char*****************************************************/

/*Đọc mảng Ratio***************************************************************/
void Read_Ratio(unsigned long *Ratio, FILE *fin)	{
	unsigned char SKT = fgetc(fin), KTHT;
	unsigned long frequencyHT;

	for (int i=0; i<SKT; ++i)	{  
		KTHT = fgetc(fin);
		fread(&frequencyHT, sizeof(unsigned long), 1, fin);
		Ratio[KTHT] = frequencyHT;
	}
}/*Kết thúc hàm Read_Ratio*****************************************************/

/*Giải mã theo bit*************************************************************/
void Decode_bit(node *root, node *&T, unsigned char bit, FILE *fout)	{
	if (bit == 1)
		T = T->right;
	else	T = T->left;

	if (T->character)	{
		fputc(T->character, fout);
		T = root;
	}
}/*Kết thúc hàm Decode_bit*****************************************************/

/*Giải mã theo byte************************************************************/
void Decode_byte(node *root, node *&T, unsigned char MangBit, FILE *fout, 
		unsigned char SBit)	{
	unsigned char temp;

	for (int i=7; i>=SBit; i--)	{
		temp = MangBit;
		temp >>= i;
		temp &= 0x1;
		Decode_bit(root, T, temp, fout);
	}
}/*Kết thúc hàm Decode_byte****************************************************/

/*Mã hóa/Nén tập tin dùng mã Huffman*******************************************/
void Cmd_encrypt(char *parameter)	{
	char Bang[MAX_CHAR][MAX_CHAR] = {0};
	char source[MAX_FILE_NAME_LEN], destination[MAX_FILE_NAME_LEN];
	source[0] = destination[0] = '\0';

	if (!Trim(parameter, source, destination, 0))
		return;

	unsigned long Ratio[MAX_CHAR] = {0}, finLen = 0;;
	node *root = NULL;

	Count_char(source, Ratio, finLen);
	Make_Huffman_Tree(root, Ratio);
	Tranverse(root);

	unsigned char Tam[MAX_CHAR];
	Make_Code_Table(root, Bang, 0, Tam);

	cout << "\n|Ky tu|  |Ma Huffman|\n\n";

	for (int i=0; i<MAX_CHAR; ++i)
		if(Bang[i][0])	{
			cout << char(i) << "           ";
			for (int j=1; j<=Bang[i][0]; ++j)
				cout << int(Bang[i][j]) << " ";				//Xuat bo ma Huffman
			cout << "\n";
		}

	FILE *fin = fopen(source, "rt");
	FILE *fout = fopen(destination, "wb");

	fputc(0, fout);					  //Ghi Ky Tu dau chiem cho cho SBitThua

	unsigned char SKT;
	Write_char_and_freq(Ratio, fout, SKT);

	int T;
	while (!feof(fin))	{
		T = fgetc(fin);
		if (T != EOF)
			Write_char(Bang, char(T), fout);
	}

	unsigned char SBitThua = (8-SoBit) % 8;

	//KT & ghi byte cuoi
	while (SoBit)
		Write_bit(0, fout);
	//ghi SBitThua Vao dau file
	rewind(fout);
	fputc(SBitThua, fout);
	fclose(fin);
	fclose(fout);

	unsigned long TLNen = Get_File_Size(destination) *100 / Get_File_Size(source);
	cout << "Ty Le Nen: " << TLNen << "%";
}/*Kết thúc hàm Cmd_encrypt****************************************************/

/*Giải mã/Giải nén tin dùng mã Huffman*****************************************/
void Cmd_decrypt(char *parameter)	{
	char Bang[MAX_CHAR][MAX_CHAR] = {0};
	char source[MAX_FILE_NAME_LEN], destination[MAX_FILE_NAME_LEN];
	source[0] = destination[0] = '\0';

	if (!Trim(parameter, source, destination, 0))
		return;

	unsigned long Ratio[MAX_CHAR] = {0};
	node *root = NULL;

	FILE *fin = fopen(source, "rb");
	FILE *fout = fopen(destination, "wt");

	unsigned char SBitThua = fgetc(fin);

	Read_Ratio(Ratio, fin);
	Make_Huffman_Tree(root, Ratio);

	node *Tam = root;
	int T1 = fgetc(fin), T2;
	while(T1 != EOF)	{  
		T2 = T1;
		T1 = fgetc(fin);
		if (T1 != EOF)
			Decode_byte(root, Tam, char(T2), fout, 0);
		else Decode_byte(root, Tam, char(T2), fout, SBitThua);
	}

	fclose(fin);
	fclose(fout);
}/*Kết thúc hàm Cmd_encrypt****************************************************/
