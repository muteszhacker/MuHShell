/*THÔNG TIN*********************************************************************
 *Tập tin		: Traverse.h
 *Mô tả			: Thư viện các với đồ thị vô hướng không có chu trình
 *Ngày tạo		: 25/09/2012
 *Cập nhật cuối	: 10/10/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

/*Khai báo các kiểu dữ liệu****************************************************/

/*Lớp các hàm với DAG**********************************************************/
class DAG : GRAPH	{
private:
	// Mảng lưu kết quả đánh số
	vector <uint16_t> number;
	// Thời gian đầu, cuối thực hiện thuật toán
	clock_t time_begin, time_end;

public:
	// Khởi tạo mảng number
	bool Initiate_Topo(bool mode, string input_file);
	// Thuật toán Topo đánh số lại các đỉnh
	void Topological_order();
	// In thông báo kết thúc thuật Topo
	void Final_Topo();
	// Kiểm tra đồ thị có chu trình không
	void Has_cycle();
	// In kết quả đánh số
	void Print_Topo(string input_file);

	// In đồ thị được đánh số lại
	void Print_new_graph_to_dot(string input_file);
};/*Kết thúc khai báo lớp DAG**************************************************/

/*Khởi tạo mảng number*********************************************************/
bool DAG :: Initiate_Topo(bool mode, string input_file)	{
	if (mode)	{
		if (!Read_txt(true, input_file))
			return false;
	}
	else	{
		if (!Read_grf(input_file))
			return false;
	}

	number.resize(Get_vertices());
	fill(number.begin(), number.end(), UINT16_MAX);

	cout << "Thuc hien thuat toan Topo..........";
	time_begin = clock();

	return true;
}/*Kết thúc hàm Initiate_Topo**************************************************/

/*Đánh số đỉnh theo thuật toán Topo********************************************/
void DAG :: Topological_order()	{
	uint16_t left = 0, right = 0;
	vector <uint16_t> deg(Get_vertices());
	vector <uint16_t> queue(Get_vertices(), UINT16_MAX);

	for (uint16_t i=0; i!=Get_vertices(); ++i)
		for (uint16_t j=0; j!=Get_vertices(); ++j)
			if (Get_length(i, j) > 0.0 && Get_length(i, j)<UINT16_MAX)
				++deg[j];

	for (uint16_t i=0; i!=Get_vertices(); ++i)
		if (deg[i] == 0)
			queue[right++] = i;

	uint16_t num = 0, i = 0;

	while (left < right)	{
		i = queue[ left++ ];
		number[i] = (num++);

		for (uint16_t j=0; j!=Get_vertices(); ++j)
			if (Get_length(i, j) > 0.0 && Get_length(i, j)<UINT16_MAX)	{
				--deg[j];
				if (deg[j] == 0)
					queue[ right++ ] = j;
			}
	}
}/*Kết thúc hàm Topological_order**********************************************/

/*In thông báo kết thúc thuật Topo*********************************************/
void DAG :: Final_Topo()	{
	time_end = clock();
	cout << "Xong trong " 
		 << (double)(time_end - time_begin) / CLOCKS_PER_SEC << " s.\n";
}/*Kết thúc hàm Final_Topo*****************************************************/

/*Kiểm tra đồ thị có chu trình không*******************************************/
void DAG :: Has_cycle()	{
	Topological_order();

	for (uint16_t i=0; i!=Get_vertices(); ++i)
		if (number[i] == UINT16_MAX)	{
			cout << "\nDo thi co chu trinh.";
			return;
		}
	cout << "\nDo thi khong co chu trinh.";
}/*Kết thúc hàm Has_cycle******************************************************/

/*In kết quả ra file***********************************************************/
void DAG :: Print_Topo(string input_file)	{
	string output_file(input_file.begin(), input_file.end()-4);

	output_file += "_Topo.out";

	fstream f(output_file, ios :: out);
	
	cout << "Luu thu tu dinh moi ra file " << output_file << "..........";

	for (uint16_t i=0; i!=Get_vertices(); ++i)
		if (number[i] == UINT16_MAX)	{
			f << "Do thi vua nhap co chu trinh.\n";
			cout << "Xong.\n";
			f.close();
			return;
		}

	f << "Thu tu cac dinh moi la: \n";

	for (uint16_t i=0; i!=Get_vertices(); ++i)	{
		f << number[i]+1 << " ";
		
		if (i!=Get_vertices()-1)
			if (number[i+1] == 0)
				break;
	}

	f << "\n";

	cout << "Xong.\n";
	f.close();
}/*Kết thúc hàm Print_result***************************************************/

/*In đồ thị ban đầu và đồ thị mới được đánh số lại*****************************/
void DAG :: Print_new_graph_to_dot(string input_file)	{
	string input_header(input_file.begin(), input_file.end()-4);

	string output_file = input_header + "_Topo.dot";

	fstream f(output_file, ios :: out);
	
	cout << "Luu do thi moi ra file " << output_file << "..........";

	f << "digraph " << input_header << "_Topo" << " {\n";

	bool ok = false;

	for (uint16_t i=0; i!=Get_vertices(); ++i)
		if (number[i] == UINT16_MAX)	{
			f << "label = \"\\n\\nDo thi nhap tu file " << input_file << " co chu trinh.\"\n";
			ok = true;		
		}

	if (!ok)	{
		for (uint16_t i=0; i<Get_vertices(); ++i)
			for (uint16_t j=0; j<Get_vertices(); ++j)	{
				if (Get_length(i, j) > 0.0 && Get_length(i, j) < UINT16_MAX)
					f << i+1 << "." << number[i]+1 << " -> " << j+1 << "." << number[j]+1 << " [label = \"" 
					  << Get_length(i, j) << "\", len = " << Get_length(i, j) << "]\n";
		}
		f << "label = \"\\n\\nDo thi duoc danh so lai nho thuat toan Topo voi du lieu tu file " << input_file << ".\"\n";
	}

	f << "}";

	cout << "Xong.\n";
	f.close();

	cout << "Luu do thi moi ra file anh " << input_header + "_Topo.bmp" << "..........";

	string command = "dot -Tbmp -o" + input_header + "_Topo.bmp " + output_file;

	system(command.c_str());

	cout << "Xong.\n\n\n";
}/*Kết thúc hàm Print_new_graph_to_dot*****************************************/
