#ifndef IZANAMI_PARSER_TRAINING_H
#define IZANAMI_PARSER_TRAINING_H

#include "data_structure.h"
#include <stddef.h>

int parse_training_data(const char *, struct training_data_entity *, size_t *);

int string_to_date(char*, struct date_entity*);
const char* date_to_string(struct date_entity*);

#endif /* IZANAMI_PARSER_TRAINING_H */