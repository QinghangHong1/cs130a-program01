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
    if(nslots / 2 <= nitems){
        rehash();
    }
    uint64_t stringToIntHash = strfn -> hash(value);
    
    uint64_t hashValue = intfn -> hash(stringToIntHash) % nslots;
   
    if(slots[hashValue] == NULL){
       slots[hashValue] = new string(value);
    //    cout << "insert " << value << " during the first attempt at " << hashValue << endl;
    }else{
        int newHashValue = hashValue;
        while(slots[newHashValue] != NULL){
            // cout << "The " << newHashValue << "th slot is taken" << endl;
            newHashValue = (newHashValue + 1) % nslots;
        }
        slots[newHashValue] = new string(value);
        // cout <<"Inserting " << value << " at " << newHashValue << "th slot" << endl; 
    }
    nitems ++;

}
bool HashSet::lookup(const string& value) const{
    uint64_t stringToIntHash = strfn -> hash(value);

    uint64_t hashValue = intfn -> hash(stringToIntHash) % nslots;

    if(slots[hashValue] == NULL){
        // cout << value << " not found";
        return false;
    }else if(*slots[hashValue] == value){
        // cout << value << " found" << endl;
        return true;
    }else{

        uint64_t newHashValue = (hashValue) % nslots;
        while(slots[newHashValue] != NULL){
            // cout << "Looking at " << newHashValue << "th slot" << endl;
            if(*(slots[newHashValue]) != value){
                // cout << "value not matched" << endl;
                newHashValue = (newHashValue + 1) % nslots;
            }else{
                // cout << "matched" << endl;
                return true;
            }
        }
        return false;
    }
}
void HashSet::rehash(){
    // cout << "In rehash" << endl;
    string** newTable = new string* [nslots * 2 + 1];
    int newNslots = nslots * 2 + 1;
    // cout << "old nslots = " << nslots << endl;
    // cout << "new nslots = " << newNslots << endl;
    for(int i = 0; i < newNslots; i++){
        newTable[i] = NULL;
        
    }
    for(int i = 0; i < nslots; i++){
        if(slots[i] != NULL){
            // cout << i <<"th element is " << *slots[i] << endl;
            string value = *slots[i];
            // cout << "The " << i << "th value in the old table is " << value << endl;
            uint64_t stringToIntHash = strfn -> hash(value);
            uint64_t hashValue = intfn -> hash(stringToIntHash) % newNslots;
            // cout << "hashValue is " << hashValue << endl;
            if(newTable[hashValue] == NULL){
                newTable[hashValue] = new string(value);
                // cout << "Insert " << *newTable[hashValue] << "at " << hashValue << "th slot in the new table" << endl;
            }else{
                uint64_t newHashValue = hashValue;
                while(newTable[newHashValue] != NULL){
                    // cout << newHashValue << " is taken" << endl;
                    newHashValue = (newHashValue + 1) % newNslots ; 
                    
                }
                newTable[newHashValue] = new string(value);
                // cout << "Inserting " << value << " at " << newHashValue << endl;
            }
        }
    }
    string** temp = slots;
    slots = newTable;
    for(int i = 0; i < nslots; i++){
        if(temp[i] != NULL){
            delete temp[i];
        }
    }
    delete []temp;
    
    nslots = newNslots;

}