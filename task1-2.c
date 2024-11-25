#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024 // Максимальный размер буфера

int main() {
  
  //Задание 1
  printf("Задание 1: Ввод/вывод строки\n");
  printf("\n");
  char buffer[BUFFER_SIZE];
  printf("Введите строку:\n");
  if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
    perror("Ошибка чтения строки"); // Вывод сообщения об ошибке
    return 1; // Возвращение кода ошибки
  }
  // Удаление символа новой строки, который fgets() добавляет в конец.
  buffer[strcspn(buffer, "\n")] = 0;
  printf("Вы ввели: %s\n", buffer);
  printf("\n");
  
  //Задание 2
  printf("Задание 2: Ввод строки в цикле и вывод по Ctrl+D\n");
  char buffer1[BUFFER_SIZE];
  while (1) { //бесконечный цикл, пока не прожмётся комбинация клавиш
      printf("Введите строку (Ctrl+D для выхода):\n");
      if (fgets(buffer1, BUFFER_SIZE, stdin) == NULL) {
          // Ctrl+D отправляет сигнал EOF (конец файла), который fgets() обрабатывает как NULL.
          break;
      }
      buffer1[strcspn(buffer1, "\n")] = 0;
      printf("Вы ввели: %s\n", buffer1);
  }
  printf("Задание 2 завершено.\n");
  printf("\n");
  
  return 0;
}


