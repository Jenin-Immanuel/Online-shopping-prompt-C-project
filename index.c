#include "./modules/login.h"
#include "./modules/userfunctionalities.h"
#include "./modules/superuser.h"
#include "./modules/utilities.h"

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
        if (!strcmp(current_user, "Admin")) {
            // Only for admin user which is the supplier
            sudo_main();
        }
        else {
            // Normal user prompt
            while (1) {
                char prompt_string[100];
                display_prompt();
                scanf("%s", prompt_string);
                if (!strcmp(prompt_string, "help")) {
                    help();
                }
                else if (!strcmp(prompt_string, "items")) {
                    view_items();
                }
                else if (!strcmp(prompt_string, "add")) {
                    add_prompt(current_user);
                }
                else if (!strcmp(prompt_string, "remove")) {
                    remove_prompt(current_user);
                }
                else if (!strcmp(prompt_string, "create_cart")) {
                    create_cart(current_user);
                }
                else if (!strcmp(prompt_string, "remove_cart")) {
                    remove_cart(current_user);
                }
                else if (!strcmp(prompt_string, "cart")) {
                    view_cart(current_user);
                }
                else if (!strcmp(prompt_string, "clear_screen")) {
                    clear_my_screen();
                }
                else if (!strcmp(prompt_string, "logout")) {
                    break;
                }
                else if (!strcmp(prompt_string, "update_user")) {
                    update_user(current_user, current_user_password);
                }
                else if (!strcmp(prompt_string, "change_password")) {
                    change_password(current_user, current_user_password);
                }
                else {
                    printf("\n\tInvalid command!\n");
                }
            }
        }
    }
    return 0;
}