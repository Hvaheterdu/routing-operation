# Variable
CC = gcc -g
CFLAGS = -Wall -Wextra -Wpedantic
INC = -I./include/
BINARIES = router_main

# Compile all files
all: $(BINARIES)

# File(s) that needs to be compiled
router_main: ./src/router_main.c libs/read_from_file.c libs/write_to_file.c libs/router_operation.c
	$(CC) $(CLFAGS) $(INC) -o router_main ./src/router_main.c ./libs/read_from_file.c ./libs/write_to_file.c ./libs/router_operation.c

# Run main file with 10 routers and 10 commands
run10: 
	./router_main ./resources/10_routers_10_edges ./resources/commands_10_routers.txt

# Run main file with 50 routers and 150 edges
run50: 
	./router_main ./resources/50_routers_150_edges ./resources/commands_50_routers.txt

# Remove delivery folder
remove:
	rm -rf -R burhanms

# Make delivery folder
delivery:
	mkdir burhanms

# Create oppgave1 delivery folder and add files
oppgave1:
	mkdir burhanms/oppgave1
	cp *.c *.h *.txt 10_routers_10_edges 50_routers_150_edges Makefile burhanms/oppgave1/

# Create oppgave2 delivery folder
oppgave2:
	mkdir burhanms/oppgave2

# Making zip file of delivery folder
zip:
	tar -czvf burhanms.tgz burhanms/

remove_zip:
	rm -rf burhanms.tgz

# Clean files
clean:
	$(RM) $(BINARIES)
	rm -rf *.dSYM
	rm -rf written_10_routers
	rm -rf written_50_routers