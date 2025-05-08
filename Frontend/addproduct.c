#include <stdio.h>
#include <stdlib.h>
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

void addProduct(char name[], float price, int quantity, int vendorId) {
    if (productCount >= MAX_PRODUCTS) {
        printf("Product limit reached.\n");
        return;
    }
    products[productCount].id = productCount + 1;
    strcpy(products[productCount].name, name);
    products[productCount].price = price;
    products[productCount].quantity = quantity;
    products[productCount].vendorId = vendorId;
    productCount++;
    printf("Product added!\n");
}

int main() {
    char name[50];
    float price;
    int quantity, vendorId;

    printf("Enter Vendor ID: ");
    scanf("%d", &vendorId);
    getchar();

    printf("Enter Product Name: ");
    fgets(name, sizeof(name), stdin); strtok(name, "\n");

    printf("Enter Price: ");
    scanf("%f", &price);

    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    addProduct(name, price, quantity, vendorId);
    return 0;
}
