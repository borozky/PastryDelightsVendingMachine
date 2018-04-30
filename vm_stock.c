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

List *create_list(void) {
    List *list;

    list = (List *) malloc(sizeof(list));
    if (list == NULL) {
        return NULL;
    }

    (*list).head = NULL;
    (*list).size = 0;
    return list;
}

Node *create_node(void) {
    Node *node;

    node = (Node *) malloc(sizeof(node));
    if (node == NULL) {
        return NULL;
    }

    (*node).data = NULL;
    (*node).next = NULL;

    return node;
}

Node *get_last_node(List* list) {
    Node *temp;
    temp = (*list).head;

    if (temp == NULL) {
        return NULL;
    }
    
    while ( (*temp).next != NULL) {
        temp = (*temp).next;
    }

    return temp;
}

Boolean push_node(List *list, Node *node) {
    Node *lastNode;

    if (list == NULL || node == NULL) {
        return FALSE;
    }

    lastNode = get_last_node(list);
    /* if has no last node (aka no elements in the list) */
    if ( lastNode == NULL ) {
        (*list).head = node;
    }
    else {
        (*lastNode).next = node;
    }

    (*list).size += 1;

    return TRUE;
}

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

Boolean add_stock_item(List *list, Stock *stockItem) {
    Node *lastNode;

    if (stockItem == NULL) {
        return FALSE;
    }

    lastNode = push_new_node(list);
    (*lastNode).data = stockItem;
    return TRUE;
}

Stock *get_stock_item_by_id (List *list, char id[ID_LEN + NULL_SPACE]) {
    Node *tempNode;
    Stock *currentStock;
    tempNode = (*list).head;

    while ( tempNode != NULL) {
        currentStock = (*tempNode).data;

        if ( strcmp(id, (*currentStock).id) == 0) {
            return currentStock;
        }

        tempNode = (*tempNode).next;
    }

    return NULL;
}

Boolean remove_stock_item_by_id (List *list, char id[ID_LEN + NULL_SPACE]) {
    Node *previousNode;
    Node *currentNode;
    Stock *currentStock;

    previousNode = NULL;
    currentNode = (*list).head;

    while (currentNode != NULL) {
        currentStock = (*currentNode).data;

        if ( strcmp(id, (*currentStock).id) != 0) {
            previousNode = currentNode;
            currentNode = (*currentNode).next;
            continue;
        }

        /* when we arrive at this point means ID has been found */

        /* if current node is the first node */
        if (previousNode == NULL) {
            (*list).head = (*currentNode).next;
        }
        /* current node is 2nd, 3rd, 4th,... */
        else {
            (*previousNode).next = (*currentNode).next;
        }

        (*list).size -= 1;
        free(currentNode);

        return TRUE;
    }

    return FALSE;
}



