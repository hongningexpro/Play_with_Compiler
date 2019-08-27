#include "base.h"

int isAlpha(char ch){
    return (ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z');
}

int isDigit(char ch){
    return ch>='0'&&ch<='9';
}

int isBlank(char ch){
    return ch==' '||ch=='\t'||ch=='\n';
}
