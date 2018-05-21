/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#ifndef VM_OPTIONS_H
#define VM_OPTIONS_H

#include "vm_stock.h"

#define DEFAULT_STOCK_FILE "stock.dat"
#define DEFAULT_COIN_FILE "coins.dat"
#define STOCK_LINE_SIZE 1024
#define COIN_LINE_SIZE 64


Boolean systemInit(VmSystem * system);
void systemFree(VmSystem * system);
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName);
Boolean loadStock(VmSystem * system, const char * fileName);
Boolean loadCoins(VmSystem * system, const char * fileName);
Boolean saveStock(VmSystem * system);
Boolean saveCoins(VmSystem * system);

void displayItems(VmSystem * system);
void purchaseItem(VmSystem * system);
void saveAndExit(VmSystem * system);
void addItem(VmSystem * system);
void removeItem(VmSystem * system);
void displayCoins(VmSystem * system);
void resetStock(VmSystem * system);
void resetCoins(VmSystem * system);
void abortProgram(VmSystem * system);

/* gets the cent value based on denomination */
int get_cent_value(Denomination denomination);

/* HELPER FUNCTIONS */

int compare_coins(const void *coin1, const void *coin2);
int size_of_longest_stock_name(List *stock_list);
void printStock(Stock *stock, int longest_name_size);
char *get_payment();
Boolean add_payment(int *payments, int payment);
void display_payments(int *payments);
int *get_all_payments(int item_price_in_cents);
int get_total_amount(int *payments);
int *get_coins_change(int change, Coin cash_register[NUM_DENOMS]);
void display_change(int *change);
void add_to_cash_register(VmSystem *vmSystem, int *payment);
void refund(VmSystem *vmSystem, int *payments);

#endif
