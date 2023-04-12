import time
from hashlib import sha256
import argparse
import os
from statistics import mean
import random


class Block:
    """
    klasa reprezentujaca blok
    """

    def __init__(self, data, previous_hash, difficulty):
        """
        konstruktor bloku
        """
        self.data = data
        self.timestamp = time.time()
        self.previous_hash = previous_hash
        self.nonce = 0
        self.difficulty = difficulty
        self.hash = self.mine_block()

    def calculate_hash(self):
        """
        funkcja obliczajaca hash bloku na podstawie jego danych
        """
        data_string = str(self.data) + str(self.timestamp) + \
            str(self.previous_hash) + str(self.nonce)
        return sha256(data_string.encode()).hexdigest()

    def mine_block(self):
        """
        szuka hashu ktory zgadza sie z zadana trudnoscia blockchainu
        """
        block_hash = self.calculate_hash()

        while not block_hash.startswith('0' * self.difficulty):
            self.nonce += 1
            block_hash = self.calculate_hash()

        return block_hash

    def modify_block(self, new_data):
        """
        modyfikuje dane bloku, normalnie zakazane jedynie w celach
        demonstracyjnych
        """
        self.data = new_data

    def __str__(self):
        """
        konwersja bloku do ladnego stringa
        """
        napis = "Data: {data}\nTimestamp: {timestamp}\nPrevious hash:\n"\
            "{prev_hash}\nHash:\n{hash}\nNonce: {nonce}".format(
            data=self.data, timestamp=time.strftime('%Y-%m-%d %H:%M:%S',
            time.localtime(self.timestamp)), prev_hash=self.previous_hash,
            hash=self.hash, nonce=self.nonce)

        return napis


class Blockchain:
    """
    klasa reprezentujaca blockchain
    """

    def __init__(self, difficulty):
        """
        konstruktor blockchainu
        """
        self.mining_times = []
        self.chain = []
        self.difficulty = difficulty
        self.create_genesis_block()

    def last_block(self):
        """
        zwraca ostatni dodany blok w blockchanie
        """
        return self.chain[-1]

    def create_genesis_block(self):
        """
        tworzy tzw. blok genesis, ktory jest pierwszym blokiem w blockchainie
        """
        start_time = time.time()
        genesis_block = Block("Genesis", "0", self.difficulty)
        end_time = time.time()
        elapsed = end_time - start_time
        self.mining_times.append(elapsed)
        self.chain.append(genesis_block)
        print("Blockchain created\nTime spent on creating genesis block: " +
              str(elapsed) + " s")

    def add_block(self, data):
        """
        kopie i dodaje nowy blok do blockchainu o podanej zawartosci
        """
        previous_hash = self.last_block().hash
        start_time = time.time()
        new_block = Block(data, previous_hash, self.difficulty)
        end_time = time.time()
        elapsed = end_time - start_time
        self.mining_times.append(elapsed)
        self.chain.append(new_block)
        print("=" * 79)
        print("Block added (time spent on mining: " + str(elapsed) + " s)")
        print("=" * 79)
        print(new_block)
        print("=" * 79)

    def print_chain(self):
        """
        wypisuje caly blockchain na wyjscie standardowe
        """
        for i in range(len(self.chain)):
            print("=" * 79)
            print("Block nr: " + str(i))
            print("=" * 79)
            print(self.chain[i])
            print("=" * 79)

    def edit_block(self, index, new_data):
        """
        edytuje dane bloku na podanym indeksie, normalnie zabronione, jedynie do
        demonstracji
        """
        self.chain[index].modify_block(new_data)

    def delete_block(self, index):
        """
        usuwa blok o podanym indeksie, normalnie niedozwolone
        """
        del self.chain[index]

    def is_chain_valid(self):
        """
        skanuje caly blockchain i weryfikuje jego poprawnosc to jest: 1) czy
        bloki sa wykopane, czyli hashe zaczynaja sie od podanej liczby zer 2)
        czy hash kazdego bloku zgadza sie z previous hashem zawartym w kolejnym
        bloku jesli znajdzie podejrzany blok to wypisuje jego zawartosc
        """
        for i in range(0, len(self.chain) - 1):
            flag = (self.chain[i+1].previous_hash ==
                    self.chain[i].calculate_hash()
                    ) and (self.chain[i].hash.startswith('0' * self.difficulty))
            if not flag:
                if(self.chain[i].hash == self.chain[i].calculate_hash()):
                    print("=" * 79)
                    print(
                        "Chain is not valid found missing block at index: "
                        + str(i + 1))
                    print("Adjacent blocks with missing block in between:")
                    print("=" * 79)
                    print(self.chain[i])
                    print("=" * 79)
                    print(self.chain[i+1])
                    print("=" * 79)
                else:
                    print("=" * 79)
                    print(
                        "Chain is not valid found modified block at index: "
                        + str(i))
                    print("=" * 79)
                    print(self.chain[i])
                    print("Actual recalculated hash:\n" +
                          str(self.chain[i].calculate_hash()))
                    print("=" * 79)
                return

        print("Chain is valid.")

    def average_mining_time(self):
        return mean(self.mining_times)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Demonstracja blockchainu.")
    parser.add_argument("difficulty", metavar='difficulty', type=int,
                        help="Trudnosc blockchainu tzn. ilosc zer wymagana na \
                            poczatku kazdego hashu.")
    args = parser.parse_args()

    input_difficulty = args.difficulty

    blockchain = Blockchain(input_difficulty)

    run = True
    while(run):
        command = input(
            "\nPodaj komende:\n"
            "    add <data> - dodaje blok\n"
            "    fill <n> - dodaje n blokow o losowych danych "\
            "(uwaga moze zajac duzo czasu)\n"
            "    print - wyswietla blockchain\n"
            "    modify <index> <data> - edytuj dane w bloku\n"
            "    delete <index> - usun blok\n"
            "    verify - sprawdz czy blockchain jest poprawny\n"
            "    clear - wyczysc konsole\n"
            "    exit - wyjdz z programu\n"
        )

        if(command.split()[0] == "add"):
            blockchain.add_block(str(command.split(maxsplit=1)[1]))
        elif(len(command.split()) == 2 and command.split()[0] == "fill"):
            for i in range(int(command.split()[1])):
                blockchain.add_block(random.randint(0, 1000000))
        elif(len(command.split()) == 1 and command.split()[0] == "print"):
            blockchain.print_chain()
        elif(command.split()[0] == "modify"):
            blockchain.edit_block(int(command.split()[1]), str(
                command.split(maxsplit=2)[2]))
        elif(len(command.split()) == 2 and command.split()[0] == "delete"):
            blockchain.delete_block(int(command.split()[1]))
        elif(len(command.split()) == 1 and command.split()[0] == "verify"):
            blockchain.is_chain_valid()
        elif(len(command.split()) == 1 and command.split()[0] == "clear"):
            os.system("clear")
        elif(len(command.split()) == 1 and command.split()[0] == "exit"):
            print("Koniec\nSredni czas kopania bloku: " +
                  str(blockchain.average_mining_time()) + " s")
            run = False
        else:
            print("Nierozpoznana komenda")
