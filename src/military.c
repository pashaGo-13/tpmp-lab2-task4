#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/military.h"

void init_serviceman(Serviceman *sm) {
    memset(sm, 0, sizeof(Serviceman));
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

int is_lieutenant(const Serviceman *sm) {
    char rank_lower[MAX_STRING];
    strcpy(rank_lower, sm->rank);
    
    for(int i = 0; rank_lower[i]; i++) {
        rank_lower[i] = tolower(rank_lower[i]);
    }
    
    return (strstr(rank_lower, "лейтенант") != NULL);
}

void filter_lieutenants(const Serviceman *input, int input_count, Serviceman *output, int *output_count) {
    *output_count = 0;
    for(int i = 0; i < input_count && *output_count < MAX_RECORDS; i++) {
        if(is_lieutenant(&input[i])) {
            output[*output_count] = input[i];
            (*output_count)++;
        }
    }
}