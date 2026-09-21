#ifndef CATALOG_H
#define CATALOG_H

#define MAX_ITEMS 100

/*定义商品*/
typedef struct{
    char code[16];
    char name[32];
    int price;
    int stock;
} Item;

extern Item items[MAX_ITEMS];
extern int load_items(const char *filename, int *item_count);
extern int compare_code(const char *line, int item_count);

#endif