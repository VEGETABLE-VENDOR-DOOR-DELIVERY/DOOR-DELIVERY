#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sample static price lookup
int get_price(const char *product) {
    if (strcmp(product, "Carrot") == 0) return 30;
    if (strcmp(product, "Tomato") == 0) return 20;
    if (strcmp(product, "Onion") == 0) return 25;
    if (strcmp(product, "Potato") == 0) return 15;
    if (strcmp(product, "Cabbage") == 0) return 35;
    if (strcmp(product, "Brinjal") == 0) return 40;
    return 0;
}

int main() {
    FILE *cart = fopen("cart.txt", "r");

    printf("Content-type: text/html\n\n");
    printf("<html><head><title>Order Summary</title>");
    printf("<link rel='stylesheet' href='../frontend/about_us.css'>"); // use your actual stylesheet
    printf("</head><body background='../frontend/bg.jpg'>");

    printf("<h1>Order Summary</h1>");
    printf("<table border='1'><tr><th>Vegetable</th><th>Quantity</th><th>Price</th><th>Subtotal</th></tr>");

    char line[100];
    char product[50];
    int quantity, price, subtotal, total = 0;

    if (cart) {
        while (fgets(line, sizeof(line), cart)) {
            sscanf(line, "%49[^,],%d", product, &quantity);
            price = get_price(product);
            subtotal = price * quantity;
            total += subtotal;
            printf("<tr><td>%s</td><td>%d</td><td>%d</td><td>%d</td></tr>",
                   product, quantity, price, subtotal);
        }
        fclose(cart);
    } else {
        printf("<tr><td colspan='4'>Cart is empty or missing.</td></tr>");
    }

    printf("</table><h2>Total: %d</h2>", total);
    printf("<form action='../frontend/confirmation.html'>");
    printf("<input type='submit' value='Payment Done' style='padding:10px;margin-top:20px;'>");
    printf("</form>");
    printf("</body></html>");

    return 0;
}

