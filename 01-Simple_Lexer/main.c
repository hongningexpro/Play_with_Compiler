#include "SimpleLexer.h"

int main(int argc, char *argv[]){
    SimpleLexer simple_lexer; 
    char code1[1024], code2[1024], code3[1024];
    memset(code1, 0, 1024);
    memset(code2, 0, 1024);
    memset(code3, 0, 1024);
    memcpy(code1, "age>=45", strlen("age>=45"));
    memcpy(code2, "int age=40", strlen("int age=40"));
    memcpy(code3, "2+3*5", strlen("2+3*5"));
    /*1*/
    initSimpleLexer(&simple_lexer);
    simple_lexer.tokenize(&simple_lexer, code1);
    simple_lexer.dump(&simple_lexer.m_token_list);
    clearSimpleLexer(&simple_lexer);
    printf("================================================\n");
    /*2*/
    initSimpleLexer(&simple_lexer);
    simple_lexer.tokenize(&simple_lexer, code2);
    simple_lexer.dump(&simple_lexer.m_token_list);
    clearSimpleLexer(&simple_lexer);
    printf("================================================\n");
    /*3*/
    initSimpleLexer(&simple_lexer);
    simple_lexer.tokenize(&simple_lexer, code3);
    simple_lexer.dump(&simple_lexer.m_token_list);
    clearSimpleLexer(&simple_lexer);
    return 0;
}
