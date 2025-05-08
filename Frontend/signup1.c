#include <stdio.h>

int main() {
    // Required CGI header — must be first
    printf("Content-type: text/html\n\n");

    // Simple HTML output
    printf("<html><body><h1>Signup CGI is working!</h1></body></html>\n");

    return 0;
}

