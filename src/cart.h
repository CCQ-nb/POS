#ifndef CART_H
#define CART_H

#define MAX_CART_ITEMS 100

/*购物车*/
typedef struct{
    char code[16];
    char name[32];
    int price;
    int quantity;
} Cart_item;

extern Cart_item cart_items[MAX_CART_ITEMS];
extern int cart_item_count;
extern int cart_item_sub;
extern int create_item_cart(const int item_sub, const int cart_item_sub);
extern int compare_cart_to_item(const int item_sub);
extern int add_cart(char *line, const int item_count);
extern int delete_cart(const char *item_code);
extern int drop(void);

#endif