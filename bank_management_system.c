#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Account {
    int accNumber;
    char name[50];
    float balance;
};

// Existing function for updating transaction log remains unchanged

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
    scanf(" %[^\n]s", newAccount.name);
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
    
    while (fscanf(file, "%d %[^\n]s %f\n", &account.accNumber, account.name, &account.balance) != EOF) {
        printf("%d\t%s\t%.2f\n", account.accNumber, account.name, account.balance);
    }
    fclose(file);
}

void transact() {
    // The transact function with updates made earlier
    // ...
}

void deleteAccount() {
    int accNumber;
    printf("Enter account number to delete: ");
    scanf("%d", &accNumber);

    FILE *tempFile = fopen("temp.txt", "w");
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("No accounts found.\n");
        return;
    }

    struct Account account;
    int found = 0;
    while (fscanf(file, "%d %[^\n]s %f\n", &account.accNumber, account.name, &account.balance) != EOF) {
        if (account.accNumber == accNumber) {
            found = 1;
            printf("Account deleted successfully.\n");
            continue;
        }
        fprintf(tempFile, "%d %s %.2f\n", account.accNumber, account.name, account.balance);
    }
    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Account not found.\n");
        remove("temp.txt"); // Delete temporary file if account is not found
    } else {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }
}

void editAccount() {
    int accNumber;
    printf("Enter account number to edit: ");
    scanf("%d", &accNumber);

    FILE *tempFile = fopen("temp.txt", "w");
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("No accounts found.\n");
        return;
    }

    struct Account account;
    int found = 0;
    while (fscanf(file, "%d %[^\n]s %f\n", &account.accNumber, account.name, &account.balance) != EOF) {
        if (account.accNumber == accNumber) {
            found = 1;
            printf("Enter new name: ");
            scanf(" %[^\n]s", account.name);
            printf("Enter new balance: ");
            scanf("%f", &account.balance);
            printf("Account details updated successfully.\n");
        }
        fprintf(tempFile, "%d %s %.2f\n", account.accNumber, account.name, account.balance);
    }
    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Account not found.\n");
        remove("temp.txt"); // Delete temporary file if account is not found
    } else {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }
}

int main() {
    int choice;

    do {
        printf("\nBank Management System\n");
        printf("1. Create Account\n");
        printf("2. View Accounts\n");
        printf("3. Transact\n");
        printf("4. Delete Account\n");
        printf("5. Edit Account\n");
        printf("6. Exit\n");
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
                transact();
                break;
            case 4:
                deleteAccount();
                break;
            case 5:
                editAccount();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
