#/* Project Information */
# This project allows to create a simple shell to execute files and make pipes between processes
# Assignment 2: MicroShell
# Names: Kylee Webb, Martin Philip
# Class: CS 570, Summer 2020
# Red ID: 818022992, 820711145 
# Class Accounts: CSSC 2159, CSSC 2126
# Emails: Kawebb@sdsu.edu, martin.phillip@gcccd.edu */



EXEC = mot 
FILES = main.cpp threads.cpp threads.h  

LFLAGS = -g++ 
CFLAGS = -g++ -c
 
OBJECTS = $(FILES:.c=.o)
 
$(EXEC):$(OBJECTS) 
	$(LFLAGS) -o $(EXEC) $(OBJECTS) -lpthread
	rm -f *.o
 
c.o: 
	$(CC) $(CFLAGS) $<
 
clean: 
	rm -f *.o $(EXEC)
