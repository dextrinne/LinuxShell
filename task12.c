#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 
#define BUFFER_SIZE 1024

void mem_dump(DIR* dir, char* path) {
    FILE* res = fopen("12.txt", "w+");
    fclose(res);
    struct dirent* ent;
    char* file_path;
    
    while ((ent = readdir(dir)) != NULL) {
        asprintf(&file_path, "%s/%s", path, ent->d_name);
        FILE *f1 = fopen("12.txt", "a");
        FILE *f2 = fopen(file_path, "r");
        if (!f1 || !f2) {
        printf("Ошибка чтения файла %s\n", file_path);
        return;
    }
    char buf[256];

    while (fgets(buf, 256, f2) != NULL) {
        fputs(buf, f1);
    }
    fclose(f1);
    fclose(f2);
    }
    printf("Готово\n");
}

 
int main() {
    printf("Задание 12: По mem <procid> получить дамп памяти процесса\n");
    printf("\n");
    
    char input[BUFFER_SIZE];
 
    do {
        printf("Введите функцию: ");
        fflush(stdout);
        bool check=false;

        // input
        if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
            printf("\nЗавершение работы (Ctrl+D)\n");
            break; // выход из цикла при EOF
        }
 
        // \n
        input[strcspn(input, "\n")] = '\0';
 
        // exit
        if (strcmp(input, "exit") == 0) {
            printf("Завершение работы (exit)\n");
            break;
        }
        
        if (strncmp(input, "\\mem ", 5) == 0) {
            char* path;
            asprintf(&path, "/proc/%s/map_files", input+5);

            DIR* dir = opendir(path);
            if (dir) {
                mem_dump(dir, path);
            }
            else {
                printf("Процесс не найден\n");
            }
            check = true;
            continue;
        }

        if(check==false){
        printf("Команда '%s' не найдена\n", input);
        }
       
    }
    while (!feof(stdin));
 
    return 0;
}
