
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser/data_structure.h"
#include "parser/training_parser.h"

int
main(int argc, char *argv[])
{
    struct training_data_entity *all_data;
    return parse_training_data("../training_data/5GN.AX.csv", all_data);
}