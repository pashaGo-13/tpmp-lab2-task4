// pashaGo
#include <stdio.h>
#include <stdlib.h>
#include "../include/military.h"

#define INPUT_FILE "data.txt"
#define OUTPUT_FILE "lieutenants.txt"

int main() {
    Serviceman servicemen[MAX_RECORDS];
    Serviceman lieutenants[MAX_RECORDS];
    int count = 0;
    int lieutenants_count = 0;
    
    count = read_servicemen_from_file(INPUT_FILE, servicemen, MAX_RECORDS);
    if (count <= 0) {
        printf("Ошибка чтения данных из файла\n");
        return 1;
    }
    
    filter_lieutenants(servicemen, count, lieutenants, &lieutenants_count);
    
    printf("\nВоеннослужащие в звании 'лейтенант' (%d чел.) \n", 
           lieutenants_count);
    for(int i = 0; i < lieutenants_count; i++) {
        print_serviceman(&lieutenants[i]);
    }
    
    if (lieutenants_count > 0) {
        int written = write_servicemen_to_file(OUTPUT_FILE, lieutenants, lieutenants_count);
    } else {
        printf("\nЛейтенантов не найдено\n");
    }
    
    return 0;
}