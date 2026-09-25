#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "catalog.h"
#include "input.h"
#include "cart.h"
#include "sales.h"
#include "admin.h"

int main(){

    char line[MAX_LINE];

    /*加载初始商品*/
    load_items("data/items.csv");

    /*获取当前date*/
    date = load_max_date(); 
    printf("Date: %d\n", date);

    while(1)
    {
        input_admin();

        printf(">");

        input_password();

        /*读取输入*/
        input(line, sizeof(line));

        /*处理输入*/
        if (handle(line) == 1 ){
            break;
        }
        else{
            continue;
        }

    }

    return 0;
}

