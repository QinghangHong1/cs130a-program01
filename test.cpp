//test.cpp
#include <iostream>
#include <fstream>
#include "HashSet.h"
#include "BloomFilter.h"
using namespace std;
int main(int argc, char* argv[]){
    ifstream ifs;
    if(argc == 1){
        cerr << "Usage: " << argv[0] << " fileName" << endl;
        return 1;
    }
    if(argc == 2){
        ifs.open(argv[1]);
        if(ifs.fail()){
            cerr << "Open file failed" << endl;
        }
        BloomFilter* s = new BloomFilter(10, 15000, "jenkins", "squareroot"); 
        string value;
        while(getline(ifs, value)){
            // cout << "Insert " << value << endl;
            s -> insert(value);
            if(!s -> lookup(value)){
                cout << "Failed 1" << endl;
            }
        }
        ifs.close();
        delete s;
        BloomFilter s1(6,50000, "jenkins", "squareroot");
        for(int i = 0; i < 10000; i ++){
            // cout << "Insert " << i << endl;
            s1.insert(to_string(i));
            if(s1.lookup(to_string(i + 100))){
                cout << "Failed 2" << endl;
            }
            if(i != 0 & !s1.lookup(to_string(i - 1))){
                cout << "Failed 3" << endl;
            }
        }
    }
}
