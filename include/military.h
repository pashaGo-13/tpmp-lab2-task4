// pashaGo
#ifndef MILITARY_H
#define MILITARY_H

#define MAX_STRING 100
#define MAX_ADDRESS 256
#define MAX_RECORDS 100

typedef struct {
    char country[MAX_STRING];
    char region[MAX_STRING];
    char district[MAX_STRING];
    char city[MAX_STRING];
    char street[MAX_STRING];
    char house[MAX_STRING];
    char apartment[MAX_STRING];
    char postal_code[MAX_STRING];
} Address;

typedef struct {
    char surname[MAX_STRING];
    char name[MAX_STRING];
    char patronymic[MAX_STRING];
    Address address;
    char nationality[MAX_STRING];
    int birth_year;
    int birth_month;
    int birth_day;
    char position[MAX_STRING];
    char rank[MAX_STRING];
} Serviceman;

void init_serviceman(Serviceman *sm);
void print_serviceman(const Serviceman *sm);
int is_lieutenant(const Serviceman *sm);

int read_servicemen_from_file(const char *filename, Serviceman *servicemen, int max_count);
int write_servicemen_to_file(const char *filename, const Serviceman *servicemen, int count);
void filter_lieutenants(const Serviceman *input, int input_count, Serviceman *output, int *output_count);

#endif
