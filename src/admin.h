#ifndef ADMIN_H
#define ADMIN_H

extern int admin_request;
extern int admin_status;
extern char admin_password[20];
extern int input_password(void);
extern int input_admin(void);
extern int itemdel(char *code, int item_count);
extern int setprice(char *code, int new_price, int item_count);
extern int itemadd(char *code, char *name, int price, int item_count);
extern int restock(char *code, int quantity, int item_count);
extern int setstock(char *code, int quantity, int item_count);

#endif