#include <stdio.h>
#include <string.h>
#define MAX_LINE 256

/*定义结构体*/
typedef struct{
    char code[16];
    char name[32];
    int price;
    int stock;
} Item;

/*初始化商品信息(待分开写)*/


int main(){

    /*读取用户输入*/
    char line[MAX_LINE];
    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\r\n")] = '\0';

    printf("%s\n", line);

    return 0;
}

