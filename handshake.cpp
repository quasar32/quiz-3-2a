#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

using namespace std;

struct context {
	int count = 0;
	bool syn = true, ack = false;
	condition_variable cv;
	mutex m;
};

void query(context *ctx) { 
	for (int i = 0; i < ctx->count; i++) { 
		unique_lock lk(ctx->m);
		ctx->cv.wait(lk, [=] {return ctx->syn; });
		printf("[%d] SYN ...", i);
		ctx->ack = true;
		ctx->syn = false;
		lk.unlock();
		ctx->cv.notify_one();
	}
}

void response(context *ctx) { 
	for (int i = 0; i < ctx->count; i++) {
		unique_lock lk(ctx->m);
		ctx->cv.wait(lk, [=] {return ctx->ack; }); 
		printf(" ACK\n");
		ctx->ack = false;
		ctx->syn = true;
		lk.unlock();
		ctx->cv.notify_one();
	}
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Usage: ./handshake <count>\n");
		exit(1);
	}
	context ctx;
	ctx.count = atoi(argv[1]); 
	thread tsyn(query, &ctx);
	ctx.cv.notify_one();
	thread tack(response, &ctx);
	tsyn.join();
	tack.join();
	return 0;
}
