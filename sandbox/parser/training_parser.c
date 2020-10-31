#include "training_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t
data_entries_in_csv(const char* file)
{
    FILE *fp = fopen(file, "r");
    if (!fp) return 0;

    char* line = NULL;
    size_t len, line_num = 0;

    while (getline(&line, &len, fp) >= 0) line_num++;
    
    fclose(fp);
    return --line_num;
}

int assign_training_data_to_entry(int index, char *val, 
    struct training_data_entity *entry)
{
    switch(index) {
        case 0:
            entry->t_date = val;
            printf("%s | ", entry->t_date);
            break;
        case 1:
            entry->t_open = strtof(val, NULL);
            printf("%f | ", entry->t_open);
            break;
        case 2:
            entry->t_high = strtof(val, NULL);
            printf("%f | ", entry->t_high);
            break;
        case 3:
            entry->t_low = strtof(val, NULL);
            printf("%f | ", entry->t_low);
            break;
        case 4:
            entry->t_close = strtof(val, NULL);
            printf("%f | ", entry->t_close);
            break;
        case 5:
            entry->t_adj_close = strtof(val, NULL);
            printf("%f | ", entry->t_adj_close);
            break;
        case 6:
            entry->t_volume = strtol(val, NULL, 10);
            printf("%d \n", entry->t_volume);
            break;
    }
    return 0;
}

int
split_training_csv(char* line, struct training_data_entity *entry)
{
    char *split = strtok(line, ",");
    int pos = 0;
    while(split) {
        assign_training_data_to_entry(pos++, split, entry);
        split = strtok(NULL, ",");
        if (split == "null") {
            entry->t_invalid = 1;
            return 1;
        }
    }

    return 0;
}

int
parse_training_data(const char *file, struct training_data_entity *data)
{
    size_t data_size = data_entries_in_csv(file);
    data = (struct training_data_entity *) calloc(data_size, 
	sizeof(struct training_data_entity));

    FILE *fp = fopen(file, "r");
    if (!fp) return 1;

    char* line = NULL;
    size_t len, num = 0;
    while (getline(&line, &len, fp) >= 0) {
        if (!(num++)) continue;

        split_training_csv(line, &data[num - 2]);
    }

    fclose(fp);
    return 0;
}

int 
string_to_date(char* in, struct date_entity* out)
{   
    char *split = strtok(in, "-");
    int pos = 0;
    while(split) {
        if (pos == 0) out->data.year = strtol(split, NULL, 10);
        else if (pos == 1) out->data.month = strtol(split, NULL, 10);
        else if (pos == 2) out->data.day = strtol(split, NULL, 10);

        split = strtok(NULL, "-");
        pos++;
    }

	return 0;
}

const char 
*date_to_string(struct date_entity* in)
{
	return "temp";
}