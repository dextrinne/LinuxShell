#include <stdio.h>
#include <stdlib.h> //Для работы getenv

int main() {
  char *path = getenv("PATH");// Получает значение переменной окружения с именем "PATH".  Она возвращает указатель на строку, содержащую значение, или NULL, если переменная не найдена.
  if (path != NULL) {
    printf("Значение переменной PATH: %s\n", path);
  } else {
    printf("Переменная PATH не найдена.\n");
  }
  return 0;
}
