/**
 * @file bloom.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

 #include "bloom.h"
 #include <algorithm>

BF::BF(uint64_t size, std::vector<hashFunction> hashList){

    // Your code here 
    for(int i=0;i<(int)hashList.size();i++){
        hv.push_back(hashList[i]);
    }
    bv.resize(size);
}

BF::BF(const BF& other){
    // Your code here 
    hv = other.hv;
    bv = other.bv;
}

BF::~BF(){
    return;
}

void BF::add(const int & key){
    // Your code here 
    for(int i=0;i<(int)hv.size();i++){
        int index = (hv[i](key))%(bv.size());
        bv[index] = true;  
    }
}

bool BF::contains(const int& key) const{
    // Your code here 
    for(int i=0;i<(int)hv.size();i++){
        if(bv[hv[i](key)%bv.size()]!=true)return false;
    }
    return true;
}

void BF::bit_union(const BF& other){
    // Your code here 
    int len = (int)bv.size();
    if((int)other.bv.size()<len){
        len = (int)other.bv.size();
    }
    for(int i=0;i<len;i++){
        bv[i] = bv[i] || other.bv[i];
    }
}

void BF::intersect(const BF& other){
    // Your code here 
    int len = (int)bv.size();
    if((int)other.bv.size()<len){
        len = (int)other.bv.size();
    }
    for(int i=0;i<len;i++){
        bv[i] = bv[i] && other.bv[i];
    }
}

float measureFPR(std::vector<int> inList, uint64_t size, std::vector<hashFunction> hashList, unsigned max){
    // Your code here
    float actual_false = (float)max;
    float false_positive = 0;
    BF bf = BF(size, hashList);
    for(int i=0;i<(int)inList.size();i++){
        actual_false--;
        bf.add(inList[i]);
    }
    for(int i=0;i<(int)max;i++){
        if(bf.contains(i) && std::find(inList.begin(),inList.end(),i)==inList.end()){
            false_positive++;
        }
    }

    return false_positive/actual_false;

}

bool getBitFromArray(std::vector<char> bv, int index){
    // Your code here
    int num_char = index/8;
    int i = index%8;
    return getBitFromByte(bv[num_char],i);
}

bool getBitFromByte(char in, int index){
    // Your code here
    return (in >> (7-index)) & 1;

}

