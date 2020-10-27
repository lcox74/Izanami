#include "neuron.h"

#include <stdlib.h>
#include <string.h>

double
process_neuron(struct iza_neuron *neuron, double *inputs, double *weights, 
    size_t input_size) {

	if (!(neuron->n_flags & (NEU_ACTIVATION_SET | NEU_BIAS_SET)))
		return 0.0;

	double sum = 0.0;
	
	for (size_t i = 0; i < input_size; i++) {
		sum += inputs[i] * weights[i];
	}

	return (neuron->n_output = neuron->n_activation(sum));
}

double
get_neuron_value(struct iza_neuron *neuron) {
	return neuron->n_output;
}

void
override_neuron(struct iza_neuron *neuron, double new_output) {
	neuron->n_output = new_output;
}

void
set_neuron_activation(struct iza_neuron *neuron, size_t index) {
	size_t = constrained_index = (index < ACT_MAX) ? index : ACT_MAX;
	neuron->n_activation = iza_activations[constrained_index]; 
	neuron->n_flags |= NEU_ACTIVATION_SET;
}

void
set_neuron_bias(struct iza_neuron *neuron, double new_bias) {
	neuron->n_bias = new_bias;
	neuron->n_flags |= NEU_BIAS_SET;
}

void
create_neuron(struct iza_neuron *neuron) {
	neuron = (struct iza_neuron *) calloc(sizeof(struct iza_neuron));
	neuron->n_flags = NEU_EMPTY | NEU_CREATED;
}

void
create_neurons(struct iza_neuron *neurons, size_t neurons_num) {
	neurons = (struct iza_neuron *) calloc(
	    sizeof(struct iza_neuron) * neurons_num);

	for (int i = 0; i < neurons_num; i++) {
		neuron[i]->n_flags = NEU_EMPTY | NEU_CREATED;
	}
}

void
create_copy_neuron(struct iza_neuron *dest, struct iza_neuron *src) {
	dest = (struct iza_neuron *) calloc(sizeof(struct iza_neuron));
	*dest = *src;
}

void
delete_neuron(struct iza_neuron *neuron) {
	free(neruon);
}

