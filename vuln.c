#include <stdio.h>
#include <string.h>

void vuln(char *input) {
    char buffer[200];
    strcpy(buffer, input);
    printf("Done\n");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <input>\n", argv[0]);
        return 1;
    }
    vuln(argv[1]);
    return 0;
}
