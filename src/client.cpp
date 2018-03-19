#include <iostream>
#include <python2.7/python.h>
#include <stdio.h>
#include "peercoin.cpp"

void begin(){
    std::string input;
    std::cout<<"Welcome to PeerCoin!\nWhat would you like to do?\n";
    std::cin>>input;
    std::cout<<input<<"\n"; 
}

//There will always be a copy of the chain on a client system, so loading the chain is justified
int main(){
    System me;
    me.loadConfig();
    me.loadChain();
    std::cout<<"Welcome to PeerCoin!\n";
    char choice;
    std::string data, more;
    bool quit = false;
    while(!quit){
        std::cout<<"What would you like to do?\n";
        std::cout<<"(r)equest, (s)hare, (j)oin, (u)nshare, (i)nfo, (q)uit\n";
        std::cin>>choice;
        switch(choice){
            case 'r':{
                std::cout<<"Who would you like to request from?\n";
                std::cin>>data;
                me.request(data, "file");
                break;
            }
            case 's':{
                std::cout<<"File to share?\n";
                std::cin>>data;
                me.share(data);
                break;
            }
            case 'j':{
                std::cout<<"Your username?\n";
                std::cin>>data;
                me.join(data);
                break;
            }
            case 'u':{
                std::cout<<"File to unshare.\n";
                std::cin>>data;
                me.unshare(data);
                break;
            }
            case 'i':{
                me.getInfo();
                break;
            }
            case 'q':{
                quit = true;
                break;
            }
            default:{
                std::cout<<"Invalid choice.\n";
                break;
            }
        }
    }
    me.saveChain();
    return 0;
}