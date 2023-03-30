#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

using namespace std;

bool syn = true, ack = false;
int count;
condition_variable cv;
mutex m;

void query() {
	for (int i = 0; i < count; i++) { 
		unique_lock lk(m);
		cv.wait(lk, [] {return syn; });
		printf("[%d] SYN ...", i);
		ack = true;
		syn = false;
		lk.unlock();
		cv.notify_one();
	}
}

void response() {
	for (int i = 0; i < count; i++) {
		unique_lock lk(m);
		cv.wait(lk, [] {return ack; }); 
		printf(" ACK\n");
		ack = false;
		syn = true;
		lk.unlock();
		cv.notify_one();
	}
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Usage: ./handshake <count>\n");
		exit(1);
	}

	count = atoi(argv[1]); 

	thread tsyn(query);
	cv.notify_one();
	thread tack(response);
	tsyn.join();
	tack.join();
	return 0;
}
