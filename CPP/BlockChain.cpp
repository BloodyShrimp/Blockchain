#include "LinkedList.hpp"
#include "Block.hpp"
#include "BlockChain.hpp"

BlockChain::BlockChain(int _complexity)
{
    complexity = _complexity;
    Block genesis = createGenesisBlock();
    chain.push_back(genesis);
}

Block BlockChain::createGenesisBlock()
{
    Block genesis("Genesis", "None", complexity);
    return genesis;
}

void BlockChain::addBlock(std::string data)
{
    std::string prevHash = chain[chain.size() - 1].getHash();
    Block newBlock(data, prevHash, complexity);
    chain.push_back(newBlock);
    chain[chain.size() - 1].printBlock();
}

List<Block> BlockChain::getChain()
{
    return chain;
}

bool BlockChain::isChainValid()
{
    bool is_hash_valid = true;
    bool is_previous_hash_valid = true;
    bool is_block_mined = true;
    bool flag = true;
    std::string previousHash;
    for (int i = 0; i < chain.size(); i++)
    {
        previousHash = i == 0 ? "None" : chain[i - 1].getHash();
        is_hash_valid = chain[i].getHash() == chain[i].generateHash();
        is_previous_hash_valid = previousHash == chain[i].getPrevHash();
        is_block_mined = chain[i].isHashValid(chain[i].getHash());
        flag = is_hash_valid && is_previous_hash_valid && is_block_mined;
        if (!flag)
        {
            break;
        }
    }

    return flag;
}

void BlockChain::printChain()
{
    for (int i = 0; i < chain.size(); i++)
    {
        time_t saveTime = chain[i].getTimestamp();
        std::cout << std::string(30, '=') << std::endl;
        std::cout << "Block nr " << i << std::endl;
        std::cout << std::string(30, '=') << std::endl;
        std::cout << "Data: " << chain[i].getData() << std::endl;
        std::cout << "Timestamp: " << std::put_time(std::localtime(&saveTime), "%Y-%m-%d %H:%M:%S") << std::endl;
        std::cout << "Hash: " << chain[i].getHash() << std::endl;
        std::cout << "Previous hash: " << chain[i].getPrevHash() << std::endl;
        std::cout << "Is block mined? " << std::boolalpha << chain[i].isHashValid(chain[i].getHash()) << std::endl;
        if (i != 0)
        {
            std::cout << "Is block valid? " << std::boolalpha << (chain[i].getPrevHash() == chain[i - 1].getHash()) << std::endl;
        }
    }

    std::cout << std::string(30, '=') << std::endl;
    std::cout << "Is chain valid? " << std::boolalpha << isChainValid() << std::endl;
}

void BlockChain::editBlock(int _index, std::string new_data)
{
    Block *temp = &chain[_index];
    temp->modifyBlock(new_data);
}

void BlockChain::deleteBlock(int _index)
{
    chain.erase(_index);
}

void BlockChain::validateChain()
{
    bool is_chain_valid = true;
    int faulty_index = 0;
    for (int i = 1; i < chain.size(); i++)
    {
        is_chain_valid = chain[i].getPrevHash() == chain[i - 1].getHash();
        if (!is_chain_valid)
        {
            faulty_index = i - 1;
            break;
        }
    }

    time_t saveTime = chain[faulty_index].getTimestamp();
    if (!is_chain_valid)
    {
        std::cout << std::string(30, '=') << std::endl;
        std::cout << "Chain is not valid found modified or missing block at index: " << faulty_index << std::endl;
        std::cout << "Faulty block: " << std::endl;
        std::cout << std::string(30, '=') << std::endl;
        std::cout << "Block nr " << faulty_index << std::endl;
        std::cout << std::string(30, '=') << std::endl;
        std::cout << "Data: " << chain[faulty_index].getData() << std::endl;
        std::cout << "Timestamp: " << std::put_time(std::localtime(&saveTime), "%Y-%m-%d %H:%M:%S") << std::endl;
        std::cout << "Hash: " << chain[faulty_index].getHash() << std::endl;
        std::cout << "Previous hash: " << chain[faulty_index].getPrevHash() << std::endl;
        std::cout << "Is block mined? " << std::boolalpha << chain[faulty_index].isHashValid(chain[faulty_index].getHash()) << std::endl;
    }
    else
    {
        std::cout << "The chain is valid." << std::endl;
    }
}