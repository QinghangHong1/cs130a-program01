#include <cstdlib>
#include <iostream>
#include "BloomFilter.h"

using namespace std;
BloomFilter::BloomFilter(int k, int m, string strfn, string intfn){
    this -> k = k;
    this -> m = m;
    bits = new uint64_t;
    *bits = *bits & 0;
    if(strfn == "JenkinsHash"){
        this -> strfn = new JenkinsHash();
    }
    if(strfn == "PearsonHash"){
        this -> strfn = new PearsonHash();
    }else{
        cerr << "Not a valid stringHash" << endl;
        exit(1);
    }
    this -> intfns = new IntegerHash*[k];
    if(intfn == "DivisionHash"){
        for(int i = 0; i < k; i++){
        this -> intfns[i] = new DivisionHash(i, m);
        }
    }else if(intfn == "ReciprocalHash"){
        for(int i = 0; i < k; i++){
            this -> intfns[i] = new ReciprocalHash(i, m);
        }
    }else if(intfn == "SquareRootHash"){
        for(int i = 0; i < k; i++){
            this -> intfns[i] = new SquareRootHash(i, m);
        }
    }else{
        cerr << "Invalid StringHash function" << endl;
        exit(1);
    }
        
}
BloomFilter::~BloomFilter(){
    delete strfn;
    for(int i = 0; i < k; i++){
        delete [](intfns[i]);
    }
    delete []intfns;
    delete bits;
}
void BloomFilter::insert(const string& value){
    uint64_t stringHashValue = strfn ->  hash(value);
    for(int i = 0; i < k; i++){
        *bits = *bits | (1 << intfns[i]-> hash(stringHashValue));
    }

}
bool BloomFilter::lookup(const string& value) const{
    uint64_t stringHashValue = strfn -> hash(value);
    for(int i = 0; i < k; i++){
        uint64_t hashIndex = intfns[i] -> hash(stringHashValue);
        uint64_t bit = 2 ^ hashIndex;
        if((*bits & bit) == 0){
            return false;
        }
    }
    return true;
}