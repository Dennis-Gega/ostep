#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    char *command, *key, *value;

    for (int i = 1; i < argc; i++) {
        command = strsep(&argv[i], ",");

        if (strcmp(command, "p") == 0) {
            key = strsep(&argv[i], ",");
            if (key == NULL || strcmp(key, "") == 0) {
                fprintf(stderr, "usage: ./kv <mode>,<key>,<value> ...\n");
            }
            value = strsep(&argv[i], ",");
            if (value == NULL || strcmp(value, "") == 0) {
                fprintf(stderr, "usage: ./kv <mode>,<key>,<value> ...\n");
            }

            FILE *database = fopen("database.txt", "a");
            fprintf(database, "%s,%s\n", key, value);
            fclose(database);
        }
    }
    return EXIT_SUCCESS;
}
