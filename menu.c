#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define COMMAND_HISTORY_FILE "command_history.txt" // Будем сохранять в этот файл историю команд пользователя - задание 4
#define MAX_COMMANDS 100

void log_command(const char* command) {
    FILE *file = fopen(COMMAND_HISTORY_FILE, "a");
    if (file) {
        fprintf(file, "%s\n", command);
        fclose(file);
    }
}

void list_c_files(char files[][100], int* count) {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Ошибка открытия директории");
        return; // Выход из функции
    }

    struct dirent *entry;
    *count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strlen(entry->d_name) > 2 && strcmp(entry->d_name + strlen(entry->d_name) - 2, ".c") == 0) { // Обеспечиваем то, чтобы отображались только файлы С в меню
            strncpy(files[(*count)], entry->d_name, 100);
            files[(*count)][99] = '\0'; // Гарантируем нуль-терминатор
            (*count)++;
        }
    }

    closedir(dir);
}

int main() {
    char files[MAX_COMMANDS][100];
    int count = 0;
    char command[200];

    while (1) { //Бесконечный цикл для работы меню
        list_c_files(files, &count);
        printf("Выберите файл для компиляции:\n");
        
        for (int i = 0; i < count; i++) {
            printf("%d: %s\n", i + 1, files[i]); 
        }

        printf("0: Выйти\n"); 
        int choice;
        printf("\n"); 
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        printf("\n"); 

        if (choice == 0) break; // Выход из программы

        if (choice > 0 && choice <= count) {
            sprintf(command, "gcc %s -o output && ./output", files[choice - 1]); // Запись того, какие файлы компилировали и запускали
            log_command(command); // Сохраняем команду в историю
            
            int ret = system(command); // Выполняем команду
            if (ret == -1) {
                perror("Ошибка выполнения команды");
            }
        } 
        else {
            printf("Неверный выбор.\n");
        }
        printf("\n");
    }

    return 0;
}
