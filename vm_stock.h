/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#ifndef VM_STOCK_H
#define VM_STOCK_H

#include "vm_coin.h"

/**
 * The default stock level that all new stock should start with and the value
 * to use when restting stock.
 **/
#define DEFAULT_STOCK_LEVEL 20

#define STOCK_DELIM "|"

#endif

List *create_list(void);
Node *create_node(void);
Node *get_last_node(List *list);
Boolean push_node(List *list, Node *node);
Node *push_new_node(List *list);
Boolean add_stock_item(List *list, Stock *stockItem);
Stock *get_stock_item_by_id(List *list, char id[ID_LEN + NULL_SPACE]);
Boolean remove_stock_item_by_id(List *list, char id[ID_LEN + NULL_SPACE]);
Stock *create_stock(char *line);
char *next_stock_id(List *list);

