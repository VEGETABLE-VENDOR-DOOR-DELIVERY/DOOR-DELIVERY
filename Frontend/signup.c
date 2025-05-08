#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 2048

void urldecode(char *src, char *dest) {
    char a, b;
    while (*src) {
        if ((*src == '%') && isxdigit(src[1]) && isxdigit(src[2])) {
            a = src[1];
            b = src[2];
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

void parseForm(char *data, char *name, char *email, char *password, char *role, char *phone) {
    char *token = strtok(data, "&");
    while (token) {
        if (strncmp(token, "name=", 5) == 0) strcpy(name, token + 5);
        else if (strncmp(token, "email=", 6) == 0) strcpy(email, token + 6);
        else if (strncmp(token, "password=", 9) == 0) strcpy(password, token + 9);
        else if (strncmp(token, "role=", 5) == 0) strcpy(role, token + 5);
        else if (strncmp(token, "phone=", 6) == 0) strcpy(phone, token + 6);
        token = strtok(NULL, "&");
    }
}

int main() {
    char *lenStr = getenv("CONTENT_LENGTH");
    int len = lenStr ? atoi(lenStr) : 0;

    char input[MAX] = {0}, decoded[MAX] = {0};
    char name[100] = "", email[100] = "", password[100] = "", role[20] = "", phone[30] = "";

    if (len > 0 && len < MAX) {
        fread(input, 1, len, stdin);
        urldecode(input, decoded);
        parseForm(decoded, name, email, password, role, phone);

        FILE *file = fopen("users.txt", "a+");
        if (file) {
            // Count ID
            int id = 1;
            char temp[512];
            while (fgets(temp, sizeof(temp), file)) id++;

            fprintf(file, "%d,%s,%s,%s,%s,%s\n", id, name, email, password, role, phone);
            fclose(file);

            // ? Redirect based on role
            printf("Status: 302 Found\n");
            if (strcmp(role, "customer") == 0)
                printf("Location: /product_list_page.html\n\n");
            else if (strcmp(role, "vendor") == 0)
                printf("Location: /admin%%20page.html\n\n");
            else
                printf("Location: /signup.html\n\n");
            return 0;
        }
    }

    // ? Error fallback
    printf("Content-type: text/html\n\n");
    printf("<html><body><h2>Signup failed or invalid data.</h2></body></html>");
    return 0;
}

