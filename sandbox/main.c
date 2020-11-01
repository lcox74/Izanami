
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser/data_structure.h"
#include "parser/training_parser.h"
#include "user_data.h"

struct training_data {
    
    struct bot_data t_bot_data;

    size_t t_training_size;
    struct training_data_entity *t_data;
    
    // Bot's Brain
};

const int bots_per_generation = 1000; /* Subject to change */


void train_bot(void *);




int
main(int argc, char *argv[])
{
    size_t data_len;
    struct training_data_entity *all_data;
    parse_training_data("../training_data/5GN.AX.csv", all_data, &data_len);

    unsigned char running = 1;
    while (running) {

        for (size_t i = 0; i < data_len; i++) {

        }


    }

    return 0;
}

void train_bot(void *args) {
    // Get bot's brain, bot data and training data
    struct training_data *bot = (struct training_data *)args;

    // Loop through training data
    for (size_t i = 0; i < bot->t_training_size; i++) {
        // Allow bot to buy and sell

    }
    
    // Calculate fitness
    bot->t_bot_data.b_fitness = bot->t_bot_data.b_pool; /* Add extra here */
}