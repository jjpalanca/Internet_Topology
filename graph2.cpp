#include <bits/stdc++.h>

using namespace std;

unordered_map<string, vector<string>> ASREL;

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

            if (ASREL.find(lineSplit[0])!=ASREL.end()){ // if it's in the map
                string key = lineSplit[0];
                ASREL[key].push_back(lineSplit[1]);
            } else{
                vector<string> val{lineSplit[1]};
                string key = lineSplit[0];
                ASREL[key] = val;
            }
            if(ASREL.find(lineSplit[1])!=ASREL.end()){
                string key = lineSplit[1];
                ASREL[key].push_back(lineSplit[0]);
            } else{
                vector<string> val{lineSplit[0]};
                string key = lineSplit[1];
                ASREL[key] = val;
            }

        }
    }
    // {1234:<13334>, 13334: <1234,12123>}

    myFile.close();

    
    int bin1 = 0;
    int bin2to5 = 0;
    int bin5to100 = 0;
    int bin100to200 = 0;
    int bin200to1000 = 0;
    int bin1000toinf = 0;

    for (auto x: ASREL){
        if (x.second.size() == 1){
            bin1++;
        } else if ((x.second.size() >= 2) and (x.second.size() <= 5)){
            bin2to5++;
        } else if ((x.second.size() >= 6) and (x.second.size() <= 100)){
            bin5to100++;
        } else if ((x.second.size() >= 101) and (x.second.size() <= 200)){
            bin100to200++;
        } else if ((x.second.size() >= 201) and (x.second.size() <= 1000)){
            bin200to1000++;
        } else if (x.second.size() >= 1001) {
            bin1000toinf++;
        }
    }

    cout << "Bin 1: " << bin1 << endl;
    cout << "Bin 2-5: " << bin2to5 << endl;
    cout << "Bin 5-100: " << bin5to100 << endl;
    cout << "Bin 100-200: " << bin100to200 << endl;
    cout << "Bin 200-1000: " << bin200to1000 << endl;
    cout << "Bin 1000+: " << bin1000toinf << endl;

    return 0;
}