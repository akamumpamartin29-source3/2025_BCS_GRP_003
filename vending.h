#ifndef VENDING_H_INCLUDED
#define VENDING_H_INCLUDED

#define SODA 1500
#define WATER 1000
#define JUICE 2000
#define CRISPS 1200
#define CHOCOLATE 2500

// Struct to represent a vending machine item
typedef struct {
    int id;
    char name[20];
    int price;
    int quantity;
} Item;

// Function declarations
int item_price(int item_number);
int Total_item_cost(int item_number, int item_quantity);
void change_output(int change);
void final_transaction(int total_cost, int money_paid, Item items[]);
void display_menu(Item items[], int total_cost);
int purchase_item(Item items[], int item_number, int item_quantity);

#endif // VENDING_H_INCLUDED
