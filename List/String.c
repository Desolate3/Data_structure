#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAXSIZE 255

typedef struct{
    char ch[MAXSIZE];
    int length;
}String;

//取出子串
bool SubString(String *Sub, String S, int pos, int len){
    if(pos + len -1 > S.length)
        return false;
    for(int i = pos; i < pos + len; i++){
        Sub->ch[i - pos] = S.ch[i - 1];
    }
    Sub->length = len;
    return true;
}

//字符串大小对比
int StrCompare(String S, String T){
    if(S.length == T.length){
        for(int i = 0; i < S.length && i < T.length; i++){
            if(S.ch[i] != T.ch[i]){
                return S.ch[i] - T.ch[i];
            }
        }
    }
    else{
        return S.length - T.length;
    }
    return 0;
}

//在S中查找T的第一个位置
int Index(String S, String T){
    String Sub;
    for(int i = 1; i <= S.length - T.length + 1; i++){
        SubString(&Sub, S, i, T.length);
        if(StrCompare(Sub, T) == 0){
            return i;
        }
    }
    return 0;
}

int main(){
    String S;
    strcpy(S.ch, "abcdefgh");
    S.length = strlen(S.ch);

    String T;
    strcpy(T.ch, "abcdefg");
    T.length = strlen(T.ch);

    int cmp = StrCompare(S, T);
    if(cmp == 0){
        printf("S和T相等\n");
    }
    else if(cmp < 0){
        printf("S小于T\n");
    }
    else{
        printf("S大于T\n");
    }

    int index = Index(S, T);
    if(index != 0){
        printf("T在S中的位置是: %d\n", index);
    }
    else{
        printf("T不在S中\n");
    }

    return 0;
}

