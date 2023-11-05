#include "header.h"

struct router **read_from_file(char *filename)
{
    N = 0;
    FILE *fptr;
    fptr = fopen(filename, "rb");
    if (fptr == NULL)
    {
        printf("Unable to open file\n");
        exit(EXIT_FAILURE);
    }

    fread(&N, sizeof(int), 1, fptr);

    struct router **router_array = (struct router **)malloc(N * sizeof(struct router *));

    if (router_array == 0)
    {
        printf("Malloc failed\n");
        exit(EXIT_FAILURE);
    }

    printf("\n--- READING FROM BINARY FILE ---\n");

    unsigned int i;
    for (i = 0; i < N; i++)
    {
        router_array[i] = malloc(sizeof(struct router));

        printf("\n--- ROUTER STRUCT %d ---\n", i);

        fread(&router_array[i]->router_ID, sizeof(unsigned int), 1, fptr);
        printf("ID: %d\n", router_array[i]->router_ID);

        fread(&router_array[i]->flag, sizeof(char), 1, fptr);
        printf("Flag: %d\n", router_array[i]->flag);

        fread(&router_array[i]->length, sizeof(char), 1, fptr);
        printf("Name length: %d\n", router_array[i]->length);

        fread(router_array[i]->name, sizeof(char), router_array[i]->length, fptr);

        router_array[i]->name[router_array[i]->length] = '\0';
        printf("Name: %s", router_array[i]->name);
        printf("\n");

        router_array[i]->counter = 0;

        unsigned int j;
        for (j = 0; j < 10; j++)
        {
            router_array[i]->connection_to[j] = NULL;
        }

        fseek(fptr, 1, SEEK_CUR);
    }

    printf("\n--- ROUTER CONNECTIONS ---\n");

    unsigned int temp_from;
    unsigned int temp_to;
    while (fread(&temp_from, sizeof(int), 1, fptr))
    {
        fread(&temp_to, sizeof(int), 1, fptr);

        fseek(fptr, sizeof(char), SEEK_CUR);

        router_array[temp_from]->connection_to[router_array[temp_from]->counter] = router_array[temp_to];
        router_array[temp_from]->counter++;
        printf("Connection from %d to %d\n", router_array[temp_from]->router_ID, router_array[temp_to]->router_ID);
    }
    
    fclose(fptr);
    printf("\n--- READING FROM BINARY FILE COMPLETED ---\n");

    return router_array;
}
