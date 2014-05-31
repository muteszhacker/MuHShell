/*THÔNG TIN*********************************************************************
 *Tập tin		: Shortest_Path.h
 *Mô tả			: Thư viện các hàm tìm đường đi ngắn nhất
 *Ngày tạo		: 03/09/2012
 *Cập nhật cuối	: 10/10/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

/*Khai báo các kiểu dữ liệu****************************************************/

/*Lớp các hàm tìm kiếm đường đi ngắn nhất**************************************/
class PATH : GRAPH	{
private:
	// Mảng đánh dấu đỉnh đã được xét
	vector <bool> final;
	// Mảng lưu đỉnh trước trong khi duyệt
	vector < vector <uint16_t> > before;
	// Mảng lưu độ dài đường đi từ start đến đỉnh i
	vector < vector <double> > min_len;
	// Mnagr lưu kết quả đường đi
	vector <uint16_t> result;
	// Số cạnh trên đường đi tìm được
	uint16_t count;
	// Thời gian đầu, cuối thực hiện thuật toán
	clock_t time_begin, time_end;

public:
	// Khởi tạo thông tin cơ bản về đồ thị
	bool Initiate_Find(bool mode, uint16_t opt, string input_file);

	// Thuật toán Dijkstra tìm đường đi ngắn nhất giữa 2 đỉnh bất kỳ trên đồ thị bất kỳ
	void Dijkstra();
	// In thông báo kết thúc thuật toán tìm kiếm
	void Final_Find();
	// Kiểm tra xem có đường đi không
	bool Exist_path(uint16_t opt);
	// In độ dài đường đi nếu có
	void Print_min_length(fstream& f, uint16_t opt);
	//Lưu đường đi vào mảng result
	void Build_result(uint16_t opt, vector <uint16_t> &result);
	//In đường đi và độ dài các cạnh
	void Print_path(fstream& f, uint16_t opt, vector <uint16_t> result);
	// In kết quả tìm đường đi ngắn nhất ra file
	void Print_result(uint16_t opt, string input_file);

	// In kết quả đường đi ngắn nhất ra file DOT
	void Print_dot_result(string input_file, uint16_t opt);
};/*Kết thúc khai báo lớp PATH*************************************************/

/*Khai báo các hàm*************************************************************/

/*Khởi tạo thông tin cơ bản về đồ thị******************************************/
bool PATH :: Initiate_Find(bool mode, uint16_t opt, string input_file)	{
	if (mode)	{
		if (!Read_txt(false, input_file))
			return false;
	}
	else	{
		if (!Read_grf(input_file))
			return false;
	}

	final.resize( Get_vertices() );
	before.resize(1);
	before[0].resize( Get_vertices() );	
	min_len.resize(1);
	min_len[0].resize( Get_vertices() );

	srand(uint16_t(time(0)));

	if (Get_vertices() > 1)	{
		Set_start( uint16_t( rand() ) % Get_vertices() );

		do	{
			Set_destination( uint16_t( rand() ) % Get_vertices() );
		}	while ( Get_destination() == Get_start() );
	}

	cout << "Dinh xuat phat: " << Get_start()+1 << "\n";
	cout << "Dinh ket thuc: " << Get_destination()+1 << "\n";

	cout << "Thuc hien thuat toan tim kiem duong di..........";
	time_begin = clock();

	return true;
}/*Kết thúc hàm Initiate_Find**************************************************/

/*Giải thuật Dijkstra để tìm đường đi ngắn nhất********************************/
void PATH :: Dijkstra()	{
	// Khởi tạo
	uint16_t i, j, counter = 0;

	for (i=0; i<Get_vertices(); ++i)	{
		min_len[0][i] = Get_length(Get_start(), i);
		final[i] = false;
		before[0][i] = Get_start();		
	}
	final[Get_start()] = true;
	before[0][Get_start()] = UINT16_MAX;	

	do	{
		double min = double(UINT16_MAX);
		i = UINT16_MAX;

		/*Tìm trong các đỉnh lân cận j đỉnh nào gần đỉnh 0 nhất*/
		for (j=0; j<Get_vertices(); ++j)	{
			if (!final[j])
				if (min>min_len[0][j] && min_len[0][j]>0.0)	{
					min = min_len[0][j];
					i = j;
			}
		}

		if (i==UINT16_MAX || i==Get_destination())
			break;

		final[i] = true;

		for (j=0; j<Get_vertices(); ++j)
			if (!final[j])
				if (min_len[0][j] > min_len[0][i] + Get_length(i, j))	{
					min_len[0][j] = min_len[0][i] + Get_length(i, j);
					before[0][j] = i;
			}
	} while (true);
}/*Kết thúc hàm Dijkstra*******************************************************/

/*In thông báo kết thúc thuật toán*********************************************/
void PATH :: Final_Find()	{
	time_end = clock();
	cout << "Xong trong " 
		 << double(time_end - time_begin) / CLOCKS_PER_SEC << " s.\n";
}/*Kết thúc hàm Final_traverse*************************************************/

/*Kiểm tra xem có đường đi không***********************************************/
bool PATH :: Exist_path(uint16_t opt)	{
	auto ok = min_len[0][Get_destination()];

	if (ok > 0.0 && ok < UINT16_MAX)
		return true;
	else
		return false;
}/*Kết thúc hàm Exist_path*****************************************************/

/*In độ dài đường đi nếu có****************************************************/
void PATH :: Print_min_length(fstream& f, uint16_t opt)	{
	f << "Do dai duong di ngan nhat tu " << Get_start()+1 << " den " << 
		Get_destination()+1 << " la " << min_len[0][Get_destination()] << ".\n";
}/*Kết thúc hàm Print_min_length***********************************************/

/*Lưu đường đi vào mảng result*************************************************/
void PATH :: Build_result(uint16_t opt, vector <uint16_t> &result)	{
	uint16_t i;
	
	i = result[0] = Get_destination();
	count = 0;
	while (before[0][i] != UINT16_MAX)	{
		i = before[0][i];
		result[ ++count ] = i;
	}
}/*Kết thúc hàm Build_result***************************************************/

/*In đường đi và độ dài các cạnh***********************************************/
void PATH :: Print_path(fstream& f, uint16_t opt, vector <uint16_t> result)	{
	f << "Duong di la: \n";

	for (uint16_t i=count; i>0; --i)
		f << result[i]+1 << "--(" << Get_length(result[i], result[i-1]) << ")-->";

	f << result[0]+1 << "\n";
}/*Kết thúc hàm Print_path*****************************************************/

/*In kết quả ra file***********************************************************/
void PATH :: Print_result(uint16_t opt, string input_file)	{
	string output_file(input_file.begin(), input_file.end()-4);

	if (opt == 10)
		output_file += "_Dijkstra.out";

	fstream f(output_file, ios :: out);

	cout << "Luu ket qua tim kiem duong di ngan nhat ra file " << output_file << "..........";

	if (!Exist_path(opt))
		f << "Khong co duong di tu " << Get_start()+1 << " den " 
		  << Get_destination()+1 << ".\n";
	else	{
		Print_min_length(f, opt);

		result.resize( Get_vertices() );

		Build_result(opt, result);
		Print_path(f, opt, result);
	}

	f.close();
	cout << "Xong.\n";
}/*Kết thúc hàm Print_result***************************************************/

/*In kết quả đường đi ngắn nhất ra file DOT************************************/
void PATH :: Print_dot_result(string input_file, uint16_t opt)	{
	string input_header(input_file.begin(), input_file.end()-4);

	string output_file = input_header;
	if (opt == 10)
		output_file += "_Dijkstra.dot";

	fstream f(output_file, ios :: out);
	
	cout << "Luu ket qua tim duong di ngan nhat ra file " << output_file << "..........";

	f << "digraph " << input_header;

	if (opt == 10)
		f << "_Dijkstra" << " {\n";

	if (Exist_path(opt))	{
		for (uint16_t i=0; i<Get_vertices(); ++i)
			for (uint16_t j=0; j<Get_vertices(); ++j)	{
				if (Get_length(i, j) > 0.0 && Get_length(i, j) < UINT16_MAX)	{
					f << i+1 << " -> " << j+1 << " [";

					bool ok = false;

					for (uint16_t k=count; k!=0; --k)
						if (result[k] == i && result[k-1] == j)	{
							ok = true;
							break;
						}

					if (!ok)
						f << "style = dotted, ";

					f << "label = \"" << Get_length(i, j) << "\", len = " << Get_length(i, j);
			
					f << "]\n";
				}
			}

		f << "label = \"\\n\\nDuong di ngan nhat dung thuat toan ";
		if (opt == 10)	{
			f << "Dijkstra voi du lieu tu file " << input_file << "\\n";
			f << "Do dai duong di ngan nhat tu " << Get_start()+1 << " den " 
			  << Get_destination()+1 << " la " << min_len[0][Get_destination()] << ".\"\n";
		}
	}
	else	{
		f << "label = \"\\n\\nKhong co duong di tu " << Get_start()+1 << " den " 
		  << Get_destination()+1 << " voi du lieu tu file " << input_file << ".\"\n";
	}

	f << "}";

	cout << "Xong.\n";
	f.close();

	string image_name = input_header;

	if (opt == 10)
		image_name += "_Dijkstra.bmp";

	cout << "Luu do thi moi ra file anh " << image_name << "..........";

	string command = "dot -Tbmp -o" + image_name + " " + output_file;

	system(command.c_str());

	cout << "Xong.\n\n\n";
}
