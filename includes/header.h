// Global include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Global variable to hold max amount of routers in file
unsigned int N;
unsigned int new_N;

// Global double pointer
struct router **router_array;

// Global struct
struct router
{
    unsigned int router_ID;
    unsigned char flag;
    unsigned char length;
    char name[248];
    struct router *connection_to[10];
    unsigned int counter;
    bool visited;
};

// Global functions
struct router **read_from_file(char *filename);

struct router **get_commands(char *filename);

void unvisited();

void print(unsigned int router_ID);

void set_flag(unsigned int router_ID, unsigned char bitpos, unsigned char value);

void set_model(unsigned int router_ID, char new_name[253]);

void add_connection(unsigned int router_from, unsigned int router_to);

void delete_router(unsigned int router_ID);

bool router_existence(unsigned int router_start, unsigned int router_end);

void write_to_file(char *filename);
