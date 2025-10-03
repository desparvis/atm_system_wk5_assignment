#include <stdio.h>
#include <string.h>

#define MAX_USERS 3
#define MAX_TRANSACTIONS 10

typedef struct {
    char username[20];
    char pin[5]; 
    int balance;
    char transactions[MAX_TRANSACTIONS][50];
    int transactionCount;
} User;

User users[MAX_USERS] = {
    {"user1", "1234", 1000, {}, 0},
    {"user2", "5678", 2000, {}, 0},
    {"user3", "0000", 500, {}, 0}
};

int currentUser = -1;

int login();
void menu();
void checkBalance();
void deposit();
void withdraw();
void viewTransactions();
void addTransaction(const char *msg);

int main() {
    printf("===== Welcome to the ATM System =====\n");

    if (login()) {
        menu();
    } else {
        printf("Too many failed attempts. Exiting...\n");
    }
    return 0;
}

int login() {
    char uname[20], pin[5];
    int attempts = 0;

    while (attempts < 3) {
        printf("Enter username: ");
        scanf("%s", uname);
        printf("Enter PIN: ");
        scanf("%s", pin);

        for (int i = 0; i < MAX_USERS; i++) {
            if (strcmp(uname, users[i].username) == 0 && strcmp(pin, users[i].pin) == 0) {
                currentUser = i;
                printf("Login successful! Welcome, %s.\n", users[i].username);
                return 1;
            }
        }
        printf("Invalid username or PIN. Try again.\n");
        attempts++;
    }
    return 0;
}

void menu() {
    int choice;
    do {
        printf("\n===== ATM Menu =====\n");
        printf("1. Check Balance\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. View Transactions\n");
        printf("5. Logout\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: checkBalance(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: viewTransactions(); break;
            case 5: printf("Logging out...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);
}

void checkBalance() {
    printf("Your balance: %d\n", users[currentUser].balance);
}

void deposit() {
    int amount;
    printf("Enter amount to deposit: ");
    scanf("%d", &amount);
    if (amount > 0) {
        users[currentUser].balance += amount;
        printf("Deposited %d successfully.\n", amount);

        char msg[50];
        sprintf(msg, "Deposited %d", amount);
        addTransaction(msg);
    } else {
        printf("Invalid amount.\n");
    }
}

void withdraw() {
    int amount;
    printf("Enter amount to withdraw: ");
    scanf("%d", &amount);
    if (amount > 0 && amount <= users[currentUser].balance) {
        users[currentUser].balance -= amount;
        printf("Withdrew %d successfully.\n", amount);

        char msg[50];
        sprintf(msg, "Withdrew %d", amount);
        addTransaction(msg);
    } else {
        printf("Insufficient balance or invalid amount.\n");
    }
}

void viewTransactions() {
    printf("Transaction History:\n");
    if (users[currentUser].transactionCount == 0) {
        printf("No transactions yet.\n");
    } else {
        for (int i = 0; i < users[currentUser].transactionCount; i++) {
            printf("%d. %s\n", i + 1, users[currentUser].transactions[i]);
        }
    }
}

void addTransaction(const char *msg) {
    if (users[currentUser].transactionCount < MAX_TRANSACTIONS) {
        strcpy(users[currentUser].transactions[users[currentUser].transactionCount], msg);
        users[currentUser].transactionCount++;
    } else {
        for (int i = 1; i < MAX_TRANSACTIONS; i++) {
            strcpy(users[currentUser].transactions[i - 1], users[currentUser].transactions[i]);
        }
        strcpy(users[currentUser].transactions[MAX_TRANSACTIONS - 1], msg);
    }
}
