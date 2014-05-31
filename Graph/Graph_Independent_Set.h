/*Thông tin*********************************************************************
 *Tên tập tin	: Graph_Independent_Set.h
 *Mô tả			: Thư viên các hàm tìm tập độc lập
 *Phiên bản		: 6.0
 *Ngày tạo		: 24/10/2012
 *Cập nhật cuối	: 25/10/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

class INDEPENDENT : GRAPH	{
private:
	struct EDGE		{
		uint16_t x, y;
	};

	// Thời gian đầu, cuối thực hiện thuật toán
	clock_t time_begin, time_end;
	// Mảng lưu các đỉnh lân cận của i là neighbors[i]
	vector <vector <uint16_t> > neighbors;	
	// Mảng lưu kết quả
	vector <uint16_t> result;

	// Kích thước rừng đang duyệt
	uint16_t size;

	// Trọng số cực đại của tập độc lập của cây con T_u chứa u
	vector <double> Max_in;
	// Trọng số cực đại của tập độc lập của cây con T_u không chứa u
	vector <double> Max_out;
	vector <double> Big;
	// Trọng số ứng với mỗi đỉnh v - là trọng số cạnh (v, i) lớn nhất
	vector <double> weight;

public:
	// Khởi tạo
	bool Initiate_Set(bool mode, string input_file);
	//Thiết lập cho mảng neighbors
	void Find_neighbors();
	// Tìm xem trong đồ thị có cạnh (i, neighbors[i][j]) mà neighbors[i][j] là lá
	EDGE Has_edge_v_leaf();
	// Thuật toán tìm tập độc lập với đồ thị cây/rừng
	void Find_Independent_Set();
	// In thông báo kết thúc thuật toán tìm tập độc lập
	void Final_Set();
	// In kết quả tìm kiếm tập độc lập
	void Print_Set(string input_file);
	// In tập độc lập ra file dot
	void Print_Set_to_dot(string input_file);

	// Tính Max_in(v) và Max_out(v) tại v
	void Calculate_M(uint16_t v);
	// Thuật toán tìm tập độc lập lớn nhất với đồ thị cây/rừng
	void Find_Max_Independent_Set(uint16_t v);
	// In thông báo kết thúc thuật toán tìm tập độc lập kích thước lớn nhất
	void Final_Max_Set();
	// In kết quả tìm kiếm tập độc lập kích thước lớn nhất
	void Print_Max_Set(string input_file);
	// In tập độc lập kích thước lớn nhất ra file dot
	void Print_Max_Set_to_dot(string input_file);
};

/*Khởi tạo**********************************************************************/
bool INDEPENDENT :: Initiate_Set(bool mode, string input_file)	{
	if (mode)	{
		if (!Read_txt(true, input_file))
			return false;
	}
	else	{
		if (!Read_grf(input_file))
			return false;
	}

	size = Get_edges();

	cout << "Thuc hien thuat toan tim kiem tap doc lap..........";
	time_begin = clock();

	return true;
}/*Kết thúc hàm Initiate_Set***************************************************/

/*Thiết lập cho mảng neighbors*************************************************/
void INDEPENDENT :: Find_neighbors()	{
	for (uint16_t i=0; i<Get_vertices(); i++)	{
		vector <uint16_t> neighbor;

		for (uint16_t j=0; j<Get_vertices(); j++)
			if (Get_length(i, j)>0.0 && Get_length(i, j)<UINT16_MAX)
				neighbor.push_back(j);

		neighbors.push_back(neighbor);
	}
}/*Kết thúc hàm Find_neighbors*************************************************/

/*Tìm xem trong đồ thị có cạnh (i, neighbors[i][j]) mà neighbors[i][j] là lá***/
INDEPENDENT :: EDGE INDEPENDENT :: Has_edge_v_leaf()	{
	for (uint16_t i=0; i<neighbors.size(); i++)	{
		for (uint16_t j=0; j<neighbors[i].size(); j++)	{
			if (neighbors[i][j] != UINT16_MAX && neighbors[i][j]>=0)	{
				bool is_leaf = true;
				uint16_t v = neighbors[i][j];

				for (uint16_t k=0; k<neighbors[v].size(); ++k)
					if (neighbors[v][k] != UINT16_MAX && neighbors[v][k]>=0)	{
						is_leaf = false;
						break;
					}

				if (is_leaf)	{
					EDGE e;
					e.x = i;
					e.y = neighbors[i][j];

					return e;
				}
			}
		}
	}
}/*Kết thúc hàm Has_edge_v_leaf************************************************/

/*Thuật toán tìm tập độc lập với đồ thị cây/rừng*******************************/
void INDEPENDENT :: Find_Independent_Set()	{
	result.resize(0);

	while (size)	{
		EDGE e = Has_edge_v_leaf();

		uint16_t u = e.x, v = e.y;

		if (u>=0 && u<Get_vertices() && v>=0 && v<Get_vertices())	{
			// Thêm v vào tập kết quả
			result.push_back(v);

			// Xóa các con của u
			for (uint16_t k=0; k<neighbors[u].size(); ++k)
				if (neighbors[u][k] != UINT16_MAX)	{
					neighbors[u][k] = UINT16_MAX;
					--size;
				}

			// Xóa các con của v
			for (uint16_t k=0; k<neighbors[v].size(); ++k)
				if (neighbors[v][k] != UINT16_MAX)	{
					neighbors[v][k] = UINT16_MAX;
					--size;
				}

			// Xóa các cạnh nối đến i, j
			for (uint16_t k=0; k<neighbors.size(); k++)
				for (uint16_t t=0; t<neighbors[k].size(); t++)
					if (neighbors[k][t] == u || neighbors[k][t] == u)	{
						neighbors[k][t] = UINT16_MAX;
						--size;
					}
		}
		else
			return;
	}
}/*Kết thúc hàm Find_Independent_Set*******************************************/

/*In thông báo kết thúc thuật toán tìm tập độc lập*****************************/
void INDEPENDENT :: Final_Set()	{
	time_end = clock();
	cout << "Xong trong " 
		 << (double)(time_end - time_begin) / CLOCKS_PER_SEC << " s.\n";
}/*Kết thúc hàm Final_cover****************************************************/

/*In kết quả ra file***********************************************************/
void INDEPENDENT :: Print_Set(string input_file)	{
	string output_file(input_file.begin(), input_file.end()-4);

	output_file += "_Indep.out";

	fstream f(output_file, ios :: out);
	
	cout << "Luu thu tu dinh moi ra file " << output_file << "..........";

	if (size)	{
			f << "Khong tim duoc tap doc lap.\n";
			cout << "Xong.\n";
			f.close();
			return;
		}

	f << "Cac dinh trong tap doc lap la: \n";

	for (uint16_t i=0; i!=result.size(); ++i)
		f << result[i] + 1 << " ";

	f << "\n";

	cout << "Xong.\n";
	f.close();
}/*Kết thúc hàm Print_Set*****************************************************/

/*In tập độc lập ra file dot**************************************************/
void INDEPENDENT :: Print_Set_to_dot(string input_file)	{
	string input_header(input_file.begin(), input_file.end()-4);

	string output_file = input_header + "_Indep.dot";

	fstream f(output_file, ios :: out);
	
	cout << "Luu do thi moi ra file " << output_file << "..........";

	f << "digraph " << input_header << "_Indep" << " {\n";

	bool ok = false;

	if (size)	{
		f << "label = \"\\n\\nDo thi nhap tu file " << input_file 
		  << " khong co tap doc lap.\"\n";
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

		f << "label = \"\\n\\nTap doc lap cua do thi voi du lieu tu file " << input_file << "\"\n";
	}
	
	f << "}";
	cout << "Xong.\n";
	f.close();

	cout << "Luu do thi moi ra file anh " << input_header + "_Indep.bmp" << "..........";

	string command = "dot -Tbmp -o" + input_header + "_Indep.bmp " + output_file;

	system(command.c_str());

	cout << "Xong.\n\n\n";
}/*Kết thúc hàm Print_Set_to_dot***************************************************/

/*Tính Max_in(v) và Max_out(v) tại v***********************************************/
void INDEPENDENT :: Calculate_M(uint16_t v)	{
	Max_in[v] = weight[v];
	Max_out[v] = 0.0;

	for (uint16_t u=0; u!=neighbors[v].size(); ++u)	{
		Max_in[v] += Max_out[neighbors[v][u]];
		Max_out[v] += Big[neighbors[v][u]];
	}

	Big[v] = Max_in[v] > Max_out[v] ? Max_in[v] : Max_out[v];
}/*Kết thúc hàm Calculate_M****************************************************/

/*Thuật toán tìm tập độc lập lớn nhất với đồ thị cây/rừng**********************/
void INDEPENDENT :: Find_Max_Independent_Set(uint16_t v)	{
	for (uint16_t u=0; u!=neighbors[v].size(); ++u)
		if (neighbors[v][u]>=0 && neighbors[v][u]!=UINT16_MAX)	{
			Find_Max_Independent_Set(neighbors[v][u]);
		}

	result.push_back(v);

	Calculate_M(v);
}/*Kết thúc hàm Find_Max_Independent_Set***************************************/

/*In thông báo kết thúc thuật toán tìm tập độc lập kích thước lớn nhất*********/
void INDEPENDENT :: Final_Max_Set()	{
	result.resize(0);

	weight.resize(Get_vertices());
	Max_in.resize(Get_vertices());
	Max_out.resize(Get_vertices());
	Big.resize(Get_vertices());

	srand(uint16_t(time(0)));
	// Trọng số của đỉnh là ngẫu nhiên
	for (uint16_t i=0; i!=Get_vertices(); ++i)
		weight[i] = uint16_t( rand() ) % 10 + 1;
	
	Find_Max_Independent_Set(0);

	time_end = clock();
	cout << "Xong trong " 
		 << (double)(time_end - time_begin) / CLOCKS_PER_SEC << " s.\n";
}/*Kết thúc hàm Final_Max_Set**************************************************/

/*In kết quả ra file***********************************************************/
void INDEPENDENT :: Print_Max_Set(string input_file)	{
	string output_file(input_file.begin(), input_file.end()-4);

	output_file += "_Max_Indep.out";

	fstream f(output_file, ios :: out);
	
	cout << "Luu thu tu dinh moi ra file " << output_file << "..........";

	if (Big[0] == 0.0)	{
			f << "Khong tim duoc tap doc lap.\n";
			cout << "Xong.\n";
			f.close();
			return;
		}

	f << "Cac dinh trong tap doc lap kich thuoc cuc dai " << Big[0] << " la: \n";

	for (uint16_t i=0; i!=result.size(); ++i)
		f << result[i] + 1 << " ";

	f << "\n";

	cout << "Xong.\n";
	f.close();
}/*Kết thúc hàm Print_Set*****************************************************/

/*In tập độc lập kích thước lớn nhất ra file dot******************************/
void INDEPENDENT :: Print_Max_Set_to_dot(string input_file)	{
	string input_header(input_file.begin(), input_file.end()-4);

	string output_file = input_header + "_Max_Indep.dot";

	fstream f(output_file, ios :: out);
	
	cout << "Luu do thi moi ra file " << output_file << "..........";

	f << "digraph " << input_header << "_Max_Indep" << " {\n";

	bool ok = false;

	if (Big[0] == 0.0)	{
		f << "label = \"\\n\\nDo thi nhap tu file " << input_file 
		  << " khong co tap doc lap.\"\n";
		ok = true;
	}

	if (!ok)	{
		f << "node [style = filled, color = red]";
		for (uint16_t i=0; i!=result.size(); ++i)
			f << " " << result[i]+1 << "." << weight[result[i]];
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
				f << " " << b[i]+1 << "." << weight[b[i]];
		f << "\n";

		for (uint16_t i=0; i<Get_vertices(); ++i)
			for (uint16_t j=0; j<Get_vertices(); ++j)	{
				if (Get_length(i, j) > 0.0 && Get_length(i, j) < UINT16_MAX)
					f << i+1 << "." << weight[i] << " -> " << j+1 << "." << weight[j] << " [label = \"" << Get_length(i, j) 
					  << "\", len = " << Get_length(i, j) << "]\n";
			}

		f << "label = \"\\n\\nTap doc lap kich thuoc cuc dai " << Big[0] 
		  << " cua do thi\\nvoi du lieu tu file " << input_file << "\"\n";
	}
	
	f << "}";
	cout << "Xong.\n";
	f.close();

	cout << "Luu do thi moi ra file anh " << input_header + "_Max_Indep.bmp" << "..........";

	string command = "dot -Tbmp -o" + input_header + "_Max_Indep.bmp " + output_file;

	system(command.c_str());

	cout << "Xong.\n\n\n";
}/*Kết thúc hàm Print_Max_Set_to_dot******************************************/