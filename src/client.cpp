#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
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
    me.request("DankMeme", "Dankenade");
    me.saveChain();
}