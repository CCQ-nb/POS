#include <stdio.h>
#include <string.h>
#include "input.h"
#include "catalog.h"
#include "cart.h"

/*读取用户输入*/
int input(char *line, int size){

    fgets(line, size, stdin);
    line[strcspn(line, "\r\n")] = '\0';

    return 0;
}

int output_product_iofo(int item_sub, int cart_item_sub, const char *type){

    if (strcmp(type, "code") == 0){
        printf("%-10s%d.%02d\n",
            items[item_sub].name,
            items[item_sub].price / 100,
            items[item_sub].price % 100
            );
    }

    if (strcmp(type, "prices") == 0){
        printf("%-10s%s %d.%02d\n",
               items[item_sub].name,
               items[item_sub].code,
               items[item_sub].price / 100,
               items[item_sub].price % 100
              );

    }

    if (strcmp(type, "cart") == 0){

        int amount = cart_items[cart_item_sub].price * cart_items[cart_item_sub].quantity;

        printf("%-10s%d.%02d x%d =%d.%02d\n",
               cart_items[cart_item_sub].name,
               cart_items[cart_item_sub].price / 100,
               cart_items[cart_item_sub].price % 100,
               cart_items[cart_item_sub].quantity,
               amount / 100,
               amount % 100
            );
    }

    if (strcmp(type, "print") == 0){

        int amount = cart_items[cart_item_sub].price * cart_items[cart_item_sub].quantity;

        printf("%-10s%d.%02d x%d =%d.%02d\n",
               cart_items[cart_item_sub].name,
               cart_items[cart_item_sub].price / 100,
               cart_items[cart_item_sub].price % 100,
               cart_items[cart_item_sub].quantity,
               amount / 100,
               amount % 100
            );
        
    }

    return 0;
}

/*处理用户输入*/
int handle(char *line, int item_count){

    /*复制一份line*/
    char buffer[MAX_LINE];
    strcpy(buffer, line);

    /*检测输入是否有空格*/
    if (strchr(line, ' ') != NULL){

        char *token = strtok(line, " ");
        
        /*输入条码*/
        if (strncmp(token, "0", 1) == 0){
            add_cart(buffer, item_count);
        }
    }

    /*没有空格*/
    else {
        /*输入quit/exit*/
        if (strcmp(line, "quit") == 0 || strcmp(line, "exit") == 0){
            return handle_exit;
        }

        /*输入条码*/
        if (strncmp(line, "0", 1) == 0){
            add_cart(buffer, item_count);
        }

        /*输入-条码*/
        if (strncmp(line, "-", 1) == 0){
            const char *code = line + 1;
            delete_cart(code);
        }

        /*输入prices*/
        if (strcmp(line, "prices") == 0){

            printf("Item      No. Pri.\n");
            printf("------------------\n");

            for (int i = 0; i < item_count; i ++){
                output_product_iofo(i, 0, "prices");
            }
        }

        /*输入print*/
        if (strcmp(line, "print") == 0){

            /*定义总价*/
            int total = 0;

            printf("Item      Pri. Qty Amount\n");
            printf("-------------------------\n");

            for (int i = 0; i < cart_item_count; i ++){

                /*总价累加*/
                int amount = cart_items[i].price * cart_items[i].quantity;
                total = total + amount;

                output_product_iofo(0, i, "print");
            }

            printf("-------------------------\n");
            printf("Total               =%d.%02d\n", total / 100, total % 100);

        }

        /*输入drop*/
        if (strcmp(line, "drop") == 0){
            drop();
            printf("Clear cart\n");
        }

        /*输入checkout*/
        if (strcmp(line, "checkout") == 0){

            /*定义总价*/
            int total = 0;

            printf("Item      Pri. Qty Amount\n");
            printf("-------------------------\n");

            for (int i = 0; i < cart_item_count; i ++){

                /*总价累加*/
                int amount = cart_items[i].price * cart_items[i].quantity;
                total = total + amount;

                output_product_iofo(0, i, "print");
            }

            printf("-------------------------\n");
            printf("Total               =%d.%02d\n", total / 100, total % 100);

            drop();

        }

    }
    

    return handle_continue;

}