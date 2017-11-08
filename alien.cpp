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
	
	//key_t key = ftok("msg2.txt", 'a');
	key_t key = 10;
	int msqid = msgget(key, 666 | IPC_CREAT);
	
	
	if (msqid == -1) {
		cerr << "error: " << errno << endl;
		perror("msgget");
	}
	
	bool isFound = false;
	bool isLess = false;
	
	int max = 9999;
	int min = 0;
	
	struct location_buf newGuess = {2, 100};
	struct location_buf result = {1, 100};
	
	while (!isFound) {
		int guess = rand() % (max - min + 1) + min;
		newGuess.location = guess;
		
		msgsnd(msqid, &newGuess, sizeof(int), 0);
		std::cout << "Alien going to " << guess << endl;
		std::this_thread::sleep_for (std::chrono::seconds(1));
		msgrcv(msqid, &result, sizeof(int), 1, 0);
		
		switch (result.location) {
			case 0:
				//alien found her!
				isFound = true;
				break;
			case 1:
				//too low
				min = guess + 1;
				break;
			case 2:
				//too high
				max = guess - 1;
				break;
			default:
				std::cout << "ERROR: " << result.location << " :Somethin' bad happened!\n";
		}
	}
	cout << "Alien: KEKEKEKEKEKEKEEKEKE\n";
	
}