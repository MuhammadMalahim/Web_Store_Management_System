#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main()
{
    shopping* store = (shopping*)malloc(sizeof(shopping));
    store->productsCount = 0;
    int totalCapacityOfStore = 1;    
    store->products = (product *) malloc(totalCapacityOfStore*sizeof(product));
    

    shopping* cart = (shopping*)malloc(sizeof(shopping));
    cart->productsCount = 0;
    int totalCapacityOfCart = 1;
    cart->products = (product *) malloc(totalCapacityOfCart*sizeof(product));

    int choice = 0;
    do
    {
        
        printPossibleOperations();

        printf("Enter the choice number (1-6): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            {
                loadWebstore(store, &totalCapacityOfStore);
                break;
            }
        case 2:
            {
                writeWebStore(store);
                break;
            }
        case 3:
            {
                insertToCart(store, cart, &totalCapacityOfCart);
                break;
            }
        case 4:
            {
                printPrice(cart);
                break;
            }
        case 5:
            {
                buyProducts(store, cart, &totalCapacityOfCart);
                break;
            }
        }


    }while( choice != 6);
    
    printf("Thanks for coming! See you soon :) ");

    free(store->products);
    free(store);
    free(cart->products);
    free(cart);
    return 0;    
}
