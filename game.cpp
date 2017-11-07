#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <thread>
#include <chrono>



using namespace std;
int main(int argc, char *argv[]) {
    
    // alien is trying to kill the player
    // the player is gonna hide in a location(1-100)
    // alien is guessing where player is
    // if alien finds the player the player screams

	if (!fork()) {
        
        //TODO: kill process and close
        //child process
    }
    else {
        int playerLocation = rand() % 100;
        //TODO: implement parent process
        //parent process
    }
	
	// both Steve and Jim throw a rock, paper, or scissors
	
	
	// Steve gets Jims throw and decides the winner
	
	
	
	
	
}