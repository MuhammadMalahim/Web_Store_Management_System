#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int isMember(char* name, shopping* myShopping){
    for(int i=0; i<myShopping->productsCount;i++)
    {
        int result = strcmp(name, myShopping->products[i].name);
        if( result == 0 )
            return 1;
    }
    return 0;
}

void insertItem(shopping* myShopping, product myProduct, int* totalCapacity){
    //Already Inserted
    if(isMember(myProduct.name, myShopping))
    {
        for(int i=0; i<myShopping->productsCount;i++)
        {
            int result = strcmp(myProduct.name, myShopping->products[i].name);
            if( result == 0 )
                myShopping->products[i].quantity += myProduct.quantity;
        }
        return;
    }

    //Making space, if necessary
    if(myShopping->productsCount == *totalCapacity)
    {
        (*totalCapacity) = (*totalCapacity)*2; 
        product* temp = (product*) realloc(myShopping->products, (*totalCapacity) * sizeof(product));
        if(temp != NULL)
            myShopping->products = temp;
        else
        {
            printf("Memory Reallocation Error");
            return;
        }


    }

    //Inserting the product
    strcpy(myShopping->products[myShopping->productsCount].name, myProduct.name);
    myShopping->products[myShopping->productsCount].price = myProduct.price;
    myShopping->products[myShopping->productsCount].quantity = myProduct.quantity;


    //Increasing total products in myShopping
    myShopping->productsCount++;


}

void printPossibleOperations(){
    printf("--------------------Menu--------------------\n"); 
    printf("1.Load webshop store from a file\n");
    printf("2.Write the content of the store to a file\n");
    printf("3.Insert an item to cart\n");
    printf("4.Get the price of cart\n");
    printf("5.Buy the products\n");
    printf("6.Exit the program\n");
}

void loadWebstore(shopping* store, int* totalCapacityOfStore){
    char nameOfInputFile[50];
    printf("Enter the name of the file with .txt : ");
    scanf("%s", nameOfInputFile);

    FILE* file = fopen(nameOfInputFile, "r");
    
    if(file != NULL)
    {
        product myProduct;
        while(fscanf(file, "%s %d %d", myProduct.name, &myProduct.price, &myProduct.quantity) == 3)
        {
            insertItem(store, myProduct, totalCapacityOfStore);
        }
        
        printf("Successfully loaded webshop store from %s\n", nameOfInputFile);
        
    }
    else
    {
        printf("There was an error while opening %s.\n", nameOfInputFile);
    }
    
    fclose(file);
}

void writeWebStore(shopping* store){
    
    char nameOfOutputFile[50];
    printf("Enter the name of output file: including .txt: ");
    scanf("%s", nameOfOutputFile);
    FILE* file = fopen(nameOfOutputFile, "w");
    for(int i=0; i<store->productsCount; i++)
    {
        fprintf(file, "%s %d %d\n", store->products[i].name, store->products[i].price, store->products[i].quantity );
    }
    fclose(file);
    printf("Sucessfully written the content of the store to %s\n", nameOfOutputFile);
                
}

void insertToCart(shopping* store, shopping* cart, int* totalCapacityOfCart){
    product myProduct;
    printf("Enter the name and quantity of the product to be bought respectively: ");
    scanf("%s %d", myProduct.name, &myProduct.quantity);

    //Product Available?
    if(!isMember(myProduct.name, store))
    {
        printf("Sorry, the product is not available in the store.\n");
        return;
    }

    //Getting the price
    int price;
    for(int i=0; i<store->productsCount;i++)
    {
        int result = strcmp(myProduct.name, store->products[i].name);
        if( result == 0 )
            myProduct.price = store->products[i].price;
    }

    insertItem(cart, myProduct, totalCapacityOfCart);
    printf("%d %ss sucessfully added to cart.\n", myProduct.quantity, myProduct.name);
}

void printPrice(shopping* cart){
    int price = 0;
    for(int i=0; i<cart->productsCount; i++)
    {
    price = price + (cart->products[i].price*cart->products[i].quantity);
    }

    printf("Total price: %d\n", price);

}

void buyProducts(shopping* store, shopping *cart, int* totalCapacityOfCart){
    for(int i=0; i<cart->productsCount; i++)
    {
        for(int j=0; j<store->productsCount;j++)
        {
            int result = strcmp(cart->products[i].name, store->products[j].name);
            if( result == 0 )
            {
                if(cart->products[i].quantity <= store->products[j].quantity)
                {
                    printf("%d %ss bought successfully.\n", cart->products[i].quantity, cart->products[i].name);
                    store->products[j].quantity -= cart->products[i].quantity;
                }
                else
                {
                    int diff = cart->products[i].quantity - store->products[j].quantity;
                    printf("%d %ss are missing.\n", diff, store->products[j].name);
                }
            }

        }
    }

    
    //Resetting Cart
    (*totalCapacityOfCart) = 1;
    cart->productsCount = 0;
    cart->products = (product *) malloc((*totalCapacityOfCart)*sizeof(product));


}
