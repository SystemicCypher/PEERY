#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <vector>
#include "rsa.cpp"
#include "sha.cpp"

struct Transaction{
    std::string receiver;
    std::string sender;
    unsigned int coins;
    char* data;
};

struct State{
    std::string user;
    unsigned int coins;
    
};

struct BlockData{
    unsigned int blocknum;
    std::string parentHash;
    unsigned int transactionCount;
    std::vector<std::vector<State>> codex;
};

struct Block{
    std::string blockHash;
    BlockData data;
};

class System{
public:
//for the user's personal use
    std::string personalAddress;
//The records must be incomplete...
    std::vector<State> present;
    std::vector<std::vector<State>> history;
    
    unsigned int total_coins;
    unsigned int starter_coins;
    
    std::vector<Block> chain;

    System(){
        starter_coins = 10;
        total_coins = present.size() *10;
    }

    static void duplication(System source, System& clone){
        clone.present = source.present;
        clone.chain = source.chain;
        clone.history = source.history;
        clone.total_coins = source.total_coins;
    }

//User-facing functions
    void join(std::string addr){
        State newUser;
        newUser.user = addr;
        personalAddress = addr;
        newUser.coins = starter_coins;
        total_coins += 10;
        present.push_back(newUser);
        history.push_back(present);
    }

    void getPersonalAddr(){
        std::cout<<personalAddress;
    }

    void request(std::string receiveAddr, std::string chosenData){
        Transaction b;
        b.receiver = receiveAddr;
        b.sender = personalAddress;
        b.coins = 5;
        b.data = "";
        history.push_back(updateState(b, present));
    }

    void share(std::string filepath){
        total_coins += 5;
        history.push_back(present);
        for(unsigned i = 0; i < present.size(); i++){
            if(present.at(i).user == personalAddress){
                present.at(i).coins += 5;
            }
        }
        

    }

//Internal functions, users don't touch these
    void updateChain(){

    }

    std::vector<State>  updateState(Transaction tra, std::vector<State>& current){
        std::vector<State> dup(current);
        bool foundRec, foundSen;
        foundSen = false;
        foundRec = false;
        
        if(!validTransaction(tra, current)){
            std::cout<<"Nope. Transaction invalid\n";
            return current;
        }

        for(unsigned i = 0; i < current.size(); i++){
            if(dup.at(i).user == tra.receiver){
                foundRec = true;
                dup.at(i).coins += tra.coins;
                //std::cout<<current.at(i).user<<current.at(i).coins<<"\n";
            }
            else if(dup.at(i).user == tra.sender){
                foundSen = true;
                dup.at(i).coins -= tra.coins;
                //std::cout<<current.at(i).user<<current.at(i).coins<<"\n";
            }
        }

        if(foundSen && foundRec){
            current = dup;
            return dup;
        }
        else{
            return current;
        }

    }
    void addNewUser(std::string addr){
        State newUser;
        newUser.user = addr;
        newUser.coins = starter_coins;
        total_coins += 10;
        present.push_back(newUser);
        history.push_back(present);
    }

    Transaction addTran(std::string sen, std::string rec, unsigned int coin){
        Transaction output;
        output.sender = sen;
        output.receiver = rec;
        output.coins = coin;
        return output;
    }

    Transaction state2tran(std::vector<State> states){

    }


    bool validTransaction(Transaction tra, std::vector<State> state){
        State current_person;
        for(auto person : state){
            if(person.user == tra.sender){
                current_person.user = person.user;
                current_person.coins = person.coins;
            }
        }
        if (tra.sender == tra.receiver){
            return false;
        }
        if (tra.coins > current_person.coins && tra.coins != 0){
            return false;
        }
        else{
            return true;
        }
    }

    Block makeBlock(std::vector<std::vector<State>> codex, std::vector<Block> chain){
        Block parent = chain.back();
        std::string pHash = parent.blockHash;
        unsigned int blocknum = parent.data.blocknum + 1;
        unsigned int tranCount = codex.size();
        BlockData inside;
        inside.blocknum = blocknum;
        inside.transactionCount = tranCount;
        inside.parentHash = pHash;
        inside.codex = codex;
        Block output;
        output.blockHash = hash(inside);
        output.data = inside;
        return output;
    }

    void addToChain(Block newBlock){
        history.erase(history.begin(), history.end());
        for(auto x : newBlock.data.codex){
            history.push_back(x);
        }
        present = history.back();
        chain.push_back(newBlock);
    }


    std::string hash(BlockData d){
        std::string toHash = "";
        toHash += std::to_string(d.blocknum);
        toHash += std::to_string(d.transactionCount);
        toHash += d.parentHash;
        for (auto x : d.codex){
            for (auto y : x){
                toHash += y.user;
                toHash += std::to_string(y.coins);
            }
        }
        int n = toHash.length();
        char hashy[n+1];
        strcpy(hashy, toHash.c_str());

        std::string out = SHA256(hashy);
        return out;
    }

    bool goodHash(Block b){
        std::string expected = hash(b.data);
        if(b.blockHash != expected){
            return false;
        }
        return true;
    }

    bool checkValid(Block b, Block p, State atm){
        unsigned int parentNumber = p.data.blocknum;
        std::string parentHash   = p.blockHash;
        unsigned int blockNumber  = b.data.blocknum;
        bool chk1, chk2, chk3, chk4;
        chk1 = true;
        chk2 = false;
        chk3 = true;
        chk4 = true;
        for (auto x : b.data.codex){
            //if(validTransaction(x,atm)){
            //    chk1 = true;
            //}
            chk2 = goodHash(b);

            if (blockNumber != parentNumber+1){
                chk3 = false;
            }
            if (b.data.parentHash != parentHash){
                chk4 = false;
            }

        }
        if(chk1 == true && chk2 == true && chk3 == true && chk4 == true){
            return true;
        }
        else{
            return false;
        }
    }




};