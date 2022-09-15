#include "../include/header.h"

/**
 * @brief Read commands from file and execute commands
 * @param filename: name of file
 * @return router_array
 */
struct router **get_commands(char *filename)
{
    // File management
    FILE *fptr;
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        perror("ERROR! File not found\n");
        exit(EXIT_FAILURE);
    }

    // Line storing variable
    char line[256];

    printf("\n--- COMMANDS FROM FILE ---\n");

    // Reading until EOF
    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        // strtok splits a string up in tokens at a given char (in our case that is whitespace)
        char *command = strtok(line, " ");

        // Reading what function to run and type converting to correct data type.
        if ((strcmp(command, "print") == 0))
        {
            char *temp = strtok(NULL, " ");
            unsigned int router_ID = (unsigned int)atoi(temp);

            print(router_ID);
        }
        else if ((strcmp(command, "set_flag") == 0))
        {
            char *temp = strtok(NULL, " ");
            unsigned int router_ID = (unsigned int)atoi(temp);

            char *temp1 = strtok(NULL, " ");
            unsigned char flag = (unsigned char)atoi(temp1);

            char *temp2 = strtok(NULL, " ");
            unsigned char value = (unsigned char)atoi(temp2);

            set_flag(router_ID, flag, value);
        }
        else if ((strcmp(command, "set_model") == 0))
        {
            char *temp = strtok(NULL, " ");
            unsigned int router_ID = (unsigned int)atoi(temp);

            char *new_name = strtok(NULL, "");

            set_model(router_ID, new_name);
        }
        else if (strcmp(command, "add_connection") == 0)
        {
            char *temp = strtok(NULL, " ");
            unsigned int router_from = (unsigned int)atoi(temp);

            char *temp1 = strtok(NULL, " ");
            unsigned int router_to = (unsigned int)atoi(temp1);

            add_connection(router_from, router_to);
        }
        else if (strcmp(command, "delete_router") == 0)
        {
            char *temp = strtok(NULL, " ");
            unsigned int router_ID = (unsigned int)atoi(temp);

            delete_router(router_ID);
        }
        else if (strcmp(command, "router_existence") == 0)
        {
            char *temp = strtok(NULL, " ");
            unsigned int router_from = (unsigned int)atoi(temp);

            char *temp1 = strtok(NULL, " ");
            unsigned int router_to = (unsigned int)atoi(temp1);

            // Mark all routers as unvisited before performing DFS on graph
            unvisited();

            printf("\n--- PATH SEARCH ---");

            printf("\nChecking path between %d and %d\n", router_from, router_to);

            bool existing = router_existence(router_from, router_to);
            if (existing)
            {
                printf("Path exist\n");
            }
            else
            {
                printf("Path doesn't exist\n");
            }
        }
    }
    fclose(fptr);
    printf("\n--- COMMANDS FROM FILE COMPLETED ---\n");

    return router_array;
}

/**
 * @brief Main function were the program runs from
 */
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("To few arguments! Usage <program> <router_infofile> <commands_file>\n");
        return -1;
    }

    router_array = read_from_file(argv[1]);

    router_array = get_commands(argv[2]);

    if (strcmp(argv[1], "./resources/10_routers_10_edges") == 0)
    {
        write_to_file("written_10_routers");
    }
    else
    {
        write_to_file("written_50_routers");
    }

    // Freeing every malloced router
    unsigned int i;
    for (i = 0; i < N; i++)
    {
        free(router_array[i]);
    }
    // Freeing router array
    free(router_array);

    return 0;
}
