#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

char current_user[100];
char current_user_password[100];
int login_status = 0;

struct  Register {
    char user[100];
    char password[100];
    char con_password[100];
} reg;

struct Login {
    char user[100];
    char password[100];
} login;


void clear_my_screen() {
    printf("\n");
    printf("\e[1:1h\e[2J");
    printf("\n");
}

void create_user() {
    FILE *fptr1;
    FILE *fptr2;
    fptr1 = fopen("./Texts/users.txt", "ab+");
    fptr2 = fopen("./Texts/passwords.txt", "ab+");
    printf("Create User:\n");
    printf("\t Enter User Name:");
    scanf("%s", reg.user);
    redo :
    printf("\t Enter the password:");
    scanf("%s", reg.password);
    printf("\t Confirm password:");
    scanf("%s", reg.con_password);
    int val = strcmp(reg.password, reg.con_password);
    if(val != 0) {
        printf("Password is not Valid:\n");
        goto redo;
    }
    fprintf(fptr1, "%s\n", reg.user);
    fprintf(fptr2, "%s\n", reg.password);
    fclose(fptr1);
    fclose(fptr2);
    printf("\nConfirming details...\n...\nWelcome, %s!\n\n",reg.user);
    printf("\nRegistration Successful!\n");
    printf("Press any key to continue...");
    getch();
    clear_my_screen();
}

void login_user() {
    // login_user :
    while (1) {
        FILE *fptr1;
        FILE *fptr2;
        char s;
        fptr1 = fopen("./Texts/users.txt", "r");
        fptr2 = fopen("./Texts/passwords.txt", "r");
        printf("Login:\n");
        if (fptr1 == NULL) {
            printf("This file does not exits...\n");
            return;
        }
        char on_user[100];
        char on_password[100];
        printf("\t Enter User Name:");
        scanf("%s", login.user);
        int  i = 0, line = 0, user_exists = 0;
        //Read user names from file user.txt
        while (fscanf(fptr1, "%s", on_user) != EOF) {
            if (strcmp(on_user, login.user) == 0) {
                line = i;
                user_exists = 1;
                break;
            }
            i++;
        }
        if (user_exists == 0) {
            printf("User does not exist!\n");
            printf("Press any key to continue...");
            getch();
            continue;
        }
        printf("%s\n", on_user);
        // Fetch the password in the current line from passwords.txt
        int internal_lines = 0;
        while (fscanf(fptr2, "%s", on_password) != EOF) {
            if (internal_lines == line) {
                break;
            }
            internal_lines++;
        }
        printf("%s\n", on_password);
        if (strcmp(login.user, on_user) != 0) {
            printf("User name is not valid...\n");
            break;
        }
        else {
            printf("User is valid...\n");
        }
        printf("\t Enter the password:");
        scanf("%s", login.password);
        if (strcmp(login.password, on_password) == 0) {
            printf("\n\nWelcome, %s!\n\n", login.user);
            printf("\nLogin Successful!\n");
            strcpy(current_user, login.user);
            strcpy(current_user_password, login.password);
            login_status = 1;
            fclose(fptr1);
            fclose(fptr2);
            break;
        }
        else {
            printf("\n\nLogin Failed!\n\n");
            on_user[0] = '\0';
            on_password[0] = '\0';
            line = 0;
            i = 0;
            fclose(fptr1);
            fclose(fptr2);
            continue;
        }
    }
}

// Delete a user and its password from user.txt and password.txt
void delete_user() {
    while (1) {
        char on_user[100];
        char on_password[100];
        FILE *fptr1;
        FILE *fptr2;
        fptr1 = fopen("./Texts/users.txt", "r");
        fptr2 = fopen("./Texts/passwords.txt", "r");
        printf("Delete User:\n");
        if (fptr1 == NULL) {
            printf("This file does not exits...\n");
            return;
        }
        printf("\t Enter User Name:");
        scanf("%s", login.user);
        int  i = 0, line = 0, user_exists = 0;
        //Read user names from file user.txt
        while (fscanf(fptr1, "%s", on_user) != EOF) {
            if (strcmp(on_user, login.user) == 0) {
                line = i;
                user_exists = 1;
                break;
            }
            i++;
        }
        if (user_exists == 0) {
            printf("User does not exist!\n");
            printf("Press any key to continue...");
            getch();
            continue;
        }
        printf("%s\n", on_user);
        // Fetch the password in the current line from passwords.txt
        int internal_lines = 0;
        while (fscanf(fptr2, "%s", on_password) != EOF) {
            if (internal_lines == line) {
                break;
            }
            internal_lines++;
        }
        printf("%s\n", on_password);
        if (strcmp(login.user, on_user) != 0) {
            printf("User name is not valid...\n");
            printf("Press any key to continue...");
            getch();
            continue;
        }
        else {
            printf("User is valid...\n");
        }
        printf("\t Enter the password:");
        scanf("%s", login.password);
        if (strcmp(login.password, on_password)) {
            printf("\n\nLogin Failed!\n\n");
            on_user[0] = '\0';
            on_password[0] = '\0';
            line = 0;
            i = 0;
            fclose(fptr1);
            fclose(fptr2);
            continue;
        }
        else {
            printf("\n\nLogin Successful!\n");
            printf("\nDeleting User...\n");
            fclose(fptr1);
            fclose(fptr2);
        }
        printf("%d\n", line);
        // Delete a line from user.txt
        FILE *fptr3;
        fptr3 = fopen("./Texts/users.txt", "r");
        FILE *fptr4;
        fptr4 = fopen("./Texts/users_temp.txt", "w");
        internal_lines = 0;
        while (fscanf(fptr3, "%s", on_user) != EOF) {
            if (internal_lines == line) {
                internal_lines++;
                continue;
            }
            fprintf(fptr4, "%s\n", on_user);
            internal_lines++;
        }
        fclose(fptr3);
        fclose(fptr4);
        remove("./Texts/users.txt");
        rename("./Texts/users_temp.txt", "./Texts/users.txt");
        // Delete a line from password.txt
        FILE *fptr5;
        fptr5 = fopen("./Texts/passwords.txt", "r");
        FILE *fptr6;
        fptr6 = fopen("./Texts/passwords_temp.txt", "w");
        internal_lines = 0;
        while (fscanf(fptr5, "%s", on_password) != EOF) {
            if (internal_lines == line) {
                internal_lines++;
                continue;
            }
            fprintf(fptr6, "%s\n", on_password);
            internal_lines++;
        }
        fclose(fptr5);
        fclose(fptr6);
        remove("./Texts/passwords.txt");
        rename("./Texts/passwords_temp.txt", "./Texts/passwords.txt");
        printf("\n\nUser deleted successfully!\n\n");
        printf("Press any key to continue...");
        getch();
        break;
    }
}

void main_screen() {
    FILE *fptr;
    char s;
    fptr = fopen("./Texts/header.txt", "r");
    if (fptr == NULL) {
        printf("File doesn't exits\n");
        return;
    }
    while((s=fgetc(fptr))!=EOF) {
        printf("%c", s);
    }
    fclose(fptr);
}

void main_login() {
    clear_my_screen();
    main_screen();
    int option;
    printf("\n\tWelcome to our online Ecommerece platform....\n");
    printf("\tPress '1' to Register\n\tPress '2' to Login\n\tPress '3' to Delete User\n\n");
    scanf("%d", &option);
    switch (option) {
        case 1:
            create_user();
            break;
        case 2:
            login_user();
            break;
        case 3:
            delete_user();
            break;
        default:
            printf("Invalid option!\n");
            break;
    
    }
}