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

//寻找字串--朴素模式匹配算法
int Index2(String S, String T){
    int i = 0;
    int j = 0;
    while(i < S.length && j < T.length){
        if(S.ch[i] ==T.ch[j]){
            i++;
            j++;
        }
        else {
            i = i -j + 1;
            j = 0;
        }
        if(j == T.length){
            return i - j + 1;
        }

    }
    return 0;
}

//寻找子串--KMP算法
int Index_KMP(String S, String T, int next[]){
    int i = 0;
    int j = 0;
    while(i < S.length && j < T.length){
        if(j == -1 || S.ch[i] ==T.ch[j]){
            i++;
            j++;
        }
        else {
            j = next[j];
        }
        if(j == T.length){
            return i - j + 1;
        }
    }
    return 0;
}


int main(){
    String S;
    strcpy(S.ch, "abaacacabaabc");
    S.length = strlen(S.ch);

    String T;
    strcpy(T.ch, "abaabc");
    T.length = strlen(T.ch);

    //KMP算法的next数组
    int next[] = {-1, 0, 0, 1, 1, 2};

    // 测试字符串大小对比函数
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

    // 测试寻找子串函数
    int index = Index_KMP(S, T, next);
    if(index != 0){
        printf("T在S中的位置是: %d\n", index);
    }
    else{
        printf("T不在S中\n");
    }

    return 0;
}

