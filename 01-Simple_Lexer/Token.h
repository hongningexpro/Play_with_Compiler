#ifndef _TOKEN_H_
#define _TOKEN_H_
#include "base.h"

#define     TOKEN_TEXT_MAX_LEN  128

/* 词法标记符 */
#define     TOKEN_TYPE_BASE     0
#define     TOKEN_TYPE_INT          TOKEN_TYPE_BASE+1
#define     TOKEN_TYPE_ID           TOKEN_TYPE_BASE+2
#define     TOKEN_TYPE_GT           TOKEN_TYPE_BASE+3
#define     TOKEN_TYPE_LT           TOKEN_TYPE_BASE+4
#define     TOKEN_TYPE_GE           TOKEN_TYPE_BASE+5
#define     TOKEN_TYPE_IF           TOKEN_TYPE_BASE+6
#define     TOKEN_TYPE_ELSE         TOKEN_TYPE_BASE+7
#define     TOKEN_TYPE_ELIF         TOKEN_TYPE_BASE+8
#define     TOKEN_TYPE_PLUS         TOKEN_TYPE_BASE+9
#define     TOKEN_TYPE_MINUS        TOKEN_TYPE_BASE+10
#define     TOKEN_TYPE_STAR         TOKEN_TYPE_BASE+11
#define     TOKEN_TYPE_SLASH        TOKEN_TYPE_BASE+12
#define     TOKEN_TYPE_INTV         TOKEN_TYPE_BASE+13
#define     TOKEN_TYPE_SEMICOLON    TOKEN_TYPE_BASE+14
#define     TOKEN_TYPE_LEFTPAREN    TOKEN_TYPE_BASE+15
#define     TOKEN_TYPE_RIGHTPAREN   TOKEN_TYPE_BASE+16
#define     TOKEN_TYPE_ASSIGNMENT   TOKEN_TYPE_BASE+17
/* end */

typedef struct _tag_token_text_map{
    uint8       m_type;
    char        m_text[TOKEN_TEXT_MAX_LEN];
}Token_Text_Map;


typedef struct _tag_token{
    char                m_text[TOKEN_TEXT_MAX_LEN];     /* 词语文本名 */
    uint8               m_type;                         /* token类型 */
    uint8               m_index;                        /* 当前text指示位置 */
    uint8               m_length;                       /* 当前Token text长度 */
    struct _tag_token   *p_next;                        /* 指向下一个TokenList */
}Token;
typedef Token*      pToken;

typedef struct _tag_token_list{
    pToken      p_token;        /* Token成员 */
    uint64      m_count;        /* 当前Token数量 */
}TokenList;
typedef TokenList*  pTokenList;

/* 初始化Token */
int initToken(pToken p_token);

/* 往Token中添加字符 */
int appendToken(pToken p_token, char ch);

/* 创建TokenList */
int initTokenList(pTokenList p_token_list);

/* 增加Token */
int addToken(pTokenList p_token_list, pToken p_token);

/* 销毁 */
void clearTokenList(pTokenList p_token_list);

#endif
