#include <bits/stdc++.h>

using namespace std;

unordered_map<string, vector<string>> ASREL;
unordered_map<string, vector<string>> FINAL;


bool cmp(pair<string, int>& a, pair<string, int>& b){
    return a.second > b.second;
}

vector<string> addCustomers_R(vector<string> customers, vector<string> temp){
    for (auto cust: customers){
        if (ASREL.find(cust) != ASREL.end()){   // IT'S IN THE MAP   
            temp = addCustomers_R(ASREL[cust], temp);
        } 
    }
    vector<string> v(customers.size() + temp.size());
    vector<string>::iterator it, st;

    it = set_union(customers.begin(), customers.end(), temp.begin(), temp.end(), v.begin());
    vector<string> res;
    for (st = v.begin(); st != it; ++st){
        res.push_back(*st);
    }

    return res;
}

int main(int argc, const char * argv[]){

    ifstream myFile;
    myFile.open(argv[1]);
    vector<string> setR;

    if (myFile){
        string line;
        while(getline(myFile, line, '\n')){
            size_t pos = 0;
            string delim = "|";
            string token;
            vector<string> lineSplit;

            if (line[0] == '#'){
                continue;
            }
            

            do {
                pos = line.find(delim);
                token = line.substr(0, pos);
                if (token == "|"){
                    token = "NULL";
                }
                lineSplit.push_back(token);
                line.erase(0, pos + delim.length());
            } while(pos != string::npos);

            if (lineSplit[2] != "0"){           // make sure that it is a p2c
                if (ASREL.find(lineSplit[0])!=ASREL.end()){ // if it's in the map
                    string key = lineSplit[0];
                    ASREL[key].push_back(lineSplit[1]);
                } else{
                    vector<string> val{lineSplit[1]};
                    string key = lineSplit[0];
                    ASREL[key] = val;
                }
            
            }
        }
    }

    myFile.close();

    vector<string> custList;
    for (auto x: ASREL){
        vector<string> temp{};
        custList = addCustomers_R(x.second, temp);
        FINAL[x.first] = custList;
    }

    // {map[AS1] =  customer.size(), map[AS2] = customers.size(),...}
    map<string, int> customerConeMap;
    for(auto x: FINAL){
        customerConeMap[x.first] = x.second.size();
    }

    vector<pair<string, int>> sortedCustomerConeMap;
    for (auto x: customerConeMap){
        sortedCustomerConeMap.push_back(x);
    }

    sort(sortedCustomerConeMap.begin(), sortedCustomerConeMap.end(), cmp);


    int y = 0;
    for (auto x: FINAL){
        if (y == 15){
            break;
        }
        cout << x.first << ": ";
        for (auto y: x.second){
            cout << y << ", ";
        }
        cout << endl;
    }

    int z = 0;

    for (auto x: sortedCustomerConeMap){
        if (z == 15){
            break;
        }
        cout << "AS: " << x.first << ", Customer cone size: " << x.second << endl;
    }

    return 0;

}