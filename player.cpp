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
	int playerLocation = rand() % 10000;
		
	struct location_buf resultLocation = {1,200};
	struct location_buf receivedLocation = {2,200};
	
	
//	key_t key = ftok("msg2.txt", 'a');
	key_t key = 10;
	int msqid = msgget(key, 666 | IPC_CREAT);
	
	if (msqid == -1) {
		cerr << "error: " << errno << endl;
		perror("msgget");
	}
	
	
	cout << "Sam: Shhhh.....I'm hiding" << endl;
	
	bool isDead = false;
	while (!isDead) {
		
		msgrcv(msqid, &receivedLocation, sizeof(int), 2, 0);
		
		std::this_thread::sleep_for (std::chrono::seconds(1));
		
		int difference = abs(receivedLocation.location - playerLocation);
		if(difference < 8 && difference >= 4 && difference != 0){
			cout << "Sam: Oh no I think I hear it..." << endl;
		} else if (difference < 4 && difference >= 3 && difference != 0){
			cout << "Sam: ........(heavy breathing)" << endl;
		} else if (difference <= 2 && difference != 0){
			cout << "Sam: ........(heavy breathing intesifies)" << endl;
		} else if (difference >= 8){
			cout << "Sam: ........." << endl;
		}
		
		
		
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


