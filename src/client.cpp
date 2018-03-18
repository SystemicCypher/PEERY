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


int main(){
    System me;
    me.loadConfig();
    me.loadChain();
    me.request("DankMeme", "file");
    me.saveChain();
    return 0;
}