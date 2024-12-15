    #ifndef HEADER_H
#define HEADER_H

typedef struct product{
    char name[50];
    int price;
    int quantity;
} product;

typedef struct shopping{
    product* products;
    int productsCount;

} shopping;

int isMember(char* name, shopping* myShopping);
void insertItem(shopping* myShopping, product myProduct, int* totalCapacity);
void printPossibleOperations();
void loadWebstore(shopping* store, int* totalCapacityOfStore);
void writeWebStore(shopping* store);
void insertToCart(shopping* store, shopping* cart, int* totalCapacityOfCart);
void printPrice(shopping* cart);
void buyProducts(shopping* store, shopping *cart, int* totalCapacityOfCart);

#endif
