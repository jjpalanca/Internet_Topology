#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;


class as {
public:
	int source;
	int dest;
	int type;
	
	string dsource;

};

class as_Data {
public:
	int source;
	vector<int> nodes;
	int customers;
	int peers;

};


int main()
{
	int transit_Ctr = 0;
	int content_Ctr = 0;
	int enterprise_Ctr = 0;
	int tot = 0;
	int flag = 0;
	int j =0;
	int bin1, bin2, bin3, bin4, bin5, bin6;
	bin1 = bin2 = bin3 = bin4 = bin5 = bin6 = 0;

	vector <string> tokens;
	string intermediate;
	string line;
	fstream myFile;

	
	vector<as> data;
	vector<as_Data> g_data;
	myFile.open("20201001.as-rel2.txt");

	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			tot++;
			istringstream check1(line);

			while (std::getline(check1, intermediate, '|')) {//tokenize string
				tokens.push_back(intermediate);
			}

			if (tokens.size() == 4) {//checks if line is relevant data
				 
					as temp;
					temp.source = stoi(tokens[0]);
					temp.dest = stoi(tokens[1]);
					temp.type = stoi(tokens[2]);
					temp.dsource.assign(tokens[3]);

					
					data.push_back(temp);
				



			}

			tokens.clear();
		}
	}
	else {
		cout << "ERROR" << endl;
	}
	myFile.close();

	//data manipulation

	

	for(int i = 0; i < data.size();++i) {
		flag = 0;
		as_Data temp;
		temp.source = data[i].source;
		temp.nodes.push_back(data[i].dest);
		if (data[i].type == 0) {
			temp.peers += 1;
		}
		else if (data[i].type == -1) {
			temp.customers += 1;
		}
		//first
		if (i == 0) {
			
			g_data.push_back(temp);
		}
		else {
			//rest
			if (g_data[j].source == data[i].source) {
				g_data[j].nodes.push_back(data[i].dest);
				if (data[i].type == 0) {
					g_data[j].peers += 1;
				}
				else if (data[i].type == -1) {
					g_data[j].customers += 1;
				}
			}
			else {
				g_data.push_back(temp);
				++j;
			}
		}
	}
	
	for (int k = 0;k < g_data.size();++k) {
		if (g_data[k].nodes.size() == 1) {
			bin1++;
		}
		if (g_data[k].nodes.size() > 1 && g_data[k].nodes.size() < 6) {
			bin2++;
		}
		if (g_data[k].nodes.size() > 5 && g_data[k].nodes.size() < 101) {
			bin3++;
		}
		if (g_data[k].nodes.size() > 100 && g_data[k].nodes.size() < 201) {
			bin4++;
		}
		if (g_data[k].nodes.size() > 200 && g_data[k].nodes.size() < 1001) {
			bin5++;
		}
		if (g_data[k].nodes.size() > 1001) {
			bin6++;
		}
	}
	

	cout << bin1 << endl;
	cout << bin2 << endl;
	cout << bin3 << endl;
	cout << bin4 << endl;
	cout << bin5 << endl;
	cout << bin6 << endl;
	cout << "this is the end" << endl;


}
