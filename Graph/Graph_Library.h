/*THÔNG TIN*********************************************************************
 *Tập tin		: Graph_Library.h
 *Mô tả			: Thư viện các hàm với đồ thị
 *Ngày tạo		: 29/08/2012
 *Cập nhật cuối	: 10/10/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

/*Khai báo các kiểu dữ liệu****************************************************/

/*Lóp đồ thị*******************************************************************/
class GRAPH	{
private:
	struct COORD	{
		double x, y;
	};

	struct EDGE	{
		uint16_t x, y;
	};

	// Số đỉnh, đỉnh xuất phát, đỉnh kết thúc
	uint16_t vertices, start, destination;
	// Số cạnh
	uint32_t edges;
	// Ma trận cạnh
	vector < vector<double> > length;

public:
	// Hàm khởi tạo
	GRAPH();

	// Lấy số đỉnh
	inline uint16_t Get_vertices();
	// Thiết lập số đỉnh
	inline void Set_vertices(uint16_t value);
	// Lấy số cạnh
	inline uint32_t Get_edges();
	// Thiết lập số cạnh
	inline void Set_edges(uint32_t value);
	// Lấy đỉnh xuất phát
	inline uint16_t Get_start();
	// Thiết lập đỉnh xuất phát
	inline void Set_start(uint16_t value);
	// Lấy đỉnh kết thúc
	inline uint16_t Get_destination();
	// Thiết lập đỉnh kết thúc
	inline void Set_destination(uint16_t value);
	// Lấy độ dài cạnh (i, j)
	inline double Get_length(uint16_t i, uint16_t j);
	// Thiết lập độ dài cạnh (i, j)
	inline void Set_length(uint16_t i, uint16_t j, double value);
	// Lấy thông tin cạnh i

	// Khởi tạo thông tin cơ bản về đồ thị đọc từ file txt
	fstream Initiate_txt(string input_file);
	// Đọc dữ liệu đồ thị từ file txt
	bool Read_txt(bool mode, string input_file);

	// Hàm tính khoảng cách theo công thức tọa độ giữa hai cạnh
	double Distance(COORD c1, COORD c2);
	// Khởi tạo thông tin cơ bản về đồ thị đọc từ file grf
	fstream Initiate_grf(string input_file);
	// Đọc dữ liệu đồ thị từ file grf
	bool Read_grf(string input_file);

	// Lưu đồ thị dưới dạng file DOT
	void Save_dot(string input_file);
};/*Kết thúc khai báo lớp GRAPH************************************************/

/*Khai báo các hàm*************************************************************/

/*Hàm khởi tạo*****************************************************************/
GRAPH :: GRAPH()	{
	vertices = 0;
	edges = 0;
	start = 0;
	destination = 0;
}/*Kết thúc hàm GRAPH**********************************************************/

/*Lấy số đỉnh******************************************************************/
uint16_t GRAPH :: Get_vertices()	{
	return vertices;
}/*Kết thúc hàm Get_vertices***************************************************/

/*Đặt số đỉnh******************************************************************/
void GRAPH :: Set_vertices(uint16_t value)	{
	vertices = value;
}/*Kết thúc hàm Set_vertices***************************************************/

/*Lấy số cạnh******************************************************************/
uint32_t GRAPH :: Get_edges()	{
	return edges;
}/*Kết thúc hàm Get_edges******************************************************/

/*Đặt số cạnh******************************************************************/
void GRAPH :: Set_edges(uint32_t value)	{
	edges = value;
}/*Kết thúc hàm Set_edges******************************************************/

/*Lấy đỉnh xuất phát***********************************************************/
uint16_t GRAPH :: Get_start()	{
	return start;
}/*Kết thúc hàm Get_start******************************************************/

/*Đặt đỉnh xuất phát***********************************************************/
void GRAPH :: Set_start(uint16_t value)	{
	start = value;
}/*Kết thúc hàm Set_start******************************************************/

/*Lấy đỉnh đích****************************************************************/
uint16_t GRAPH :: Get_destination()	{
	return destination;
}/*Kết thúc hàm Get_destination************************************************/

/*Đặt đỉnh đích****************************************************************/
void GRAPH :: Set_destination(uint16_t value)	{
	destination = value;
}/*Kết thúc hàm Set_destination************************************************/

/*Lấy độ dài cạnh**************************************************************/
double GRAPH :: Get_length(uint16_t i, uint16_t j)	{
	return length[i][j];
}/*Kết thúc hàm Get_length*****************************************************/

/*Đặt độ dài cạnh**************************************************************/
void GRAPH :: Set_length(uint16_t i, uint16_t j, double value)	{
	length[i][j] = value;
}/*Kết thúc hàm Set_length*****************************************************/

/*Khởi tạo thông tin cơ bản về đồ thị đọc từ file txt**************************/
fstream GRAPH :: Initiate_txt(string input_file)	{
	fstream f(input_file, ios :: in);

	if (!f)	{
		cout << "Loi: File khong ton tai\n";
		return f;
	}

	cout << "Doc du lieu do thi..........";

	f >> vertices >> edges;

	length.resize(vertices);
	
	for (uint16_t i=0; i!=vertices; ++i)	{
		length[i].resize(vertices);
		fill(length[i].begin(), length[i].end(), UINT16_MAX);
		length[i][i] = 0.0;
	}

	return f;
}/*Kết thúc hàm Initiate_txt***************************************************/

/*Đọc dữ liệu đồ thị từ file txt***********************************************/
bool GRAPH :: Read_txt(bool mode, string input_file)	{
	fstream f = Initiate_txt(input_file);
	if (!f)
		return false;

	// Đọc dữ liệu các cạnh
	if (mode)	{
		uint16_t temp_1, temp_2;
		for (uint32_t i=0; i!=edges; ++i)	{
			f >> temp_1 >> temp_2;
			length[temp_1][temp_2] = 1.0;
		}
	}
	else	{
		uint16_t temp_1, temp_2;
		double temp_3;
		for (uint32_t i=0; i!=edges; ++i)	{
			f >> temp_1 >> temp_2 >> temp_3;
			length[temp_1][temp_2] = temp_3;
		}
	}

	f.close();
	cout << "Xong.\n";
	return true;
}/*Kết thúc hàm Read_txt*******************************************************/

/*Hàm tính khoảng cách theo công thức tọa độ giữa hai cạnh*********************/
double GRAPH :: Distance(COORD c1, COORD c2)	{
	double dx = c1.x - c2.x, dy = c1.y - c2.y;

	return sqrt(dx*dx + dy*dy);
}/*Kết thúc hàm Distance*******************************************************/

/*Khởi tạo thông tin cơ bản về đồ thị đọc từ file grf**************************/
fstream GRAPH :: Initiate_grf(string input_file)	{
	fstream f(input_file, ios :: in);

	if (!f)	{
		cout << "Loi: File khong ton tai\n";
		return f;
	}

	cout << "Doc du lieu do thi..........";

	char line[500];

	while (!f.eof())	{
		f.getline(line, 500);
		
		if (line[1] == '\0')
			break;
		else	{
			++vertices;
		}
	}

	--vertices;
	length.resize(vertices);

	for (uint16_t i=0; i!=vertices; ++i)	{
		length[i].resize(vertices);
		fill(length[i].begin(), length[i].end(), UINT16_MAX);
		length[i][i] = 0.0;
	}

	f.close();

	return fstream(input_file, ios :: in);
}/*Kết thúc hàm Initiate_grf***************************************************/

/*Đọc dữ liệu đồ thị từ file grf***********************************************/
bool GRAPH :: Read_grf(string input_file)	{
	fstream f = Initiate_grf(input_file);
	
	if (!f)
		return false;

	vector <COORD> list;
	list.resize(vertices);
	vector <EDGE> edge_list;
	edge_list.resize(vertices * vertices);

	char edge_list_string[500];

	while (!f.eof())	{
		// Đọc tên đỉnh, tọa độ đỉnh
		uint16_t index = 0;
		f >> index;
		if (index == 0)
			break;
		f >> list[index-1].x >> list[index-1].y;
		
		// Đọc xâu chứa danh sách đỉnh mà từ index có đường đi đến
		f.getline(edge_list_string, 500);
		size_t len = strlen(edge_list_string);
		if (len == 0)
			continue;

		// Trích xuất các đỉnh
		uint16_t i=0;
	
		while (i!=len)	{
			if (edge_list_string[i] == ' ')
				++i;
			else if ( (edge_list_string[i]>='0') && (edge_list_string[i]<='9') )	{
				// Nhận diện từng đỉnh đọc vào xâu con num
				uint16_t count = 0;
				char num[10];
				num[0] = edge_list_string[i];
				
				while ( (edge_list_string[i+1]>='0') && (edge_list_string[i+1]<='9') )	{
					++count;
					++i;
					num[count] = edge_list_string[i];
				}
				
				// Chuyển xâu num thành sô ver
				uint16_t ver;

				if (count == 0)
					ver = num[0]-48;
				else	{
					ver = 0;
					uint16_t tich10 = 1;

					for (uint16_t j=count; j>=0; --j)	{
						ver = ver + (num[j]-48) * tich10;
						tich10 = tich10 * 10;
						if (j == 0)
							break;
					}
				}

				// Lưu danh sách cạnh vào mảng edge_list
				edge_list[edges].x = index-1;
				edge_list[edges].y = ver-1;
				++edges;

				++i;
			}				
		}
	}

	for (uint16_t i=0; i!=edges; ++i)
		length[edge_list[i].x][edge_list[i].y] = 1.0;

	for (uint16_t i=0; i!=vertices; ++i)
		for (uint16_t j=0; j!=vertices; ++j)
			if (length[i][j] > 0.0  && Get_length(i, j)<UINT16_MAX)
				length[i][j] = Distance(list[i], list[j]);

	cout << "Xong.\n";
	return true;
	f.close();
}/*Kết thúc hàm Read_grf*******************************************************/

/*Lưu đồ thị dưới dạng file DOT************************************************/
void GRAPH :: Save_dot(string input_file)	{
	string output_file(input_file);
	size_t size = output_file.size();

	output_file[size-3] = 'd';
	output_file[size-2] = 'o';
	output_file[size-1] = 't';

	fstream f(output_file, ios :: out);
	
	cout << "Luu do thi goc ra file " << output_file << "..........";

	string input_header(input_file.begin(), input_file.end()-4);

	f << "digraph " << input_header << " {\n";

	for (uint16_t i=0; i<vertices; ++i)
		for (uint16_t j=0; j<vertices; ++j)	{
			if (length[i][j] > 0.0 && length[i][j] < UINT16_MAX)
				f << i+1 << " -> " << j+1 << " [label = \"" << length[i][j] << "\", len = " << length[i][j] << "]\n";
		}

	f << "label = \"\\n\\nDo thi voi du lieu tu file " << input_file << "\"\n";

	f << "}";

	cout << "Xong.\n";
	f.close();

	cout << "Luu do thi goc ra file anh " << input_header + ".bmp" << "..........";

	string command = "dot -Tbmp -o" + input_header + ".bmp " + output_file;

	system(command.c_str());

	cout << "Xong.\n";
}/*Kết thúc hàm Save_dot*******************************************************/
