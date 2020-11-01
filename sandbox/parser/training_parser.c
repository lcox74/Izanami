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

int
parse_training_data(const char *file, struct training_data_entity *data, size_t *len)
{
    size_t data_size = data_entries_in_csv(file);
    *len = data_size;

    data = (struct training_data_entity *) calloc(data_size, 
	sizeof(struct training_data_entity));

    FILE *fp = fopen(file, "r");
    if (!fp) return 1;

    char* line = NULL;
    size_t line_len, num = 0;
    while (getline(&line, &line_len, fp) >= 0) {
        if (!(num++)) continue;

        struct training_data_entity *current = &data[num - 2];

        if (line[11] == 'n') {
            current->t_invalid = 1;
            continue;
        }

        sscanf(line, "%hu-%hhu-%hhu,%lf,%lf,%lf,%lf,%lf,%d\n", 
            &current->t_date.data.year, 
            &current->t_date.data.month, 
            &current->t_date.data.day, 
            &current->t_open, &current->t_high, &current->t_low,
            &current->t_adj_close, &current->t_close, &current->t_volume);
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