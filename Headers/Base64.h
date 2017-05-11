//
// Created by youssef on 11/05/17.
//

#ifndef MYKEYLOGGER_BASE64_H
#define MYKEYLOGGER_BASE64_H
#include<vector>
#include <string>
using namespace std;

namespace Base64{

    string base64Encode(const string);
    const string SALT1= "LM::TB::BB";
    const string SALT2= "_:QWERTYAZERTY";
    const string  SALT3="DoYouMindGettingMeIceCream?";
    const string base64codes="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string encrypt(string s)
    {

        s +=SALT1 +SALT2 +SALT3;
        s = base64Encode(s);
        s.insert(7,SALT1);
        s+=SALT2+SALT1;
        s=base64Encode(s);
        s+= SALT1+SALT3+SALT3;
        s=base64Encode(s);
        return s;
    }
    string base64Encode(const string str)
    {
        string toReturn;
        const unsigned int b63= 0x3F;
        int val=0;
        int bits = -6;

        for(auto c : str)
        {
            val=(val << 8)+c;
            bits+=8;
            while(bits>=0)
            {
                toReturn.push_back(base64codes[(val >> bits) & b63]);
                bits-=6;
            }

        }
        if(bits>-6)
        {
            toReturn.push_back(base64codes[(val<<8) >>(bits+8)&b63]);
        }
        while(toReturn.size() % 4)
        {
            toReturn.push_back(' ');
        }
        return toReturn;
    }
}









#endif //MYKEYLOGGER_BASE64_H
