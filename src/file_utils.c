#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/military.h"

int read_servicemen_from_file(const char *filename, Serviceman *servicemen, int max_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("ОШИБКА: Не удалось открыть файл %s для чтения\n", filename);
        return -1;
    }
    
    int count = 0;
    int line_num = 0;
    int error_count = 0;
    char buffer[1024];
    
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        printf("ОШИБКА: Файл пуст\n");
        fclose(file);
        return -1;
    }
    line_num++;
    
    while (count < max_count && fgets(buffer, sizeof(buffer), file)) {
        line_num++;
        
        buffer[strcspn(buffer, "\n")] = 0;
        
        int field_count = 1;
        for(char *p = buffer; *p; p++) {
            if(*p == ';') field_count++;
        }
        
        if (field_count != EXPECTED_FIELDS) {
            printf("ПРЕДУПРЕЖДЕНИЕ: Строка %d содержит %d полей (ожидалось %d).\n", 
                   line_num, field_count, EXPECTED_FIELDS);
            error_count++;
            continue;
        }
        
        Serviceman *sm = &servicemen[count];
        init_serviceman(sm);
        
        char *token = strtok(buffer, ";");
        if (token) strcpy(sm->surname, token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->name, token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->patronymic, token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.country, token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.region, token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.district, token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.city, token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.street, token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.house, token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.apartment, token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->address.postal_code, token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->nationality, token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) sm->birth_year = atoi(token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) sm->birth_month = atoi(token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) sm->birth_day = atoi(token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->position, token);
        else sm->is_valid = 0;
        
        token = strtok(NULL, ";");
        if (token) strcpy(sm->rank, token);
        else sm->is_valid = 0;
        
        if (!validate_serviceman(sm)) {
            printf("ПРЕДУПРЕЖДЕНИЕ: Строка %d содержит некорректные данные.\n", line_num);
            sm->is_valid = 0;
            error_count++;
        } else {
            count++;
        }
    }
    
    fclose(file);

    return count;
}

int write_servicemen_to_file(const char *filename, const Serviceman *servicemen, int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("ОШИБКА: Не удалось открыть файл %s для записи\n", filename);
        return -1;
    }
    
    fprintf(file, "Фамилия;Имя;Отчество;Страна;Область;Район;Город;Улица;Дом;Квартира;Индекс;Национальность;Год;Месяц;День;Должность;Звание\n");
    
    int valid_count = 0;
    for(int i = 0; i < count; i++) {
        const Serviceman *sm = &servicemen[i];
        
        if (sm->is_valid) {
            fprintf(file, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%d;%d;%d;%s;%s\n",
                    sm->surname,
                    sm->name,
                    sm->patronymic,
                    sm->address.country,
                    sm->address.region,
                    sm->address.district,
                    sm->address.city,
                    sm->address.street,
                    sm->address.house,
                    sm->address.apartment,
                    sm->address.postal_code,
                    sm->nationality,
                    sm->birth_year,
                    sm->birth_month,
                    sm->birth_day,
                    sm->position,
                    sm->rank);
            valid_count++;
        }
    }
    
    fclose(file);
    return valid_count;
}