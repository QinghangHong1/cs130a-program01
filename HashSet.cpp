#include "HashSet.h"
#include <iostream>
#include <cstdlib>
using namespace std;
HashSet::HashSet(){
    nitems = 0;
    nslots = 97;
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
    if(nitems * 2 >= nslots){
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
        cout << value << " not found";
        return false;
    }else if(*slots[hashValue] == value){
        cout << value << " found" << endl;
        return true;
    }else{

        uint64_t newHashValue = (hashValue + 1) % nslots;
        while(slots[newHashValue] != NULL){
            // cout << "Looking at " << newHashValue << "th slot" << endl;
            if(*slots[newHashValue] != value){
                
                newHashValue = (newHashValue + 1) % nslots;
            }else{
                
                return true;
            }
        }
        return false;
    }
}
void HashSet::rehash(){
    string** newTable = new string* [nslots * 2 + 1];
    int newNslots = nslots * 2 + 1;
    for(int i = 0; i < newNslots; i++){
        newTable[i] = NULL;
    }
    for(int i = 0; i < nslots; i++){
        if(slots[i] != NULL){
            string value = *slots[i];
            int stringToIntHash = strfn -> hash(value);
            int hashValue = intfn -> hash(stringToIntHash) % newNslots;
            if(newTable[hashValue] == NULL){
                newTable[hashValue] = new string(value);
            }else{
                int newHashValue = hashValue;
                while(newTable[hashValue] != NULL){
                    newHashValue = (newHashValue + 1) % newNslots ; 
                }
                newTable[newHashValue] = new string(value);
            }
        }
    }
    slots = newTable;
    for(int i = 0; i < nslots; i++){
        if(slots[i] != NULL){
            delete slots[i];
        }
    }
    delete []slots;
    nslots = newNslots;

}