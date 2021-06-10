#ifndef IZANAMI_GENOME_H_
#define IZANAMI_GENOME_H_

#include <stdlib.h>

#include "pch.h"

#define CONN_DISABLED(x) (x.flags & 1)

typedef struct _iz_connection {
    u16 in;
    u16 out;
    double weight;
    u8 flags;
    u32 innovation;
} iz_connection;

typedef struct _iz_genome {
    u8 node_sensors;    /* 255 possible sensors  */
    u8 node_outputs;    /* 255 possible outputs  */
    u16 node_size;      /* 65,535 possible nodes */
    double* nodes;
    
    double fitness;

    u32 connection_size;
    iz_connection* connections;
} iz_genome;

/* Genome doens't support recursive connections */

u8 create_new_genome(iz_genome* target, u8 inputs, u8 outputs);
u8 refresh_nodes(iz_genome* target);

u8 genome_set_inputs(iz_genome* target, double* inputs, u8 size);
u8 genome_process(iz_genome* target);

u8 genome_crossover(iz_genome* target, iz_genome* p1, iz_genome* p2);

u8 mutate_add_connection(iz_genome* target, double chance);
u8 mutate_add_node(iz_genome* target, double chance);
u8 mutate_perturb_connections(iz_genome* target, double chance);


#endif /* IZANAMI_GENOME_H_ */
