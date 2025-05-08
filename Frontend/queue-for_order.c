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

typedef struct {
    Order data[MAX_ORDERS];
    int front, rear;
} OrderQueue;

OrderQueue orderQueue = { .front = -1, .rear = -1 };

void enqueueOrder(Order o) {
    if (orderQueue.rear >= MAX_ORDERS - 1) {
        printf("Queue overflow!\n");
        return;
    }
    orderQueue.data[++orderQueue.rear] = o;
    printf("Order %d enqueued.\n", o.id);
}

Order dequeueOrder() {
    if (orderQueue.front == orderQueue.rear) {
        printf("Queue underflow!\n");
        Order empty = {0};
        return empty;
    }
    return orderQueue.data[++orderQueue.front];
}

int main() {
    Order o1 = {1, 1, {{1, 2}}, 1, "pending", "12, Gandhi Street"};
    Order o2 = {2, 2, {{2, 1}}, 1, "pending", "45, Anna Nagar"};

    enqueueOrder(o1);
    enqueueOrder(o2);

    Order processed = dequeueOrder();
    printf("Dequeued Order ID: %d\n", processed.id);

    return 0;
}

