#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <python2.7/python.h>
#include <stdio.h>
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

    std::vector<std::string> filesSharing;

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
        if(personalAddress != ""){
            return;
        }
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
        if(validTransaction(b, present)){
            if (chosenData == "file"){
                FILE* fp;
                fp = fopen("client.py","r");
                Py_Initialize();
                PyRun_AnyFile(fp, "client.py");
                Py_Finalize();
            }
        }
    }

    void share(std::string filepath){
        filesSharing.push_back(filepath);
        saveConfig();
        total_coins += 5;
        history.push_back(present);
        for(unsigned i = 0; i < present.size(); i++){
            if(present.at(i).user == personalAddress){
                present.at(i).coins += 5;
            }
        }
        

    }

    void unshare(std::string filepath){
        for(auto it = filesSharing.begin(); it != filesSharing.end(); ++it){
            if(*it == filepath){
                filesSharing.erase(it);
                break;
            }
        }
        saveConfig();
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

    //Transaction state2tran(std::vector<State> states){

    //}

//checks if a transaction is valid
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

//makes blocks for the chain
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

//Changes total coin count - used when block received
    void totalCoin(std::vector<State> current){
        unsigned newTotal = 0;
        for (auto x : current){
            newTotal += x.coins;
        }
        total_coins = newTotal;
    }

//Adds the received block to chain and updates state
    void addToChain(Block newBlock){
        history.erase(history.begin(), history.end());
        for(auto x : newBlock.data.codex){
            history.push_back(x);
        }
        present = history.back();
        totalCoin(present);
        chain.push_back(newBlock);
    }

//Hasher using SHA
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

//validity checks
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



//File operations
    void saveConfig(){
        std::fstream config;
        config.open("peercoin.config", std::fstream::out);
        config<<"personaladdress: "<<personalAddress<<"\n";
        config<<"filesharelist: {"<<"\n";
        for(auto file : filesSharing){
            config<<file<<"\n";
        }
        config<<"}\n";
        config<<"END";
        config.close();
    }
    void loadConfig(){
        std::fstream config;
        config.open("peercoin.config", std::fstream::in);
        std::string x;
        config>>x;
        config>>x;
        personalAddress = x;
        config>>x;
        config>>x;
        while(x != "}"){
            filesSharing.push_back(x);
            config>>x;
        }
        config.close();
    }

    void saveChain(){
        std::fstream chains;
        chains.open("blocks.chain", std::fstream::out);
        chain.push_back(makeBlock(history, chain));
        chains<<chain.size()<<"\n";
        for(auto block : chain){
            chains<<"Block: "<<block.data.blocknum<<"\n";
            chains<<"Hash: "<<block.blockHash<<"\n";
            chains<<"parentHash: "<<block.data.parentHash<<"\n";
            chains<<"TransactionCnt: "<<block.data.transactionCount<<"\n";
            chains<<"(\n";
            int counter = 0;
            for(auto datas : block.data.codex){
                chains<<"\t"<<counter<<"State: {\n";
                for(auto person : datas){
                    chains<<"\t\t"<<person.user<<" "<<person.coins<<"\n";
                }
                chains<<"\t}\n";
                counter++;
            }
            chains<<")\n";
        }

        chains.close();
    }

    void loadChain(){
        std::fstream chains;
        chains.open("blocks.chain", std::fstream::in);

        std::string values;
        unsigned nums;

        Block l;
        BlockData d;
        std::vector<std::vector<State>> past;
        std::vector<Block> loadedChain;
        State s;
        std::vector<State> txns;
        unsigned limit;
        chains>>limit;
        unsigned counter = 0;
        bool first = true;

        while(counter < limit){
            past.clear();
            chains>>values;     //block
            
            chains>>nums;       //blocknum
            
            d.blocknum = nums;  //stores into data
            chains>>values;     //Hash:
            
            chains>>values;     // ~~~~~~
            
            l.blockHash = values; //stores the blockhash
            chains>>values;       //Parenthash
            
            if(first) {
                d.parentHash = "";
                first = false;
            }
            else{
                chains>>values;       //~~~~
                
                d.parentHash = values;// stores
            }
            chains>>values;       //txn# 
                 
            chains>>nums;        // #
            
            d.transactionCount = nums; //stores #
            chains>>values;      //  (
            
            while(values != ")"){
                txns.clear();
                chains>>values; //states
                
                if(values == ")") break;
                chains>>values; //{}
                
                    while(values != "}"){
                        chains>>values; //user
                        
                        if(values == "}") break;
                        s.user = values;
                        chains>>nums;   // coins
                        
                        s.coins = nums;
                        txns.push_back(s);
                    }
                //chains>>values;
                if(txns.size() > d.transactionCount){
                    int reduce = txns.size() - d.transactionCount;
                    txns.erase(txns.begin(), txns.begin()+reduce);
                }
                past.push_back(txns);
            }
            d.codex = past;
            l.data = d;

            loadedChain.push_back(l);
            counter++;
        }

        chains.close();
        chain = loadedChain;
        history = loadedChain.back().data.codex;
        present = history.back();

    }



};