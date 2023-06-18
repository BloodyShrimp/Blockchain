# Blockchain
Two simple implementations of blockchain technology using both C++ and Python

The project consists of two classes: Block and Blockchain. The Block class represents an individual block in the blockchain, while the Blockchain class manages the chain of blocks.

Each Block object contains data, a timestamp, a previous hash, a nonce, a difficulty level, and a hash value. The Block class has methods to calculate its hash, mine the block by finding a hash that satisfies the difficulty level, and convert the block to a string representation.

The Blockchain class maintains a list of blocks and has methods to create the genesis block (the first block in the chain), add new blocks to the chain, print the entire blockchain, edit a block's data, delete a block from the chain, verify the validity of the blockchain, and calculate the average mining time.


The main program accepts commands from the user to interact with the blockchain. The available commands include adding a block, filling the chain with a specified number of blocks with random data, printing the blockchain, modifying a block's data, deleting a block from the chain, verifying the blockchain's validity, clearing the console, and exiting the program.
