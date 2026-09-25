#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "catalog.h"
#include "input.h"
#include "cart.h"
#include "sales.h"

char admin_password[20] = "admin123";
int admin_request = -1;
int admin_status = -1;

int input_password(void){
    if (admin_request == 0){
        printf("Password:");
    }
    return 0;
}

int input_admin(void){
    if (admin_status == 0){
        printf("admin");
    }
    return 0;
}

/*更新items.csv*/
int update_items_csv(void){

    FILE *fp = fopen("data/items.csv", "w");

    if (fp == NULL){
        printf("Error: cannot open data/items.csv");
        return -1;
    }

    /*写入表头*/
    fprintf(fp, "code,name,price,stock\n");

    for (int i = 0; i < item_count; i ++){
        fprintf(fp, "%s,%s,%d.%02d,%d\n", 
                items[i].code,
                items[i].name,
                items[i].price / 100,
                items[i].price % 100,
                items[i].stock);
    }

    fclose(fp);
    return 0;
}

/*修改指定商品价格*/
int setprice(char *code, int new_price){
    for (int i = 0; i < item_count; i ++){
        if (strcmp(items[i].code, code) == 0){
            items[i].price = new_price;
        }
    }

    update_items_csv();

    return 0;

}

/*添加一个新商品*/
int itemadd(char *code, char *name, int price){
    
    /*是否已经有该条码*/
    for (int i = 0; i < item_count; i ++){
        if (strcmp(code, items[i].code) == 0){
            printf("Error: Duplicate code %s", code);
            return -1;
        }
    }

    strcpy(items[item_count].code, code);
    strcpy(items[item_count].name, name);
    items[item_count].price = price;
    items[item_count].stock = 0;

    item_count ++;

    update_items_csv();

    return 0;
}

/*删除一个商品*/
int itemdel(char *code){

    int target_item_sub = -1;

    for (int i = 0; i < item_count; i ++){
        if (strcmp(items[i].code, code) == 0){
            target_item_sub = i;
            break;
        }
    }

    if (target_item_sub != -1){
        for (int i = target_item_sub; i < item_count; i ++){
            items[i] = items[i + 1];
        }

        item_count --;
        update_items_csv();

        return 0;

    }

    return -1;
}

/*增加指定商品的库存*/
int restock(char *code, int quantity){

    for (int i = 0; i < item_count; i ++){
        if (strcmp(items[i].code, code) == 0){
            items[i].stock = items[i].stock + quantity;
            update_items_csv();
            
            return 0;
        }
    }

    return -1;
}

/*指定商品的库存*/
int setstock(char *code, int quantity){

    for (int i = 0; i < item_count; i ++){
        if (strcmp(items[i].code, code) == 0){
            items[i].stock = quantity;
            update_items_csv();

            return 0;
        }
    }

    return -1;
}