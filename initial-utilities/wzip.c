#include <stdio.h>
#include <stdlib.h>

void compress(char *line, ssize_t linelen) {
    if (linelen <= 0)
        return;
    int curr_count = 1;

    for (int i = 0; i < linelen - 1; i++) {
        if (line[i] == line[i + 1]) {
            curr_count++;
        } else {
            fwrite(&curr_count, 4, 1, stdout);
            fwrite(&line[i], 1, 1, stdout);
            curr_count = 1;
        }
    }

    fwrite(&curr_count, 4, 1, stdout);
    fwrite(&line[linelen - 1], 1, 1, stdout);
    return;
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp;
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;

    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wzip: cannot read file\n");
            exit(1);
        }

        while ((linelen = getline(&line, &linecap, fp)) > 0)
            compress(line, linelen);
        free(line);
        fclose(fp);
    }

    return 0;
}
