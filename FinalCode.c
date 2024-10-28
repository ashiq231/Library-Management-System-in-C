#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char usernames[10][30];
char passwords[10][30];

typedef struct {
    char name[50];
    char category[50];
    float price;
    int isRented;
} Product;

typedef struct {
    char username[50];
    char password[50];
    float balance;
    int rentedProductIndices[5];
    int rentedCount;
} Account;

Product products[10] = {
    {"LAPTOP", "Electronics", 50.0, 0},
    {"BOOK", "Education", 10.0, 0},
    {"BICYCLE", "Sports", 20.0, 0}
};
int numProducts = 3;

Account accounts[10];
int numAccounts = 0;

char notifications[100][100];
int notificationCount = 0;

void takeRent(Product products[], int numProducts, Account *user);
void giveRent(Product products[], int *numProducts);
void search(Product products[], int numProducts, Account *user);
void showNotifications();
void viewAccountInfo(Account user);
void changePassword(Account *user);
void cancelRenting(Product products[], Account *user);
void store(Product products[], int numProducts);
void storeUserDetails(Account user);

void registerUser();
int loginUser();
void logoutUser();
void rentingSystemMenu(Product products[], int *numProducts, Account *user);

void addNotification(const char *message) {
    if (notificationCount < 100) {
        strncpy(notifications[notificationCount], message, sizeof(notifications[notificationCount]) - 1);
        notifications[notificationCount][sizeof(notifications[notificationCount]) - 1] = '\0';
        notificationCount++;
    }
}

int main() {
    system("color F1");
    printf("\t\t\t\t    Daffodil International University\n\n");
    printf("\t\t\t\t  Software Development Capstone Project\n\n");
    
    printf("\t\t\t\t\t  Online Renting System \n\n");
    
    printf("\t\t\t\t\t   Developed by AshiQ\n\n");
    
    printf("\t\t\t\t\t        ID : 1042\n\n");
    

    printf("\t\t\t\t\t Press ANY to Continue");
    getch();
    
    
    system("COLOR F5");

    int i;
    for (i = 15; i <= 100; i += 5) {
        system("cls");
        printf("\t\t\t\t\t\t\tLOADING  %d%%", i);
        Sleep(100);
    }
    system("cls");

    char welcome[] = "Welcome to the ";
    char online[] = "ONLINE";
    char rent[] = "RENTING";
    char sys[] = "SYSTEM";

    int delay = 50000; 

    
    printf("\t\t\t\t\t\t");
    for (i = 0; welcome[i] != '\0'; i++) {
        printf("%c ", welcome[i]);
        usleep(delay);
    }
    printf("\n");
    printf("\t\t\t\t\t ");
    for (i = 0; online[i] != '\0'; i++) {
        printf("%c ", online[i]);
        usleep(delay);
    }
    printf("  "); 

   
    for (i = 0; rent[i] != '\0'; i++) {
        printf("%c ", rent[i]);
        usleep(delay);
    }
    printf("  ");

   
    for (i = 0; sys[i] != '\0'; i++) {
        printf("%c ", sys[i]);
        usleep(delay);
    }
    printf("\n"); 

    printf("\n");

    memset(accounts, 0, sizeof(accounts));

    int running = 1;
    int loggedInUserId = -1;

    while (running) {
        int choice;

        printf("\t\t\t\t\t\t\t1. Register\n");
        printf("\t\t\t\t\t\t\t2. Login\n");
        
        printf("\t\t\t\t\t\t\t3. Exit\n");
        printf("\t\t\t\t\t\t  Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                registerUser();
                break;
            case 2: 
                loggedInUserId = loginUser();
                if (loggedInUserId != -1) {
                    rentingSystemMenu(products, &numProducts, &accounts[loggedInUserId]);
                }
                break;
            
            case 3:
                running = 0;
                printf("\t\t\t\t\t\t  Exiting...\n");
                break;
            default:
                system("COLOR FC");
                printf("\t\t\t\t\t\t  Invalid choice. Please enter a number between 1 and 4.\n");
                 
        }
    }

    return 0;
}

void registerUser() {
    char username[30];
    char password[30];
    int i;

    printf("\t\t\t\t\t\t  Enter a new username: ");
    scanf("%s", username);
    printf("\t\t\t\t\t\t  Enter a new password: ");
    scanf("%s", password);

    for (i = 0; i < numAccounts; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            system("COLOR F4");
            printf("\t\t\t\t\t\t  User already exists. Try a different username.\n");
             
            return;
        }
    }

    if (numAccounts >= 10) {
        system("COLOR F4");
        printf("\t\t\t\t\t\t  Maximum number of users reached.\n");
        return;
    }

    Account newAccount;
    strcpy(newAccount.username, username);
    strcpy(newAccount.password, password);
    newAccount.balance = 0.0;
    newAccount.rentedCount = 0;
    accounts[numAccounts++] = newAccount;
    
    printf("\t\t\t\t\t\t  Registration successful!\n");
}

int loginUser() {
    char username[30];
    char password[30];

    printf("\t\t\t\t\t\t  Enter your username: ");
    scanf("%s", username);
    printf("\t\t\t\t\t\t  Enter your password: ");
    scanf("%s", password);

    for (int i = 0; i < numAccounts; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            system("COLOR FB");
            printf("\t\t\t\t\t\t  Login successful!\n");
            return i; 
        }
    }
    system("COLOR FC");
    printf("\t\t\t\t\t\t  Invalid username or password.\n");
    return -1; 

}

void logoutUser() {
    int loggedInUserId = -1;
    
    printf("\t\t\t\t\t\t  You have been logged out.\n");
}

void rentingSystemMenu(Product products[], int *numProducts, Account *user) {system("COLOR F1");
    int choice;system("cls");
    do {
        printf("\t\t\t\t\t\t\xB2\xDB\xDB\xDB\xDB\xDB\xDB\xB2 Renting System Menu \xB2\xDB\xDB\xDB\xDB\xDB\xDB\xB2\n");
        printf("\t\t\t\t\t\t\t1. Take Rent\n");
        printf("\t\t\t\t\t\t\t2. Give Rent\n");
        printf("\t\t\t\t\t\t\t3. Search\n");
        printf("\t\t\t\t\t\t\t4. Notifications\n");
        printf("\t\t\t\t\t\t\t5. Account\n");
        printf("\t\t\t\t\t\t\t6. Store\n");
        printf("\t\t\t\t\t\t\t7. Store User Details\n");
        printf("\t\t\t\t\t\t\t8. Logout\n");
       // printf("\t\t\t\t\t\t\t9. Exit\n");
        printf("\t\t\t\t\t\t  Enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1: 
                
                takeRent(products, *numProducts, user);
                break;
            case 2: 
                giveRent(products, numProducts);
                break;
            case 3: 
                search(products, *numProducts, user);
                break;
            case 4: 
                showNotifications();
                break;
            case 5:
                printf("\t\t\t\t\t\t  Account Management\n");
                printf("\t\t\t\t\t\t\t1. View Account Info\n");
                printf("\t\t\t\t\t\t\t2. Change Password\n");
                printf("\t\t\t\t\t\t\t3. Cancel Renting\n");
                printf("\t\t\t\t\t\t  Enter your choice: ");
                int accountChoice;
                scanf("%d", &accountChoice);
                getchar();  
                switch (accountChoice) {
                    case 1:
                        viewAccountInfo(*user);
                        break;
                    case 2:
                        changePassword(user);
                        break;
                    case 3:
                        cancelRenting(products, user);
                        break;
                    default:
                        printf("\t\t\t\t\t\t  Invalid choice. Please enter a number between 1 and 3.\n");
                }
                break;
            case 6:
                store(products, *numProducts);
                break;
            case 7:
                storeUserDetails(*user);
                break;
            case 8: 
                logoutUser();       
                break;
            /*case 9:
                printf("\t\t\t\t\t\t  Exiting...\n");
                break;*/
            default:
                printf("\t\t\t\t\t\t  Invalid choice. Please enter a number between 1 and 8.\n");
        }
    } while (choice != 8);
}

void takeRent(Product products[], int numProducts, Account *user) {
    if (user->rentedCount >= 5) {system("COLOUR FC");
        printf("\t\t\t\t\t\t  You have reached the maximum number of rented products.\n");
        return;
    }

    int choice;
    printf("\t\t\t\t\t\t  Select category:\n");
    for (int i = 0; i < numProducts; i++) {
        printf("\t\t\t\t\t\t\t%d. %s\n", i + 1, products[i].category);
    }
    printf("\t\t\t\t\t\t  Enter your choice (or 0 to go back): ");
    scanf("%d", &choice);
    getchar();

    if (choice == 0) {
        return;
    }

    printf("\t\t\t\t\t\t  Products in the selected category:\n");
    int availableProducts = 0;
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(products[i].category, products[choice - 1].category) == 0 && !products[i].isRented) {
            printf("\t\t\t\t\t\t\t%d. %s - $%.2f\n", i + 1, products[i].name, products[i].price);
            availableProducts++;
        }
    }

    if (availableProducts == 0) {
        printf("\t\t\t\t\t\t  No products available in this category. Press 0 to go back.");
        int goBackChoice;
        scanf("%d", &goBackChoice);
        getchar();
        if (goBackChoice == 0) {
            return; 
        }
    }

    int productChoice;
    printf("\t\t\t\t\t\t  Select product (or 0 to go back): ");
    scanf("%d", &productChoice);
    getchar();

    if (productChoice == 0) {
        return; 
    }

    printf("\t\t\t\t\t\t  Enter renting time (in hours): ");
    int rentingTime;
    scanf("%d", &rentingTime);
    getchar();

    float totalPrice = rentingTime * products[productChoice - 1].price;
    printf("\t\t\t\t\t\t  Total payment: $%.2f\n", totalPrice);

    user->rentedProductIndices[user->rentedCount++] = productChoice - 1;
    products[productChoice - 1].isRented = 1;

    char notification[100];
    snprintf(notification, sizeof(notification), "Rented %s for $%.2f", products[productChoice - 1].name, totalPrice);
    addNotification(notification);
    printf("\t\t\t\t\t\t  Press ANY Key to Continue..\n");
    getch();
}


void giveRent(Product products[], int *numProducts) {
    if (*numProducts >= 5) {
        printf("\t\t\t\t\t\t  Maximum number of products reached.\n");
        return;
    }

    char productName[50];
    char productInfo[100];
    float rentPrice;

    printf("\t\t\t\t\t\t  Enter product name in UpperCase: ");
    scanf("%s", productName);
    getchar();  

    printf("\t\t\t\t\t\t  Enter product category: ");
    scanf("%s", productInfo);
    getchar(); 

    printf("\t\t\t\t\t\t  Enter rent price: ");
    scanf("%f", &rentPrice);
    getchar();  

    strcpy(products[*numProducts].name, productName);
    strcpy(products[*numProducts].category, productInfo);
    products[*numProducts].price = rentPrice;
    products[*numProducts].isRented = 0;
    (*numProducts)++;

    printf("\t\t\t\t\t\t  Product registered successfully!\n");

    char notification[100];
    snprintf(notification, sizeof(notification), "Added %s to the store", productName);
    addNotification(notification);
    printf("\t\t\t\t\t\t  Press ANY Key to Continue..\n");
    getch();
}

void search(Product products[], int numProducts, Account *user) {
    char keyword[50];
    printf("\t\t\t\t\t\t  Enter keyword to search in Upper Case: ");
    scanf("%s", keyword);
    getchar();

    printf("\t\t\t\t\t\t  Search results:\n");
    for (int i = 0; i < numProducts; i++) {
        if (strstr(products[i].name, keyword) != NULL && !products[i].isRented) {
            printf("\t\t\t\t\t\t  %d. %s - %s - $%.2f\n", i + 1, products[i].name, products[i].category, products[i].price);
        }
    }

    int productChoice;
    printf("\t\t\t\t\t\t  Enter the number of the product to rent (0 to cancel): ");
    scanf("%d", &productChoice);
    getchar();  

    if (productChoice > 0 && productChoice <= numProducts && !products[productChoice - 1].isRented) {
        printf("\t\t\t\t\t\t  Enter renting time (in hours): ");
        int rentingTime;
        scanf("%d", &rentingTime);
        getchar(); 

        float totalPrice = rentingTime * products[productChoice - 1].price;
        printf("\t\t\t\t\t\t  Total payment: $%.2f\n", totalPrice);

        user->rentedProductIndices[user->rentedCount++] = productChoice - 1;
        products[productChoice - 1].isRented = 1;

        
        char notification[100];
        snprintf(notification, sizeof(notification), "Rented %s for $%.2f", products[productChoice - 1].name, totalPrice);
        addNotification(notification);
    } else if (productChoice != 0) {
        printf("\t\t\t\t\t\t  Invalid choice or product unavailable.\n");
    }
    printf("\t\t\t\t\t\t  Press ANY Keyto Continue..\n");
    getch();
}

void showNotifications() {
    printf("\t\t\t\t\t\t  Notifications:\n");
    for (int i = 0; i < notificationCount; i++) {
        printf("\t\t\t\t\t\t  %d. %s\n", i + 1, notifications[i]);
    }printf("\t\t\t\t\t\t  Press ANY key to Continue..\n");
    getch();
}

void viewAccountInfo(Account user) {
    printf("\t\t\t\t\t\t  Account Information:\n");
    printf("\t\t\t\t\t\t\tUsername: %s\n", user.username);
    printf("\t\t\t\t\t\t\tBalance: $%.2f\n", user.balance);
    printf("\t\t\t\t\t\t\tCurrently Rented Products:\n");
    for (int i = 0; i < user.rentedCount; i++) {
        printf("\t\t\t\t\t\t  %s\n", products[user.rentedProductIndices[i]].name);
    }
    if (user.rentedCount == 0) {
        printf("\t\t\t\t\t\t  No product currently rented.\n");
    }printf("\t\t\t\t\t\t  Press ANY Key to Continue..\n");
    getch();
}

void changePassword(Account *user) {
    char oldPassword[50];
    char newPassword[50];

    printf("\t\t\t\t\t\t  Enter old password: ");
    scanf("%s", oldPassword);
    getchar();  

    if (strcmp(user->password, oldPassword) == 0) {
        printf("\t\t\t\t\t\t  Enter new password: ");
        scanf("%s", newPassword);
        getchar(); 

        strcpy(user->password, newPassword);
        printf("\t\t\t\t\t\t  Password changed successfully!\n");
    } else {
        printf("\t\t\t\t\t\t  Incorrect old password.\n");
    }
}

void cancelRenting(Product products[], Account *user) {
    if (user->rentedCount == 0) {
        printf("\t\t\t\t\t\t  No product is currently rented.\n");
        return;
    }

    printf("\t\t\t\t\t\t  Currently Rented Products:\n");
    for (int i = 0; i < user->rentedCount; i++) {
        printf("\t\t\t\t\t\t  %d. %s\n", i + 1, products[user->rentedProductIndices[i]].name);
    }
    printf("\t\t\t\t\t\t  Enter the number of the product you want to cancel: ");
    int cancelChoice;
    scanf("%d", &cancelChoice);
    getchar(); 

    if (cancelChoice < 1 || cancelChoice > user->rentedCount) {
        printf("\t\t\t\t\t\t  Invalid choice.\n");
        return;
    }

    int cancelIndex = user->rentedProductIndices[cancelChoice - 1];
    products[cancelIndex].isRented = 0;
    printf("\t\t\t\t\t\t\tCanceled renting of %s.\n", products[cancelIndex].name);

    
    char notification[100];
    snprintf(notification, sizeof(notification), "Canceled renting of %s", products[cancelIndex].name);
    addNotification(notification);

  
    for (int i = cancelChoice - 1; i < user->rentedCount - 1; i++) {
        user->rentedProductIndices[i] = user->rentedProductIndices[i + 1];
    }
    user->rentedCount--;
}
void storeUserDetails(Account user) {
    FILE *file = fopen("user_details.txt", "w");
    if (file == NULL) {
        printf("\t\t\t\t\t\t  Error opening file for writing.\n");
        return;
    }

    fprintf(file, "Username: %s\n", user.username);
    fprintf(file, "Password: %s\n", user.password);
    fprintf(file, "Balance: $%.2f\n", user.balance);
    if (user.rentedCount > 0) {
        fprintf(file, "Currently Rented Products:\n");
        for (int i = 0; i < user.rentedCount; i++) {
            fprintf(file, "- %s\n", products[user.rentedProductIndices[i]].name);
        }
    } else {
        fprintf(file, "No product currently rented.\n");
    }

    fclose(file);
    printf("\t\t\t\t\t\t  User details stored successfully.\n");
}


void store(Product products[], int numProducts) {
    printf("\t\t\t\t\t\t  Available Products:\n");
    for (int i = 0; i < numProducts; i++) {
        if (!products[i].isRented) {
            printf("\t\t\t\t\t\t\t%d. %s - %s - $%.2f\n", i + 1, products[i].category, products[i].name, products[i].price);
        }
    }

    printf("\t\t\t\t\t\t  Unavailable Products:\n");
    for (int i = 0; i < numProducts; i++) {
        if (products[i].isRented) {
            printf("\t\t\t\t\t\t  %d. %s - %s - $%.2f\n", i + 1, products[i].category, products[i].name, products[i].price);
        }
    }printf("\t\t\t\t\t\t  Press ANY key to Continue..\n");
    getch();
}