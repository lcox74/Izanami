#include "layer.h"

#include <stdlib.h>

/*
 * The first layer of the network is the input layer, this overrides the
 * conventional hidden layer and sets all its neurons to the given values.
 * Returns 0 on success.
 */
int
override_inputs(struct iza_layer *layer, double *inputs, size_t size)
{
	if (size != layer->l_layer_size) return 1;

	int error = 0;
	for (size_t i = 0; i < size; i++) 
		if ((error = override_neuron(&layer->l_neurons[i], inputs[i]))) break;

	return error;
}

/*
 * Linking a new previous layer resets the weights. Returns 0 on success.
 */
int
link_prev_layer(struct iza_layer *layer, struct iza_layer *prev)
{
	/* Setting up input layer */
	layer->l_prev = prev;
	layer->l_input_size = prev->l_layer_size;

	/* Construct weights (input size * layer size) */
	layer->l_weights = (double *) calloc(layer->l_layer_size * 
	    prev->l_layer_size, sizeof(double));

	return 0;
}

/*
 * Creates a input layer of 'size' neurons, as it's the first layer in the
 * network, it doesn't require a reference to the previous layer. Returns 0
 * on success.
 */
int
create_input_layer(struct iza_layer *layer, size_t size) 
{
	int error = 0;
	layer = (struct iza_layer *) calloc(1, sizeof(struct iza_layer));

	/* Setting up this layer's neurons */
	layer->l_layer_size = size;
	error = create_neurons(layer->l_neurons, size);

	return error;
}

/*
 * Creates a standard hidden layer of 'size' neurons and gives a reference
 * to the previous layer in the network. Returns 0 on success.
 */
int
create_layer(struct iza_layer *layer, struct iza_layer *prev, size_t size) 
{
	int error = 0;
	layer = (struct iza_layer *) calloc(1, sizeof(struct iza_layer));

	/* Setting up input layer */
	layer->l_prev = prev;
	layer->l_input_size = prev->l_layer_size;

	/* Setting up this layer's neurons */
	layer->l_layer_size = size;
	error = create_neurons(layer->l_neurons, size);

	/* Construct weights (input size * layer size) */
	layer->l_weights = (double *) calloc(size * prev->l_layer_size, 
	    sizeof(double));

	return error;
}

/*
 * Cleans the layer as well as freeing neurons, weights. Returns 0 on success.
 */
int
delete_layer(struct iza_layer *layer) 
{
	int error = 0;
	error = delete_neuron(layer->l_neurons);
	free(layer->l_weights);
	free(layer);

	return error;
}



