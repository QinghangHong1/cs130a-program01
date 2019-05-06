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
        uint64_t intHash = intfns[i]-> hash(stringHashValue);
        uint64_t index = intHash % (m);
        bits[index] = 1;
        // int index = (intHash / 64) % m;
        // int position = index % 64;
        // cout << "beforechange " << bitset<64>(bits[index]) << endl;
        // cout << "setting " << position << "th bit to 1" << endl;
        // bits[index] |= (1 << position);
        // cout << "After change " <<bitset<64>(bits[index]) << endl;
       
    }

}
bool BloomFilter::lookup(const string& value) const{
    uint64_t stringHashValue = strfn -> hash(value);
    for(int i = 0; i < k; i++){
        uint64_t intHash = intfns[i]-> hash(stringHashValue);
        // int index = (intHash / 64) % m;
        // int position = index % 64;
        // if(!(bits[index] & (1 << position))){
        //     return false;
        // }
        uint64_t index = intHash % m; 
        if (bits[index] == 0){
            return false;
        }
        // uint64_t index = intHash % (m * 64);
        // uint64_t digit = index / 64;
        // int numBit = index - digit *  64;
        // cout << "the bit are " << bitset<64>(bits[digit]) << endl;
        // uint64_t a = bits[digit] & (1 << numBit);
        // cout << "Compare bits are " << bitset<64>(a) << endl;
        // if(!a){
        //     return false;
        // }
    }
    return true;
}