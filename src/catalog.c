#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalog.h"
#include "input.h"

int item_count = 0;

/*初始化物品数组*/
Item items[MAX_ITEMS];


int load_items(const char *filename){


    FILE *fp = fopen(filename, "r");
    
    if (fp == NULL){
        printf("ERROR: cannot open %s\n", filename);
        return -1;
    }

    char line[MAX_LINE];
    if (fgets(line, sizeof(line), fp) == NULL){
        printf("ERROR: empty file\n");
        return -1;
    } 

    /*读取初始商品信息*/
    while (fgets(line, sizeof(line), fp) != NULL){
        line[strcspn(line, "\r\n")] = '\0';

        char *token = strtok(line, ",");
        if (token == NULL){
            continue;
        }
        strcpy(items[item_count].code, token);

        token = strtok(NULL, ",");
        if (token == NULL){
            continue;
        }
        strcpy(items[item_count].name, token);

        token = strtok(NULL, ",");
        if (token == NULL){
            continue;
        }
        double price_yuan = atof(token);
        int price_fen = (int)(price_yuan * 100 + 0.5);  /*采用整数分的形式储存价格*/
        items[item_count].price = price_fen;

        token = strtok(NULL, ",");
        if (token == NULL){
            continue;
        }
        int current_stock = atoi(token); 
        items[item_count].stock = current_stock;

        (item_count) ++;

    }

    fclose(fp);
    return 0;
}

/*对比用户输入与商品条码，并返回下标，否则返回-1*/
int compare_code(const char *line){
    for (int i = 0; i < item_count; i ++){
        if (strcmp(line, items[i].code) == 0){
            return i;
        }
        
    }
    return -1;
}