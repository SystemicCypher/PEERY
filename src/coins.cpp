//Implementing the blockchain here
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <boost/asio.hpp>
#include <boost/array.hpp>
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


    System b;
    System::duplication(a,b);
    Block newBlock;
    b.personalAddress = "Ryuko";
    b.request("Chuck", "n");
    b.personalAddress = "Chuck";
    b.request("Deus", "o");
    newBlock = b.makeBlock(b.history, b.chain);

    a.addToChain(newBlock);

    a.saveConfig();
    a.saveChain();
    System c;
    c.loadChain();
    c.join("DankMeme");
    c.request("Ryuko", "o");
    c.saveChain();
    

    return 0;
}