//
//  Player.c
//  Lab08
//
//  Created by Nikhil Thankasala on 5/20/22.
//
#include <stdio.h>
#include "Player.h"

uint8_t inventory[INVENTORY_SIZE];
int currentItemIndex = 0;

/**
 * Adds the specified item to the player's inventory if the inventory isn't full.
 * @param item The item number to be stored: valid values are 0-255.
 * @return SUCCESS if the item was added, STANDARD_ERRROR if the item couldn't be added.
 */
int AddToInventory(uint8_t item) {
    printf("\nInventory: ");
    if (currentItemIndex >= INVENTORY_SIZE - 1) {
        for (int i = 0; i < INVENTORY_SIZE; i++) {
            printf("\n %u", inventory[i]);
        }
        printf("\n");
        return STANDARD_ERROR;
    }
    else {
        inventory[currentItemIndex] = item;
        currentItemIndex += 1;
        for (int i = 0; i < INVENTORY_SIZE; i++) {
            printf("\n %u", inventory[i]);
        }
        printf("\n");
        return SUCCESS;
    }
}

/**
 * Check if the given item exists in the player's inventory.
 * @param item The number of the item to be searched for: valid values are 0-255.
 * @return SUCCESS if it was found or STANDARD_ERROR if it wasn't.
 */
int FindInInventory(uint8_t item) {
    int len = sizeof(inventory);
    for (int i = 0; i < len; i++) {
        if ((inventory[i] == item) && (inventory[i] != 0)) {
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
    
}
