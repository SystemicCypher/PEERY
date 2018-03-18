//Implementing the blockchain here
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include "peercoin.cpp"

void genesis(System& x){
    Block parent;
    std::string pHash = "";
    unsigned int blocknum = 0;
    unsigned int tranCount = 1;
    BlockData inside;
    inside.blocknum = blocknum;
    inside.transactionCount = tranCount;
    inside.parentHash = pHash;
    
    x.addNewUser("Deus");

    inside.codex = x.history;
    Block output;
    output.blockHash = x.hash(inside);
    output.data = inside;
    x.chain.push_back(output);
}



int main(){
    System a;
    genesis(a);
    a.join("Austin");
    a.addNewUser("Ryuko");
    a.addNewUser("Chuck");

    a.request("Deus", "nothing");
    a.share("home");


    for( auto x : a.present){
        std::cout<<x.user<<" "<<x.coins<<"\n";
    }
    std::cout<<"\n";
    System b;
    System::duplication(a,b);
    Block newBlock;
    b.personalAddress = "Ryuko";
    b.request("Chuck", "n");
    b.personalAddress = "Chuck";
    b.request("Deus", "o");
    newBlock = b.makeBlock(b.history, b.chain);

    for( auto x : a.present){
        std::cout<<x.user<<" "<<x.coins<<"\n";
    }

    a.addToChain(newBlock);

    std::cout<<"\n";

    for( auto x : a.chain.back().data.codex.back()){
        std::cout<<x.user<<" "<<x.coins<<"\n";
    }
    a.saveConfig();
    a.saveChain();
}