#ifndef IZANAMI_NETWORK_NEURON_H
#define IZANAMI_NETWORK_NEURON_H

#include <stddef.h>

#define NEU_EMPTY   		 0
#define NEU_CREATED 		(1 << 0)
#define NEU_ACTIVATION_SET 	(1 << 1)
struct iza_neuron {
	double n_output;
	double n_bias;

	unsigned char n_flags;

	/* Activation can be selected */
	double (*n_activation)(double);
};

double 	process_neuron(struct iza_neuron *, double *, double *, size_t);
double	get_neuron_value(struct iza_neuron *);

int  	override_neuron(struct iza_neuron *, double);
int 	set_neuron_activation(struct iza_neuron *, size_t);
int 	set_neuron_bias(struct iza_neuron *, double);

int 	create_neuron(struct iza_neuron *);
int 	create_neurons(struct iza_neuron *, size_t);
int 	create_copy_neuron(struct iza_neuron *, struct iza_neuron *);

int 	delete_neuron(struct iza_neuron *);

#endif /* IZANAMI_NETWORK_NEURON_H */
