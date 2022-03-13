#include "utilities.h"

void display_users() {
    FILE *fptr;
    fptr = fopen("./Texts/users.txt", "r");
    char user[100];
    printf("\n\tUsers using this application:\n");
    while (fscanf(fptr, "%s", user) != EOF) {
        if (!strcmp(user, "Admin")) {
            continue;
        }
        printf("\t%s\n", user);
    }
    fclose(fptr);
}

void add_item() {
    // Add new item with its rate and stock
    FILE *fptr1;
    FILE *fptr2;
    FILE *fptr3;
    fptr1 = fopen("./items/items.txt", "a");
    fptr2 = fopen("./items/rate.txt", "a");
    fptr3 = fopen("./items/stock.txt", "a");
    char item[100], rate[100], stock[100];
    printf("\n\tEnter the name of the item: ");
    scanf("%s", item);
    printf("\n\tEnter the rate of the item: ");
    scanf("%s", rate);
    printf("\n\tEnter the stock of the item: ");
    scanf("%s", stock);
    fprintf(fptr1, "%s\n", item);
    fprintf(fptr2, "%s\n", rate);
    fprintf(fptr3, "%s\n", stock);
    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
    printf("\n\tItem added successfully!\n");
}

void sudo_view_items() {
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

void delete_item() {
    // Delete item and the corresponding rate and stock from items.txt, rate.txt and stock.txt
    char item[100], rate[100], stock[100], current_item[100];
    printf("\n\tEnter the name of the item: ");
    scanf("%s", current_item);
    FILE *fptr1;
    FILE *fptr2;
    FILE *fptr3;
    FILE *fptr4;
    FILE *fptr5;
    FILE *fptr6;
    fptr1 = fopen("./items/items.txt", "r");
    fptr2 = fopen("./items/rate.txt", "r");
    fptr3 = fopen("./items/stock.txt", "r");
    fptr4 = fopen("./items/items_temp.txt", "w");
    fptr5 = fopen("./items/rate_temp.txt", "w");
    fptr6 = fopen("./items/stock_temp.txt", "w");
    int flag = 0;
    while (fscanf(fptr1, "\n%[^\n]%*c", item) != EOF && fscanf(fptr2, "\n%[^\n]%*c", rate) != EOF && fscanf(fptr3, "\n%[^\n]%*c", stock) != EOF) {
        if (strcmp(current_item, item) != 0) {
            fprintf(fptr4, "%s\n", item);
            fprintf(fptr5, "%s\n", rate);
            fprintf(fptr6, "%s\n", stock);
        }
        else flag = 1;
    }
    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
    fclose(fptr4);
    fclose(fptr5);
    fclose(fptr6);
    remove("./items/items.txt");
    remove("./items/rate.txt");
    remove("./items/stock.txt");
    rename("./items/items_temp.txt", "./items/items.txt");
    rename("./items/rate_temp.txt", "./items/rate.txt");
    rename("./items/stock_temp.txt", "./items/stock.txt");
    if (!flag) {
        printf("\n\tThe item is not found!\n");
    }
    else {
        printf("\n\tItem deleted successfully!\n");
    }
}

void update_stock() {
    // Update the stock by getting the item name and changing the corresponding stock in stock.txt
    char item[100], stock[100], current_item[100], new_stock[100];
    printf("\n\tEnter the name of the item: ");
    scanf("%s", current_item);
    FILE *fptr1;
    FILE *fptr2;
    FILE *fptr3;
    fptr1 = fopen("./items/items.txt", "r");
    fptr2 = fopen("./items/stock.txt", "r");
    fptr3 = fopen("./items/stock_temp.txt", "w");
    int flag = 0;
    while(fscanf(fptr1, "\n%[^\n]%*c", item) != EOF && fscanf(fptr2, "\n%[^\n]%*c", stock) != EOF) {
        if (strcmp(current_item, item) != 0) {
            fprintf(fptr3, "%s\n", stock);
        }
        else {
            printf("\n\tEnter the new stock of the item: ");
            scanf("%s", new_stock);
            fprintf(fptr3, "%s\n", new_stock);
            flag = 1;
        }
    }
    if (flag) {
        printf("\n\tStock updated successfully!\n");
    }
    else {
        printf("\n\tThe item name is invalid!!\n");
    }
    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
    if (remove("./items/stock.txt")) {
        printf("\n\tError in deleting the file!\n");
    }
    rename("./items/stock_temp.txt", "./items/stock.txt");
}

void sudo_help() {
    FILE *fptr;
    fptr = fopen("./users/Admin/help.txt", "r");
    char s;
    while (fscanf(fptr, "%c", &s) != EOF) {
        printf("%c", s);
    }
    fclose(fptr);
}


void sudo_main() {
    printf("\nYou are now an admin.....\n");
    while (1) {
        char prompt_string[100];
        printf("\nAdmin> ");
        scanf("%s", prompt_string);
        if (!strcmp(prompt_string, "help")) {
            sudo_help();
        }
        else if (!strcmp(prompt_string, "add_item")) {
            add_item();
        }
        else if (!strcmp(prompt_string, "delete_item")) {
            delete_item();
        }
        else if (!strcmp(prompt_string, "items")) {
            sudo_view_items();
        }
        else if (!strcmp(prompt_string, "users")) {
            display_users();
        }
        else if (!strcmp(prompt_string, "update_stock")) {
            update_stock();
        }
        else if (!strcmp(prompt_string, "logout")) {
            break;
        }
        else {
            printf("\nInvalid command!\n");
        }
    }
}