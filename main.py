import os
from neat import neat




def main():
    brain = 0

    # Lead Brain
    if os.path.isfile('izanami.neat'):
        brain = neat.Brain.load('izanami')
    else:
        hyperparams = neat.Hyperparameters()
        hyperparams.delta_threshold = 0.75

        hyperparams.mutation_probabilities['node'] = 0.05
        hyperparams.mutation_probabilities['edge'] = 0.05

        brain = neat.Brain(4, 1, 100, hyperparams)
        brain.generate()
    
    

if __name__ == "__main__":
    main()