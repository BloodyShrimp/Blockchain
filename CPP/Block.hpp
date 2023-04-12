#ifndef BLOCK
#define BLOCK
#include <iostream>
#include <ctime>
#include <iomanip>

class Block
{
private:
    // hash of the block
    std::string hash;
    // hash of the previous block
    std::string prevHash;
    // data stored in the block
    std::string data;
    // timestamp of the creation of the block
    time_t timestamp;
    // number used in hashing
    unsigned long long int nonce;
    // numbers of leading zeros in the hash
    int zeros;

public:
    // default constructor
    Block();
    // constructor with parameters
    Block(std::string _data, std::string _prevHash, int zerosAtBeg);
    // generates the hash for the block based on its parameters
    std::string generateHash();
    // generates hashes until it finds one that starts with the number of leading zeros defined in field zeros
    std::string mineBlock();
    // returns the hash of the block
    std::string getHash();
    // returns the hash of the previous block
    std::string getPrevHash();
    // returns data in the block
    std::string getData();
    // returns the timestamp of the block
    time_t getTimestamp();
    // checks whether the hash starts with correct number of zeros
    bool isHashValid(std::string _hash);
    // function to check whether string starts with a given substring
    bool startsWith(std::string mainString, std::string substring);
    // converts int number to hex and returns it as a string
    std::string int_to_hex(unsigned long long int i);
    // prints block
    void printBlock();
    // edits data and rehashes the block (normally illegal)
    void modifyBlock(std::string new_data);
};

#endif // BLOCK
