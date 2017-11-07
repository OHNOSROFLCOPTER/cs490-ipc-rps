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

	if (!fork()) {
        key_t key = ftok("msgQueue.txt", 'a');
        int msqid = msgget(key, 666 | IPC_CREAT);
        bool isFound = false;
        bool isLess = false;
        int locationGuess = 100;
        int max = 99;
        int min = 0;
        struct location_buf newGuess = {2, 100};
        while (!isFound) {
            int guess = rand()%(max - min + 1) + min;
            newGuess.location = guess;
            msgsnd(msqid, &newGuess, sizeof(int), 0);
            std::cout << "Alien going to " << guess << endl;
            std::this_thread::sleep_for (std::chrono::seconds(1));
            msgrcv(msqid, &newGuess, sizeof(int), 1, 0);
            switch (newGuess.location) {
                case '0':
                    //alien found her!
                    isFound = true;
                    break;
                case '1':
                    //too low
                    min = guess;
                    break;
                case '2':
                    //too high
                    max = guess;
                    break;
                default:
                    std::cout << "Somethin' bad happened!\n";
            }
        }
        std::cout << "KEKEKEKEKEKEKEEKEKE\n";
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