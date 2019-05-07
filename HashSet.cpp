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
    
    if(lookup(value)){
        return;
    }
    nitems ++;
    if(nitems / double(nslots) > 0.4){
        rehash();
    }
    uint64_t stringToIntHash = strfn -> hash(value);
    
    uint64_t hashValue = intfn -> hash(stringToIntHash);
    
    while(slots[hashValue] != NULL){
        hashValue = (hashValue + 1) % nslots;
    }
    slots[hashValue] = new string(value);
}
bool HashSet::lookup(const string& value) const{
    // cout << "In lookup" << endl;
    uint64_t stringToIntHash = strfn -> hash(value);
    uint64_t hashValue = intfn -> hash(stringToIntHash);

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
    
    int oldslot = nslots;
    delete intfn;
    nslots = oldslot * 2;
    intfn = new DivisionHash(3,nslots);
    string** oldTable = slots;
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