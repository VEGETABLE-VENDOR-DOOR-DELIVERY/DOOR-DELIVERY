#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct OrderNode {
    Order data;
    struct OrderNode *next;
} OrderNode;

OrderNode *orderHead = NULL;

void addOrderToList(Order o) {
    OrderNode *newNode = malloc(sizeof(OrderNode));
    if (!newNode) return;
    newNode->data = o;
    newNode->next = NULL;
    if (!orderHead) {
        orderHead = newNode;
    } else {
        OrderNode *temp = orderHead;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
    printf("Order %d added to history.\n", o.id);
}

void printOrderHistory() {
    OrderNode *temp = orderHead;
    while (temp) {
        printf("Order ID: %d | Status: %s | Address: %s\n",
               temp->data.id, temp->data.status, temp->data.address);
        temp = temp->next;
    }
}

int main() {
    Order o1 = {1, 1, {{1, 2}}, 1, "paid", "Block A"};
    Order o2 = {2, 2, {{2, 1}}, 1, "pending", "Block B"};

    addOrderToList(o1);
    addOrderToList(o2);

    printOrderHistory();
    return 0;
}

