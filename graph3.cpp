#include <bits/stdc++.h>

using namespace std;

unordered_map<string, vector<string>> PREFIX2AS;

int main(int argc, const char * argv[]){

    ifstream myFile;
    myFile.open(argv[1]);
    vector<string> setR;

    if (myFile){
        string line;
        while(getline(myFile, line, '\n')){
            size_t pos = 0;
            string delim = "\t";
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
                // cout << token << " ";
                lineSplit.push_back(token);
                line.erase(0, pos + delim.length());
            } while(pos != string::npos);
            // cout << endl;

            size_t found = lineSplit[2].find("_");

            if (found != string::npos){
                string ASes = lineSplit[2];
                lineSplit.pop_back();
                size_t pos2 = 0;
                string delim2 = "_";
                string token2;
                // vector<string> lineSplit;

                do {
                    pos2 = ASes.find(delim2);
                    token2 = ASes.substr(0, pos2);
                    if (token2 == "|"){
                        token2 = "NULL";
                    }
                    // cout << token << " ";
                    lineSplit.push_back(token2);
                    ASes.erase(0, pos2 + delim2.length());
                } while(pos2 != string::npos);
            }

            if (lineSplit.size() > 3){  // multiple ASes

            } else if(lineSplit.size() == 3){
                if (PREFIX2AS.find(lineSplit[2])!=PREFIX2AS.end()){ // if it's in the map
                    string key = lineSplit[2];
                    PREFIX2AS[key].push_back(lineSplit[0]);
                } else{
                    vector<string> val{lineSplit[0]};
                    string key = lineSplit[2];
                    PREFIX2AS[key] = val;
                }
            }

            

            
            // if (PREFIX2AS.find(lineSplit[0])!=PREFIX2AS.end()){ // if it's in the map
            //     string key = lineSplit[0];
            //     PREFIX2AS[key].push_back(lineSplit[1]);
            // } else{
            //     vector<string> val{lineSplit[1]};
            //     string key = lineSplit[0];
            //     PREFIX2AS[key] = val;
            // }
            // if(PREFIX2AS.find(lineSplit[1])!=PREFIX2AS.end()){
            //     string key = lineSplit[1];
            //     PREFIX2AS[key].push_back(lineSplit[0]);
            // } else{
            //     vector<string> val{lineSplit[0]};
            //     string key = lineSplit[1];
            //     PREFIX2AS[key] = val;
            // }
        }
    }
    return 0;
}