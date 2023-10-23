#include "header.h"

/**
 * @brief Writing to file
 * @param filename: name of file
 */
void write_to_file(char *filename)
{
    FILE *fptr;
    fptr = fopen(filename, "wb");
    if (fptr == NULL)
    {
        perror("ERROR! File not found\n");
        exit(EXIT_FAILURE);
    }

    if (new_N < N)
    {
        fwrite(&new_N, sizeof(int), 1, fptr);
    }
    else
    {
        fwrite(&N, sizeof(int), 1, fptr);
    }

    fwrite("\0", sizeof(char), 1, fptr);

    printf("\n--- WRITING TO FILE ---\n");

    unsigned int i;
    for (i = 0; i < N; i++)
    {
        if (router_array[i] != NULL)
        {
            fwrite(&router_array[i]->router_ID, sizeof(int), 1, fptr);
            fwrite(&router_array[i]->flag, sizeof(char), 1, fptr);
            fwrite(&router_array[i]->length, sizeof(char), 1, fptr);
            fwrite(router_array[i]->name, sizeof(char), router_array[i]->length, fptr);
            fwrite("\0", sizeof(char), 1, fptr);
        }
    }
    printf("\nWriting...\n");

    /**
     * Looping through the connections for each router
     * that is not deleted and writing them to file
     */
    for (i = 0; i < N; i++)
    {
        if (router_array[i] != NULL)
        {
            unsigned int j;
            for (j = 0; j < router_array[i]->counter; j++)
            {
                fwrite(router_array[i], sizeof(int), 1, fptr);
                fwrite(router_array[i]->connection_to[j], sizeof(int), 1, fptr);
                fwrite("\0", sizeof(char), 1, fptr);
            }
        }
    }
    fclose(fptr);

    printf("\n--- WRITING TO FILE COMPLETED ---\n");
}
