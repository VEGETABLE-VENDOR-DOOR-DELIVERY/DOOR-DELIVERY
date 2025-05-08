#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100

typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
    int vendorId;
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;

void dummyLoad() {
    strcpy(products[0].name, "Apple"); products[0].price = 10.5; products[0].quantity = 20; products[0].id = 1;
    strcpy(products[1].name, "Banana"); products[1].price = 5.0; products[1].quantity = 50; products[1].id = 2;
    productCount = 2;
}

void listProducts() {
    for (int i = 0; i < productCount; i++) {
        printf("ID: %d, Name: %s, Price: %.2f, Qty: %d\n",
               products[i].id, products[i].name,
               products[i].price, products[i].quantity);
    }
}

int main() {
    dummyLoad();
    listProducts();
    return 0;
}
