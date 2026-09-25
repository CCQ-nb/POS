#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "input.h"
#include "catalog.h"
#include "cart.h"
#include "sales.h"

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

    if (strcmp(type, "sales") == 0){

        printf("Date: %d\n", date_input);
        printf("No.   Time      Items               Ament\n");
        printf("-----------------------------------------\n");

        FILE *fp = fopen("data/sales.csv", "r");

        if (fp == NULL){
            printf("Error: cannot open data/sales.csv\n");
            return -1;
        }

        char line[MAX_LINE];
        if (fgets(line, sizeof(line), fp) == NULL){
            printf("Error: empty file\n");
            return -1;
        }

        char time[9];
        char name[16];
        int quantity = 0;
        int ament = 0;
        int daily = 0;
        int judge = -1;     /*检测流水号是否改变*/
        int receipt_id_current = 1;

        while (fgets(line, sizeof(line), fp) != NULL){

            if (line[0] == '\0'){
                continue;
            }

            if ((line[0] - '0') == date_input){

                int i = 0;

                for (char *token = strtok(line, ","); ; token = strtok(NULL, ",")){
                    
                    if (i == ROWS){
                        break;
                    }

                    /*流水号*/
                    if (i == 1){
                        if (receipt_id_current != atoi(token)){

                            printf("%38d.%02d\n", ament / 100, ament % 100);

                            receipt_id_current = atoi(token);
                            daily = daily + ament;
                            ament = 0;
                            judge = -1;
                        }
                    }
                    /*时间*/
                    if (i == 2){
                        strcpy(time, token);
                    }

                    /*名称*/
                    if (i == 4){
                        strcpy(name, token);
                    }

                    /*数量*/
                    if (i == 6){
                        quantity = atoi(token);
                    }

                    /*单种商品总金额*/
                    if (i == 7){
                        double price = atof(token);
                        int cents = (int)(price * 100 + 0.5);
                        ament = ament + cents;
                    }

                    i ++;
                }

                if (judge == -1){
                    judge = 0;
                    printf("%d   %s  ", receipt_id_current, time);
                    printf("  %s x%d\n", name, quantity);
                }
                else {
                    printf("                %s x%d\n", name, quantity);
                }

            }
        }

        printf("%38d.%02d\n", ament / 100, ament % 100);

        receipt_id_current = 1;
        daily = daily + ament;
        ament = 0;
        judge = -1;

        printf("-----------------------------------------\n");
        printf("Daily: %d.%02d\n", daily / 100, daily % 100);

        fclose(fp);
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

        /*输入sales <date>*/
        if (strcmp(token, "sales") == 0){
            token = strtok(NULL, " ");
            date_input = atoi(token);
            output_product_iofo(0, 0, "sales");
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

            /*将销售记录写入sales.csv中*/
            set_time();
            sales_record("data/sales.csv");
            receipt_id ++;
            


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

        /*输入sales*/
        if (strcmp(line, "sales") == 0){
            date_input = date;
            output_product_iofo(0, 0, "sales");
        }

        /*输入newday*/
        if (strcmp(line, "newday") == 0){
            date ++;
            printf("Newday start\n");
            printf("Date: %d", date);
        }
    }
    

    return handle_continue;

}