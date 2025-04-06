/**
 * @file bloom.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

 #include "bloom.h"

BF::BF(uint64_t size, std::vector<hashFunction> hashList){

    // Your code here
    bv.resize(size, false);
    hv = hashList;
}

BF::BF(const BF& other){
    // Your code here 
    bv = other.bv;
    hv = other.hv;
}

BF::~BF(){
    return;
}

void BF::add(const int & key){

    // Your code here 
    int index = 0;
    for (const auto& hash : hv) {
        index = hash(key) % bv.size();
        bv.at(index) = true;
    }
}

bool BF::contains(const int& key) const{
    // Your code here
    int index = 0;
    for (const auto& hash : hv) {
        index = hash(key) % bv.size();
        if (bv.at(index) == false) return false;
    }
    return true;

}

void BF::bit_union(const BF& other){
    // Your code here 
    for (unsigned int i = 0; i < bv.size(); i++) {
        if (other.bv.at(i)) {
            bv.at(i) = true;
        }
    }
}

void BF::intersect(const BF& other){
    // Your code here 
    for (unsigned int i = 0; i < bv.size(); i++) {
        if (bv.at(i) && other.bv.at(i)) {
            bv.at(i) = true;
        } else {
            bv.at(i) = false;
        }
    }
}

float measureFPR(std::vector<int> inList, uint64_t size, std::vector<hashFunction> hashList, unsigned max){
    // Your code here
    BF bloomFilter(size, hashList);
    for (int i : inList) {
        bloomFilter.add(i);
    }

    float falsePositive = 0;
    float trueNegative = 0;

    for (unsigned int i = 0; i < max; i++) {
        if (std::find(inList.begin(), inList.end(), i) == inList.end()) {
            if (bloomFilter.contains(i)) {
                falsePositive++;
            } else {
                trueNegative++;
            }
        }
    }
    return (falsePositive) / (falsePositive + trueNegative);

}

bool getBitFromArray(std::vector<char> bv, int index){
    // Your code here
    int byteIndex = index / 8;
    int bitIndex = index % 8;
    return getBitFromByte(bv[byteIndex], bitIndex);
}

bool getBitFromByte(char in, int index){
    // Your code here
    /*char mask = in << index;
    mask = mask >> 7;
    return (in & mask) != 0;*/
    int shift = int((7 - index) % 8);
    return (in & (1 << shift)) >> shift;
    return (in & (1 << index)) != 0;

}

