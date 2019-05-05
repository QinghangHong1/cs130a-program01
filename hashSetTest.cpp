//hashSetTest.cpp
#include "HashSet.h"
#include <iostream>
using namespace std;

int main(){
    HashSet* s = new HashSet();
    for(int i = 0; i < 10; i++){
        s -> insert(to_string(i));
        if(s -> lookup(to_string(i))){
            cout << "successful lookup" << endl;
        }
    }
}
