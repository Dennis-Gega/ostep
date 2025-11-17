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

    open_file("database.txt", "a+", &databasep);

    for (int i = 1; i < argc; i++) {
        command = strsep(&argv[i], ",");

        if (strcmp(command, "p") == 0) {
            /*
             * put mode routine
             */

            read_input(&argv[i], &key);
            read_input(&argv[i], &value);

            fprintf(databasep, "%s,%s\n", key, value);

        } else if (strcmp(command, "g") == 0) {
            /*
             * get mode routine
             */

            read_input(&argv[i], &key);

            char *linep = NULL;
            size_t linecapp = 0;
            rewind(databasep);
            while (getline(&linep, &linecapp, databasep) != -1) {
                char *db_key = strsep(&linep, ",");
                if (strcmp(db_key, key) == 0) {
                    value = strsep(&linep, "\n"); 
                    printf("%s\n", value);
                    break;
                }
            }
            free(linep);

        } else if (strcmp(command, "d") == 0) {
            read_input(&argv[i], &key);
            read_input(&argv[i], &value);
            FILE *new_databasep;
            open_file("database2.txt", "w", &new_databasep);


            char *linep = NULL;
            size_t linecapp = 0;

            rewind(databasep);

            while (getline(&linep, &linecapp, databasep) != -1) {

                char *temp = linep;
                char *db_key = strsep(&temp, ",");
                char *db_value = strsep(&temp, "\n");

                if (strcmp(db_key, key) == 0 && strcmp(db_value, value) == 0)
                    continue;
                
                fprintf(new_databasep, "%s,%s\n", db_key, db_value);

            }

            free(linep);
            fclose(databasep);
            fclose(new_databasep);

            rename("database2.txt", "database.txt");

            open_file("database.txt", "a+", &databasep);

        } else if (strcmp(command, "c") == 0) {
            open_file("database.txt", "w", &databasep);

        } else if (strcmp(command, "a") == 0) {
            open_file("database.txt", "r", &databasep);

            char *linep = NULL;
            size_t linecapp = 0;
            rewind(databasep);
            while (getline(&linep, &linecapp, databasep) != -1) {
                printf("%s", linep);
            }

            free(linep);


        } else {
            printf("bad command\n");
        }

    }
    fclose(databasep);
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
    if (*to == NULL) {
        fprintf(stderr, "error: fopen() call failed\n");
        exit(EXIT_FAILURE);
    }
    return;
}
