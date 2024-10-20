#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> tbl;  //Storing hash table
    int size;              
    int cnt;               

    //Next prime numeber finder
    int nextPrime(int n) {
        while (true) {
            bool isPrime = true;
            for (int i = 2; i <= std::sqrt(n); i++) {
                if (n % i == 0) {
                    isPrime = false; 
                    break;
                }
            }
            if (isPrime) return n; 
            n++;
        }
    }

    //Hash function
    int hash(int key) {
        return key % size; //Return the index for the given key
    }

    //Load factor threshold
    void resize() {
        int oldSize = size; 
        size = nextPrime(size * 2); 
        std::vector<int> oldTbl = tbl; 
        tbl = std::vector<int>(size, -1); 
        cnt = 0; 

        
        for (int i = 0; i < oldSize; i++) {
            if (oldTbl[i] != -1) { //Slot occupied check
                insert(oldTbl[i]); //Insert old element
            }
        }
    }

public:
    //Constructor
    HashTable(int initialSize = 11) : size(nextPrime(initialSize)), cnt(0) {
        tbl = std::vector<int>(size, -1); //Initializing the table with -1
    }

    //Insert
    void insert(int key) {
        if (cnt / (float)size > 0.8) { //Load factor check
            resize(); //Resize if load factor>0.8
        }

        int idx = hash(key); //Index
        int i = 0; //Probe counter

        //Quadratic probing
        while (i < size) {
            int probeIdx = (idx + i * i) % size; //next index: h(k)+i^2 mod m

            if (tbl[probeIdx] == -1) { //Empty slot
                tbl[probeIdx] = key; //Insert
                cnt++; //Increment
                return; 
            } else if (tbl[probeIdx] == key) { //Duplicate count
                std::cout << "Duplicate key insertion is not allowed" << std::endl;
                return; 
            }

            i++; 
        }

        std::cout << "Max limit reached for probing" << std::endl; 
    }

    //Remove 
    void remove(int key) {
        int idx = hash(key); //Index of key
        int i = 0; 

        //Quadratic probing
        while (i < size) {
            int probeIdx = (idx + i * i) % size; //Calculate next index

            if (tbl[probeIdx] == -1) { 
                std::cout << "Element not found" << std::endl;
                return; 
            } else if (tbl[probeIdx] == key) { //Key found
                tbl[probeIdx] = -1; //Mark as deleted
                cnt--; //Decrement count
                return; 
            }

            i++; //Increment probe counter
        }

        std::cout << "Element not found" << std::endl; 
    }

    //Search
    int search(int key) {
        int idx = hash(key); //Index for key
        int i = 0; 

        //Quadratic probing
        while (i < size) {
            int probeIdx = (idx + i * i) % size; 

            if (tbl[probeIdx] == -1) { 
                return -1; //Return -1 if not found
            } else if (tbl[probeIdx] == key) { 
                return probeIdx; 
            }

            i++; 
        }

        return -1; //Key not found
    }

    //Print table 
    void printTable() {
        for (int i = 0; i < size; i++) {
            if (tbl[i] == -1) {
                std::cout << "- "; //Print - for empty slots
            } else {
                std::cout << tbl[i] << " "; //Print key for occupied slots
            }
        }
        std::cout << std::endl; 
    }
};

