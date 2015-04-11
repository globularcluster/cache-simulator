#include <math.h>
#include "cache.h"

Cache::Cache(int x, int y, int z) :
    n_sets{x}, b_size{y}, assoc {z} {}

Cache::Cache() {
    n_sets = 1024;
    b_size = 4;
    assoc = 1;
}
Cache::~Cache(){};

void Cache::alocaCache(){

    this->nbits_offset = log2(b_size);
    this->nbits_indice = log2(n_sets);
    this->nbits_tag = 32 - nbits_indice - nbits_offset;
    this->access = this->hits =  this->miss = 0;

    this->Val = new int [n_sets * assoc];
    this->Tag = new int [n_sets * assoc];
    this->Dirty = new int [n_sets * assoc];

    for(int i=0; i<n_sets; i++){
        for (int j=0; j<assoc; j++)
            this->Val[i] = this->Tag[i] = this->Dirty[i] = 0;
    }
}

void Cache::setTag(int l, int c, int n) { this->Tag[l * n_sets + c]=n; }
void Cache::setVal(int l, int c, int n) { this->Val[l * n_sets + c]=n; }
int Cache::getVal(int l, int c) { return ((Val[l * n_sets + c]==1) ? 1 : 0); }
int Cache::getTag(int l, int c) { return Tag[l * n_sets + c]; }


#include <iostream>
#include <bitset>
#include <time.h>
using namespace std;
int Cache::cache_access(int address, int RorW){

    int empty_block = -1;

    access++;
    int indice = (address >> nbits_offset) & ((2^nbits_indice)-1);
    int tag = address >>(nbits_offset + nbits_indice);

        cout    << "address: " << address << " - " <<  (bitset<8>) address << endl
                << "bits_offset: " << " - " << nbits_offset << endl
                << "bits_indice: " << " - " << nbits_indice << endl
                << "bits_tag: " << " - " << nbits_tag << endl
                << "indice: " << indice << " - " <<  (bitset<8>) indice << endl
                << "tag: "  << tag << " - "  <<  (bitset<8>) tag <<endl << endl;

    for (int i=(getAssoc()-1); i>=0; i--)    //percorre as vias da direita para esquerda, para pegar o bloco
    {                                        //vazio mais a a esquerda.
        if (getVal(indice, i) == 1){
            if(getTag(indice, i) == tag){   // HIT!
                hits++;
                return 1;
            }
            else {
                // (miss?) procurar na proximo assoc
            }
        }
        else
            empty_block = i;
    }
    if (empty_block >=0){    // MISS D: , porém, existe bloco vazio em alguma via
        miss++;
        setVal(indice, empty_block, 1);
        setTag(indice, empty_block, tag);
    }
    else {      // MISS D: , coloca tag em algum bloco random
        miss++;
        srand (time(NULL));
        int bloco = rand() % assoc;
        setVal(indice, bloco, 1);
        setTag(indice, bloco, tag);
    }

//    if(getVal(indice)==1) {
//        if(getTag(indice)==tag)    // HIT!
//            hits++;
//        else {      // miss D: (conflito?)
//            miss++;
//            setTag(indice, tag);
//        }

//    } else {        //miss D: (compulsírio (cold start) ?)
//        miss++;
//        setVal(indice, 1);
//        setTag(indice, tag);
//    }
    return 2;
}

