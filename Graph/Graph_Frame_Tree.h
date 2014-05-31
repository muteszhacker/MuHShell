/*THÔNG TIN*********************************************************************
 *Tập tin		: Graph_Frame_Tree.h
 *Mô tả			: Thư viện các hàm tìm cây khung
 *Ngày tạo		: 29/08/2012
 *Cập nhật cuối	: 10/10/2012
 *Trình dịch	: Microsoft Visual C++ 10.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

/*Khai báo các kiểu dữ liệu****************************************************/

/*Lớp các hàm tìm cây khung nhỏ nhất*******************************************/
class FRAME	: GRAPH	{
private:
	// Cấu trúc mô tả cạnh
	struct EDGE_2	{
		uint16_t begin, end;
		double length;
	};

	// Số cạnh của cây khung nhỏ nhất
	uint16_t count;
	// Tổng trọng số cây khung nhỏ nhất
	double sum_length;

	// Mảng lưu các cạnh của cây khung nhỏ nhất
	vector <EDGE_2> result;
	// Thời gian đầu, cuối thực hiện thuật toán
	clock_t time_begin, time_end;

public:
	// Hàm khởi tạo
	FRAME();

	// Khởi tạo mảng visited, result
	bool Initiate_Frame(bool mode, uint16_t opt, string input_file);
	// Thuật toán Prim tìm cây khung nhỏ nhất
	void Prim();
	// In thông báo kết thúc thuật toán tìm kiếm cây khung nhỏ nhất
	void Final_Frame();

	// In kết quả cây khung tìm được ra file
	void Print_Frame(uint16_t opt, string input_file);

	// In cây khung vào file dot
	void Print_dot_frame(string input_file, uint16_t opt);
};/*Kết thúc khai báo lớp FRAME************************************************/

/*Khai báo các hàm*************************************************************/

/*Hàm khởi tạo*****************************************************************/
FRAME :: FRAME()	{
	count = 0;
	sum_length = 0;
}/*Kết thúc hàm FRAME**********************************************************/

/*Khởi tạo thông tin cơ bản về đồ thị: số đỉnh, tỉ lệ cạnh*********************/
bool FRAME :: Initiate_Frame(bool mode, uint16_t opt, string input_file)	{
	if (mode)	{
		if (!Read_txt(false, input_file))
			return false;
	}
	else	{
		if (!Read_grf(input_file))
			return false;
	}

	result.resize( Get_vertices() );

	srand(uint16_t(time(0)));

	if (Get_vertices() > 1)	{
		Set_start( uint16_t( rand() ) % Get_vertices() );

		do	{
			Set_destination( uint16_t( rand() ) % Get_vertices() );
		}	while ( Get_destination() == Get_start() );
	}

	cout << "Dinh xuat phat: " << Get_start() << "\n";
	cout << "Dinh ket thuc: " << Get_destination() << "\n";

	cout << "Thuc hien thuat toan tim cay khung nho nhat..........";
	time_begin = clock();

	return true;
}/*Kết thúc hàm Initiate_Frame*************************************************/

/*Giải thuật Prim tìm cây khung nhỏ nhất***************************************/
void FRAME :: Prim()	{
	// Khởi tạo
	vector <bool> mark ( Get_vertices() );

	for (uint16_t i = 0; i!=Get_vertices(); ++i)	{
		mark[i] = false;
		result[i].begin = UINT16_MAX;
		result[i].end = UINT16_MAX;
		result[i].length = 0.0;
	}
	mark[0] = true;

	do	{
		double min = double(UINT16_MAX);
		uint16_t last_i = UINT16_MAX, last_j = UINT16_MAX;


		for (uint16_t i=0; i!=Get_vertices(); ++i)
			for (uint16_t j=0; j!=Get_vertices(); ++j)
				if (Get_length(i, j)>0.0 && Get_length(i, j)<min && mark[i] && !mark[j])	{
					min = Get_length(i, j);
					last_i = i;
					last_j = j;
				}

				if (last_j == UINT16_MAX)
					return;

				mark[last_j] = true;

				result[count].begin = last_i;
				result[count].end = last_j;
				result[count].length = Get_length(last_i, last_j);
				++count;

				sum_length += Get_length(last_i, last_j);
	} while (count != Get_vertices()-1);
}/*Kết thúc hàm Prim***********************************************************/

/*In thông báo kết thúc thuật toán*********************************************/
void FRAME :: Final_Frame()	{
	time_end = clock();
	cout << "Xong trong " 
		 << double(time_end - time_begin) / CLOCKS_PER_SEC << " s.\n";
}/*Kết thúc hàm Final_traverse*************************************************/

/*In kết quả*******************************************************************/
void FRAME :: Print_Frame(uint16_t opt, string input_file)	{
	string output_file(input_file.begin(), input_file.end()-4);

	if (opt == 0)
		output_file += "_Prim.out";

	fstream f(output_file, ios :: out);

	cout << "Luu ket qua tim cay khung ra file " << output_file << "..........";

	f << "Cac canh cua cay khung la:\n";
	
	for (uint16_t i=0; i!=count; ++i)
		f << result[i].begin+1 << ", " << result[i].end+1 << ", " << result[i].length << "\n";
	f << "Tong trong so cay khung la " << sum_length << "\n";

	f.close();
	cout << "Xong.\n";
}/*Kết thúc hàm Print_Frame****************************************************/

/*In cây khung vào file dot****************************************************/
void FRAME :: Print_dot_frame(string input_file, uint16_t opt)	{
	string input_header(input_file.begin(), input_file.end()-4);

	string output_file = input_header;
	if (opt == 0)
		output_file += "_Prim.dot";

	fstream f(output_file, ios :: out);
	
	cout << "Luu ket qua tim cay khung ra file " << output_file << "..........";

	f << "digraph " << input_header;

	if (opt == 0)
		f << "_Prim" << " {\n";

	for (uint16_t i=0; i<Get_vertices(); ++i)
		for (uint16_t j=0; j<Get_vertices(); ++j)	{
			if (Get_length(i, j) > 0.0 && Get_length(i, j) < UINT16_MAX)	{
				f << i+1 << " -> " << j+1 << " [";

				bool ok = false;

				for (uint16_t k=0; k!=count; ++k)
					if (result[k].begin == i && result[k].end == j)	{
						ok = true;
						break;
					}

				if (!ok)
					f << "style = dotted, ";

				f << "label = \"" << Get_length(i, j) << "\", len = " << Get_length(i, j);

				f << "]\n";
			}
		}

	f << "label = \"\\n\\nCay khung cua do thi dung thuat toan ";
	if (opt == 0)
		f << "Prim voi du lieu tu file " << input_file << "\"\n";

	f << "}";

	cout << "Xong.\n";
	f.close();

	string image_name = input_header;

	if (opt == 0)
		image_name += "_Prim.bmp";

	cout << "Luu do thi moi ra file anh " << image_name << "..........";

	string command = "dot -Tbmp -o";
	
	if (opt == 0)
		command += image_name + " " + output_file;

	system(command.c_str());

	cout << "Xong.\n\n\n";
}
