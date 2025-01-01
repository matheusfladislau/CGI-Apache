#include <ctype.h>

#include "../header/url_enc_dec.h"

char to_hex(char character) {
    static char hex[] = "0123456789abcdef";

    //bitwise AND operator
    return hex[character & 15];
}

char to_dec(char character) {
    if (character >= '0' && character <= '9') {
        //caractere númerico decimal para seu valor correspondente
        return character - '0';
    } 
    //caractere hexadecimal para decimal
    return (character - 'a') + 10;
}

void encode(char *og, char *enc) {
    char *pNew = enc;
    char *pOg  = og;

    while (*pOg) {
        if (isalnum(*pOg) || *pOg == '-' || *pOg == '_' || *pOg == '.' || *pOg == '~') {
            *pNew++ = *pOg;
        } else if (*pOg == ' ') {
            *pNew++ = '+';
        } else {
            *pNew++ = '%'; 
            //bitwise right-shift, mover 4 bits à direita -> num / 2^4 -> num / 16
            *pNew++ = to_hex(*pOg >> 4); 
            //bitwise AND, extrair os últimos 4 bits do número (2^4 - 1) -> 15 -> bits 1111
            *pNew++ = to_hex(*pOg & 15);
        }
        ++pOg;
    }
    *pNew = '\0';
}

void decode(char *enc, char *dec) {
    char *pEnc = enc;
    char *pDec = dec;

    while (*pEnc) {
        if (*pEnc == '%' && pEnc[1] && pEnc[2]) {
            //bitwise left-shift, mover 4 bits à esquerda -> num * 2^4 -> num * 16
            *pDec++ = ((pEnc[1]) << 4) + to_dec(pEnc[2]);
            pEnc += 2;
        } else if (*pEnc == '+') {
            *pDec++ = ' ';
        } else {
            *pDec++ = *pEnc;
        }
        ++pEnc;
    }
    *pDec = '\0';
}
