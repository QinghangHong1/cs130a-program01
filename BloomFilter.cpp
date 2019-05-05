#include <cstdlib>
#include <iostream>
#include <bitset>
#include "BloomFilter.h"

using namespace std;
BloomFilter::BloomFilter(int k, int m, string strfn, string intfn){
    this -> k = k;
    this -> m = m;
    bits = new uint64_t[m];
    for(int i = 0; i < m; i++){
        bits[i] = 0;
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
        int intHash = intfns[i]-> hash(stringHashValue);
        int index = intHash % m;
        // cout << "setting the " << index << "th elements " << digit <<"th"<< "bit to 0" << endl;
        // *bits = *bits | (1 << (index));
        bits[index] = 1;
    }

}
bool BloomFilter::lookup(const string& value) const{
    uint64_t stringHashValue = strfn -> hash(value);
    for(int i = 0; i < k; i++){
        int intHash = intfns[i]-> hash(stringHashValue);
        // cout << "The hash is " << intHash << endl;
        int index = intHash % m;
        // cout << "setting the " << index << "th elements " << digit <<"th"<< "bit to 1" << endl;
        //uint64_t bit = 1 << digit;
        if (bits[index] == 0){
            return false;
        }
        // if((bits[index] & bit) == 0){
        //     return false;
        // }
    }
    return true;
}