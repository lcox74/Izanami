#include "layer.h"

#include <stdlib.h>

/*
 * Linking a new previous layer resets the weights
 */
void
link_prev_layer(struct iza_layer *layer, struct iza_layer *prev) {
	/* Setting up input layer */
	layer->l_prev = prev;
	layer->l_input_size = prev->l_layer_size;

	/* Construct weights (input size * layer size) */
	layer->l_weights = (double *) calloc(layer->l_layer_size * 
	    prev->l_layer_size, sizeof(double));
}

void
create_input_layer(struct iza_layer *layer, size_t size) {
	layer = (struct iza_layer *) calloc(1, sizeof(struct iza_layer));

	/* Setting up this layer's neurons */
	layer->l_layer_size = size;
	create_neurons(layer->l_neurons, size);
}

void
create_layer(struct iza_layer *layer, struct iza_layer *prev, size_t size) {
	layer = (struct iza_layer *) calloc(1, sizeof(struct iza_layer));

	/* Setting up input layer */
	layer->l_prev = prev;
	layer->l_input_size = prev->l_layer_size;

	/* Setting up this layer's neurons */
	layer->l_layer_size = size;
	create_neurons(layer->l_neurons, size);

	/* Construct weights (input size * layer size) */
	layer->l_weights = (double *) calloc(size * prev->l_layer_size, 
	    sizeof(double));
}

void
delete_layer(struct iza_layer *layer) {
	delete_neuron(layer->l_neurons);
	free(layer->l_weights);
	free(layer);
}



