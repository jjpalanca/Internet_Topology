#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>


using namespace std;

class as {
public:
	string name;
	vector<string>customers;
	vector<string>prefix;
	unsigned int ipCount;
};

class cone {
public:
	string start;
	vector<string> nodes;
	int nodeCount;
	unsigned int ipCount;
	int prefixCount;
};

cone findCone( map<string,as>  b, string d) {
	cone temp,temp2;
	temp.ipCount += b[d].ipCount;
	temp.nodeCount += b[d].customers.size() ;
	temp.prefixCount += b[d].prefix.size();
	//if (b[d].customers.size() == 0) { temp.nodeCount += 1; }
	for (auto i : b[d].customers) {
		temp2 = findCone( b, i);
		temp.ipCount += temp2.ipCount;
		temp.nodeCount += temp2.nodeCount;
		temp.prefixCount += temp2.prefixCount;
	}
	
	

	return temp;
}

int main() {

	string line;
	string intermediate;
	string key;
	vector<string> tokens;

	as temp;

	fstream myFile;

	map<string, as>ASREL;

	myFile.open("test1.txt");

	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			istringstream check1(line);

			while (getline(check1, intermediate, '|')) {
				tokens.push_back(intermediate);
			}
			if (tokens.size() == 4) {
				if (stoi(tokens[2]) == -1) {//p2c only
					//first AS
					if (ASREL.find(tokens[0]) != ASREL.end()) {

						key = tokens[0];
						ASREL[key].customers.push_back(tokens[1]);

					}
					else {
						temp.name = tokens[0];
						temp.customers.push_back(tokens[1]);
						ASREL.insert(pair<string, as>(tokens[0], temp));
					}
					temp.customers.clear();//clear temp.
					//second AS
					if (ASREL.find(tokens[1]) != ASREL.end()) {

					}
					else {
						temp.name = tokens[1];
						ASREL.insert(pair<string, as>(tokens[1], temp));
					}
					temp.customers.clear();//clear temp.
					
				}
			}
			tokens.clear();//clear tokens
		}
	}
	myFile.close();
	tokens.clear();
	//---------------------------------------------------------------------------------------------
	//second file
	myFile.open("test2.txt");

	if (myFile.is_open()) {
		while (getline(myFile, line)) {

			istringstream chekck2(line);

			while (getline(chekck2, intermediate, '\t')) {
				tokens.push_back(intermediate);
			}

			istringstream check3(tokens[2]);
				while (getline(check3, intermediate, '_')) {
					tokens.push_back(intermediate);
				}
			
				if (ASREL.find(tokens[2]) != ASREL.end()) {
					key = tokens[2];
					ASREL[key].prefix.push_back(tokens[1]);//add to prefix vector
					ASREL[key].ipCount += pow(2, (32 - stoi(tokens[1])));//add to ip total

				}

				if (tokens.size() > 4) {
					for (auto i : tokens) {
						if (ASREL.find(tokens[2]) != ASREL.end()) {
							key = tokens[2];
							ASREL[key].prefix.push_back(tokens[1]);//add to prefix vector
							ASREL[key].ipCount += pow(2, (32 - stoi(tokens[1])));//add to ip total

						}
					}
				}
				tokens.clear();
		}
	}
	//--------------------------------------------------------------------------------------------------------------------------
	//customer cones
	map<string, cone>cone_Map;

	cone temp2;

	for (auto x : ASREL) {

		temp2 = findCone(ASREL, x.first);
		if (cone_Map.find(x.first) != cone_Map.end()) {
			cout << "Customer cone Error" << endl;
		}
		else {
			cone_Map.insert(pair<string, cone>(x.first, temp2));
		}
	}

	//sort by nodeCount
	vector<string> top15;
	vector<string>ip15;

	vector<int> nodes;
	vector<unsigned int> ips;

	int max = 0;
	int min = 0;
	int ipmax =0;
	int iptotal=0;
	//# of AS
	for (auto x : cone_Map) {
		nodes.push_back(x.second.nodeCount);
	}
	sort(nodes.begin(), nodes.end() );
	reverse(nodes.begin(), nodes.end());

	for (int i = 0; i < 15;++i) {
		for (auto x : cone_Map) {
			if (x.second.nodeCount == nodes[i]) {
				if (find(top15.begin(), top15.end(), x.first) == top15.end()) {
					top15.push_back(x.first);
					break;
				}
			}
		}
	}

	//# of Ip
	for (auto x : cone_Map) {
		ips.push_back(x.second.ipCount);
		iptotal += x.second.ipCount;
	}
	sort(ips.begin(), ips.end());
	reverse(ips.begin(), ips.end());

	for (int i = 0; i < 15;++i) {
		for (auto x : cone_Map) {
			if (x.second.ipCount == ips[i]) {
				ip15.push_back(x.first);
				break;
			}
		}
	}

	for (int i = 0; i < 15;++i) {
		cout << "AS " << top15[i] << ": " << "Nodes :" << ASREL[top15[i]].customers.size() << "  AS in cone :" << cone_Map[top15[i]].nodeCount << "  IP Prefix :" << cone_Map[top15[i]].prefixCount << "  IP :" << cone_Map[top15[i]].ipCount << endl;
	}
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	for (int i = 0; i < 15;++i) {
		cout << "AS " << ip15[i] << ": " << "Nodes :" << ASREL[ip15[i]].customers.size() << "  AS in cone :" << cone_Map[ip15[i]].nodeCount << "  IP Prefix :" << cone_Map[ip15[i]].prefixCount << "  IP :" << cone_Map[ip15[i]].ipCount << endl;
	}

	cout << "Total IPs :" << iptotal << endl;
	cout << "this is the end" << endl;
}
