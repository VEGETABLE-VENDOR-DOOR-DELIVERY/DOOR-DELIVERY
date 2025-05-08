// Fully updated add_to_cart.c using struct
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for a cart item
typedef struct {
    char product[50];
    int quantity;
} CartItem;

int main() {
    char *lenStr = getenv("CONTENT_LENGTH");
    int len = lenStr ? atoi(lenStr) : 0;
    char data[1024] = {0}, product[50] = "";
    int quantity = 0;

    printf("Content-type: text/html\n\n");

    if (len > 0 && len < sizeof(data)) {
        fread(data, 1, len, stdin);
        sscanf(data, "product=%49[^&]&quantity=%d", product, &quantity);

        FILE *f = fopen("cart.txt", "a");
        if (f) {
            CartItem item;
            strcpy(item.product, product);
            item.quantity = quantity;
            fprintf(f, "%s,%d\n", item.product, item.quantity);
            fclose(f);
            printf("<h2>%d kg of %s added to cart!</h2>", item.quantity, item.product);
        } else {
            printf("<h2>Error: Could not open cart.txt</h2>");
        }
    } else {
        printf("<h2>No data received.</h2>");
    }
    printf("<a href=\"/product_list_page.html\">Back to Products</a>");
    return 0;
}

