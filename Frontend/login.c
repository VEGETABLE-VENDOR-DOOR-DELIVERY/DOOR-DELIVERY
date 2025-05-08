#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 2048

void urldecode(char *src, char *dest) {
    char a, b;
    while (*src) {
        if ((*src == '%') && isxdigit(*(src + 1)) && isxdigit(*(src + 2))) {
            a = *(src + 1);
            b = *(src + 2);
            a = (a >= 'A') ? ((a & ~0x20) - 'A' + 10) : (a - '0');
            b = (b >= 'A') ? ((b & ~0x20) - 'A' + 10) : (b - '0');
            *dest++ = 16 * a + b;
            src += 3;
        } else if (*src == '+') {
            *dest++ = ' ';
            src++;
        } else {
            *dest++ = *src++;
        }
    }
    *dest = '\0';
}

void parseForm(char *data, char *email, char *password) {
    char *token = strtok(data, "&");
    while (token) {
        if (strncmp(token, "email=", 6) == 0) strcpy(email, token + 6);
        else if (strncmp(token, "password=", 9) == 0) strcpy(password, token + 9);
        token = strtok(NULL, "&");
    }
}

int main() {
    char *lenStr = getenv("CONTENT_LENGTH");
    int len = lenStr ? atoi(lenStr) : 0;

    char input[MAX] = {0}, decoded[MAX] = {0};
    char email[100] = "", password[100] = "", role[20] = "";

    if (len > 0 && len < MAX) {
        fread(input, 1, len, stdin);
        urldecode(input, decoded);
        parseForm(decoded, email, password);

        FILE *file = fopen("users.txt", "r");
        if (file) {
            char line[512];
            int found = 0;
            while (fgets(line, sizeof(line), file)) {
                char file_email[100], file_password[100], file_role[20];
                int matched = sscanf(line, "%*[^,],%*[^,],%[^,],%[^,],%[^,]", file_email, file_password, file_role);
                file_password[strcspn(file_password, "\n")] = 0;
                file_role[strcspn(file_role, "\n")] = 0;

                if (matched == 3 && strcmp(email, file_email) == 0 && strcmp(password, file_password) == 0) {
                    strcpy(role, file_role);
                    found = 1;
                    break;
                }
            }
            fclose(file);

            if (found) {
                // ? Send redirect headers
                printf("Status: 302 Found\n");
                if (strcmp(role, "customer") == 0)
                    printf("Location: /product_list_page.html\n\n");
                else if (strcmp(role, "vendor") == 0)
                    printf("Location: /admin%%20page.html\n\n");
                else
                    printf("Location: /login.html\n\n"); // fallback
                return 0;
            }
        }
    }

    // ? Failed login response
    printf("Content-type: text/html\n\n");
    printf("<html><body><h2 style='color:red;'>Invalid email or password.</h2></body></html>");
    return 0;
}

