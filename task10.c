#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    printf("Задание 10: определить является ли диск загрузочным\n");
    printf("\n");
    
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <диск>\n", argv[0]);
        return 1;
    }

    char path[20];
    snprintf(path, sizeof(path), "/dev/%s", argv[1]);

    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("Ошибка открытия диска");
        return 1;
    }

    uint8_t buffer[512];
    if (read(fd, buffer, sizeof(buffer)) != sizeof(buffer)) {
        perror("Ошибка чтения первого сектора");
        close(fd);
        return 1;
    }

    close(fd);

    if (buffer[510] == 0x55 && buffer[511] == 0xAA) {
        printf("Диск %s является загрузочным.\n", argv[1]);
    } else {
        printf("Диск %s не является загрузочным.\n", argv[1]);
    }

    return 0;
}
