#include <stdio.h>
#include <string.h>
#include "input.h"
#include "catalog.h"

/*读取用户输入*/
int input(char *line){

    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\r\n")] = '\0';

    return 0;
}

int output_product_iofo(int item_sub, const char *type){

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

    return 0;
}

/*处理用户输入*/
int handle(char *line, int item_count){

    /*检测输入是否有空格*/
    if (strchr(line, ' ') != NULL){

        char *token = strtok(line, " ");
        
        /*输入条码*/
        if (strncmp(token, "0", 1) == 0){
            int item_sub = compare_code(token, item_count);

            if (item_sub == -1){
                printf("Error: code %s not found\n", token);
            }
            else{
                output_product_iofo(item_sub, "code");
            }
        }
        
            for (token = strtok(NULL, " "); token != NULL; token = strtok(NULL, " ")){

                    int item_sub = compare_code(token, item_count);

                    if (item_sub == -1){
                        printf("Error: code %s not found\n", token);
                    }
                    else{
                        output_product_iofo(item_sub, "code");
                    }
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
            int item_sub = compare_code(line, item_count);
            
            if (item_sub == -1){
                printf("Error: code %s not found\n", line);
            }
            else{
                output_product_iofo(item_sub, "code");
            }
        }

        /*输入prices*/
        if (strcmp(line, "prices") == 0){

            printf("Item      No. Pri.\n");
            printf("------------------\n");

            for (int i = 0; i < item_count; i ++){
                output_product_iofo(i, "prices");
            }
        }

    }
    

    return handle_continue;

}