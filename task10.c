#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h> 

int main(int argc, char *argv[]) {
    printf("Задание 10: определить является ли диск загрузочным\n");
    printf("\n");

    char device_name[100];

    printf("Введите имя устройства (например, sda, sdb): ");
    if (fgets(device_name, sizeof(device_name), stdin) == NULL) {
        fprintf(stderr, "Ошибка чтения с клавиатуры.\n");
        return 1;
    }

    // Удаляем перенос строки, добавленный fgets
    device_name[strcspn(device_name, "\n")] = 0;

    char path[20];
    snprintf(path, sizeof(path), "/dev/%s", device_name);

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
        printf("Диск %s является загрузочным.\n", device_name);
    } else {
        printf("Диск %s не является загрузочным.\n", device_name);
    }

    return 0;
}

