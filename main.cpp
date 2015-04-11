#include <iostream>
#include <string>
#include <fstream>

#include "cache.h"

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream arquivo ("teste2.txt");
    if(!arquivo.is_open()) { cout << "falha ao abrir o arquivo!"; return -1; }

    string buffer;
    int address, RorW;

    Cache cache;
    cache.alocaCache();

    while(getline(arquivo, buffer)){    // recebe endereço do arquivo
        address = stoi(buffer);

        getline(arquivo, buffer);
        RorW = stoi(buffer);            // recebe flag leitura/escrita

        cache.cache_access(address, RorW);  // acessa a cache
    }
    cout << "hits: " << cache.getHits() << endl;
    cout << "miss: " << cache.getMiss() << endl;

    return 0;
}
