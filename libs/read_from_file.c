#include "header.h"

/**
 * @brief Reading from file
 * @param *filename: name of file
 * @return router_array
 */
struct router **read_from_file(char *filename)
{
    N = 0;

    // File management
    FILE *fptr;
    fptr = fopen(filename, "rb");
    if (fptr == NULL)
    {
        printf("Unable to open file\n");
        exit(EXIT_FAILURE);
    }

    // N number of routers
    fread(&N, sizeof(int), 1, fptr);

    /**
     * A double pointer. This is a pointer that points at an array containing information
     * about were N router struct are stored in memory. The total use of each struct in
     * memory is 259 bytes. I am unsure if I should count the pointer to the connections
     * or not. If I add them, then we will have to add 10 * struct router.
     */
    struct router **router_array = (struct router **)malloc(N * sizeof(struct router *));

    if (router_array == 0)
    {
        printf("Malloc failed\n");
        exit(EXIT_FAILURE);
    }

    printf("\n--- READING FROM BINARY FILE ---\n");

    // Reading from file and adding information to each router struct
    unsigned int i;
    for (i = 0; i < N; i++)
    {
        // Allocate memory space for each struct router
        router_array[i] = malloc(sizeof(struct router));

        printf("\n--- ROUTER STRUCT %d ---\n", i);

        // routerID
        fread(&router_array[i]->router_ID, sizeof(unsigned int), 1, fptr);
        printf("ID: %d\n", router_array[i]->router_ID);

        // flag
        fread(&router_array[i]->flag, sizeof(char), 1, fptr);
        printf("Flag: %d\n", router_array[i]->flag);

        // length
        fread(&router_array[i]->length, sizeof(char), 1, fptr);
        printf("Name length: %d\n", router_array[i]->length);

        // name
        fread(router_array[i]->name, sizeof(char), router_array[i]->length, fptr);

        // Adding nullbyte to length
        router_array[i]->name[router_array[i]->length] = '\0';
        printf("Name: %s", router_array[i]->name);
        printf("\n");

        // Making counter to be 0 to begin with
        router_array[i]->counter = 0;

        // Set connections to NULL
        unsigned int j;
        for (j = 0; j < 10; j++)
        {
            router_array[i]->connection_to[j] = NULL;
        }

        // Skip nullbyte after each block of router information
        fseek(fptr, 1, SEEK_CUR);
    }

    printf("\n--- ROUTER CONNECTIONS ---\n");

    // Reading connections from file until EOF is hit
    unsigned int temp_from;
    unsigned int temp_to;
    while (fread(&temp_from, sizeof(int), 1, fptr))
    {
        // Reading the router_ID that we have a connection to
        fread(&temp_to, sizeof(int), 1, fptr);

        // Skip nullbyte after each router connection pair
        fseek(fptr, sizeof(char), SEEK_CUR);

        /**
         * Adding the router to the connection_to array according
         * to file and printing the connections.
         */
        router_array[temp_from]->connection_to[router_array[temp_from]->counter] = router_array[temp_to];
        router_array[temp_from]->counter++;
        printf("Connection from %d to %d\n", router_array[temp_from]->router_ID, router_array[temp_to]->router_ID);
    }
    // Close file
    fclose(fptr);
    printf("\n--- READING FROM BINARY FILE COMPLETED ---\n");

    return router_array;
}
