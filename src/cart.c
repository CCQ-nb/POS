#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cart.h" 
#include "catalog.h"
#include "input.h"

int cart_item_count = 0;
int cart_item_sub = 0;
Cart_item cart_items[MAX_CART_ITEMS];

/*创建一个未创建过的Cart_item*/
int create_item_cart(const int item_sub, const int cart_item_sub){
    strcpy(cart_items[cart_item_sub].code, items[item_sub].code);
    strcpy(cart_items[cart_item_sub].name, items[item_sub].name);

    cart_items[cart_item_sub].price = items[item_sub].price;
    cart_items[cart_item_sub].quantity = 1;

    cart_item_count ++;

    return 0;
}

/*按下标删除cart_items里的item*/
int delete_cart_item(int sub){
    for (int i = sub; i < cart_item_count; i ++){
        cart_items[i] = cart_items[i + 1];
    }
    cart_item_count --;

    return 0;
}

/*检测购物车中是否已经有该物品*/
int compare_cart_to_item(const int item_sub){
    
    for(int i = 0; i < cart_item_count; i ++){
        if (strcmp(items[item_sub].code, cart_items[i].code) == 0){
            return i;
        }
    }
    return -1;

}

/*加入购物车*/
int add_cart(char *line, const int item_count){

    /*标记数组，记录本次输入改变了哪些商品，方便后续输出(0:没改变；1:改变)*/
    int change[MAX_ITEMS] = {0};

    for (char *token = strtok(line, " "); token != NULL; token = strtok(NULL, " ")){

        int item_sub = compare_code(token, item_count);

        /*越界处理：输入了没有的条码*/
        if (item_sub == -1){
            printf("Error: code %s not found\n", token);
            continue;
        }

        /*检测库存是否足够*/
        if (check_stock(token, item_count) == 0){

            /*检测购物车中是否已经有该物品*/
            int i = compare_cart_to_item(item_sub);
            if (i != -1){
                cart_items[i].quantity ++;
                change[i] = 1;
            }
            else {
                create_item_cart(item_sub, cart_item_sub);
                change[cart_item_sub] = 1;
                cart_item_sub ++;
            }
        }
        else {
            printf("Stockerror: %s", token);
        }
    }

    /*输出*/
    for(int i = 0; i < cart_item_count; i ++){
        if (change[i] == 1){
            output_product_iofo(0, i, "cart");
        }
    }

    return 0;
}

/*去除购物车中的某商品*/
int delete_cart(const char *item_code){

    /*判断是否成功删除*/
    int judge = -1;
    
    for (int i = 0; i < cart_item_count; i ++){
        if (strcmp(cart_items[i].code, item_code) == 0){
            cart_items[i].quantity --;
            judge ++;
            output_product_iofo(0, i, "cart");

            /*若商品数量为零，则删除*/
            if (cart_items[i].quantity == 0){
                printf("There is no %s in cart now\n", cart_items[i].name);
                delete_cart_item(i);
            }
        }
    }

    if (judge == -1){
        printf("Error: No item %s in cart\n", item_code);
    }
    
    return 0;
}

/*清空cart_items*/
int drop(void){
    cart_item_count = 0;
    cart_item_sub = 0;
    memset(cart_items, 0, sizeof(cart_items));
    return 0;
}

/*检查库存是否足够*/
int check_stock(char *code, int item_count){

    for (int i = 0; i < item_count; i ++){

        if (strcmp(code, items[i].code) == 0){

            /*库存充足*/
            if (items[i].stock != 0){
                items[i].stock --;
                return 0;
            }

            /*库存不足*/
            if (items[i].stock == 0){
                return -1;
            }

        }
    }

    printf("Error: code %s not found", code);
    return -1;
}