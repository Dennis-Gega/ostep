#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc == 1) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp;
    char character;
    int character_frequency;

    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wunzip: cannot read file\n");
            exit(1);
        }

        while (fread(&character_frequency, 1, sizeof(int), fp) > 0 &&
               fread(&character, 1, sizeof(char), fp) > 0) {

            for (int i = 0; i < character_frequency; i++)
                printf("%c", character);
        }

        fclose(fp);
    }

    return 0;
}
