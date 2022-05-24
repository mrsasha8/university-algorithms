#include <iostream>
#include <vector>
#include <random>

struct rationalNumber {
    long long int nominator;
    long long int denominator;
};

class hashTable {
public:
    void insert(rationalNumber key) {insertPrivate(std::to_string(key.nominator) + "/" + std::to_string(key.denominator));}
    bool search(rationalNumber key) {return searchPrivate(std::to_string(key.nominator) + "/" + std::to_string(key.denominator));}
    void remove(rationalNumber key) {removePrivate(std::to_string(key.nominator) + "/" + std::to_string(key.denominator));}
private:
    struct hashTableElement {
        unsigned int a = 0;
        std::string list[127];
    };

    hashTableElement hashTablePrivate[127];

    unsigned int stringHash(std::string x, unsigned int a, unsigned int p) {
        unsigned int h = 0;
        for(int i=0; i<x.size(); i++) h = ((h*a) + x[i]) % p;
        return h;
    }

    void insertPrivate(std::string key) {
        unsigned int fstHash = stringHash(key, 31, 127);
        if(hashTablePrivate[fstHash].a == 0) {
            // random generator
            std::random_device generator;
            std::uniform_int_distribution<int> distribution(1, 500);
            // new secondary hash table
            hashTableElement tempHTElement;
            // initialize hash table
            tempHTElement.a = distribution(generator);
            // calculate hash
            unsigned int scdHash = stringHash(key, tempHTElement.a, 127);
            // insert value
            tempHTElement.list[scdHash] = key;
            // replace old hash table with new one
            hashTablePrivate[fstHash] = std::move(tempHTElement);
            // debug
            //::cout << key << " " << std::to_string(fstHash) << " " << std::to_string(scdHash) << " " << "\n";
        }
        else {
            // calculate hash
            unsigned int scdHash = stringHash(key, hashTablePrivate[fstHash].a, 127);
            // check if there is a value
            if(!hashTablePrivate[fstHash].list[scdHash].empty()) throw std::runtime_error("there is value already");
            // insert value
            hashTablePrivate[fstHash].list[scdHash] = key;
            // debug
            //std::cout << key << " " << std::to_string(fstHash) << " " << std::to_string(scdHash) << " " << "\n";
        }
    }

    bool searchPrivate(std::string key) {
        unsigned int fstHash = stringHash(key, 31, 127);
        std::string tempValue = hashTablePrivate[fstHash].list[stringHash(key, hashTablePrivate[fstHash].a, 127)];
        if(tempValue.empty()) return false;
        else if(tempValue != key) throw std::runtime_error("different value");
        else return true;
    }

    bool removePrivate(std::string key) {
        unsigned int fstHash = stringHash(key, 31, 127);
        unsigned int scdHash = stringHash(key, hashTablePrivate[fstHash].a, 127);
        if(hashTablePrivate[fstHash].list[scdHash].empty()) return false;
        else if(hashTablePrivate[fstHash].list[scdHash] != key) throw std::runtime_error("different value");
        else hashTablePrivate[fstHash].list[scdHash].clear();
        return true;
    }
};

int main() {
    hashTable testHashTable;

    testHashTable.insert(rationalNumber{10, 20});
    testHashTable.insert(rationalNumber{5, 7});
    testHashTable.insert(rationalNumber{17, 3});
    testHashTable.insert(rationalNumber{6, 6});
    testHashTable.insert(rationalNumber{4234234, 87865576789});
    testHashTable.insert(rationalNumber{888, 1});
    testHashTable.insert(rationalNumber{56, 56});
    testHashTable.insert(rationalNumber{434, 767});
    testHashTable.insert(rationalNumber{4892, 654});
    testHashTable.insert(rationalNumber{785446554654655, 34242342342});
    testHashTable.insert(rationalNumber{-10, 103});

    bool test1 = testHashTable.search(rationalNumber{17, 3});
    bool test2 = testHashTable.search(rationalNumber{785446554654655, 34242342342});
    bool test3 = testHashTable.search(rationalNumber{785446554654655, 34242342343});

    testHashTable.remove(rationalNumber{17, 3});
    bool test4 = testHashTable.search(rationalNumber{17, 3});

    return 0;
}
