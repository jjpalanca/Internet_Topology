#include <bits/stdc++.h>

using namespace std;

unordered_map<string, unordered_map<string, vector<string>>> AS2ORG;

bool orgExists(string org_name){
    // return AS2ORG.contains(org_name);
    bool found = false;
    for(auto x : AS2ORG){
        if(x.first.compare(org_name)==0){
            return true;
        }
    }
    return found;
}

bool orgIDExists(string org_id){
    bool found = false;
    for(auto x : AS2ORG){
        for (auto id: x.second){
            if (id.first.compare(org_id) == 0){
                return true;
            }
        }
    }
    return found;
}

void addAStoORG(string asn, string org_id){
    for (auto orgs: AS2ORG){
        for (auto id: orgs.second){
            if (id.first.compare(org_id)==0){
                AS2ORG[orgs.first][id.first].push_back(asn);
                return;
            }
        }
    }
}

int main(int argc, const char * argv[]){

    ifstream myFile;
    myFile.open(argv[1]);


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

            if (lineSplit.size() == 5){         // ORG fields
                if (!orgExists(lineSplit[2])){
                    unordered_map<string, vector<string>> org_id;
                    vector<string> ASes;
                    string id = lineSplit[0];
                    string org = lineSplit[2];
                    org_id[id] = ASes;
                    AS2ORG[org] = org_id; 
                } 
                // for (auto x: lineSplit){
                //     cout << x << " ";
                // }
                // cout << "\n";
            } else if(lineSplit.size() == 6){           // AS fields
                // exit(0);
                if (orgIDExists(lineSplit[3])){
                    // cout << "org exist" << endl;
                    string asn = lineSplit[0];
                    string org_id = lineSplit[3];
                    addAStoORG(asn, org_id);
                }
            }
        }
        for (auto org: AS2ORG){
            cout << "{ "<< org.first << ": ";
            for (auto id: org.second){
                cout << "{ " << id.first << ": <";
                for (auto x: id.second){
                    cout << x << ", ";
                }
                cout << "> }";
            }
            cout << " }\n";
        }

    } else{
        cout << "File not found!" << endl;
    }


    return 0;
}