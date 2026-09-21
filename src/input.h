#ifndef INPUT_H
#define INPUT_H

/*定义用户最大输入量*/
#define MAX_LINE 256
#define handle_exit 1
#define handle_continue 0

extern int input(char *line, int size);
extern int handle(char *line, int item_count);
extern int output_product_iofo(int item_sub, int cart_item_sub, const char *type);

#endif