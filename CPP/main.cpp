#include "BlockChain.hpp"
using namespace std;

int main()
{
    int complexity;
    cout << "Podaj ilosc zer na poczatku hasha. (od 0 do 15)" << endl;
    cin >> complexity;
    BlockChain blockchain(complexity);
    cout << "Komendy: " << endl;
    cout << "A x - dodaj blok o zawartosci x" << endl;
    cout << "P - wyswietl blockchain" << endl;
    cout << "M i x - edytuj block na indeksie i zmieniajac zawartosc na x (normalnie zabronione)" << endl;
    cout << "D i - usun block na indeksie i (normalnie zabronione)" << endl;
    cout << "V - sprawdz czy blockchain jest poprawny, jezeli nie wypisuje modyfikowany block" << endl;
    cout << "E - wyjdz z programu" << endl;
    char command;
    bool run = true;
    string data;
    int index;
    while (run)
    {
        cin >> command;
        switch (command)
        {
        case 'A':
            std::cin.ignore(1);
            std::getline(std::cin, data);
            blockchain.addBlock(data);
            break;
        case 'P':
            blockchain.printChain();
            break;
        case 'E':
            run = false;
            break;
        case 'M':
            cin >> index;
            std::cin.ignore(1);
            std::getline(std::cin, data);
            blockchain.editBlock(index, data);
            break;
        case 'D':
            cin >> index;
            blockchain.deleteBlock(index);
            break;
        case 'V':
            blockchain.validateChain();
            break;
        }
    }
}