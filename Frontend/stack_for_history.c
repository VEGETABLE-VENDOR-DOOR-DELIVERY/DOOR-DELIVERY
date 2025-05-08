#include <stdio.h>
#include <string.h>

#define STACK_SIZE 100

typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
    int vendorId;
} Product;

typedef struct {
    int top;
    Product data[STACK_SIZE];
} ProductStack;

ProductStack viewed = { .top = -1 };

void pushProduct(Product p) {
    if (viewed.top >= STACK_SIZE - 1) {
        printf("Stack overflow!\n");
        return;
    }
    viewed.data[++viewed.top] = p;
}

Product popProduct() {
    if (viewed.top < 0) {
        printf("Stack underflow!\n");
        Product empty = {0};
        return empty;
    }
    return viewed.data[viewed.top--];
}

int main() {
    Product p1 = {1, "Tomato", 30.0, 100, 101};
    Product p2 = {2, "Potato", 20.0, 80, 102};

    pushProduct(p1);
    pushProduct(p2);

    Product lastViewed = popProduct();
    printf("Last Viewed Product: %s\n", lastViewed.name);

    return 0;
}

