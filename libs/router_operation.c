#include "header.h"

/**
 * @brief Prints out the information about the router
 * @param router_ID: router ID
 */
void print(unsigned int router_ID)
{
    printf("\n--- ROUTER INFORMATION ---\n");

    printf("Router ID: %d\n", router_array[router_ID]->router_ID);
    printf("Router flag: %d\n", router_array[router_ID]->flag);
    printf("Router name length: %d\n", router_array[router_ID]->length);

    // Adding nyllbyte at end of length
    router_array[router_ID]->name[router_array[router_ID]->length] = '\0';
    printf("Router name: %s\n", router_array[router_ID]->name);
    printf("Router %d connection(s): ", router_array[router_ID]->router_ID);

    // Printing connections_to from given router
    unsigned int i;
    for (i = 0; i < router_array[router_ID]->counter; i++)
    {
        if (router_array[router_ID]->connection_to[i] != NULL)
        {
            printf("%d ", router_array[router_ID]->connection_to[i]->router_ID);
        }
    }
    printf("\n");
}

/**
 * @brief Change bits in router flag. For each bit we are performing and
 * AND or OR operation to change the correct bit to the new value.
 * For bitpos == 4, we are also doing an OR operation with a 4 bit
 * left shift.
 * @param router_ID: router ID
 * @param bitpos: bit position
 * @param value: new value
 */
void set_flag(unsigned int router_ID, unsigned char bitpos, unsigned char value)
{
    printf("\n--- FLAG CHANGE ---\n");

    if (bitpos == 0)
    {
        if (value == 0)
        {
            printf("Original flag: %d\n", router_array[router_ID]->flag);
            router_array[router_ID]->flag &= 0xFE;
            printf("Bit position: %d\n", bitpos);
            printf("New flag: %d\n", router_array[router_ID]->flag);
        }
        else if (value == 1)
        {
            printf("Original flag: %d\n", router_array[router_ID]->flag);
            router_array[router_ID]->flag |= 0x01;
            printf("Bit position: %d\n", bitpos);
            printf("New flag: %d\n", router_array[router_ID]->flag);
        }
    }
    else if (bitpos == 1)
    {
        if (value == 0)
        {
            printf("Original flag: %d\n", router_array[router_ID]->flag);
            router_array[router_ID]->flag &= 0xFD;
            printf("Bit position %d\n", bitpos);
            printf("New flag: %d\n", router_array[router_ID]->flag);
        }
        else if (value == 1)
        {
            printf("Original flag: %d\n", router_array[router_ID]->flag);
            router_array[router_ID]->flag |= 0x02;
            printf("Bit position: %d\n", bitpos);
            printf("New flag: %d\n", router_array[router_ID]->flag);
        }
    }
    else if (bitpos == 2)
    {
        if (value == 0)
        {
            printf("Original flag: %d\n", router_array[router_ID]->flag);
            router_array[router_ID]->flag &= 0xFB;
            printf("Bit position: %d\n", bitpos);
            printf("New changed: %d\n", router_array[router_ID]->flag);
        }
        else if (value == 1)
        {
            printf("Original flag: %d\n", router_array[router_ID]->flag);
            router_array[router_ID]->flag |= 0x04;
            printf("Bit position: %d\n", bitpos);
            printf("New flag: %d\n", router_array[router_ID]->flag);
        }
    }
    else if (bitpos == 4)
    {
        printf("Original flag: %d\n", router_array[router_ID]->flag);
        router_array[router_ID]->flag &= 0x0f;
        router_array[router_ID]->flag |= (value << 4);
        printf("Bit position %d\n", bitpos);
        printf("New flag: %d\n", router_array[router_ID]->flag);
    }
    else
    {
        printf("Router has been deleted\n");
    }
}

/**
 * @brief Change router name
 * @param router_ID: router ID
 * @param new_name: new router name
 */
void set_model(unsigned int router_ID, char new_name[253])
{
    printf("\n--- NAME CHANGE ---\n");
    printf("Original name: %s\n", router_array[router_ID]->name);

    // Clearing the original name array
    memset(router_array[router_ID]->name, 0, router_array[router_ID]->length);

    // Length of new name
    router_array[router_ID]->length = strlen(new_name);
    router_array[router_ID]->name[router_array[router_ID]->length] = '\0';

    // Give new name
    unsigned int i;
    for (i = 0; i < router_array[router_ID]->length; i++)
    {
        router_array[router_ID]->name[i] = new_name[i];
    }
    printf("New name: %s", router_array[router_ID]->name);

    /**
     * Adding nullbyte after the name, so it is like the
     * original file. Memset deleted nullbyte
     */
    router_array[router_ID]->name[router_array[router_ID]->length] = 0x00;
}

/**
 * @brief Add new connection between two routers
 * @param router_from: router connection from
 * @param router_to: router connection to
 */
void add_connection(unsigned int router_from, unsigned int router_to)
{
    if (router_array[router_from] || router_array[router_to] != NULL)
    {
        router_array[router_from]->connection_to[router_array[router_from]->counter] = router_array[router_to];
        router_array[router_from]->counter++;
        printf("\n--- CONNECTION(S) ADDED ---\n");
        printf("Connection from %d to %d\n", router_array[router_from]->router_ID, router_array[router_to]->router_ID);
    }
    else
    {
        printf("One of the routers have been deleted and a connection can't be created\n");
    }
}

/**
 * @brief Delete a router and all connections
 * @param router_ID: ID of the router we are printing information about
 */
void delete_router(unsigned int router_ID)
{
    printf("\n--- DELETE ROUTER ---\n");

    printf("Deleted router: %d\n", router_array[router_ID]->router_ID);

    // Adding a new N to use when writing to file
    new_N = N;

    // Deleting router connections
    unsigned int i, j, k;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < router_array[i]->counter; j++)
        {
            if (router_array[i]->connection_to[j]->router_ID == router_ID)
            {
                router_array[i]->connection_to[j] = NULL;
                router_array[i]->counter--;

                // Pushing every pointer one index towards the start
                for (k = j; k < router_array[i]->counter; k++)
                {
                    if (router_array[i]->connection_to[k + 1] != NULL)
                    {
                        router_array[i]->connection_to[k] = router_array[i]->connection_to[j + 1];
                    }
                }
                printf("Deleted connection between %d and %d\n", router_array[router_ID]->router_ID, router_array[i]->router_ID);
            }
        }
    }

    // Delete and free router
    for (i = 0; i < N; i++)
    {
        if (router_array[i]->router_ID == router_ID)
        {
            free(router_array[i]);

            router_array[i] = NULL;

            new_N--;
        }
    }
    printf("\nWe have %d router(s) left\n", new_N);
}

/**
 * @brief Checking if there is a path between two routers
 * @param router_from: checking path from
 * @param router_to: checking path to
 * @return true if path exists, else false
 */
bool router_existence(unsigned int router_start, unsigned int router_end)
{
    bool existing = false;

    // Set start router to visited
    if (!router_array[router_start]->visited)
    {
        router_array[router_start]->visited = true;
    }

    unsigned int i;
    for (i = 0; i < router_array[router_start]->counter; i++)
    {
        if (!router_array[router_start]->connection_to[i]->visited)
        {
            if (router_array[router_start]->connection_to[i]->router_ID == router_end)
            {
                existing = true;
            }
            else
            {
                if (router_existence(router_array[router_start]->connection_to[i]->router_ID, router_end))
                {
                    existing = true;
                }
            }
        }
    }
    return existing;
}

/**
 * @brief Mark routers as not visited before DFS
 */
void unvisited()
{
    unsigned int i;
    for (i = 0; i < N; i++)
    {
        if (router_array[i] != NULL)
        {
            router_array[i]->visited = false;
        }
    }
}
