#ifndef IZANAMI_NETWORK_LAYER_H_
#define IZANAMI_NETWORK_LAYER_H_

#include "neuron.h"

struct iza_layer {
	struct iza_neuron *l_neurons;
	double *l_weight;
	unsigned int l_size;	
	
	struct iza_layer *l_prev;
	struct iza_layer *l_next;
}

void override_inputs(double *);

void link_prev_layer(struct iza_layer *);
void link_next_layer(struct iza_layer *);

void create_layer(struct iza_layer *);
void create_layers(struct iza_layers *, size_t);

void delete_layer(struct iza_layer *);

#endif /* IZANAMI_NETWORK_LAYER_H_ */
