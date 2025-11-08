#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    char *searchterm = argv[1];

    FILE *fp;
    char *buffer = NULL;
    size_t len = 0;

    for (int i = 2; i < argc; i++)
    {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wgrep: cannot open file\n");
            exit(1);
        }
        while (getline(&buffer, &len, fp) != -1) {
            if (strstr(buffer, searchterm)) {
                printf("%s", buffer);
            }
        }
        free(buffer);
    }

    if (argc == 2) {
        while (getline(&buffer, &len, stdin) != -1) {
            if (strstr(buffer, searchterm)) {
                printf("%s", buffer);
            }
        }
    }

    return 0;
}
