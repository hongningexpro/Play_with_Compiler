#include "Token.h"

Token_Text_Map g_token_text_map_list[] = {
    {TOKEN_TYPE_BASE, ""},
    {TOKEN_TYPE_INT, "Int"}, 
    {TOKEN_TYPE_ID, "Identifier"}, 
    {TOKEN_TYPE_GT, "GT"}, 
    {TOKEN_TYPE_LT, "LT"}, 
    {TOKEN_TYPE_GE, "GE"}, 
    {TOKEN_TYPE_IF, "If"}, 
    {TOKEN_TYPE_ELSE, "Else"}, 
    {TOKEN_TYPE_ELIF, "Elif"}, 
    {TOKEN_TYPE_PLUS, "Plus"}, 
    {TOKEN_TYPE_MINUS, "Minus"}, 
    {TOKEN_TYPE_STAR, "Star"}, 
    {TOKEN_TYPE_SLASH, "Slash"}, 
    {TOKEN_TYPE_INTV, "IntLiteral"}, 
    {TOKEN_TYPE_SEMICOLON, "Semicolon"}, 
    {TOKEN_TYPE_LEFTPAREN, "LeftParen"}, 
    {TOKEN_TYPE_RIGHTPAREN, "RightParen"}, 
    {TOKEN_TYPE_ASSIGNMENT, "Assignment"}
};

int initToken(pToken p_token){
    if(NULL == p_token){
        return -1;
    }
    memset(p_token->m_text, 0, TOKEN_TEXT_MAX_LEN);
    p_token->m_type = TOKEN_TYPE_BASE;
    p_token->m_index = 0;
    p_token->m_length = 0;
    p_token->p_next = NULL;
    return 0;
}

int appendToken(pToken p_token, char ch){
    if(NULL == p_token){
        return -1;
    }
    p_token->m_text[p_token->m_index++] = ch;
    p_token->m_length++;
    return 0;
}

int initTokenList(pTokenList p_token_list){
    if(NULL == p_token_list){
        return -1;
    }
    p_token_list->p_token = NULL;
    p_token_list->m_count = 0;
    return 0;
}

int addToken(pTokenList p_token_list, pToken p_token){
    uint64 count;
    pToken p_before;
    pToken p_current;
    if(NULL == p_token_list||NULL == p_token){
        return -1;
    }

    p_before = p_token_list->p_token;
    p_current = p_before;
    count = p_token_list->m_count;
    while(count--){
       p_before = p_current;
       p_current = p_before->p_next; 
    }
    p_current = (pToken)malloc(sizeof(Token));
    if(NULL == p_current){
        return -1;
    }
    memset(p_current, 0, sizeof(Token));
    memcpy(p_current->m_text, p_token->m_text, p_token->m_length);
    p_current->m_type = p_token->m_type;
    p_current->p_next = NULL;
    p_token_list->m_count++;
    if(1 == p_token_list->m_count){
        /* 如果原本为空 */
        p_token_list->p_token = p_current;
    }else{
        p_before->p_next = p_current;
    }
    return 0;
}

void clearTokenList(pTokenList p_token_list){
    pToken p_current, p_after;
    uint64 count;
    if(NULL==p_token_list||0==p_token_list->m_count){
        return;
    }
    p_current = p_token_list->p_token;
    p_after = p_current->p_next;
    count = p_token_list->m_count;
    while(count--){
        free(p_current);
        if(p_after){
            p_current = p_after;
            p_after = p_current->p_next;
        }
    }
    p_token_list->m_count = 0;
    p_token_list->p_token = NULL;
}

