#include <stdio.h>
#include <string.h>
#include "vending.h"

int item_price(int item_number) {
    switch (item_number) {
        case 1: return SODA;
        case 2: return WATER;
        case 3: return JUICE;
        case 4: return CRISPS;
        case 5: return CHOCOLATE;
        default: return 0; // invalid item
    }
}

// Function to calculate total cost for item selection
int Total_item_cost(int item_number, int item_quantity) {
    int price = item_price(item_number);
    return price * item_quantity;
}

// Function to purchase an item and update quantities
int purchase_item(Item items[], int item_number, int item_quantity) {
    if (item_number < 1 || item_number > 5) {
        return 0; // Invalid item
    }

    if (items[item_number - 1].quantity <= 0) {
        printf("Sorry, %s is out of stock!\n", items[item_number - 1].name);
        return 0; // Out of stock
    }

    if (item_quantity > items[item_number - 1].quantity) {
        printf("Sorry, only %d %s(s) available in stock.\n",
               items[item_number - 1].quantity,
               items[item_number - 1].name);
        return 0; // Not enough stock
    }

    items[item_number - 1].quantity -= item_quantity;
    return 1; // Successful purchase
}

// Function to calculate and print change
void change_output(int change) {
    if (change <= 0) return; // Exit if no change is due

    printf("\n--- Change Breakdown ---\n");
    if (change >= 50000) {
        printf("50000 x %d\n", change / 50000);
        change = change % 50000;
    }
    if (change >= 20000) {
        printf("20000 x %d\n", change / 20000);
        change = change % 20000;
    }
    if (change >= 10000) {
        printf("10000 x %d\n", change / 10000);
        change = change % 10000;
    }
    if (change >= 5000) {
        printf("5000 x \t%d\n", change / 5000);
        change = change % 5000;
    }
    if (change >= 2000) {
        printf("2000 x \t%d\n", change / 2000);
        change = change % 2000;
    }
    if (change >= 1000) {
        printf("1000 x \t%d\n", change / 1000);
        change = change % 1000;
    }
    if (change >= 500) {
        printf("500 x \t%d\n", change / 500);
        change = change % 500;
    }
    if (change >= 200) {
        printf("200 x \t%d\n", change / 200);
        change = change % 200;
    }
    if (change >= 100) {
        printf("100 x \t%d\n", change / 100);
        change = change % 100;
    }
    if (change >= 50) {
        printf("50 x \t%d\n", change / 50);
        change = change % 50;
    }
}

// Function to display menu with current stock levels
void display_menu(Item items[], int total_cost) {
    printf("====Welcome to C Vending Machine====\n");
    printf("------------------------------------\n");
    for (int i = 0; i < 5; i++) {
        char stock_status[15];
        if (items[i].quantity <= 0) {
            strcpy(stock_status, "[OUT OF STOCK]");
        } else if (items[i].quantity < 5) {
            sprintf(stock_status, "[%d left]", items[i].quantity);
        } else {
            strcpy(stock_status, "");
        }
        printf("%d. %s\t\t -%d UGX %s\n", items[i].id, items[i].name, items[i].price, stock_status);
    }
    printf("\n0. Proceed to Payment/Exit\n");
}

// Function for final transaction
void final_transaction(int total_cost, int money_paid, Item items[]) {
    printf("\n--- Processing Final Payment ---\n");
    printf("Total due: %d UGX\n", total_cost);
    printf("Money paid: %d UGX\n", money_paid);

    if (money_paid >= total_cost) {
        int change = money_paid - total_cost;
        printf("\nTransaction successful! Dispensing items...\n");
        printf("Your change is: %d UGX\n", change);
        change_output(change);
    } else {
        printf("\nInsufficient funds! You need %d more UGX.\n", total_cost - money_paid);
        printf("Returning your %d UGX. Transaction canceled.\n", money_paid);
    }
}
