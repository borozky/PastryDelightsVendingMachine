/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_stock.h"

/**
 * vm_stock.c this is the file where you will implement the
 * interface functions for managing the stock list.
 **/

/**
 * Some example functions:
 * create list, free list, create node, free node, insert node, etc...
 */

/**
 * Create new list
 */
List *create_list(void) {
    List *list;

    list = (List *) malloc(sizeof(*list));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->size = 0;
    return list;
}

/**
 * Create Stock node.
 */
Node *create_node(void) {
    Node *node;

    node = (Node *) malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }

    node->data = NULL;
    node->next = NULL;

    return node;
}

/**
 * Gets the last node from the list
 */
Node *get_last_node(List* list) {
    Node *temp;
    temp = list->head;

    if (temp == NULL) {
        return NULL;
    }
    
    while ( temp->next != NULL) {
        temp = temp->next;
    }

    return temp;
}

/**
 * Push the node at the end of the list
 */
Boolean push_node(List *list, Node *node) {
    Node *lastNode;

    /* list and node are required */
    if (list == NULL || node == NULL) {
        return FALSE;
    }

    lastNode = get_last_node(list);

    /* if no elements in the list, 
    the node that will be pushed will be the first node */
    if ( lastNode == NULL ) {
        list->head = node;
    }
    else {
        lastNode->next = node;
    }

    list->size += 1;

    return TRUE;
}

/**
 * Creates a new node at the end of the list
 */
Node *push_new_node(List *list) {
    Boolean isPushed;
    Node *newNode;

    newNode = create_node();
    if (newNode == NULL) {
        return NULL;
    }

    isPushed = push_node(list, newNode);
    if (isPushed == FALSE) {
        return NULL;
    }

    return newNode;
}

/**
 * Add stock item at the end of the list
 */
Boolean add_stock_item(List *list, Stock *stockItem) {
    Node *lastNode;

    if (stockItem == NULL) {
        return FALSE;
    }

    lastNode = push_new_node(list);
    lastNode->data = stockItem;
    return TRUE;
}

/**
 * Gets the stock by stock id
 */
Stock *get_stock_item_by_id (List *list, char id[ID_LEN + NULL_SPACE]) {
    Node *tempNode;
    Stock *currentStock;
    tempNode = list->head;

    while ( tempNode != NULL) {
        currentStock = tempNode->data;

        if ( strcmp(id, currentStock->id) == 0) {
            return currentStock;
        }

        tempNode = tempNode->next;
    }

    return NULL;
}

/**
 * Remove stock item by id
 */
Boolean remove_stock_item_by_id (List *list, char id[ID_LEN + NULL_SPACE]) {
    Node *previousNode;
    Node *currentNode;
    Stock *currentStock;

    previousNode = NULL;
    currentNode = list->head;

    while (currentNode != NULL) {
        currentStock = currentNode->data;

        if ( strcmp(id, currentStock->id) != 0) {
            previousNode = currentNode;
            currentNode = currentNode->next;
            continue;
        }

        /* when we arrive at this point means ID has been found */

        /* if current node is the first node, make the next node the first */
        if (previousNode == NULL) {
            list->head = currentNode->next;
        }
        /* current node is 2nd, 3rd, 4th,... */
        else {
            previousNode->next = currentNode->next;
        }

        list->size -= 1;
        free(currentNode);

        return TRUE;
    }

    return FALSE;
}

Stock *create_stock(char *line) {
    Stock *stock;
    char *token;
    char *priceToken;
    int onHand;
    Price *price;

    /* new stock and new price */
    stock = (Stock *) malloc(sizeof(*stock));

    /* copy strings instead of assigning them  */

    /* ID */
    token = strtok(line, STOCK_DELIM);
    strcpy(stock->id, token);

    /* NAME */
    token = strtok(NULL, STOCK_DELIM);
    strcpy(stock->name, token);

    /* DESCRIPTION */
    token = strtok(NULL, STOCK_DELIM);
    strcpy(stock->desc, token);

    /* PRICE, this token will be split later */
    priceToken = strtok(NULL, STOCK_DELIM);

    /* STOCK ON HAND */
    token = strtok(NULL, STOCK_DELIM);
    onHand = atoi(token);
    stock->onHand = onHand;

    price = (Price *) malloc(sizeof(*price));

    /* dollars */
    token = strtok(priceToken, ".");
    price->dollars = atoi(token);

    /* cents */
    token = strtok(NULL, ".");
    price->cents = atoi(token);

    stock->price = *price;
    free(price);
    

    return stock;
}

/**
 * Gets the next stock id based on number of items in the list
 */
char *next_stock_id(List *list) {
    char *id;
    int last_id_num;
    char *endPointer;

    Node *node = get_last_node(list);
    Stock *stock = node->data;

    last_id_num = strtol(strtok(stock->id, "I"), &endPointer, 10);
    id = (char *) malloc(ID_LEN + NULL_SPACE);
    sprintf(id, "I%04d", last_id_num + 1);
    return id;
}



