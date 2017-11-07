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

struct location_buf{
	long mtype;
	int location;
};

int main(int argc, char *argv[]) {
	
	srand(time(NULL));
	int playerLocation = rand() % 100;
	cerr << "Sam's location: " << playerLocation << endl;
		
	struct location_buf resultLocation = {1,200};
	struct location_buf receivedLocation = {2,200};
	
	
	key_t key = ftok("msgQueue.txt", 'a');
	int msqid = msgget(key, 666 | IPC_CREAT);
	
	cout << "Sam: Shhhh.....I'm hiding" << endl;
	bool isDead = false;
	while (!isDead) {
		msgrcv(msqid, &receivedLocation, sizeof(int), 2, 0);
		
		cerr << "recieved location: " << receivedLocation.location << endl;
		std::this_thread::sleep_for (std::chrono::seconds(1));
		if(receivedLocation.location > playerLocation){
			resultLocation.location = 2;
		}
		
		if(receivedLocation.location < playerLocation){
			resultLocation.location = 1;
		}
		
		if(receivedLocation.location == playerLocation){
			resultLocation.location = 0;
			isDead = true;
			cout << "Sam: I think it fou-AAAAHHHHHHHHH!!!!" << endl;
		}
		
		msgsnd(msqid, &resultLocation, sizeof(int), 0);
	}
	
	
	
	
	
	
	
	
	
	
	
}