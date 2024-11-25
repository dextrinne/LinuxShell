#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024 // Максимальный размер буфера

int main() {
  
  //Задание 3  
  printf("Задание 3: Добавление команд выхода\n");
  char input[BUFFER_SIZE];
  printf("Введите команду для закрытия (exit или \q)\n");
  fgets(input, BUFFER_SIZE, stdin);
  input[strcspn(input, "\n")] = 0; // Удаляем символ новой строки
  if (strcmp(input, "exit") == 0 || strcmp(input, "\\q") == 0) {
            exit(1); // Прекращение работы task3.c в терминале 
  }
  else {
      printf("Вы ввели несуществующую команду.\n"); // Сообщение об ошибке
  }

  return 0;
}


