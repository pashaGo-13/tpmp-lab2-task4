// pashaGo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/military.h"

int read_servicemen_from_file(const char *filename, Serviceman *servicemen, int max_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия файла %s для чтения\n", filename);
        return -1;
    }
    
    int count = 0;
    char buffer[1024];
    
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        printf("Файл пуст\n");
        fclose(file);
        return 0;
    }
    
    while (count < max_count && fgets(buffer, sizeof(buffer), file)) {
        Serviceman *sm = &servicemen[count];
        
        buffer[strcspn(buffer, "\n")] = 0;
        
        char *token = strtok(buffer, ";");
        if (token) strcpy(sm->surname, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->name, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->patronymic, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.country, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.region, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.district, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.city, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.street, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.house, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.apartment, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.postal_code, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->nationality, token);
        
        token = strtok(NULL, ";");
        if (token) sm->birth_year = atoi(token);
        
        token = strtok(NULL, ";");
        if (token) sm->birth_month = atoi(token);
        
        token = strtok(NULL, ";");
        if (token) sm->birth_day = atoi(token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->position, token);
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->rank, token);
        
        count++;
    }
    
    fclose(file);
    return count;
}

