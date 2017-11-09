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

void samSpeak(int difference);

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
//		if(difference < 8 && difference >= 4 && difference != 0){
//			cout << "Sam: Oh no I think I hear it..." << endl;
//		} else if (difference < 4 && difference >= 3 && difference != 0){
//			cout << "Sam: ........(heavy breathing)" << endl;
//		} else if (difference <= 2 && difference != 0){
//			cout << "Sam: ........(heavy breathing intesifies)" << endl;
//		} else if (difference >= 8){
//			cout << "Sam: ........." << endl;
//		}

		samSpeak(difference);
		
		if(receivedLocation.location > playerLocation){
			resultLocation.location = 2;
		}
		
		if(receivedLocation.location < playerLocation){
			resultLocation.location = 1;
		}
		
		if(receivedLocation.location == playerLocation){
			resultLocation.location = 0;
			isDead = true;
			cout << "Sam: AAAAHHHHHHHHH!!!!" << endl;
		}
		
		msgsnd(msqid, &resultLocation, sizeof(int), 0);
	}	
	
}

void samSpeak(int difference){
	switch(difference){
		case 10:
			cout << "Sam: I think it's on the same floor as me!" << endl;
			break;
		case 9:
			cout << "Sam: If only I had my gun...." << endl;
			break;
		case 8:
			cout << "Sam: It's coming down the hall...." << endl;
			break;
		case 7:
			cout << "Sam: Theres no way out!" << endl;
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
			cout << "Sam: I think it fou-" << endl;
			break;
		default:
			cout << "Sam: ........." << endl;
	}
}

