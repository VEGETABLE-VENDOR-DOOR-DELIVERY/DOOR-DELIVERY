#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------- CONSTANTS --------------------
int MAX_USERS = 100;
int MAX_PRODUCTS = 100;
int MAX_CART = 50;
int MAX_ORDERS = 100;

// -------------------- STRUCT DEFINITIONS --------------------

typedef struct {
    int id;
    char name[50];
    char email[50];
    char password[50];
    char role[10];
    char phone[15]; // <-- Added
} User;

typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
    int vendorId;
} Product;

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
    char address[100]; // <-- Added
} Order;

typedef struct OrderNode {
    Order data;
    struct OrderNode *next;
} OrderNode;

typedef struct {
    Order data[100];
    int front, rear;
} OrderQueue;

typedef struct {
    int top;
    Product data[100];
} ProductStack;

// -------------------- GLOBAL VARIABLES --------------------

User users[100];
Product products[100];
Order orders[100];
CartItem userCart[50];

int userCount = 0, productCount = 0, orderCount = 0, cartItemCount = 0;

OrderNode *orderHead = NULL;
OrderQueue orderQueue = { .front = -1, .rear = -1 };
ProductStack viewed = { .top = -1 };

// -------------------- FUNCTION DEFINITIONS --------------------

// Signup & Login
int signup(char name[], char email[], char password[], char role[], char phone[]) {
    if (userCount >= MAX_USERS) {
        printf("User limit reached.\n");
        return -1;
    }

    // Write user details to the file
    FILE *file = fopen("users.txt", "a");
    if (!file) {
        printf("Error opening file for writing.\n");
        return -1;
    }

    fprintf(file, "%d,%s,%s,%s,%s,%s\n", userCount + 1, name, email, password, role, phone);
    fclose(file);

    users[userCount].id = userCount + 1;
    strcpy(users[userCount].name, name);
    strcpy(users[userCount].email, email);
    strcpy(users[userCount].password, password);
    strcpy(users[userCount].role, role);
    strcpy(users[userCount].phone, phone); // store phone
    userCount++;
    printf("Signup successful!\n");
    return userCount;
}

int login(char email[], char password[]) {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return -1;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        int id;
        char name[50], fileEmail[50], filePassword[50], role[10], phone[15];

        // Parse the line from the file
        sscanf(line, "%d,%49[^,],%49[^,],%49[^,],%9[^,],%14[^\n]", &id, name, fileEmail, filePassword, role, phone);

        if (strcmp(fileEmail, email) == 0 && strcmp(filePassword, password) == 0) {
            fclose(file);
            printf("Login successful. Welcome %s!\n", name);
            return id;
        }
    }
    fclose(file);
    printf("Login failed.\n");
    return -1;
}

// Product Management
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

void listProducts() {
    int i;
    for (i = 0; i < productCount; i++) {
        printf("ID: %d, Name: %s, Price: %.2f, Qty: %d\n",
               products[i].id, products[i].name,
               products[i].price, products[i].quantity);
    }
}

// Cart and Checkout
void addToCart(int productId, int qty) {
    if (cartItemCount >= MAX_CART) {
        printf("Cart is full!\n");
        return;
    }
    userCart[cartItemCount].productId = productId;
    userCart[cartItemCount].quantity = qty;
    cartItemCount++;
    printf("Added to cart.\n");
}

void checkout(int userId) {
    if (orderCount >= MAX_ORDERS) {
        printf("Cannot place more orders.\n");
        return;
    }

    char address[100];
    printf("Enter Delivery Address: ");
    fgets(address, sizeof(address), stdin);
    strtok(address, "\n");

    orders[orderCount].id = orderCount + 1;
    orders[orderCount].userId = userId;
    orders[orderCount].itemCount = cartItemCount;
    strcpy(orders[orderCount].status, "pending");
    strcpy(orders[orderCount].address, address); // save address
    int i;
    for (i = 0; i < cartItemCount; i++) {
        orders[orderCount].items[i] = userCart[i];
    }

    cartItemCount = 0;
    orderCount++;
    printf("Checkout complete! Order placed.\n");
}

// List Orders
void listOrders() {
    int i;
    for (i = 0; i < orderCount; i++) {
        printf("Order ID: %d | Status: %s | Address: %s\n", orders[i].id, orders[i].status, orders[i].address);
        int j;
        for (j = 0; j < orders[i].itemCount; j++) {
            printf("   Product ID: %d | Qty: %d\n",
                   orders[i].items[j].productId,
                   orders[i].items[j].quantity);
        }
    }
}

void payForOrder(int orderId) {
    int i;
    for (i = 0; i < orderCount; i++) {
        if (orders[i].id == orderId) {
            strcpy(orders[i].status, "paid");
            printf("Payment completed for Order %d\n", orderId);
            return;
        }
    }
    printf("Order not found.\n");
}

// Linked List for Order History
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
}

// Queue for Order Processing
void enqueueOrder(Order o) {
    if (orderQueue.rear >= MAX_ORDERS - 1) {
        printf("Queue overflow!\n");
        return;
    }
    orderQueue.data[++orderQueue.rear] = o;
}

Order dequeueOrder() {
    if (orderQueue.front == orderQueue.rear) {
        printf("Queue underflow!\n");
        Order empty = {0};
        return empty;
    }
    return orderQueue.data[++orderQueue.front];
}

// Stack for Recently Viewed Products
void pushProduct(Product p) {
    if (viewed.top >= 99) {
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
    int choice, userId = -1;
    char name[50], email[50], password[50], role[10], phone[15];
    char productName[50];
    float price;
    int quantity, productId, orderId;

    while (1) {
        printf("\n========= MENU =========\n");
        printf("1. Signup\n");
        printf("2. Login\n");
        printf("3. Add Product (Vendor Only)\n");
        printf("4. List Products\n");
        printf("5. Add to Cart\n");
        printf("6. Checkout\n");
        printf("7. List Orders\n");
        printf("8. Pay for Order\n");
        printf("9. View Last Viewed Product\n");
        printf("10. Exit\n");
        printf("========================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter Name: ");
                fgets(name, sizeof(name), stdin); strtok(name, "\n");

                printf("Enter Email: ");
                fgets(email, sizeof(email), stdin); strtok(email, "\n");

                printf("Enter Password: ");
                fgets(password, sizeof(password), stdin); strtok(password, "\n");

                printf("Enter Role (customer/vendor): ");
                fgets(role, sizeof(role), stdin); strtok(role, "\n");

                printf("Enter Phone Number: ");
                fgets(phone, sizeof(phone), stdin); strtok(phone, "\n");

                signup(name, email, password, role, phone);
                break;

            case 2:
                printf("Enter Email: ");
                fgets(email, sizeof(email), stdin); strtok(email, "\n");

                printf("Enter Password: ");
                fgets(password, sizeof(password), stdin); strtok(password, "\n");

                userId = login(email, password);
                break;

            case 3:
                if (userId == -1) {
                    printf("Please login first as vendor.\n");
                    break;
                }
                int i;
                for (i = 0; i < userCount; i++) {
                    if (users[i].id == userId && strcmp(users[i].role, "vendor") == 0) {
                        printf("Enter Product Name: ");
                        fgets(productName, sizeof(productName), stdin); strtok(productName, "\n");

                        printf("Enter Price: ");
                        scanf("%f", &price);
                        printf("Enter Quantity: ");
                        scanf("%d", &quantity);
                        getchar();

                        addProduct(productName, price, quantity, userId);
                        break;
                    } else if (i == userCount - 1) {
                        printf("Only vendors can add products.\n");
                    }
                }
                break;

            case 4:
                listProducts();
                break;

            case 5:
                if (productCount == 0) {
                    printf("No products available.\n");
                    break;
                }

                printf("Enter Product ID: ");
                scanf("%d", &productId);
                printf("Enter Quantity: ");
                scanf("%d", &quantity);
                getchar();

                if (productId <= 0 || productId > productCount) {
                    printf("Invalid Product ID!\n");
                    break;
                }

                addToCart(productId, quantity);
                pushProduct(products[productId - 1]); // simulate view
                break;

            case 6:
                if (userId == -1) {
                    printf("Please login to checkout.\n");
                    break;
                }

                checkout(userId);
                enqueueOrder(orders[orderCount - 1]);
                addOrderToList(orders[orderCount - 1]);
                break;

            case 7:
                listOrders();
                break;

            case 8:
                printf("Enter Order ID to Pay: ");
                scanf("%d", &orderId);
                getchar();
                payForOrder(orderId);
                break;

            case 9:
                if (viewed.top != -1) {
                    Product p = popProduct();
                    printf("Last Viewed Product: %s\n", p.name);
                } else {
                    printf("No product viewed yet.\n");
                }
                break;

            case 10:
                printf("Exiting program. Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

