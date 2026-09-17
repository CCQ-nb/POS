#include <stdio.h>
#include <string.h>
#include "catalog.h"
#include "input.h"

int main(){

    int item_count = 0;
    char line[MAX_LINE];

    /*加载初始商品*/
    load_items("data/items.csv", &item_count);

    while(1)
    {
        printf(">");

        /*读取输入*/
        input(line);

        /*处理输入*/
        if (handle(line, item_count) == 1 ){
            break;
        }
        else{
            continue;
        }

    }

    return 0;
}

