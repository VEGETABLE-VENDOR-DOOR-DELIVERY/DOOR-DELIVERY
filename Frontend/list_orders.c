// Fully updated list_orders.c using struct
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for an order item
typedef struct {
    char product[50];
    int quantity;
} OrderItem;

int main() {
    printf("Content-type: text/html\n\n");
    printf("<html><body><h2>Customer Orders:</h2><ul>");

    FILE *orders = fopen("orders.txt", "r");
    if (!orders) {
        printf("<li>No orders yet.</li>");
    } else {
        OrderItem item;
        char line[100];
        while (fgets(line, sizeof(line), orders)) {
            sscanf(line, "%49[^,],%d", item.product, &item.quantity);
            printf("<li>%s x %d kg</li>", item.product, item.quantity);
        }
        fclose(orders);
    }

    printf("</ul><a href=\"/admin%%20page.html\">Back to Admin</a></body></html>");
    return 0;
}

