#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

void read_input(char **from , char **to);
void open_file(char *filename, char *mode, FILE **to);


int main(int argc, char* argv[])
{
    char *command, *key, *value;
    FILE *databasep;

    for (int i = 1; i < argc; i++) {
        command = strsep(&argv[i], ",");

        if (strcmp(command, "p") == 0) {
            /*
             * put mode routine
             */

            read_input(&argv[i], &key);
            read_input(&argv[i], &value);

            open_file("database.txt", "a", &databasep);

            fprintf(databasep, "%s,%s\n", key, value);
            fclose(databasep);

        } else if (strcmp(command, "g") == 0) {
            /*
             * get mode routine
             */

            read_input(&argv[i], &key);

            open_file("database.txt", "r", &databasep);

            char *linep = NULL;
            size_t linecapp = 0;
            while (getline(&linep, &linecapp, databasep) != -1) {
                char *db_key = strsep(&linep, ",");
                if (strcmp(db_key, key) == 0) {
                    value = strsep(&linep, "\n"); 
                    printf("%s\n", value);
                    break;
                }
            }

            fclose(databasep);
        }
    }
    return EXIT_SUCCESS;
}

void read_input(char **from , char **to)
{
    *to = strsep(from, ",");
    if (*to == NULL || strcmp(*to, "") == 0) {
        fprintf(stderr, "usage: ./kv <mode>,<key>,<value> ...\n");
        exit(EXIT_FAILURE);
    }
    return;
}

void open_file(char *filename, char *mode, FILE **to)
{
    *to = fopen(filename, mode);
    if (to == NULL) {
        fprintf(stderr, "error: fopen() call failed\n");
        exit(EXIT_FAILURE);
    }
    return;
}
