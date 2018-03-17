//TODO:
//Fix random prime breakage
//THAT'S ALL FOLKS!
#include <iostream>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <utility>
#include <map>
#include <vector>


class RSA{
public:
    RSA(){
        srand(time(NULL));
    }

    bool isPrime(unsigned long long p){
    for(unsigned long long i = 2; i < p; i++){
            if (fmod(p,i) == 0){
                return false;
            }
        }
        return true;
    }

    unsigned long long gcd(unsigned long long a, unsigned long long b){
        unsigned long long temp;
        while (true){
            temp = a%b;
            if (temp == 0)
              return b;
            a = b;
            b = temp;
        }
    }

//Found on stackoverflow LCM algorithm
    unsigned long long lcm(unsigned long long a, unsigned long long b){
        unsigned long long temp = gcd(a, b);
        return temp ? (a / temp * b) : 0;
    }

//found on wikipedia Modular Inverse
    unsigned long long modInverse(unsigned long long a, unsigned long long m){
        a = a % m;
        for (unsigned long long x = 1; x < m; x++)
            if ((a*x) % m == 1)
                return x;
        return a;
    }

    unsigned long long powerMod(unsigned long long a, unsigned long long b, unsigned long long m){
        unsigned long long collect = 1;      // Initialize result     
        a = a % m;
        while (b > 0){
            if (b & 1)
                collect = (collect * a) % m;
            b = b>>1;
            a = (a*a) % m;  
        }
        return collect;
    }

    //pairs will be (n, (d,e))
    //e is your  public key
    //d is your private key

    std::pair<unsigned long long,std::pair<unsigned long long, unsigned long long>> generateKeys(){
        unsigned long long p = 79;
        unsigned long long q = 97;



        unsigned long long n = p*q;
        unsigned long long e = 2;
        unsigned long long phi = lcm(p-1,q-1);

        while(e < phi){
            if(gcd(e,phi)==1){
                break;
            }
            else
                e++;
        }

        unsigned long long d = modInverse(e,phi);

        std::pair<unsigned long long,std::pair<unsigned long long,unsigned long long>> output;
        output.first = n;
        output.second.first = d;
        output.second.second = e;
        return output;
    }

    void saveKeyToFile(std::pair<unsigned long long,std::pair<unsigned long long,unsigned long long>> keychain){
        std::ofstream keychainFile;
        keychainFile.open("keychain.dat", std::ofstream::out | std::ofstream::app);
        keychainFile<<"N: "<<keychain.first<<" PRV: "<<keychain.second.first<<" PUB: "<<keychain.second.second<<"\n";
        keychainFile.close();

    }

    void clearFile(){
        std::ofstream keychainFile;
        keychainFile.open("keychain.dat", std::ofstream::out);
        keychainFile.close();
    }

    unsigned long long enc(unsigned long long encryptChar, unsigned long long e, unsigned long long n){
        unsigned long long m = powerMod(encryptChar, e, n);
        return m;
    }

    unsigned long long dec(unsigned long long decryptChar, unsigned long long d, unsigned long long n){
        unsigned long long c = powerMod(decryptChar, d, n);
        return c;
    }

};


