#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sighup(int sig) {
    printf("Configuration reloaded\n");
    exit(0);
}

int main() {
    printf("Задание 9: по сигналу SIGHUP вывести Configuration reloaded\n");
    printf("\n");
    signal(SIGHUP, handle_sighup);
    
    while (1) {
        pause(); // Ожидание сигнала
    }
    
    return 0;
}
