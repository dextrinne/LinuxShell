#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

// Функция для обработки команды echo
bool handle_echo(char *command, char *output) {
    if (strncmp(command, "echo ", 5) == 0) {
        strcpy(output, command + 5); // Выводим весь текст после "echo"
        return true;
    }
    return false;
}

int main() {
    
    // Задание 5: команда echo и проверка этой команды
    printf("Задание 5: команда echo и проверка этой команды\n");
    printf("\n");
    char buffer[BUFFER_SIZE]; // Ввод команды
    char output[BUFFER_SIZE]; // Вывод строки

    while (1) {
        printf("Введите команду echo и текст после команды (если хотите выйти введите exit):\n");
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break; // Выход при Ctrl+D
        }

        buffer[strcspn(buffer, "\n")] = 0; // Удаляем символ новой строки

        if (strcmp(buffer, "exit") == 0) {
            break; // Выход при вводе "exit"
        }

        if (handle_echo(buffer, output)) {
            printf("%s\n", output);
        } 
        
        else {
            printf("Неправильный ввод: %s\n", buffer);
        }
        printf("\n");
    }
    printf("Выход из программы.\n");
    return 0;
}


