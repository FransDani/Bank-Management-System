#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNumber;
    char name[50];
    float balance;
};

void createAccount() {
    FILE *file = fopen("accounts.txt", "a+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Account newAccount;
    printf("Enter account number: ");
    scanf("%d", &newAccount.accNumber);
    printf("Enter name: ");
    scanf("%s", newAccount.name);
    printf("Enter initial balance: ");
    scanf("%f", &newAccount.balance);

    fprintf(file, "%d %s %.2f\n", newAccount.accNumber, newAccount.name, newAccount.balance);
    fclose(file);
}

void viewAccounts() {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("No accounts found.\n");
        return;
    }

    struct Account account;
    printf("\nAccount Details:\n");
    printf("Acc No.\tName\tBalance\n");
    while (fscanf(file, "%d %s %f", &account.accNumber, account.name, &account.balance) != EOF) {
        printf("%d\t%s\t%.2f\n", account.accNumber, account.name, account.balance);
    }
    fclose(file);
}

void editAccount() {
    int accNumber;
    printf("Enter account number to edit: ");
    scanf("%d", &accNumber);

    FILE *file = fopen("accounts.txt", "r+");
    if (file == NULL) {
        printf("No accounts found.\n");
        return;
    }

    struct Account account;
    int found = 0;
    while (fscanf(file, "%d %s %f", &account.accNumber, account.name, &account.balance) != EOF) {
        if (account.accNumber == accNumber) {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", account.name);
            printf("Enter new balance: ");
            scanf("%f", &account.balance);

            fseek(file, -1 * sizeof(account), SEEK_CUR);
            fprintf(file, "%d %s %.2f\n", account.accNumber, account.name, account.balance);
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Account not found.\n");
    } else {
        printf("Account details updated.\n");
    }
}

void transact() {
    int accNumber, choice;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNumber);

    FILE *file = fopen("accounts.txt", "r+");
    if (file == NULL) {
        printf("No accounts found.\n");
        return;
    }

    struct Account account;
    int found = 0;
    while (fscanf(file, "%d %s %f", &account.accNumber, account.name, &account.balance) != EOF) {
        if (account.accNumber == accNumber) {
            found = 1;
            printf("1. Deposit\n");
            printf("2. Withdraw\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter amount to deposit: ");
                    scanf("%f", &amount);
                    account.balance += amount;
                    printf("Amount deposited successfully.\n");
                    break;
                case 2:
                    printf("Enter amount to withdraw: ");
                    scanf("%f", &amount);
                    if (amount > account.balance) {
                        printf("Insufficient balance.\n");
                    } else {
                        account.balance -= amount;
                        printf("Amount withdrawn successfully.\n");
                    }
                    break;
                default:
                    printf("Invalid choice.\n");
            }

            fseek(file, -1 * sizeof(account), SEEK_CUR);
            fprintf(file, "%d %s %.2f\n", account.accNumber, account.name, account.balance);
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Account not found.\n");
    }
}

int main() {
    int choice;
    
    do {
        printf("\nBank Management System\n");
        printf("1. Create Account\n");
        printf("2. View Accounts\n");
        printf("3. Edit Account\n");
        printf("4. Transact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                viewAccounts();
                break;
            case 3:
                editAccount();
                break;
            case 4:
                transact();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
