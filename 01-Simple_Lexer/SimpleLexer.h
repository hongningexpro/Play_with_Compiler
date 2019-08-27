#ifndef _SIMPLE_LEXER_H_
#define _SIMPLE_LEXER_H_
#include "base.h"
#include "Token.h"

enum DfaState{
    Initial=1, 
    If,Id_if1,Id_if2,Else,Id_else1,Id_else2,Id_else3,Id_else4,Int,Id_int1,Id_int2,Id_int3,Id,GT,LT,GE,
    Assignment,
    Plus,Minus,Star,Slash,
    SemiColon,
    LeftParen,
    RightParen,
    IntLiteral
};

typedef struct _Tag_Simple_Lexer{
    TokenList   m_token_list;
    int         (*initState)(struct _Tag_Simple_Lexer*, pToken, char);
    void        (*tokenize)(struct _Tag_Simple_Lexer*, char*);
    void        (*dump)(pTokenList);
}SimpleLexer;
typedef SimpleLexer* pSimpleLexer;

int initSimpleLexer(pSimpleLexer p_lexer);
void clearSimpleLexer(pSimpleLexer p_lexer);

int initState(pSimpleLexer p_lexer, pToken p_token, char ch);

void tokenize(pSimpleLexer p_lexer, char *code);

void dump(pTokenList p_token_list);


#endif
