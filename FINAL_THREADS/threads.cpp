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
#include <iostream>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <time.h> 
#include "threads.h"

// Semaphore flag used to manage threads 
sem_t FLAG;

// This checks if it is a number
bool isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}



void signalHandler(int signum) {
 cout << "Interrupt signal (" << signum << ") received. Bye! see you later !\n";
 exit(signum);
}
//count down timer that will signal to all threads and main to exist when timer is reached its time
void *countdownMonitor(void *t)
{         
  
    sem_wait(&FLAG); 
    signal(SIGINT, signalHandler); 
    long ti = (long) t;;
    sem_post(&FLAG);
        
    while(1){  
        ti--;   
        if(ti == 0) raise(SIGINT);
        sleep(1);  
    }     
   
    pthread_exit((void*)t);

}
//will print a message after the third argument time has ran out.
void *Alarm(void *t)
{         
    
    sem_wait(&FLAG); 
    signal(SIGINT, signalHandler);     
    sem_post(&FLAG);
    long ti = (long)t;    
    while(ti !=0){  
        ti--;
        
        sleep(1);
        if(ti == 0){
            printf("Alarm!: count time has been reached!\n");
          
         }  
    }     
   
    pthread_exit((void*)t);

}
// This function will print the current date and time.
void *printtime(void*t)
{         
  
   long times = (long ) t;
    while(1){ 
        time_t rawtime;
        struct tm * timeinfo;

        time (&rawtime);
        timeinfo = localtime (&rawtime); 
        
        printf ("%s", asctime(timeinfo));
        if (times == 60)sleep (60);
        if (times == 1)sleep (1);
        
    }     
   
    pthread_exit((void*)t);

}

// This function spawns threads and error checks
int dowork(int argc,char *argv[])
{


    // Gets the args
    char *p;
    char *o;
    char *j;
    bool it = true;
    int firstArg,secondArg,thirdArg;
    //Checks if no arguments were entered
    if (argc != 4 ){
    firstArg = 25;
    secondArg = 1;
    thirdArg = 17;
    }else{
        if(!isNumber(argv[1])) {
        cout << "Error: please make sure your input are numbers." << endl;
        return 0; 
    }

    if(!isNumber(argv[2])) {
        cout << "Error: please make sure your input are numbers." << endl;
        return 0; 
    }

    if(!isNumber(argv[3])) {
        cout << "Error: please make sure your input are numbers." << endl;
        return 0; 
    }
    
    //Gets the arguments as int
     firstArg = strtol(argv[1], &p, 10);
     secondArg = strtol(argv[2], &o, 10);
     thirdArg = strtol(argv[3], &j, 10);
    }
    // Checks for seconds or minutes
    if (secondArg != 1 && secondArg != 60){
     cout<<"Error: please make sure your 2nd argument is 1 or 60"<<endl;
     return 0;
    }
    
    //Array to hold our threads 
    pthread_t thread[NUM_Of_THREADS];
    pthread_attr_t attr; 
    /*initialising semaphore*/
    sem_init(&FLAG, 0, 1);  
    // Initialize the thread attribute object and set the detachstate to Joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    // Creates the 3 threads
    int error;
    error = pthread_create(&thread[0], &attr, countdownMonitor, (void *)(firstArg));
        if (error) {
            printf("ERROR; %d\n", error);
            exit(-1);
        }
    error = pthread_create(&thread[1], &attr, Alarm, (void *)(thirdArg));
        if (error) {
            printf("ERROR; %d\n", error);
            exit(-1);
        }
    error = pthread_create(&thread[2], &attr, printtime, (void *)(secondArg));
        if (error) {
            printf("ERROR; %d\n", error);
            exit(-1);
        }

    
   
    // Handle the threads before the main process ends
    pthread_attr_destroy(&attr);
    for(long thrd=0;thrd<NUM_Of_THREADS;thrd++){
        void *s;
        error = pthread_join(thread[thrd], &s);
        if (error) {
            printf("ERROR; %d\n", error);
            exit(-1);
        }
       
    }

    // Destroys the semaphore and print message 
    sem_destroy(&FLAG);
    
    printf("Program is done. Yay!\n");
    pthread_exit(NULL);



}


