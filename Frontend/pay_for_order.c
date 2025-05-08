#include <stdio.h>
#include <string.h>

#define MAX_ORDERS 100

typedef struct {
    int productId;
    int quantity;
} CartItem;

typedef struct {
    int id;
    int userId;
    CartItem items[50];
    int itemCount;
    char status[20];
    char address[100];
} Order;

Order orders[MAX_ORDERS];
int orderCount = 2;

void dummyOrders() {
    orders[0].id = 1; strcpy(orders[0].status, "pending");
    orders[1].id = 2; strcpy(orders[1].status, "pending");
}

void payForOrder(int orderId) {
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].id == orderId) {
            strcpy(orders[i].status, "paid");
            printf("Payment completed for Order %d\n", orderId);
            return;
        }
    }
    printf("Order not found.\n");
}

int main() {
    int orderId;
    dummyOrders();
    printf("Enter Order ID to Pay: ");
    scanf("%d", &orderId);
    payForOrder(orderId);
    return 0;
}

