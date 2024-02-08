#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/signal.h>

void handler(int signo) {
	exit(1);
}

int main(void) {
	signal(SIGINT, handler);
	while (1) {}
	return (0);
}
