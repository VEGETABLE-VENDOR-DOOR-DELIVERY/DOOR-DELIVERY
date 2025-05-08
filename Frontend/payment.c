#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100

struct CartItem {
    char name[50];
    int quantity;
    int price_per_kg;
};

int get_price(const char *name) {
    if (strcmp(name, "Potato") == 0) return 35;
    if (strcmp(name, "Tomato") == 0) return 30;
    if (strcmp(name, "Carrot") == 0) return 50;
    if (strcmp(name, "Garlic") == 0) return 100;
    if (strcmp(name, "Onion") == 0) return 45;
    if (strcmp(name, "Cabbage") == 0) return 40;
    if (strcmp(name, "Cucumber") == 0) return 25;
    if (strcmp(name, "Chilies") == 0) return 60;
    if (strcmp(name, "Spinach") == 0) return 20;
    if (strcmp(name, "Cauliflower") == 0) return 40;
    if (strcmp(name, "Brinjal") == 0) return 30;
    if (strcmp(name, "Mushrooms") == 0) return 80;
    if (strcmp(name, "Radish") == 0) return 25;
    return 0;
}

int main() {
    FILE *file = fopen("cart.txt", "r");
    printf("Content-type: text/html\n\n");

    printf("<html><head><title>Payment Summary</title>");
    printf("<style>"
           "body { font-family: Arial; background-color: #f0f0f0; padding: 20px; }"
           "table { width: 80%%; margin: auto; border-collapse: collapse; background-color: #fff; }"
           "th, td { padding: 10px; border: 1px solid #ccc; text-align: center; }"
           "th { background-color: #007bff; color: white; }"
           ".pay { text-align: center; margin-top: 20px; }"
           ".done-btn { background-color: #28a745; color: white; padding: 10px 20px; text-decoration: none; border-radius: 5px; }"
           "</style></head><body>");
    printf("<h1 style='text-align:center;'>Payment Summary</h1>");

    if (!file) {
        printf("<p style='text-align:center;'>Cart is empty!</p>");
    } else {
        struct CartItem items[MAX_ITEMS];
        int count = 0;
        char name[50];
        int qty;
        int total = 0;

        while (fscanf(file, "%s %d", name, &qty) != EOF && count < MAX_ITEMS) {
            strcpy(items[count].name, name);
            items[count].quantity = qty;
            items[count].price_per_kg = get_price(name);
            total += qty * items[count].price_per_kg;
            count++;
        }
        fclose(file);

        printf("<table><tr><th>Vegetable</th><th>Quantity (kg)</th><th>Price per kg</th><th>Subtotal</th></tr>");
        for (int i = 0; i < count; i++) {
            int item_total = items[i].quantity * items[i].price_per_kg;
            printf("<tr><td>%s</td><td>%d</td><td>?%d</td><td>?%d</td></tr>",
                   items[i].name, items[i].quantity, items[i].price_per_kg, item_total);
        }
        printf("<tr><th colspan='3'>Total Amount to Pay</th><th>?%d</th></tr>", total);
        printf("</table>");

        printf("<div class='pay'><a href='/confirmation.html' class='done-btn'>Confirm Payment</a></div>");

        // Clear the cart
        FILE *clear = fopen("cart.txt", "w");
        if (clear) fclose(clear);
    }

    printf("</body></html>");
    return 0;
}

