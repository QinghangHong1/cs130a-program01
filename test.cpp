//test.cpp
#include <iostream>
#include <fstream>
#include "HashSet.h"
using namespace std;
int main(int argc, char* argv[]){
    ifstream ifs;
    if(argc == 1){
        cerr << "Usage: " << argv[0] << " fileName" << endl;
        return 1;
    }
    if(argc == 2){
        ifs.open(argv[1]);
        HashSet* s = new HashSet(); 
        string value;
        while(getline(ifs, value)){
            s -> insert(value);
            if(!s -> lookup(value)){
                cout << "Failed" << endl;
            }
        }
    }
}
