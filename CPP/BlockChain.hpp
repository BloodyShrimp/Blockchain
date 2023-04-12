#ifndef BLOCKCHAIN
#define BLOCKCHAIN
#include "LinkedList.hpp"
#include "Block.hpp"

class BlockChain
{
private:
    // method creating the genesis block
    Block createGenesisBlock();
    // list containing the blockchain
    List<Block> chain;
    // number of zeros required at the beggining of the hash
    int complexity;

public:
    // constructor
    BlockChain(int _complexity);
    // method returning the chain
    List<Block> getChain();
    // check whether the blockchain is valid i.e. the hashes are valid and the blocks are mined
    bool isChainValid();
    // add new block
    void addBlock(std::string data);
    // print out the information about the blockchain
    void printChain();
    // edit block's data (normally forbidden)
    void editBlock(int _index, std::string new_data);
    // deletes block (normally forbidden)
    void deleteBlock(int _index);
    // checks if chain is valid and finds faulty block if not
    void validateChain();
};

#endif // BLOCKCHAIN
