#include <stdio.h>
#include <stdlib.h>
#include "../include/military.h"

#define INPUT_FILE "data.txt"
#define OUTPUT_FILE "lieutenants.txt"

void display_file_content() {
    FILE *file = fopen(INPUT_FILE, "r");
    if (!file) {
        printf("Ошибка открытия файла %s\n", INPUT_FILE);
        return;
    }
    
    printf("\nСодержимое файла %s\n", INPUT_FILE);
    char buffer[1024];
    int line_num = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%2d: %s", ++line_num, buffer);
    }
    
    fclose(file);
}

int main() {
    Serviceman servicemen[MAX_RECORDS];
    Serviceman lieutenants[MAX_RECORDS];
    int count = 0;
    int lieutenants_count = 0;

    display_file_content();
    
    count = read_servicemen_from_file(INPUT_FILE, servicemen, MAX_RECORDS);
    if (count <= 0) {
        printf("Ошибка чтения данных из файла\n");
        return 1;
    }
    
    
    printf("Все военнослужащие \n");
    for(int i = 0; i < count; i++) {
        print_serviceman(&servicemen[i]);
    }
    
    filter_lieutenants(servicemen, count, lieutenants, &lieutenants_count);
    
    printf("\nВоеннослужащие в звании 'лейтенант' (%d чел.) \n", 
           lieutenants_count);
    for(int i = 0; i < lieutenants_count; i++) {
        print_serviceman(&lieutenants[i]);
    }
    
    if (lieutenants_count > 0) {
        int written = write_servicemen_to_file(OUTPUT_FILE, lieutenants, lieutenants_count);
        if (written > 0) {
            printf("\nРезультаты сохранены в файл %s\n", OUTPUT_FILE);
            printf("Найдено и сохранено %d лейтенантов\n", lieutenants_count);
        }
    } else {
        printf("\nЛейтенантов не найдено\n");
    }
    
    return 0;
}