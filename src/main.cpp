#include <iostream>
#include "rsa.cpp"


int main(){
    RSA x;
    std::pair<unsigned long long,std::pair<unsigned long long,unsigned long long>> keychain = x.generateKeys();
    x.clearFile();
    x.saveKeyToFile(keychain);
    unsigned y = 'a';
    std::cout<<(char)y<<std::endl;
    y = x.enc(y, keychain.second.second, keychain.first);
    std::cout<<(unsigned long long)y<<std::endl;
    y = x.dec(y, keychain.second.first, keychain.first);
    std::cout<<(char)y<<std::endl;
    return 0;

}