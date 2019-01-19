#include <chrono>
#include <thread>
#include <queue>

#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <bitset>
#include <mutex>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <openssl/md5.h>
using namespace std;

/*
g++ -std=c++11 main2.cc -lcrypto -pthread
*/
int numberOfThreads = 8;

int power(int base, int exponent) //cmath pow function doesn't like variables
{
    int ret = 1;
    for(int i = 0; i < exponent; i ++)
    {
        ret = base*ret;
    }
    return ret;
}

void hasher(int threadNumber)
{
    int length = 6;
    // int start = power(26,length)-1;
    int start = 308191348; //zykujk
    for(int num=start-threadNumber; num>=0; num-=numberOfThreads)
	{
        int temp = num;
        char combination[6] = { 'a','b','c','d','e','f' };
        for( int n= 0; n < length; n++) //creates permutation combination
    	{
    		combination[n] = (char) (int('a') + (int)(temp / power(26,length-1-n) ));
    	    temp = temp % power(26,length-1-n);
    	}
    	string password = "";
    	for(int c = 0; c < 6; c++)
        {
            password += combination[c];
        }
        // password = "abcdef";
        
        ///////
       mutex mtx;
       auto start = chrono::high_resolution_clock::now();
       string salt = "hfT7jp2q";
       string prealtsum = password + salt + password;
       string magic = "$1$";
       unsigned char result[16];
       unsigned char result2[16];
       unsigned char result3[16];
       char cry[] = {'.','/','0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
       MD5_CTX context;
       MD5_Init(&context);
       MD5_Update(&context, prealtsum.c_str(), prealtsum.size());
       MD5_Final(result, &context);
       basic_string<unsigned char> altsum;
    
       for (unsigned i = 0; i < 16; i++ ) {
            altsum = altsum + result[i];
       }
       basic_string<unsigned char> preinterm0;
    
       for (int aa = 0; aa < password.size(); aa++) {
           preinterm0 = preinterm0 + static_cast<unsigned char>(password[aa]);
       }
       for (int bb = 0; bb < magic.size(); bb++) {
           preinterm0 = preinterm0 + static_cast<unsigned char>(magic[bb]);
       }
       for (int cc = 0; cc < salt.size(); cc++) {
           preinterm0 = preinterm0 + static_cast<unsigned char>(salt[cc]);
       }
    
       if (password.size() < 16) {
                preinterm0 = preinterm0 + altsum.substr(0,password.size());
       }
       string binary = std::bitset<8>(password.size()).to_string();
       int flag = binary.find('1');
    
    
       for (int k = binary.size() -1; k >= flag ; k--) {
           if (binary[k] == '1') {
               preinterm0 = preinterm0 + static_cast<unsigned char>('\0');
           }
           else {
               preinterm0 = preinterm0 + static_cast<unsigned char>(password[0]);
           }
       }
    
       MD5_CTX context2;
       MD5_Init(&context2);
       MD5_Update(&context2, preinterm0.c_str(), preinterm0.size());
       MD5_Final(result2, &context2);
       basic_string<unsigned char> interm0;
       for (int d = 0; d < 16; d++) {
           interm0 = interm0 + result2[d];
    
       }
    
       MD5_CTX context3;
       basic_string<unsigned char> intermi = interm0;
       basic_string<unsigned char> intermi1;
       for (unsigned s = 0; s <= 999; s++ ) {
           intermi1.clear();
           if (s % 2 == 0) {
               intermi1 = intermi1 + intermi;
           }
            if (s % 2 == 1) {
               for (unsigned bh = 0; bh < password.size();bh++) {
               intermi1 = intermi1 + static_cast<unsigned char>(password[bh]);
               }
           }
           if (s%3 != 0) {
               for (unsigned zh = 0; zh < salt.size();zh++) {
               intermi1 = intermi1 + static_cast<unsigned char>(salt[zh]);
               }
           }
           if (s%7 != 0) {
               for (unsigned jh = 0; jh < password.size();jh++) {
               intermi1 = intermi1 + static_cast<unsigned char>(password[jh]);
               }
           }
           if (s % 2 == 0) {
               for (unsigned qh = 0; qh < password.size();qh++) {
               intermi1 = intermi1 + static_cast<unsigned char>(password[qh]);
               }
           }
            if (s % 2 == 1) {
               intermi1 = intermi1 + intermi;
           }
           MD5_Init(&context3);
           MD5_Update(&context3, intermi1.c_str(), intermi1.size());
           MD5_Final(result3, &context3);
           intermi.clear();
           for (unsigned q = 0; q < 16;q++) {
            intermi = intermi + result3[q];
           }
       }
    
       basic_string<unsigned char> preprefinal;
       string prefinal;
       string final;
       for (int c = 0; c < 16; c ++) {
               preprefinal = preprefinal + intermi[c];
       }
       prefinal = std::bitset<8>(preprefinal[11]).to_string() + std::bitset<8>(preprefinal[4]).to_string() + std::bitset<8>(preprefinal[10]).to_string() + std::bitset<8>(preprefinal[5]).to_string() + std::bitset<8>(preprefinal[3]).to_string() + std::bitset<8>(preprefinal[9]).to_string() + std::bitset<8>(preprefinal[15]).to_string() + std::bitset<8>(preprefinal[2]).to_string() + std::bitset<8>(preprefinal[8]).to_string() +std::bitset<8>(preprefinal[14]).to_string() + std::bitset<8>(preprefinal[1]).to_string() + std::bitset<8>(preprefinal[7]).to_string() + std::bitset<8>(preprefinal[13]).to_string() +std::bitset<8>(preprefinal[0]).to_string() +std::bitset<8>(preprefinal[6]).to_string() + std::bitset<8>(preprefinal[12]).to_string();
    
       for (int y = prefinal.size() -1; y > 1; y -=6) {
           final = final + cry[stoi(prefinal.substr(y-5, 6), NULL , 2)];
       }
       final = final + cry[stoi(prefinal.substr(0,2),NULL,2)];
       
       if (final == "OuCy/cfigw2ZVyQ0bkOOU.") {
            ofstream ofs;
            cout << password << endl;
            ofs.open("finalpassword.txt");
            ofs << password << endl;
            ofs << final << endl;
            ofs.close();
        }
        else if (final == "9TvDSyPgrW9ypSVM4lXCs.")
        {
            cout<<"Example: correct"<<endl;
            // ofs.open("finalpassword.txt");
            // ofs << password << endl;
            // ofs << final << endl;
            // ofs.close();
        }
    
       	auto stop = chrono::high_resolution_clock::now();
       	chrono::duration<double> elapsed = stop - start;
    	mtx.lock();

        cout << threadNumber << "    " <<num<<"   "<<password << "   "<<elapsed.count()<<endl;
    	mtx.unlock();
    
	}
}



int main() {
    int length = 6;
    vector<thread>tharray;
    for(int t = 0; t <numberOfThreads; t++)
    {
        tharray.push_back(thread(hasher,t ));
        
    }
    for(int t = 0; t <numberOfThreads; t++)
    {
        tharray.at(t).join();
        
    }
    cout<<"Threads joined"<<endl;
 
    
    
    // hasher(10);
    

    return 0;
}
