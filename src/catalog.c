#include <stdio.h>
#include <string.h>
#include <catalog.h>

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

    /*读取商品信息*/
    while (fgets(line, sizeof(line), fp) != NULL){
        line[strcspn(line, "\r\n")] = '\0';

    }
        
}