#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

char current_user[100];
char current_password[100];

// Count the lines of a file
int count_lines(char filename[100]) {
    FILE *fp;
    char ch;
    int lines = 0;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File not found\n");
        exit(0);
    }
    ch = fgetc(fp);
    while (ch != EOF) {
        if (ch == '\n')
            lines++;
        ch = fgetc(fp);
    }
    fclose(fp);
    return lines;
}

// Display all the commands which can be used by the user
void help() {
    FILE *fptr;
    fptr = fopen("./Texts/help.txt", "r");
    char ch;
    while ((ch = fgetc(fptr)) != EOF) {
        printf("%c", ch);
    }
    fclose(fptr);
}

void view_items() {
    FILE *fptr1;
    FILE *fptr2;
    FILE *fptr3;
    int lines = count_lines("./items/items.txt");
    fptr1 = fopen("./items/items.txt", "r");
    fptr2 = fopen("./items/rate.txt", "r");
    fptr3 = fopen("./items/stock.txt", "r");
    int i = 0;
    printf("\n");
    printf("S.no\tName\tRate\tStock\n");
    char item[100], rate[100], stock[100];
    while (fscanf(fptr1,"\n%[^\n]%*c", item) != EOF && fscanf(fptr2, "%s", rate) != EOF && fscanf(fptr3, "%s", stock) != EOF) {
        if (i > lines) {
            break;
        }
        printf("%d\t%s\t%s\t%s\n", i+1, item, rate, stock);
        i++;
    }
    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
}

void create_cart(char username[100]) {
    FILE *fptr;
    char command[100] =  "./users/", amount_file[100];
    strcat(command, username);
    strcat(amount_file, "/amount.txt");
    strcat(command, "/cart.txt");
    if ((fptr = fopen(command, "r")) != NULL) {
        printf("\n\t Cart already exits.. Delete before creating a new cart\n");
        fclose(fptr);
        return;
    }
    fclose(fptr);
    FILE *am_fptr;
    fptr = fopen(command, "w");
    am_fptr = fopen(amount_file, "w");
    fprintf(fptr, "User: %s\n", username);
    fprintf(fptr, "Sno\tName\tRate\tQuantity\tAmount\n");
    printf("\n\tCart created sucessfully....\n");
    fclose(fptr);
    fclose(am_fptr);
}

void remove_cart(char username[100]) {
    char command[100] =  "./users/";
    strcat(command, username);
    strcat(command, "/cart.txt");
    if (remove(command) != 0) {
        printf("\n\t Cart does not exits..\n");
        return;
    }
    else {
        printf("\n\t Cart deleted successfully...\n");
    }    
}


void add_to_cart(char username[100],char item[100], char rate[100], char stock[100], int quantity, int amount) {
    FILE *fptr;
    char filename[100] = "./users/";
    strcat(filename, username);
    strcat(filename, "/cart.txt");
    int lines = count_lines(filename);
    fptr = fopen(filename, "a");
    fprintf(fptr, "%d\t%s\t%s\t%d\t\t%d\n", lines - 1, item, rate, quantity, amount);
    printf("\n\tItem added successfully...\n");
    fclose(fptr);
}

void add_prompt(char username[100]) {
    int id, quantity, amount;
    printf("\n\n\tEnter the s.no of the item: ");
    scanf("%d", &id);
    if (id > count_lines("./items/items.txt")) {
        printf("\n\n\tItem does not exist!\n\n");
        return;
    }
    // Read item, rate and stock from files on the paricular line
    FILE *fptr1;
    FILE *fptr2;
    FILE *fptr3;
    fptr1 = fopen("./items/items.txt", "r");
    fptr2 = fopen("./items/rate.txt", "r");
    fptr3 = fopen("./items/stock.txt", "r");
    char item[100], rate[100], stock[100];
    int i = 0;
    while (fscanf(fptr1,"\n%[^\n]%*c", item) != EOF && fscanf(fptr2, "%s", rate) != EOF && fscanf(fptr3, "%s", stock) != EOF) {
        if (i == id-1) {
            break;
        }
        i++;
    }
    printf("\tEnter the quantity: ");
    scanf("%d", &quantity);
    amount = quantity * atoi(rate);
    add_to_cart(username, item, rate, stock, quantity, amount);
    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
}

void view_cart(char username[100]) {
    FILE *fptr;
    char command[100] = "./users/";
    strcat(command, username);
    strcat(command, "/cart.txt");
    if ((fptr = fopen(command, "r")) == NULL) {
        printf("\n\tCart does not exist!\n");
        return;
    }
    char ch;
    while ((ch = fgetc(fptr)) != EOF) {
        printf("%c", ch);
    }
    fclose(fptr);
}

void remove_prompt(char username[100]) {
    int id;
    printf("\n\n\tEnter the s.no of the item: ");
    scanf("%d", &id);
    char command[100] = "./users/", command2[100] = "./users/";
    strcat(command, username);
    strcat(command2, username);
    strcat(command2, "/cart_temp.txt");
    strcat(command, "/cart.txt");
    if (id > count_lines(command) - 2) {
        printf("\n\n\tItem does not exist!\n\n");
        return;
    }
    FILE *fptr1;
    FILE *fptr2;
    // FILE *fptr3;
    // FILE *fptr4;
    fptr1 = fopen(command, "r");
    fptr2 = fopen(command2, "w");
    // fptr3 = fopen("./users/%s/amount.txt", "r");
    // fptr4 = fopen("./users/%s/amount.txt", "w");
    char item[100];
    char entries[100][100];
    int i = 0, condition = 0;
    while (fscanf(fptr1,"\n%[^\n]%*c", item) != EOF) { // && fscanf(fptr3, "%s", rate) != EOF && fscanf(fptr3, "%s", stock) != EOF
        if (i < 2) {
            fprintf(fptr2, "%s\n", item);         
        }
        else if (i == id + 1) {
            condition = 1;
        }
        else if (i < id + 1) {
            fprintf(fptr2, "%s\n", item);
        }
        else if (condition) {
            char item_temp[100];
            int no_char = 0;
            for (int a = 0; a < strlen(item); a++) {
                if (item[a] != '\t') {
                    no_char++;
                    continue;
                }
                break;
            }
            int b = no_char;
            for (int a = 0; a < strlen(item) - no_char; a++) {
                item_temp[a] = item[b];
                b++;
            }
            fprintf(fptr2, "%d", i - 2);
            fprintf(fptr2, "%s\n", item_temp);
        }
        i++;
    }
    printf("\n\tItem deleted successfully...\n");
    fclose(fptr1);
    fclose(fptr2);
    if (remove(command)) {
        printf("\n\tError in deleting the file...\n");
    }
    rename(command2, command);
}

void update_user(char current_username[100], char current_password[100]) {
    char verify_password[100], new_username[100], confirm_new_username[100];
    printf("\n\n\tEnter the current password: ");
    scanf("%s", verify_password);
    if (strcmp(verify_password, current_password) != 0) {
        printf("\n\n\tWrong password!\n\n");
        return;
    }
    while (1) {
        printf("\n\n\tEnter the new username: ");
        scanf("%s", new_username);
        printf("\tConfirm the new username: ");
        scanf("%s", confirm_new_username);
        if (!strcmp(new_username, confirm_new_username)) {
            break;
        }
        else {
            printf("\n\n\tUsername does not match!\n\n");
        }
    }
    if (strcmp(new_username, current_username) == 0) {
        printf("\n\n\tUsername already exists!\n\n");
        return;
    }
    char command[100] = "./Texts/users.txt", command2[100] = "./Texts/users_temp.txt";
    FILE *fptr1;
    FILE *fptr2;
    if ((fptr1 = fopen(command, "r")) == NULL) {
        printf("\n\tError in opening the file...\n");
    }
    fptr2 = fopen(command2, "w");
    char line[100];
    while (fscanf(fptr1,"\n%[^\n]%*c", line) != EOF) {
        if (strcmp(current_username, line) == 0) {
            fprintf(fptr2, "%s\n", new_username);
            continue;
        }
        fprintf(fptr2, "%s\n", line);
    }
    fclose(fptr1);
    fclose(fptr2);
    if (remove(command)) {
        printf("\n\tError in deleting the file...\n");
    }
    rename(command2, command);
    // Rename existing directory of the user
    char command3[100] = "cd users && ren ";
    strcat(command3, current_username);
    strcat(command3, " ");
    strcat(command3, new_username);
    system(command3);
    strcpy(current_user, new_username);
    printf("\n\n\tUsername changed successfully...\n\n");
}

void change_password(char current_username[100], char current_password[100]) {
    char verify_password[100], new_password[100], confirm_new_password[100];
    printf("\n\n\tEnter the current password: ");
    scanf("%s", verify_password);
    if (strcmp(verify_password, current_password) != 0) {
        printf("\n\n\tWrong password!\n\n");
        return;
    }
    while (1) {
        printf("\n\n\tEnter the new password: ");
        scanf("%s", new_password);
        if (!strcmp(new_password, current_password)) {
            printf("\n\n\tPassword cannot be same as the current password!\n\n");
            continue;
        }
        printf("\tConfirm the new password: ");
        scanf("%s", confirm_new_password);
        if (!strcmp(new_password, confirm_new_password)) {
            break;
        }
        else {
            printf("\n\n\tPassword does not match!\n\n");
        }
    }
    char command[100] = "./Texts/passwords.txt", command2[100] = "./Texts/passwords_temp.txt";
    FILE *fptr1;
    FILE *fptr2;
    if ((fptr1 = fopen(command, "r")) == NULL) {
        printf("\n\tError in opening the file...\n");
    }
    fptr2 = fopen(command2, "w");
    char line[100];
    while (fscanf(fptr1,"\n%[^\n]%*c", line) != EOF) {
        if (strcmp(current_password, line) == 0) {
            fprintf(fptr2, "%s\n", new_password);
            continue;
        }
        fprintf(fptr2, "%s\n", line);
    }
    fclose(fptr1);
    fclose(fptr2);
    if (remove(command)) {
        printf("\n\tError in deleting the file...\n");
    }
    rename(command2, command);
    strcpy(current_user_password, new_password);
    printf("\n\n\tPassword changed successfully...\n\n");
}