// pashaGo
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/military.h"

void init_serviceman(Serviceman *sm) {
    memset(sm, 0, sizeof(Serviceman));
    sm->is_valid = 1;
}

void print_serviceman(const Serviceman *sm) {
    printf("Фамилия: %s\n", sm->surname);
    printf("Имя: %s\n", sm->name);
    printf("Отчество: %s\n", sm->patronymic);
    printf("Дата рождения: %d-%02d-%02d\n", 
           sm->birth_year, sm->birth_month, sm->birth_day);
    printf("Национальность: %s\n", sm->nationality);
    printf("Должность: %s\n", sm->position);
    printf("Звание: %s\n", sm->rank);
    printf("Адрес: %s, %s, %s, %s, %s, д.%s, кв.%s, %s\n",
           sm->address.country,
           sm->address.region,
           sm->address.district,
           sm->address.city,
           sm->address.street,
           sm->address.house,
           sm->address.apartment,
           sm->address.postal_code);
}


int is_exact_lieutenant(const Serviceman *sm) {
    if (!sm->is_valid) return 0;
    
    char rank_lower[MAX_STRING];
    char lieutenant_lower[] = "лейтенант";
    char senior_lieutenant_lower[] = "старший лейтенант";
    
    strcpy(rank_lower, sm->rank);
    
    for(int i = 0; rank_lower[i]; i++) {
        rank_lower[i] = tolower(rank_lower[i]);
    }
    
    if (strstr(rank_lower, senior_lieutenant_lower) != NULL) {
        return 0;
    }
    
    return (strcmp(rank_lower, lieutenant_lower) == 0);
}

int validate_serviceman(const Serviceman *sm) {
    if (strlen(sm->surname) == 0) return 0;
    if (strlen(sm->name) == 0) return 0;
    if (strlen(sm->patronymic) == 0) return 0;
    if (strlen(sm->nationality) == 0) return 0;
    if (strlen(sm->position) == 0) return 0;
    if (strlen(sm->rank) == 0) return 0;
    
    if (strlen(sm->address.country) == 0) return 0;
    if (strlen(sm->address.region) == 0) return 0;
    if (strlen(sm->address.district) == 0) return 0;
    if (strlen(sm->address.city) == 0) return 0;
    if (strlen(sm->address.street) == 0) return 0;
    if (strlen(sm->address.house) == 0) return 0;
    if (strlen(sm->address.apartment) == 0) return 0;
    if (strlen(sm->address.postal_code) == 0) return 0;
    
    if (sm->birth_year < 1900 || sm->birth_year > 2024) return 0;
    if (sm->birth_month < 1 || sm->birth_month > 12) return 0;
    if (sm->birth_day < 1 || sm->birth_day > 31) return 0;
    
    return 1;
}

void filter_lieutenants(const Serviceman *input, int input_count, Serviceman *output, int *output_count) {
    *output_count = 0;
    for(int i = 0; i < input_count && *output_count < MAX_RECORDS; i++) {
        if(is_exact_lieutenant(&input[i])) {
            output[*output_count] = input[i];
            (*output_count)++;
        }
    }
}