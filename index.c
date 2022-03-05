#include "./modules/login.h"
#include "./modules/userfunctionalities.h"

extern char current_user[100];
extern char current_user_password[100];
extern int login_status;

void display_prompt() {
    printf("\n%s> ", current_user);
}

int main() {
    while (1) {
        login_status = 0;
        do {
            main_login();
        } while (login_status == 0);
        while (1) {
            char prompt_string[100];
            display_prompt();
            scanf("%s", prompt_string);
            if (!strcmp(prompt_string, "help")) {
                help();
            }
            else if (!strcmp(prompt_string, "logout")) {
                break;
            }
            else if (!strcmp(prompt_string, "items")) {
                view_items();
            }
        }
    }
    return 0;
}