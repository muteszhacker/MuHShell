/*Thông tin*********************************************************************
 *Tên tập tin	: Graph_Vertex_cover.h
 *Mô tả			: Thư viên các hàm giao tiếp với đồ thị
 *Phiên bản		: 6.0
 *Ngày tạo		: 16/10/2012
 *Cập nhật cuối	: 18/10/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

class COVER : GRAPH	{
private:
	// Thời gian đầu, cuối thực hiện thuật toán
	clock_t time_begin, time_end;
	// Mảng lưu các đỉnh lân cận của i là neighbors[i]
	vector <vector <uint16_t> > neighbors;
	// Kích thước phủ đỉnh
	uint16_t k;
	// Mảng lưu kết quả
	vector <uint16_t> result;

public:
	// Khởi tạo
	bool Initiate_Cover(bool mode, string input_file);
	//Thiết lập cho mảng neighbors
	void Find_neighbors();
	// Thuật toán tìm lớp phủ đỉnh
	bool Find_Vertex_Cover(vector <vector <uint16_t> > temp, uint16_t not, uint16_t ver);
	// In thông báo kết thúc thuật toán Vertex
	void Final_Cover();
	// In kết quả tìm kiếm lớp phủ đỉnh
	void Print_Cover(string input_file);

	// In lớp phủ đỉnh
	void Print_Cover_to_dot(string input_file);
};/*Kết thúc khai báo lớp COVER*************************************************/

/*Khởi tạo**********************************************************************/
bool COVER :: Initiate_Cover(bool mode, string input_file)	{
	if (mode)	{
		if (!Read_txt(true, input_file))
			return false;
	}
	else	{
		if (!Read_grf(input_file))
			return false;
	}

	srand(uint16_t(time(0)));
	k = uint16_t( rand() ) % Get_vertices() + 1;

	cout << "Kich thuoc lop phu dinh can tim la " << k << ".\n";

	cout << "Thuc hien thuat toan tim kiem lop phu dinh..........";
	time_begin = clock();

	return true;
}/*Kết thúc hàm Initiate_Cover*************************************************/

/*Thiết lập cho mảng neighbors*************************************************/
void COVER :: Find_neighbors()	{
	for (uint16_t i=0; i<Get_vertices(); i++)	{
		vector <uint16_t> neighbor;

		for (uint16_t j=0; j<Get_vertices(); j++)
			if (Get_length(i, j)>0.0 && Get_length(i, j)<UINT16_MAX)
				neighbor.push_back(j);
		
		neighbors.push_back(neighbor);
	}
}/*Kết thúc hàm Find_neighbors*************************************************/

/*Thuật toán tìm lớp phủ đỉnh**************************************************/
bool COVER :: Find_Vertex_Cover(vector <vector <uint16_t> > temp, uint16_t not, uint16_t ver)	{
	if (not != UINT16_MAX)	{
		for (uint16_t i=0; i<temp[not].size(); i++)
			temp[not][i] = UINT16_MAX;

		for (uint16_t i=0; i<temp.size(); i++)
			for (uint16_t j=0; j<temp[i].size(); j++)
				if (temp[i][j] == not)
					temp[i][j] = UINT16_MAX;
	}

	uint16_t counter = 0;
	
	for (uint16_t i=0; i<temp.size(); i++)	{
		for (uint16_t j=0; j<temp[i].size(); j++)	{
			if (temp[i][j] != UINT16_MAX)
				++counter;
		}
	}

	if (!counter)
		return true;
	else if (counter > k * ver)
		return false;
	else	{
		uint16_t i;

		for (i=0; i!=temp.size(); ++i)	{
			uint16_t size = 0;

			for (uint16_t k = 0; k!=temp[i].size(); ++k)
				if (temp[i][k] != UINT16_MAX)
					++size;

			if (size)	{
				if (Find_Vertex_Cover(temp, i, ver-1))	{
					result.push_back(i);
					return true;
				}
				else	{
					uint16_t j;

					for (j=0; j!=temp[i].size(); ++j)
						if (temp[i][j] != UINT16_MAX)
							if (Find_Vertex_Cover(temp, temp[i][j], ver-1))	{
								result.push_back(temp[i][j]);
								return true;
							}
			
					if (j == temp[i].size())
						return false;
				}
			}
		}

		if (i == temp.size())
			return false;
	}
}/*Kết thúc hàm Find_Vertex_Cover**********************************************/

/*In thông báo kết thúc thuật toán Vertex**************************************/
void COVER :: Final_Cover()	{
	bool ok = Find_Vertex_Cover(neighbors, UINT16_MAX, Get_vertices());

	time_end = clock();
	cout << "Xong trong " 
		 << (double)(time_end - time_begin) / CLOCKS_PER_SEC << " s.\n";
}/*Kết thúc hàm Final_cover****************************************************/

/*In kết quả ra file***********************************************************/
void COVER :: Print_Cover(string input_file)	{
	string output_file(input_file.begin(), input_file.end()-4);

	output_file += "_Cover.out";

	fstream f(output_file, ios :: out);
	
	cout << "Luu thu tu dinh moi ra file " << output_file << "..........";

	if (result.size() > k || result.size() == 0)	{
			f << "Do thi vua nhap khong co phu dinh kich thuoc khong lon hon " << k << ".\n";
			cout << "Xong.\n";
			f.close();
			return;
		}

	f << "Cac dinh trong Phu dinh kich thuoc khong lon hon " << k << " la: \n";

	for (uint16_t i=0; i!=result.size(); ++i)
		f << result[i] + 1 << " ";

	f << "\n";

	cout << "Xong.\n";
	f.close();
}/*Kết thúc hàm Print_result***************************************************/

/*In tập phủ đỉnh**************************************************************/
void COVER :: Print_Cover_to_dot(string input_file)	{
	string input_header(input_file.begin(), input_file.end()-4);

	string output_file = input_header + "_Cover.dot";

	fstream f(output_file, ios :: out);
	
	cout << "Luu do thi moi ra file " << output_file << "..........";

	f << "digraph " << input_header << "_Cover" << " {\n";

	bool ok = false;

	if (result.size() > k || result.size() == 0)	{
		f << "label = \"\\n\\nDo thi nhap tu file " << input_file 
		  << " khong co phu dinh kich thuoc khong lon hon " << k << ".\"\n";
		ok = true;
	}

	if (!ok)	{
		f << "node [style = filled, color = red]";
		for (uint16_t i=0; i!=result.size(); ++i)
			f << " " << result[i]+1;
		f << "\n";

		f << "node [style = filled, color = green]";
		vector <uint16_t> b;
		b.resize(Get_vertices());

		for (uint16_t i=0; i!=Get_vertices(); ++i)
			b[i] = i+1;

		for (uint16_t i=0; i!=result.size(); ++i)
			b[result[i]] = UINT16_MAX;

		for (uint16_t i=0; i!=Get_vertices(); ++i)
			if (b[i] != UINT16_MAX)
				f << " " << b[i];
		f << "\n";

		for (uint16_t i=0; i<Get_vertices(); ++i)
			for (uint16_t j=0; j<Get_vertices(); ++j)	{
				if (Get_length(i, j) > 0.0 && Get_length(i, j) < UINT16_MAX)
					f << i+1 << " -> " << j+1 << " [label = \"" << Get_length(i, j) 
					  << "\", len = " << Get_length(i, j) << "]\n";
			}

		f << "label = \"\\n\\nPhu dinh cua do thi voi du lieu tu file " << input_file << "\"\n";
	}
	
	f << "}";
	cout << "Xong.\n";
	f.close();

	cout << "Luu do thi moi ra file anh " << input_header + "_Cover.bmp" << "..........";

	string command = "dot -Tbmp -o" + input_header + "_Cover.bmp " + output_file;

	system(command.c_str());

	cout << "Xong.\n\n\n";
}/*Kết thúc hàm Print_Cover_to_dot*********************************************/
