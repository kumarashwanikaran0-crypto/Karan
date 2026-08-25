#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    STATUS_PENDING,
    STATUS_CONFIRMED,
    STATUS_LOADING,
    STATUS_IN_TRANSIT,
    STATUS_DELIVERED
} OrderStatus;

typedef struct {
    int id;
    char name[64];
    double price;
} Product;

typedef struct {
    char name[64];
    char address[128];
    char phone[32];
} Customer;

typedef struct {
    int orderId;
    Customer customer;
    Product product;
    OrderStatus status;
    char paymentMethod[32];
    char deliveryPartner[64];
} Order;

static const Product products[] = {
    {100, "Running Shoes", 59.99},
    {101, "Formal Shoes", 79.99},
    {102, "Casual Sneakers", 69.99}
};
static const int productCount = sizeof(products) / sizeof(products[0]);
static const char *paymentMethods[] = {
    "Credit Card",
    "UPI",
    "Net Banking"
};
static const char *deliveryPartners[] = {
    "FastShip Logistics",
    "Urban Courier",
    "Express Delivery"
};
static const char historyFilename[] = "orders_history.txt";

const char *statusToString(OrderStatus status) {
    switch (status) {
        case STATUS_PENDING: return "Pending";
        case STATUS_CONFIRMED: return "Confirmed";
        case STATUS_LOADING: return "Loading";
        case STATUS_IN_TRANSIT: return "In Transit";
        case STATUS_DELIVERED: return "Delivered";
        default: return "Unknown";
    }
}

void printOrder(const Order *order) {
    printf("Order ID: %d\n", order->orderId);
    printf("Customer: %s\n", order->customer.name);
    printf("Phone: %s\n", order->customer.phone);
    printf("Address: %s\n", order->customer.address);
    printf("Product: %s\n", order->product.name);
    printf("Price: $%.2f\n", order->product.price);
    printf("Payment method: %s\n", order->paymentMethod);
    printf("Delivery partner: %s\n", order->deliveryPartner);
    printf("Status: %s\n", statusToString(order->status));
    printf("----------------------------------------\n");
}

int readInteger(const char *prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        printf("Invalid input. %s", prompt);
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return value;
}

void readString(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

const Product *selectProduct(void) {
    printf("Available Products:\n");
    for (int i = 0; i < productCount; ++i) {
        printf("  %d. %s ($%.2f)\n", i + 1, products[i].name, products[i].price);
    }
    int choice = readInteger("Select a product by number: ");
    if (choice < 1 || choice > productCount) {
        printf("Invalid selection. Defaulting to %s.\n", products[0].name);
        return &products[0];
    }
    return &products[choice - 1];
}

void choosePaymentMethod(Order *order) {
    printf("\nPayment options:\n");
    for (int i = 0; i < (int)(sizeof(paymentMethods) / sizeof(paymentMethods[0])); ++i) {
        printf("  %d. %s\n", i + 1, paymentMethods[i]);
    }
    int choice = readInteger("Choose a payment method: ");
    if (choice < 1 || choice > (int)(sizeof(paymentMethods) / sizeof(paymentMethods[0]))) {
        choice = 1;
        printf("Invalid selection. Defaulting to %s.\n", paymentMethods[0]);
    }
    strcpy(order->paymentMethod, paymentMethods[choice - 1]);
}

void assignDeliveryPartner(Order *order) {
    printf("\nDelivery partners:\n");
    for (int i = 0; i < (int)(sizeof(deliveryPartners) / sizeof(deliveryPartners[0])); ++i) {
        printf("  %d. %s\n", i + 1, deliveryPartners[i]);
    }
    int choice = readInteger("Select a delivery partner: ");
    if (choice < 1 || choice > (int)(sizeof(deliveryPartners) / sizeof(deliveryPartners[0]))) {
        choice = 1;
        printf("Invalid selection. Defaulting to %s.\n", deliveryPartners[0]);
    }
    strcpy(order->deliveryPartner, deliveryPartners[choice - 1]);
}

void saveOrderHistory(const Order *order) {
    FILE *file = fopen(historyFilename, "a");
    if (file == NULL) {
        printf("Warning: could not open history file '%s' for writing.\n", historyFilename);
        return;
    }
    fprintf(file, "Order ID: %d\n", order->orderId);
    fprintf(file, "Customer: %s\n", order->customer.name);
    fprintf(file, "Phone: %s\n", order->customer.phone);
    fprintf(file, "Address: %s\n", order->customer.address);
    fprintf(file, "Product: %s\n", order->product.name);
    fprintf(file, "Price: $%.2f\n", order->product.price);
    fprintf(file, "Payment method: %s\n", order->paymentMethod);
    fprintf(file, "Delivery partner: %s\n", order->deliveryPartner);
    fprintf(file, "Status: %s\n", statusToString(order->status));
    fprintf(file, "----------------------------------------\n");
    fclose(file);
}

void showOrderHistory(void) {
    FILE *file = fopen(historyFilename, "r");
    if (file == NULL) {
        printf("No order history found. Place an order first.\n");
        return;
    }
    printf("\nOrder History:\n");
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        fputs(line, stdout);
    }
    fclose(file);
    printf("----------------------------------------\n");
}

void printOrderPreview(const Order *order) {
    printf("\nOrder preview:\n");
    printOrder(order);
}

void editOrderDetails(Order *order) {
    bool editing = true;
    while (editing) {
        printf("\nEdit order details:\n");
        printf("  1. Customer name\n");
        printf("  2. Customer phone\n");
        printf("  3. Customer address\n");
        printf("  4. Product\n");
        printf("  5. Payment method\n");
        printf("  6. Delivery partner\n");
        printf("  7. Done editing\n");
        int choice = readInteger("Choose a field to edit: ");

        switch (choice) {
            case 1:
                readString("Enter new customer name: ", order->customer.name, sizeof(order->customer.name));
                break;
            case 2:
                readString("Enter new customer phone: ", order->customer.phone, sizeof(order->customer.phone));
                break;
            case 3:
                readString("Enter new customer address: ", order->customer.address, sizeof(order->customer.address));
                break;
            case 4:
                order->product = *selectProduct();
                break;
            case 5:
                choosePaymentMethod(order);
                break;
            case 6:
                assignDeliveryPartner(order);
                break;
            case 7:
                editing = false;
                break;
            default:
                printf("Invalid option. Please choose 1 through 7.\n");
                break;
        }
    }
}

bool confirmOrderPreview(Order *order) {
    while (true) {
        printOrderPreview(order);
        printf("  1. Confirm order\n");
        printf("  2. Edit order before placing\n");
        printf("  3. Cancel order\n");
        int choice = readInteger("Choose an action: ");

        switch (choice) {
            case 1:
                return true;
            case 2:
                editOrderDetails(order);
                break;
            case 3:
                printf("Order canceled. Returning to main menu.\n");
                return false;
            default:
                printf("Invalid option. Please choose 1, 2, or 3.\n");
                break;
        }
    }
}

void simulateOrderLifecycle(Order *order) {
    printf("\nCreating order...\n");
    order->status = STATUS_PENDING;
    printOrder(order);

    printf("Processing payment through the gateway using %s...\n", order->paymentMethod);
    printf("Payment succeeded.\n");
    order->status = STATUS_CONFIRMED;
    printf("Order status updated to %s.\n", statusToString(order->status));

    printf("\nNotifying seller dashboard about the new order...\n");
    printf("Seller received the order notification.\n");

    printf("Preparing warehouse and inventory for fulfillment...\n");
    order->status = STATUS_LOADING;
    printf("Order status updated to %s.\n", statusToString(order->status));

    printf("Assigning driver and dispatching shipment with %s...\n", order->deliveryPartner);
    order->status = STATUS_IN_TRANSIT;
    printf("Order status updated to %s.\n", statusToString(order->status));

    printf("Delivering the product to the customer...\n");
    order->status = STATUS_DELIVERED;
    printf("Order status updated to %s.\n", statusToString(order->status));

    printf("\nFinal order summary:\n");
    printOrder(order);
}

void createOrder(int orderId) {
    Order order;
    order.orderId = orderId;

    readString("\nEnter customer name (default: Ashwani): ", order.customer.name, sizeof(order.customer.name));
    if (order.customer.name[0] == '\0') {
        strcpy(order.customer.name, "Ashwani");
    }

    readString("Enter customer phone (default: 9999999999): ", order.customer.phone, sizeof(order.customer.phone));
    if (order.customer.phone[0] == '\0') {
        strcpy(order.customer.phone, "9999999999");
    }

    readString("Enter customer address (default: Bihar): ", order.customer.address, sizeof(order.customer.address));
    if (order.customer.address[0] == '\0') {
        strcpy(order.customer.address, "Bihar");
    }

    const Product *product = selectProduct();
    order.product = *product;
    choosePaymentMethod(&order);
    assignDeliveryPartner(&order);

    if (confirmOrderPreview(&order)) {
        simulateOrderLifecycle(&order);
        saveOrderHistory(&order);
    }
}

int main(void) {
    int nextOrderId = 10001;
    bool running = true;

    printf("Dream House App Order Workflow Simulation\n");
    printf("========================================\n");

    while (running) {
        printf("\nMain Menu:\n");
        printf("  1. Create new order\n");
        printf("  2. View order history\n");
        printf("  3. Exit\n");
        int choice = readInteger("Select an option: ");

        switch (choice) {
            case 1:
                createOrder(nextOrderId++);
                break;
            case 2:
                showOrderHistory();
                break;
            case 3:
                running = false;
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please choose 1, 2, or 3.\n");
                break;
        }
    }

    return 0;
}
