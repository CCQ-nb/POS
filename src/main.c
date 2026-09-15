#include <stdio.h>
#include <string.h>
#include <catalog.h>
#include <catalog.c>

int main(){

    int item_count = 0;
    int item_sub;

    while(1)
    {
        printf(">");

        /*加载初始商品*/
        load_items("data/items.csv", &item_count);

        /*读取用户输入*/
        char line[MAX_LINE];
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\r\n")] = '\0';

        /*处理输入*/
        item_sub = compare_code(line);
        if (item_sub == -1){
            printf("Error: code not found");
        }
        else {
            printf("%-10s, %d.%02d\n", 
                   items[item_sub].name,
                   items[item_sub].price / 100,
                   items[item_sub].price % 100);

        }

    }

    return 0;
}

