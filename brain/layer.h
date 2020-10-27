#ifndef IZANAMI_NETWORK_LAYER_H_
#define IZANAMI_NETWORK_LAYER_H_

#include <stddef.h>

#include "neuron.h"

struct iza_layer {
	struct iza_neuron *l_neurons;
	size_t l_layer_size;
	
	double *l_weights;
	
	struct iza_layer *l_prev;
	size_t l_input_size;
};

// void override_inputs(struc iza_layer *, double *);

// Mutate functions

void link_prev_layer(struct iza_layer *, struct iza_layer *);

void create_input_layer(struct iza_layer *, size_t);
void create_layer(struct iza_layer *, struct iza_layer *, size_t);

void delete_layer(struct iza_layer *);

#endif /* IZANAMI_NETWORK_LAYER_H_ */
