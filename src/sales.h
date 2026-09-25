#ifndef SALES_H
#define SALES_H

#define ROWS 8    /*sales.csv里的表头列数*/

extern int date;
extern int date_input;
extern char time_str[16];
extern int receipt_id;
extern int set_time(void);
extern int load_max_date(void);
extern int sales_record(char *filename);

#endif