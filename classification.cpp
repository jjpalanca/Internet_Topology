#include <bits/stdc++.h>

using namespace std;


int main(int argc, const char * argv[]){

    ifstream myFile;
    myFile.open(argv[1]);
    int transAccCtr = 0;
    int contentCtr = 0;
    int enterpriseCtr = 0;
    
    if (myFile){
        string line;
        while(getline(myFile, line, '\n')){
            size_t pos = 0;
            string delim = "|";
            string token;
            vector<string> lineSplit;
            if (line[0]=='#'){
                continue;
            }
            do{
                pos = line.find(delim);
                token = line.substr(0, pos);
                lineSplit.push_back(token);
                line.erase(0, pos + delim.length());
            } while(pos != string::npos);

            string t1 = "Transit/Access"; 
            string t2 = "Content";
            string t3 = "Enterprise";

            if (lineSplit[2].compare(t1)==0){
                transAccCtr++;
            } else if (lineSplit[2].compare(t2)==0){
                contentCtr++;
            } else if (lineSplit[2].compare(t3)==0){
                enterpriseCtr++;
            } else {
                continue;
            }
        }
        cout << "Transit/Access count: " << transAccCtr << endl;
        cout << "Content count: " << contentCtr << endl;
        cout << "Enterprise count: " << enterpriseCtr++ << endl;
    } else{
        cout << "File does not exist!" << endl;
    }
    

    return 0;
}