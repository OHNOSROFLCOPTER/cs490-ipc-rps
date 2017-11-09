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

void samSpeak(int difference, int moves);

struct location_buf{
	long mtype;
	int location;
};

int main(int argc, char *argv[]) {
	
	srand(time(NULL));
	int playerLocation = rand() % 10000;
	int moves = 3;
		
	struct location_buf resultLocation = {1,200};
	struct location_buf receivedLocation = {2,200};
	
	
//	key_t key = ftok("msg2.txt", 'a');
	key_t key = 10;
	int msqid = msgget(key, 666 | IPC_CREAT);
	
	if (msqid == -1) {
		cerr << "error: " << errno << endl;
		perror("msgget");
	}
	
	
	cout << "Sam: Shhhh.....I'm hiding at " << playerLocation << endl;
	
	bool isDead = false;
	while (!isDead) {
		
		msgrcv(msqid, &receivedLocation, sizeof(int), 2, 0);
		
		std::this_thread::sleep_for (std::chrono::seconds(1));
		
		int difference = abs(receivedLocation.location - playerLocation);
		cout << playerLocation << " ";
		samSpeak(difference, moves);
		
		if(receivedLocation.location > playerLocation){
			resultLocation.location = 2;
		}
		
		if(receivedLocation.location < playerLocation){
			resultLocation.location = 1;
		}
		
		if(receivedLocation.location == playerLocation){
			resultLocation.location = 0;
			isDead = true;
		}
		
		if(difference > 10 && difference < 35 && moves > 0){
			//cerr << "Sam is gonna move" << endl;
			moves--;
			if(playerLocation > 0 && playerLocation <= 5000){
				playerLocation = playerLocation + (rand() % 100 );
			} 
			if(playerLocation > 5000 && playerLocation <= 10000) {
				playerLocation = playerLocation - (rand() % 100 );
			}
			//cerr << "new location - " << playerLocation << endl;
			resultLocation.location = 3;
		}
		
		msgsnd(msqid, &resultLocation, sizeof(int), 0);
	}	
	
}

void samSpeak(int difference, int moves){
	
	if (difference > 10 && difference < 35 && moves > 0) {
		switch (moves) {
			case 3:
				cout << "Sam: I found a way upstairs!" << endl;
				break;
			case 2:
				cout << "Sam: Theres an opening in the vent!" << endl;
				break;
			case 1:
				cout << "Sam: I should move to the other room!" << endl;
				break;
		}
	} else {
		switch(difference){
			case 10:
				cout << "Sam: I think it's on the same floor as me.." << endl;
				break;
			case 9:
				cout << "Sam: If only I had my gun...." << endl;
				break;
			case 8:
				cout << "Sam: It's coming down the hall...." << endl;
				break;
			case 7:
				cout << "Sam: I can't find a way out!" << endl;
				break;
			case 6:
				cout << "Sam: I think I hear it getting closer..." << endl;
				break;
			case 5:
				cout << "Sam: It's outside the doorway.." << endl;
				break;
			case 4:
				cout << "Sam: .........Please no" << endl;
				break;
			case 3:
				cout << "Sam: .........*gulp*" << endl;
				break;
			case 2:
				cout << "Sam: .........(heavy breathing)" << endl;
				break;
			case 1:
				cout << "Sam: .........(heavy breathing intesifies)" << endl;
				break;
			case 0:
				cout << "Sam: I think it fou-AAAAHHHHHHHHH!!!!" << endl;
				break;
			default:
				cout << "Sam: ........." << endl;
		}
	}
}

