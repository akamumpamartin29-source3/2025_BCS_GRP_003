#include <stdio.h>
#include <stdlib.h>
#include "HeaderFile.h"
#include "Vending.c"

int main() {
    // Initialize the items with struct array
    Item items[5] = {
        {1, "Soda", SODA, 10},
        {2, "Water", WATER, 15},
        {3, "Juice", JUICE, 8},
        {4, "Crisps", CRISPS, 12},
        {5, "Chocolate", CHOCOLATE, 7}
    };

    int item_number;
    int item_quantity;
    int money_paid;
    int total_cost = 0;

    while (1) {
        // Loop continuously until customer decides to EXIT
        display_menu(items, total_cost);
        printf("Enter Item Number (or 0 to Exit): ");

        if (scanf("%d", &item_number) != 1) {
            // Input validation: Clear buffer on non-integer input
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (item_number == 0) {
            break; // Exit the shopping loop to proceed to payment
        }

        // Input validation: Check if item is within the menu range
        if (item_number < 1 || item_number > 5) {
            printf("Invalid item number. Please try again.\n");
            continue;
        }

        // Check if item is in stock
        if (items[item_number - 1].quantity <= 0) {
            printf("Sorry, %s is out of stock!\n", items[item_number - 1].name);
            continue;
        }

        printf("Enter Item Quantity: ");
        if (scanf("%d", &item_quantity) != 1 || item_quantity <= 0) {
            // Input validation: Clear buffer and check for positive quantity
            while (getchar() != '\n');
            printf("Invalid quantity. Please enter a positive number.\n");
            continue;
        }

        // Check if requested quantity is available
        if (item_quantity > items[item_number - 1].quantity) {
            printf("Sorry, only %d %s(s) available. Please enter a smaller quantity.\n",
                   items[item_number - 1].quantity,
                   items[item_number - 1].name);
            continue;
        }

        // Purchase item and update stock
        if (purchase_item(items, item_number, item_quantity)) {
            total_cost += Total_item_cost(item_number, item_quantity);
            printf("Item(s) added. New total is %d UGX.\n", total_cost);
            printf("Stock remaining: %d %s(s)\n\n",
                   items[item_number - 1].quantity,
                   items[item_number - 1].name);
        }
    } // End of item selection loop

    // Payment Processing
    if (total_cost == 0) {
        printf("\nNo items selected. Thank you for using Group 3 vending machine. Goodbye!\n");
        return 0; // Exit if the user selected 0 items
    }

    printf("\n====================================\n");
    printf("TOTAL BILL IS %d UGX\n", total_cost);
    printf("====================================\n");
    printf("Enter your Money: ");

    if (scanf("%d", &money_paid) != 1 || money_paid <= 0) {
        printf("Invalid input for money. No transaction made.\n");
        return 1;
    }

    // Call Function for final payment and change
    final_transaction(total_cost, money_paid, items);
    printf("\nThank you for using Group 3 vending machine. Goodbye!\n");

    return 0;
}
