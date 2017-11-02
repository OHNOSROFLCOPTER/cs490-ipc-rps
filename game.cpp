#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

struct location_buf{
    long mtype;
    int location;
};

using namespace std;
int main(int argc, char *argv[]) {
    
    // alien is trying to kill the player
    // the player is gonna hide in a location(1-100)
    // alien is guessing where player is
    // if alien finds the player the player screams

    pid_t alien; //alien is trying to get the player
    pid_t player;
    int playerLocation = rand() % 100;
	

    pid_t temp;
	if (!(temp = fork() )) {
        alien = temp;
        //child process
    }
    else {
        //parent process
    }
	
	// both Steve and Jim throw a rock, paper, or scissors
	
	
	// Steve gets Jims throw and decides the winner
	
	
	
	
	
}