#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void display_bank_menu();
void open_new_account();
void close_account();
void add_money();
void take_money();
void send_money();
void save_to_log(char* activity);

int main() {
    printf("=== Bank Management System ===\n");
    printf("Welcome to Secure Banking!\n");
    
    system("mkdir database 2>nul");
    
    int user_selection;
    
    do {
        display_bank_menu();
        printf("Select an option: ");
        scanf("%d", &user_selection);
        
        while (getchar() != '\n');
        
        switch(user_selection) {
            case 1: open_new_account(); break;
            case 2: close_account(); break;
            case 3: add_money(); break;
            case 4: take_money(); break;
            case 5: send_money(); break;
            case 0: printf("Thank you for banking with us!\n"); break;
            default: printf("Invalid selection! Try again.\n");
        }
    } while (user_selection != 0);
    
    return 0;
}

void display_bank_menu() {
    printf("\n*** BANKING MENU ***\n");
    printf("1. Open New Account\n");
    printf("2. Close Account\n");
    printf("3. Add Funds\n");
    printf("4. Withdraw Funds\n");
    printf("5. Send Money\n");
    printf("0. Quit System\n");
    printf("********************\n");
}

void open_new_account() {
    printf("\n--- Open New Account ---\n");
    
    char customer_name[50], customer_id[20], account_kind[10], security_code[5];
    int new_account_number;
    float starting_balance = 0.0;
    
    printf("Enter customer name: ");
    scanf("%49s", customer_name);
    
    printf("Enter identification number: ");
    scanf("%19s", customer_id);
    
    printf("Account kind (Savings/Current): ");
    scanf("%9s", account_kind);
    
    printf("Set 4-digit security code: ");
    scanf("%4s", security_code);

    srand(time(NULL));
    new_account_number = 5000000 + rand() % 4000000; 
    
    char filepath[50];
    sprintf(filepath, "database/acc_%d.txt", new_account_number);
    
    FILE* account_file = fopen(filepath, "w");
    if (account_file == NULL) {
        printf("Failed to create account file!\n");
        return;
    }
    
    fprintf(account_file, "Customer: %s\n", customer_name);
    fprintf(account_file, "ID_Number: %s\n", customer_id);
    fprintf(account_file, "Account_Type: %s\n", account_kind);
    fprintf(account_file, "Security_Code: %s\n", security_code);
    fprintf(account_file, "Account_No: %d\n", new_account_number);
    fprintf(account_file, "Available_Balance: %.2f\n", starting_balance);
    fclose(account_file);
    
    FILE* master_list = fopen("database/accounts_list.txt", "a");
    if (master_list != NULL) {
        fprintf(master_list, "%d\n", new_account_number);
        fclose(master_list);
    }
    
    save_to_log("NEW_ACCOUNT_OPENED");
    
    printf("Account opened successfully!\n");
    printf("Your new account number: %d\n", new_account_number);
    printf("Welcome to our bank!\n");
}

void add_money() {
    printf("\n--- Add Funds to Account ---\n");
    
    int acc_number;
    char user_pin[5];
    float deposit_amount;
    
    printf("Enter account number: ");
    scanf("%d", &acc_number);
    
    printf("Enter security code: ");
    scanf("%4s", user_pin);
    
    char filepath[50];
    sprintf(filepath, "database/acc_%d.txt", acc_number);
    FILE* account_file = fopen(filepath, "r");
    
    if (account_file == NULL) {
        printf("Account does not exist!\n");
        return;
    }
    
    char stored_pin[5];
    char data_line[100];
    float current_balance;
    
    while (fgets(data_line, sizeof(data_line), account_file)) {
        if (sscanf(data_line, "Security_Code: %4s", stored_pin) == 1) continue;
        if (sscanf(data_line, "Available_Balance: %f", &current_balance) == 1) continue;
    }
    fclose(account_file);
    
    if (strcmp(user_pin, stored_pin) != 0) {
        printf("Incorrect security code!\n");
        return;
    }
    
    printf("Enter amount to deposit: RM ");
    scanf("%f", &deposit_amount);
    
    if (deposit_amount <= 0 || deposit_amount > 50000) {
        printf("Amount must be between RM 0.01 and RM 50,000\n");
        return;
    }
    
    current_balance += deposit_amount;
    
    account_file = fopen(filepath, "r");
    FILE* temp_file = fopen("database/temp_update.txt", "w");
    
    while (fgets(data_line, sizeof(data_line), account_file)) {
        if (strstr(data_line, "Available_Balance:")) {
            fprintf(temp_file, "Available_Balance: %.2f\n", current_balance);
        } else {
            fputs(data_line, temp_file);
        }
    }
    
    fclose(account_file);
    fclose(temp_file);
    
    remove(filepath);
    rename("database/temp_update.txt", filepath);
    
    save_to_log("FUNDS_ADDED");
    printf("Deposit completed! New balance: RM %.2f\n", current_balance);
}

void take_money() {
    printf("\n--- Withdraw Funds ---\n");
    
    int acc_number;
    char user_pin[5];
    float withdrawal_amount;
    
    printf("Enter account number: ");
    scanf("%d", &acc_number);
    
    printf("Enter security code: ");
    scanf("%4s", user_pin);
    
    char filepath[50];
    sprintf(filepath, "database/acc_%d.txt", acc_number);
    FILE* account_file = fopen(filepath, "r");
    
    if (account_file == NULL) {
        printf("Account not found in system!\n");
        return;
    }
    
    char stored_pin[5];
    char data_line[100];
    float current_balance;
    
    while (fgets(data_line, sizeof(data_line), account_file)) {
        if (sscanf(data_line, "Security_Code: %4s", stored_pin) == 1) continue;
        if (sscanf(data_line, "Available_Balance: %f", &current_balance) == 1) continue;
    }
    fclose(account_file);
    
    if (strcmp(user_pin, stored_pin) != 0) {
        printf("Security code verification failed!\n");
        return;
    }
    
    printf("Current available balance: RM %.2f\n", current_balance);
    printf("Enter withdrawal amount: RM ");
    scanf("%f", &withdrawal_amount);
    
    if (withdrawal_amount <= 0 || withdrawal_amount > 50000) {
        printf("Invalid amount entered!\n");
        return;
    }
    
    if (withdrawal_amount > current_balance) {
        printf("Insufficient funds for this transaction!\n");
        return;
    }
    
    current_balance -= withdrawal_amount;
    
    account_file = fopen(filepath, "r");
    FILE* temp_file = fopen("database/temp_update.txt", "w");
    
    while (fgets(data_line, sizeof(data_line), account_file)) {
        if (strstr(data_line, "Available_Balance:")) {
            fprintf(temp_file, "Available_Balance: %.2f\n", current_balance);
        } else {
            fputs(data_line, temp_file);
        }
    }
    
    fclose(account_file);
    fclose(temp_file);
    
    remove(filepath);
    rename("database/temp_update.txt", filepath);
    
    save_to_log("FUNDS_WITHDRAWN");
    printf("Withdrawal successful! Remaining balance: RM %.2f\n", current_balance);
}

void send_money() {
    printf("\n--- Send Money to Another Account ---\n");
    
    int sender_account, receiver_account;
    char sender_pin[5];
    float transfer_amount;
    
    printf("Enter your account number: ");
    scanf("%d", &sender_account);
    
    printf("Enter your security code: ");
    scanf("%4s", sender_pin);
    
    printf("Enter recipient account number: ");
    scanf("%d", &receiver_account);
    
    if (sender_account == receiver_account) {
        printf("Cannot send money to your own account!\n");
        return;
    }
    
    char sender_file[50], receiver_file[50];
    sprintf(sender_file, "database/acc_%d.txt", sender_account);
    sprintf(receiver_file, "database/acc_%d.txt", receiver_account);
    
    FILE* s_file = fopen(sender_file, "r");
    FILE* r_file = fopen(receiver_file, "r");
    
    if (s_file == NULL || r_file == NULL) {
        printf("One or both accounts not found in system!\n");
        if (s_file) fclose(s_file);
        if (r_file) fclose(r_file);
        return;
    }
    
    char data_line[100], correct_pin[5], sender_type[10], receiver_type[10];
    float sender_balance, receiver_balance;
    
    while (fgets(data_line, sizeof(data_line), s_file)) {
        if (sscanf(data_line, "Security_Code: %4s", correct_pin) == 1) continue;
        if (sscanf(data_line, "Account_Type: %9s", sender_type) == 1) continue;
        if (sscanf(data_line, "Available_Balance: %f", &sender_balance) == 1) continue;
    }
    fclose(s_file);

    if (strcmp(sender_pin, correct_pin) != 0) {
        printf("Security code incorrect!\n");
        fclose(r_file);
        return;
    }
    
    while (fgets(data_line, sizeof(data_line), r_file)) {
        if (sscanf(data_line, "Account_Type: %9s", receiver_type) == 1) continue;
        if (sscanf(data_line, "Available_Balance: %f", &receiver_balance) == 1) continue;
    }
    fclose(r_file);
    
    printf("Enter transfer amount: RM ");
    scanf("%f", &transfer_amount);
    
    if (transfer_amount <= 0 || transfer_amount > 50000) {
        printf("Invalid transfer amount!\n");
        return;
    }
    
    if (transfer_amount > sender_balance) {
        printf("Insufficient balance for transfer!\n");
        return;
    }

    float service_fee = 0;
    if (strcmp(sender_type, "Savings") == 0 && strcmp(receiver_type, "Current") == 0) {
        service_fee = transfer_amount * 0.02;
    } else if (strcmp(sender_type, "Current") == 0 && strcmp(receiver_type, "Savings") == 0) {
        service_fee = transfer_amount * 0.03;
    }
    
    float total_deduction = transfer_amount + service_fee;
    
    if (total_deduction > sender_balance) {
        printf("Insufficient funds including service fee!\n");
        return;
    }
    
    sender_balance -= total_deduction;
    receiver_balance += transfer_amount;
    
    s_file = fopen(sender_file, "r");
    FILE* temp_sender = fopen("database/temp_sender.txt", "w");
    while (fgets(data_line, sizeof(data_line), s_file)) {
        if (strstr(data_line, "Available_Balance:")) {
            fprintf(temp_sender, "Available_Balance: %.2f\n", sender_balance);
        } else {
            fputs(data_line, temp_sender);
        }
    }
    fclose(s_file);
    fclose(temp_sender);
    
    r_file = fopen(receiver_file, "r");
    FILE* temp_receiver = fopen("database/temp_receiver.txt", "w");
    while (fgets(data_line, sizeof(data_line), r_file)) {
        if (strstr(data_line, "Available_Balance:")) {
            fprintf(temp_receiver, "Available_Balance: %.2f\n", receiver_balance);
        } else {
            fputs(data_line, temp_receiver);
        }
    }
    fclose(r_file);
    fclose(temp_receiver);
    
    remove(sender_file);
    remove(receiver_file);
    rename("database/temp_sender.txt", sender_file);
    rename("database/temp_receiver.txt", receiver_file);
    
    save_to_log("MONEY_TRANSFER");
    printf("Transfer completed successfully!\n");
    if (service_fee > 0) {
        printf("Service fee charged: RM %.2f\n", service_fee);
    }
    printf("Your updated balance: RM %.2f\n", sender_balance);
}

void close_account() {
    printf("\n--- Close Account ---\n");
    
    int acc_number;
    char user_pin[5], user_id[20];
    
    printf("Enter account number to close: ");
    scanf("%d", &acc_number);
    
    printf("Enter security code: ");
    scanf("%4s", user_pin);
    
    printf("Enter last 4 digits of ID: ");
    scanf("%4s", user_id);
    
    char filepath[50];
    sprintf(filepath, "database/acc_%d.txt", acc_number);
    FILE* account_file = fopen(filepath, "r");
    
    if (account_file == NULL) {
        printf("Account not found!\n");
        return;
    }
    
    char correct_pin[5], full_id[20], data_line[100];
    
    while (fgets(data_line, sizeof(data_line), account_file)) {
        if (sscanf(data_line, "Security_Code: %4s", correct_pin) == 1) continue;
        if (sscanf(data_line, "ID_Number: %19s", full_id) == 1) continue;
    }
    fclose(account_file);
    
    char last_four[5];
    strncpy(last_four, full_id + strlen(full_id) - 4, 4);
    last_four[4] = '\0';
    
    if (strcmp(user_pin, correct_pin) != 0 || strcmp(user_id, last_four) != 0) {
        printf("Account verification failed!\n");
        return;
    }
    
    if (remove(filepath) == 0) {
        printf("Account closed successfully!\n");
        save_to_log("ACCOUNT_CLOSED");
    } else {
        printf("Error during account closure!\n");
    }
}

void save_to_log(char* activity) {
    FILE* log_file = fopen("database/bank_activities.log", "a");
    if (log_file != NULL) {
        time_t current_time = time(NULL);
        fprintf(log_file, "[%s] %s\n", ctime(&current_time), activity);
        fclose(log_file);
    }
}