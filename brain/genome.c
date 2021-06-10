#include "genome.h"

#define INITIAL_WEIGHT (((rand() / (double)RAND_MAX) * 4.0 - 2))

u32 GLOBAL_INOVATION_NUM = 1;

/*
 * Creates the starting/initial Genomes before learning.
 *      - No hidden nodes
 */
u8 create_new_genome(iz_genome* target, u8 inputs, u8 outputs) {
    u16 inovation = 1, index = 0, i, in, out;

    // Initialising Genome Sizes and Values
    target->node_sensors = inputs;
    target->node_outputs = outputs;
    target->node_size = inputs + outputs;
    target->fitness = 0.0;

    // Initialise Nodes
    target->nodes = (double*) malloc(target->node_size * sizeof(double));
    for (i = 0; i < target->node_size; i++) {
        target->nodes[i] = 0.0;
    }

    // Initialise Connections
    target->connections = (iz_connection*) malloc(inputs * 
                                                  outputs * 
                                                  sizeof(iz_connection));
    
    for (in = 0; in < inputs; in++) {
        for (out = 0; out < outputs; out++) {
            index = in * outputs + out;
            target->connections[index].in = in;
            target->connections[index].out = out;
            target->connections[index].weight = INITIAL_WEIGHT;
            target->connections[index].flags = 0;
            target->connections[index].innovation = (inovation)++;
        }
    }

    // Set the global inovation number for mutations
    GLOBAL_INOVATION_NUM = inovation;

    return 0;
}

/*
 * Clears all nodes in the Genome. 
 */
u8 refresh_nodes(iz_genome* target) {
    for (size_t i = 0; i < target->node_size; i++) {
        target->nodes[i] = 0.0;
    }
}
