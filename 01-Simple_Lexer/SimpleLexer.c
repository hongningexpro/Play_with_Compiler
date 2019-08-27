#include "SimpleLexer.h"

extern Token_Text_Map g_token_text_map_list[];

int initSimpleLexer(pSimpleLexer p_lexer){
    int result;
    if(NULL == p_lexer){
        return -1;
    }
    result = initTokenList(&p_lexer->m_token_list);
    if(result){
        return -1;
    }
    p_lexer->initState = initState;
    p_lexer->tokenize = tokenize;
    p_lexer->dump = dump;
    return 0;
}

void clearSimpleLexer(pSimpleLexer p_lexer){
    if(NULL == p_lexer){
        return;
    }
    clearTokenList(&p_lexer->m_token_list);
    p_lexer->initState = NULL;
    p_lexer->tokenize = NULL;
    p_lexer->dump = NULL;
}

int initState(pSimpleLexer p_lexer, pToken p_token, char ch){
    if(p_token->m_length>0){
        /* 分析完成一个词法， 添加进TokenList */
        addToken(&p_lexer->m_token_list, p_token);
        initToken(p_token);
    }
    if(!ch){
        return Initial;
    }
    enum DfaState newState = Initial;
    if(isAlpha(ch)){
        /* 第一个字符是字母 */
        if('i' == ch){
            /* 如果是i开头可能是int关键字 */
            newState = Id_int1;
        }else{
            newState = Id;
        }
        p_token->m_type = TOKEN_TYPE_ID;
    }else if(isDigit(ch)){
        /* 第一个字符是数字 */
        newState = IntLiteral;
        p_token->m_type = TOKEN_TYPE_INTV;
    }else if(ch == '>'){
        newState = GT;
        p_token->m_type = TOKEN_TYPE_GT;
    }else if(ch == '<'){
        newState = LT;
        p_token->m_type = TOKEN_TYPE_LT;
    }else if(ch == '+'){
        newState = Plus;
        p_token->m_type = TOKEN_TYPE_PLUS;
    }else if(ch == '-'){
        newState = Minus;
        p_token->m_type = TOKEN_TYPE_MINUS;
    }else if(ch == '*'){
        newState = Star;
        p_token->m_type = TOKEN_TYPE_STAR;
    }else if(ch == '/'){
        newState = Slash;
        p_token->m_type = TOKEN_TYPE_SLASH;
    }else if(ch == ';'){
        newState = SemiColon;
        p_token->m_type = TOKEN_TYPE_SEMICOLON;
    }else if(ch == '('){
        newState = LeftParen;
        p_token->m_type = TOKEN_TYPE_LEFTPAREN;
    }else if(ch == ')'){
        newState = RightParen;
        p_token->m_type = TOKEN_TYPE_RIGHTPAREN;
    }else if(ch == '='){
        newState = Assignment;
        p_token->m_type = TOKEN_TYPE_ASSIGNMENT;
    }else{
        /* 不知道的符号 */
        newState  = Initial;
        return newState;
    }
    appendToken(p_token, ch);
    return newState;
}

void tokenize(pSimpleLexer p_lexer, char *code){
    Token token;
    int i;
    char ch;
    enum DfaState state = Initial;
    for(i=0;code[i]!=0;++i){
        ch = code[i];
        switch(state){
        case Initial:
            initToken(&token);
            state = initState(p_lexer, &token, ch);
            break;
        case Id:
            if(isAlpha(ch)||isDigit(ch)){
                appendToken(&token, ch);
            }else{
                state = initState(p_lexer, &token, ch);
            }
            break;
        case GT:
            if(ch == '='){
                token.m_type = TOKEN_TYPE_GE;
                state = GE;
                appendToken(&token, ch);
            }else{
                state = initState(p_lexer, &token, ch);
            }
            break;
        case LT:
            if(ch == '='){
                token.m_type = TOKEN_TYPE_GE;
                state = GE;
                appendToken(&token, ch);
            }else{
                state = initState(p_lexer, &token, ch);
            }
            break;
        case GE:
        case Assignment:
        case Plus:
        case Minus:
        case Star:
        case Slash:
        case SemiColon:
        case LeftParen:
        case RightParen:
            state = initState(p_lexer, &token, ch);
            break;
        case IntLiteral:
            if(isDigit(ch)){
                appendToken(&token, ch);
            }else{
                state = initState(p_lexer, &token, ch);
            }
            break;
        case Id_int1:
            if(ch == 'n'){
                state = Id_int2;
                appendToken(&token, ch);
            }else if(isDigit(ch)||isAlpha(ch)){
                state = Id;
                appendToken(&token, ch);
            }else{
                state = initState(p_lexer, &token, ch);
            }
            break;
        case Id_int2:
            if(ch == 't'){
                state = Id_int3;
                appendToken(&token, ch);
            }else if(isDigit(ch)||isAlpha(ch)){
                state = Id;
                appendToken(&token, ch);
            }else{
                state = initState(p_lexer, &token, ch);
            }
            break;
        case Id_int3:
            if(isBlank(ch)){
                token.m_type = TOKEN_TYPE_INT; 
                state = initState(p_lexer, &token, ch);
            }else{
                state = Id;
                appendToken(&token, ch);
            }
            break;
        default:
            break;
        }
    }
    if(token.m_length>0){
        /* 把最后一个token送入TokenList */
        initState(p_lexer, &token, 0);
    }
}

void dump(pTokenList p_token_list){
    pToken p_current;
    if(NULL==p_token_list||0==p_token_list->m_count){
        printf("没有任何Token信息!\n");
        return;
    }
    for(p_current = p_token_list->p_token;p_current;p_current=p_current->p_next){
        printf("%16s\t%-16s\n", g_token_text_map_list[p_current->m_type].m_text, p_current->m_text);
    }
    
}
