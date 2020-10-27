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

int override_inputs(struct iza_layer *, double *, size_t);

// Mutate functions

int link_prev_layer(struct iza_layer *, struct iza_layer *);

int create_input_layer(struct iza_layer *, size_t);
int create_layer(struct iza_layer *, struct iza_layer *, size_t);

int delete_layer(struct iza_layer *);

#endif /* IZANAMI_NETWORK_LAYER_H_ */
