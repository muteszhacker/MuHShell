/*THÔNG TIN*********************************************************************
 *Tập tin		: Traverse.h
 *Mô tả			: Thư viện các hàm duyệt đồ thị
 *Ngày tạo		: 29/08/2012
 *Cập nhật cuối	: 10/10/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

/*Khai báo các kiểu dữ liệu****************************************************/

/*Lớp các hàm duyệt đồ thị*****************************************************/
class TRAVERSE	: GRAPH{
private:
	// Mảng lưu cho biết đỉnh i đã được thăm chưa
	vector <bool> visited;
	// Mảng lưu kết quả duyệt
	vector <uint16_t> result;

	// Số đỉnh đã được duyệt
	uint16_t count;

	// Mảng lưu các nhóm đỉnh liên thông
	vector <uint16_t> group;

	// Số vùng liên thông
	uint16_t group_count;

	// Thời gian đầu, cuối thực hiện thuật toán
	clock_t time_begin, time_end;

public:
	// Hàm khởi tạo
	TRAVERSE();

	// Khởi tạo mảng visited, result
	bool Initiate_traverse(bool mode, string input_file);
	// Duyệt theo chiều rộng
	void BFS(uint16_t start);
	// Duyệt theo chiều sâu
	void DFS(uint16_t ver);
	// In thông báo kết thúc thuật toán duyệt
	void Final_traverse();
	// In kết quả duyệt ra file
	void Print_traverse(string input_file, uint16_t opt);

	// Khởi tạo mảng group, before
	bool Initiate_count(bool mode, string input_file);
	// Duyệt theo chiều sâu để đếm số thành phần liên thông
	void BFS_to_count(uint16_t start);
	// Tìm các thành phần liên thông
	void Find_connected_component();
	// In thông báo kết thúc thuật toán duyệt
	void Final_count();
	// In kết quả tìm kiếm thành phần liên thông
	void Print_connected_components(string input_file);

	// In đồ thị với thứ tự duyệt các đỉnh
	void Print_traversed_graph(string input_file, uint16_t opt);
};/*Kết thúc khai báo lớp TRAVERSE*********************************************/

/*Hàm khởi tạo*****************************************************************/
TRAVERSE :: TRAVERSE()	{
	count = 0;
	group_count = 0;
}/*Kết thúc hàm TRAVERSE*******************************************************/

/*Khởi tạo mảng visited, result************************************************/
bool TRAVERSE :: Initiate_traverse(bool mode, string input_file)	{
	if (mode)	{
		if (!Read_txt(true, input_file))
			return false;
	}
	else	{
		if (!Read_grf(input_file))
			return false;
	}

	visited.resize( Get_vertices() );
	result.resize( Get_vertices() );

	cout << "Thuc hien thuat toan duyet..........";
	time_begin = clock();

	return true;
}/*Kết thúc hàm Initiate_traverse**********************************************/

/*Thuật toán BFS để duyệt đồ thị***********************************************/
void TRAVERSE :: BFS(uint16_t start)	{
	uint16_t i, left = 0, right = 0;
	vector <uint16_t> queue ( Get_vertices(), UINT16_MAX);
	queue[0] = start;
	visited[start] = true;

	while (left <= right)	{
		i = queue[ left++ ];
		result[ count++ ] = i;

		for (uint16_t j=0; j!=Get_vertices(); ++j)
			if ( Get_length(i, j)>0.0 && Get_length(i, j)<UINT16_MAX && !visited[j] )	{
				queue[ ++right ] = j;
				visited[j] = true;
			}
	}
}/*Kết thúc hàm BFS************************************************************/

/*Thuật toán DFS để duyệt đồ thị***********************************************/
void TRAVERSE :: DFS(uint16_t ver)	{
	visited[ver] = true;
	result[count++] = ver;
	
	for (uint16_t i=0; i!=Get_vertices(); ++i)
		if (Get_length(ver, i)>0.0 && Get_length(ver, i)<UINT16_MAX && !visited[i])
			DFS(i);
}/*Kết thúc hàm DFS************************************************************/

/*In thông báo kết thúc thuật toán*********************************************/
void TRAVERSE :: Final_traverse()	{
	time_end = clock();
	cout << "Xong trong " 
		 << double(time_end - time_begin) / CLOCKS_PER_SEC << " s.\n";
}/*Kết thúc hàm Final_traverse*************************************************/

/*In kết quả ra file***********************************************************/
void TRAVERSE :: Print_traverse(string input_file, uint16_t opt)	{
	string output_file(input_file.begin(), input_file.end()-4);

	if (opt == 0)
		output_file += "_BFS.out";
	else
		output_file += "_DFS.out";

	fstream f(output_file, ios :: out);
	
	cout << "Luu ket qua duyet do thi ra file " << output_file << "..........";

	f << "Thu tu duyet cac dinh la: \n";

	for (uint16_t i=0; i!=Get_vertices(); ++i)	{
		f << result[i]+1 << " ";
		
		if (i!=Get_vertices()-1)
			if (result[i+1] == 0)
				break;
	}

	f << "\n";

	cout << "Xong.\n";
	f.close();
}/*Kết thúc hàm Print_result***************************************************/

/*Khởi tạo mảng group, before**************************************************/
bool TRAVERSE :: Initiate_count(bool mode, string input_file)	{
	if (mode)	{
		if (!Read_txt(true, input_file))
			return false;
	}
	else	{
		if (!Read_grf(input_file))
			return false;
	}

	group.resize( Get_vertices() );

	cout << "Thuc hien thuat toan tim so vung lien thong..........";
	time_begin = clock();

	return true;
}/*Kết thúc hàm Initiate_count*************************************************/

// Duyệt theo chiều sâu để đếm số thành phần liên thông************************/
void TRAVERSE :: BFS_to_count(uint16_t start)	{
	uint16_t i, left = 0, right = 0;
	vector <uint16_t> queue ( Get_vertices(), UINT16_MAX);
	queue[0] = start;

	while (left <= right)	{
		i = queue[ left++ ];

		for (uint16_t j=0; j!=Get_vertices(); ++j)
			if ( Get_length(i, j)>0.0 && Get_length(i, j)<UINT16_MAX && group[j]==0 )	{
				queue[ ++right ] = j;
				group[j] = group[i];
			}
	}
}/*Kết thúc hàm BFS_to_count***************************************************/

/*Tìm các thành phần liên thông************************************************/
void TRAVERSE :: Find_connected_component()	{
	for (uint16_t i=0; i!=Get_vertices(); ++i)
		if (group[i] == 0)	{
			group[i] = (++group_count);
			BFS_to_count(i);
		}
}/*Kết thúc hàm Find_connected_component***************************************/

/*In thông báo kết thúc thuật toán đếm vùng liên thông*************************/
void TRAVERSE :: Final_count()	{
	time_end = clock();
	cout << "Xong trong " 
		 << (double)(time_end - time_begin) / CLOCKS_PER_SEC << " s.\n";
}/*Kết thúc hàm Final_count****************************************************/

/*In kết quả tìm vùng liên thông ra file***************************************/
void TRAVERSE :: Print_connected_components(string input_file)	{
	string output_file(input_file);
	size_t size = output_file.size();

	output_file[size-3] = 'o';
	output_file[size-2] = 'u';
	output_file[size-1] = 't';

	fstream f(output_file, ios :: out);
	
	cout << "Luu ket qua dem so vung lien thong ra file " << output_file << "..........";

	if (group_count == 1)
		f << "Do thi da cho lien thong.\n";
	else	{
		f << "Co " << group_count << " thanh phan lien thong";

		for (uint16_t i=1; i<=group_count; ++i)	{
			f << "\nThanh phan " << i << " gom cac dinh: ";
			for (uint32_t j=0; j!=Get_vertices(); ++j)
				if (group[j] == i)
					f << j << " ";
		}
	}

	cout << "Xong.\n";
	f.close();
}/*Kết thúc hàm Print_connected_components*************************************/

/*In đồ thị với thứ tự duyệt các đỉnh******************************************/
void TRAVERSE :: Print_traversed_graph(string input_file, uint16_t opt)	{
	string input_header(input_file.begin(), input_file.end()-4);

	string output_file = input_header;
	if (opt == 0)
		output_file += "_BFS.dot";
	else if (opt == 1)
		output_file += "_DFS.dot";

	fstream f(output_file, ios :: out);
	
	cout << "Luu ket qua duyet ra file " << output_file << "..........";

	f << "digraph " << input_header;

	if (opt == 0)
		f << "_BFS" << " {\n";
	else if (opt == 1)
		f << "_DFS" << " {\n";

	for (uint16_t i=0; i!=Get_vertices(); ++i)
		for (uint16_t j=0; j!=Get_vertices(); ++j)	{
			if (Get_length(i, j) > 0.0 && Get_length(i, j) < UINT16_MAX)	{
				f << i+1;

				for (uint16_t k = 0; k!=Get_vertices(); ++k)
					if (result[k] == i)	{
						f << "." << k+1;
						break;
					}

				f << " -> " << j+1;

				for (uint16_t k = 0; k!=Get_vertices(); ++k)
					if (result[k] == j)	{
						f << "." << k+1;
						break;
					}

				f << " [label = \"" << Get_length(i, j) << "\", len = " << Get_length(i, j) << "]\n";
			}
		}

	f << "label = \"\\n\\nThu tu duyet do thi theo thuat toan ";
	if (opt == 0)
		f << "BFS voi du lieu tu file " << input_file << "\"\n";
	else if (opt == 1)
		f << "DFS voi du lieu tu file " << input_file << "\"\n";

	f << "}";

	cout << "Xong.\n";
	f.close();

	string image_name = input_header;
	if (opt == 0)
		image_name += "_BFS.bmp";
	else if (opt == 1)
		image_name += "_DFS.bmp";

	cout << "Luu do thi moi ra file anh " << image_name << "..........";

	string command = "dot -Tbmp -o" + image_name + " " + output_file;

	system(command.c_str());

	cout << "Xong.\n\n\n";
}
