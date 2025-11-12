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
            /*
             * put mode routine
             */

            key = strsep(&argv[i], ",");
            if (key == NULL || strcmp(key, "") == 0) {
                fprintf(stderr, "usage: ./kv <mode>,<key>,<value> ...\n");
                exit(EXIT_FAILURE);
            }
            value = strsep(&argv[i], ",");
            if (value == NULL || strcmp(value, "") == 0) {
                fprintf(stderr, "usage: ./kv <mode>,<key>,<value> ...\n");
                exit(EXIT_FAILURE);
            }

            FILE *databasep = fopen("database.txt", "a");
            if (databasep == NULL) {
                fprintf(stderr, "error: fopen() call failed\n");
                exit(EXIT_FAILURE);
            }

            fprintf(databasep, "%s,%s\n", key, value);
            fclose(databasep);

        } else if (strcmp(command, "g") == 0) {
            /*
             * get mode routine
             */

            key = strsep(&argv[i], ",");
            if (key == NULL || strcmp(key, "") == 0) {
                fprintf(stderr, "usage: ./kv <mode>,<key>,<value> ...\n");
            }

            FILE *databasep = fopen("database.txt", "r");
            if (databasep == NULL) {
                fprintf(stderr, "error: fopen() call failed\n");
                exit(EXIT_FAILURE);
            }

            char *linep = NULL;
            size_t linecapp = 0;
            while (getline(&linep, &linecapp, databasep) != -1) {
                char *db_key = strsep(&linep, ",");
                if (strcmp(db_key, key)) {
                    value = strsep(&linep, ","); 
                    printf("%s\n", value);
                }
            }

            fclose(databasep);
        }
    }
    return EXIT_SUCCESS;
}
