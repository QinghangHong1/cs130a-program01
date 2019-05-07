#include "HashSet.h"
#include <iostream>
#include <cstdlib>
using namespace std;
HashSet::HashSet(){
    nitems = 0;
    nslots = 23;
    intfn = new SquareRootHash(1, nslots);
    strfn = new JenkinsHash();
    slots = new string* [nslots];
    for(int i = 0; i < nslots; i++){
        slots[i] = NULL;
    }
}
HashSet::~HashSet(){
    // cout << "In destructor" << endl;
    delete intfn;
    delete strfn;
    for(int i = 0; i < nslots; i++){
        if(slots[i] != NULL){
            delete slots[i];
        }
    }
    delete []slots;
}
void HashSet::insert(const string& value){
    // cout << "In insert" << endl;
    if(nslots / 2 <= nitems){
        rehash();
    }
   
    uint64_t stringToIntHash = strfn -> hash(value);
    
    uint64_t hashValue = intfn -> hash(stringToIntHash) % nslots;
    if(lookup(value)){
        return;
    }
    nitems ++;

    if(slots[hashValue] == NULL){
        slots[hashValue] = new string(value);
        return;
    }
    while(slots[hashValue] != NULL){
        hashValue = (hashValue + 1) % nslots;
    }
    slots[hashValue] = new string(value);
    // if(slots[hashValue] == NULL){
    //    slots[hashValue] = new string(value);
    // //    cout << "insert " << value << " during the first attempt at " << hashValue << endl;
    // }else{
    //     int newHashValue = hashValue;
    //     while(slots[newHashValue] != NULL){
    //         // cout << "The " << newHashValue << "th slot is taken" << endl;
    //         newHashValue = (newHashValue + 1) % nslots;
    //     }
    //     slots[newHashValue] = new string(value);
    //     // cout <<"Inserting " << value << " at " << newHashValue << "th slot" << endl; 
    // }
    

}
bool HashSet::lookup(const string& value) const{
    // cout << "In lookup" << endl;
    uint64_t stringToIntHash = strfn -> hash(value);
    uint64_t hashValue = intfn -> hash(stringToIntHash) % nslots;

    while(slots[hashValue] != NULL){
        if(*slots[hashValue] == value){
            return true;
        }
        hashValue = (hashValue + 1) % nslots;
    }
    return false;
    
}
void HashSet::rehash(){
    // cout << "In rehash" << endl;
    delete intfn;
    string** oldTable = slots;
    int oldslot = nslots;
    nslots = oldslot * 2 + 1;
    intfn = new SquareRootHash(10,nslots);
    slots = new string* [nslots];
   
    
    // cout << "old nslots = " << nslots << endl;
    // cout << "new nslots = " << newNslots << endl;
    for(int i = 0; i < nslots; i++){
        slots[i] = NULL;
        
    }
    for(int i = 0; i < oldslot; i++){
        if(oldTable[i] != NULL){
            insert(*oldTable[i]);
        }
    }
    for(int i = 0; i < oldslot; i++){
        if(oldTable[i] != NULL){
            delete oldTable[i];
        }
    }
    delete []oldTable;

}