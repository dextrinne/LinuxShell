#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h> // Для PATH_MAX

int main() {
    char binary_path[PATH_MAX]; // Используем PATH_MAX для безопасного хранения пути

    printf("Введите путь к бинарнику: ");
    if (fgets(binary_path, sizeof(binary_path), stdin) == NULL) {
        perror("Ошибка чтения пути к бинарнику");
        return 1;
    }

    // Удаляем завершающий символ новой строки
    binary_path[strcspn(binary_path, "\n")] = 0;

    // Проверка на пустой путь
    if (strlen(binary_path) == 0) {
        fprintf(stderr, "Ошибка: пустой путь к бинарнику.\n");
        return 1;
    }

    struct stat file_stat;
    if (stat(binary_path, &file_stat) == -1) {
        perror("Не удалось получить информацию о файле");
        return 1;
    }

    // Проверка, что файл является исполняемым
    if (!S_ISREG(file_stat.st_mode) || !(file_stat.st_mode & S_IXUSR)) {
        fprintf(stderr, "Ошибка: %s не является исполняемым файлом.\n", binary_path);
        return 1;
    }

    // Формирование команды для терминала
    char command[2 * PATH_MAX];
    snprintf(command, sizeof(command), "gnome-terminal -- bash -c '%s; exec bash'", binary_path); //"Топаем" через встроенный gnome-terminal

    pid_t pid = fork();
    if (pid < 0) {
        perror("Ошибка fork\n");
        return 1;
    } else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command, (char *) NULL);
        perror("Ошибка execl\n");
        exit(1);
    } else {
        wait(NULL); // Ожидание завершения дочернего процесса
        printf("Бинарник запущен.\n");
    }

    return 0;
}
