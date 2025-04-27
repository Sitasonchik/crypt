#include "openssl/rsa.h"
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <unistd.h>
#include <iostream>

std::fstream file, file3;

RSA *rsa;

char filename1[] = "decrypted.txt";
char filename2[] = "data.txt";
char filename3[] = "encrypted.txt";

size_t datasize = 0;

int main(){
    rsa = RSA_generate_key(2048,RSA_F4,nullptr,nullptr);

    if(std::filesystem::exists(filename1)){
        remove(filename1);    
    }

    else if(std::filesystem::exists(filename3)){
        remove(filename3);
    }

    file.open(filename1,std::fstream::out); //file decry
    file3.open(filename3,std::fstream::out); //file encry 
    
    auto tru = std::filesystem::exists(filename2);
    if(std::filesystem::exists(filename2)){
        std::ifstream file2(filename2);
        std::string s;

        while(std::getline(file2, s)){
            datasize += sizeof(s);
        }
        file2.clear(); //data
        file2.seekg(0); 
        
        auto datafile = new char[datasize];
        file2.read(datafile, datasize);

        auto out = new unsigned char[4096];
        auto encryptedsize = new int(RSA_public_encrypt(datasize, reinterpret_cast<unsigned char*>(datafile), out, rsa, RSA_PKCS1_PADDING));
        
        file3.write(reinterpret_cast<char*>(out), *encryptedsize); // en

        RSA_public_decrypt(*encryptedsize, out, reinterpret_cast<unsigned char*>(datafile), rsa, RSA_PKCS1_PADDING);

        file.write(datafile, datasize);   //de

        delete [] out;
        delete encryptedsize;
        delete[] datafile; 
        file2.close();
    }
    else{return 1;}

    file3.close();
    file.close();
    RSA_free(rsa);
    return  0;
}




