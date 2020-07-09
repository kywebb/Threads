/* 
Assignment 3: Management of Threads 

Names: Kylee Webb, Martin Philip

Red ID: 818022992, 820711145

Class: CS 570, Summer 2020 

Class Accounts: CSSC 2159, CSSC 2126

Emails: Kawebb@sdsu.edu, martin.phillip@gcccd.edu 
*/

#include "threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <time.h> 
#include "threads.h"

// This main executes the threads.cpp file
int main(int argc, char *argv[])
{
   
   dowork(argc,argv);
   return 0;

}
