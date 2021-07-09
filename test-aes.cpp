#include<iostream>
#include<ncurses.h>
#include<algorithm>
#include<utility>
#include<vector>
#include<string.h>
#include"aes-without-ni.h"

using namespace std;

int main(){
    unsigned char message[] = "Let us encrypt this message using AES!";
    unsigned char key[16] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    };
    
    /* Padding the message if needed*/
    int original_len = strlen((const char*) message);
    int padded_len = ((original_len + 15) / 16) * 16;

    unsigned char* padded_message = new unsigned char[padded_len];

    for(int i=0; i< padded_len; i++){
        if(i >= original_len) padded_message[i] = 0;
        else padded_message[i] = message[i];
    }
    
    /* Encrypting  the padded message*/
    unsigned char expandedKey[176];
    key_expansion(key, expandedKey); // Expand Keys

    for(int i=0; i < padded_len; i+=16){// encrypting 16 byte blocks
        aes_encrypt(padded_message+i, expandedKey);
    }

    cout<<"Encrypted Message: "<<endl;
    for(int i=0; i<padded_len; i++){
        print_hex(padded_message[i]);
        cout<< " ";
    }
    cout<<endl;

    // getch();
    delete[] padded_message;
    return 0;
}