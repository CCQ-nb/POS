#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "input.h"
#include "catalog.h"
#include "cart.h"

int date = 1;
char time_str[16];
int receipt_id = 1;    /*流水号*/
int date_input = 0;    /*用户输入的指定日期*/

/*获取本地时间*/
int set_time(void){
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", t);

    return 0;
}

/*获得当前date*/
int load_max_date(void) {

    FILE *fp = fopen("data/sales.csv", "r");
    if (fp == NULL) return 0;

    char line[MAX_LINE];
    int max_date = 0;

    /*跳过表头*/
    if (fgets(line, sizeof(line), fp) == NULL) {
        fclose(fp);
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0') continue;

        char *token = strtok(line, ",");
        if (token == NULL) continue;

        int d = atoi(token);
        if (d > max_date) max_date = d;
    }

    fclose(fp);

    return max_date;
}

/*保存销售记录*/
int sales_record(char *filename){

    FILE *fp = fopen(filename, "a");

    if (fp == NULL){
        printf("Error: cannot open %s\n", filename);
    }

    /*检测文件是否为空*/
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    if (size == 0){
        fprintf(fp, "date,receipt_id,time,code,name,price,quantity,amount\n");
    }
    
    for(int i = 0; i < cart_item_count; i ++){

        int amount = cart_items[i].price * cart_items[i].quantity; 

        fprintf(fp, "%d,%d,%s,%s,%s,%d.%02d,%d,%d.%02d\n",
                date, receipt_id, time_str,
                cart_items[i].code,
                cart_items[i].name,
                cart_items[i].price / 100, cart_items[i].price % 100,
                cart_items[i].quantity,
                amount / 100, amount % 100);
    }

    fclose(fp);
    return 0;
    
}