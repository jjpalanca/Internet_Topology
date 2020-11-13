#include <bits/stdc++.h>

using namespace std;

unordered_map<string, vector<string>> ASREL;

bool asKeyExist(string key){
    for(auto x: ASREL){
        if (x.first.compare(key)==0){
            return true;
        }
    }
    return false;
}

bool cmp(pair<string, int>& a, pair<string, int>& b){
    return a.second > b.second;
}

bool isConnected(string as, vector<string> ases){

    for (auto x: ases){
        if (find(ASREL[x].begin(), ASREL[x].end(), as) == ASREL[x].end()){
            return false;
        }
    }
    
    return true;
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

    map<string, int> degreeMap;
    for(auto x: ASREL){
        degreeMap[x.first] = x.second.size();
    }

    vector<pair<string, int>> sortedASDegree;
    for (auto x: degreeMap){
        // 
        sortedASDegree.push_back(x);
    }

    sort(sortedASDegree.begin(), sortedASDegree.end(), cmp);

    vector<string> clique;
    int i = 0;
    for (auto as: sortedASDegree){
        if (i == 0){
            clique.push_back(as.first);
        } else{
            if (isConnected(as.first, clique)){
                clique.push_back(as.first);
            }
        }
        i++;
    }

    int itr = 0;
    cout << "First 10 ASes of the clique:" << endl;
    for(auto x: clique){
        if (itr == 10){
            exit(0);
        }
        cout << x << endl;
        itr++;
    }

    return 0;
}

