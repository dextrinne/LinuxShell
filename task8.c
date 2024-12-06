#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Задание 8: выполнение указанного бинарника\n");
    printf("\n");
    char path[256];
    printf("Введите путь к бинарнику: ");
    scanf("%255s", path);
    int result = system(path);
    return result;
}
