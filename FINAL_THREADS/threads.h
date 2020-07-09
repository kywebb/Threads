/* 
Assignment 3: Management of Threads 

Names: Kylee Webb, Martin Philip

Red ID: 818022992, 820711145

Class: CS 570, Summer 2020 

Class Accounts: CSSC 2159, CSSC 2126

Emails: Kawebb@sdsu.edu, martin.phillip@gcccd.edu 
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <time.h> 
#include <pthread.h>
#define NUM_Of_THREADS 3
using namespace std;



void signalHandler(int signum);
void *countdownMonitor(void *t);
void *Alarm(void *t);
void *printtime(void*t);
int dowork(int t, char *array[]);
