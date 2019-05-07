#include <cstdlib>
#include <iostream>
#include "BloomFilter.h"

using namespace std;
BloomFilter::BloomFilter(int k, int m, string strfn, string intfn){
    this -> k = k;
    this -> m = m;
    int j = (m / 64) + 1;
    bits = new uint64_t[j];
    for(int i = 0; i < (j); i++){
        bits[i] = uint64_t(0);
    }
    if(strfn == "jenkins"){
        this -> strfn = new JenkinsHash();
    }else if(strfn == "pearson"){
        this -> strfn = new PearsonHash();
    }else{
        cerr << "Not a valid stringHash" << endl;
        exit(1);
    }
    this -> intfns = new IntegerHash*[k];
    if(intfn == "division"){
        for(int i = 0; i < k; i++){
        this -> intfns[i] = new DivisionHash(i, m);
        }
    }else if(intfn == "reciprocal"){ 
        for(int i = 0; i < k; i++){
            this -> intfns[i] = new ReciprocalHash(i, m);
        }
    }else if(intfn == "squareroot"){
        for(int i = 0; i < k; i++){
            this -> intfns[i] = new SquareRootHash(i, m);
        }
    }else{
        cerr << "Invalid intHash function" << endl;
        exit(1);
    }
        
}
BloomFilter::~BloomFilter(){
    delete strfn;
    for(int i = 0; i < k; i++){
        delete intfns[i]; 
    }
    delete []intfns;
    delete []bits;
}
void BloomFilter::insert(const string& value){
    uint64_t stringHashValue = strfn ->  hash(value);
    for(int i = 0; i < k; i++){
        uint64_t intHash = intfns[i]-> hash(stringHashValue);
        uint64_t index = (intHash / 64);
        int position = intHash % 64;
        uint64_t one = 1;
        uint64_t k = (one << position);
        bits[index] |= k;
    }
}
bool BloomFilter::lookup(const string& value) const{
    uint64_t stringHashValue = strfn -> hash(value);
    for(int i = 0; i < k; i++){
        uint64_t intHash = intfns[i]-> hash(stringHashValue);
        int index = (intHash / 64);
        int digit = intHash % 64;
        uint64_t temp = bits[index];
        temp >>= digit;
        uint64_t k = 1;
        if((temp & k) == 0){
            return false;
        }

    }
    return true;
}