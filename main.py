import os
import math

import numpy as np
from numpy.core.defchararray import translate
import pandas as pd

import matplotlib.pyplot as plt
from matplotlib import style
import matplotlib as mpl

import neat

generation = 0

class Trader:
    def __init__ (self):
        self.money_pool = 100
        self.num_buy = 1
        self.num_sell = 1
        self.currently_owned = False
        self.current_owned_price = 0

        self.loss = 0
        self.num_loss = 0
        self.gain = 0
        self.num_gain = 0

    def get_alive(self):
        return (self.money_pool > 0)

    def get_reward(self):
        if (self.money_pool < 0):
            return 0

        #trade_stats = self.money_pool * (self.num_gain / self.num_sell)
        #return trade_stats # will need to work on
        return self.gain

    def own_stock(self):
        if self.currently_owned:
            return 1.0
        else:
            return 0.0

    def buy_stock(self, cur_price):
        if self.currently_owned and self.money_pool > 0:
            return
        
        self.num_buy += 1
        self.currently_owned = True
        self.current_owned_price = cur_price

        self.money_pool -= 1
    
    def sell_stock(self, cur_price):
        if not self.currently_owned:
            return
        
        self.num_sell += 1
        self.currently_owned = False

        difference = (cur_price - self.current_owned_price)

        if difference > 0:
            self.gain += difference
            self.num_gain += 1
        else:
            self.loss += abs(difference)
            self.num_loss += 1

        self.money_pool += difference
        


def pre_calculations(ticker_file):
    ticker_df = pd.read_csv(ticker_file)

    date_d = ticker_df['Date']
    open_d = ticker_df['Open']
    high_d = ticker_df['High']
    low_d = ticker_df['Low']
    close_d = ticker_df['Close']
    volume_d = ticker_df['Volume']
    
    PC_Open = open_d.pct_change()
    PC_High = high_d.pct_change()
    PC_Low = low_d.pct_change()
    PC_Close = close_d.pct_change()
    PC_Volume = volume_d.pct_change()

    SMA5    = close_d.rolling(window=5).mean()
    SMA20   = close_d.rolling(window=20).mean()
    SMA50   = close_d.rolling(window=50).mean()
    SMA100  = close_d.rolling(window=100).mean()
    SMA200  = close_d.rolling(window=200).mean()

    precal_data = list(zip(date_d, close_d,
                           PC_Open, PC_High, PC_Low, PC_Close, PC_Volume, 
                           SMA5, SMA20, SMA50, SMA100, SMA200))

    precal_col = ['date', 'raw_close', 
                  'open', 'high', 'low', 'close', 'volume',
                  'sma5', 'sma20', 'sma50', 'sma100', 'sma200']

    precal_df = pd.DataFrame(precal_data[200:], columns =precal_col)

    # print(precal_df)
    # print(precal_df.iloc[[0]].values[0]) # Get first row as array

    return precal_df

def sigmoid(x):
  return 1 / (1 + math.exp(-x))

def run_sim(genomes, config):
    # Init NEAT
    nets = []
    traders = []

    # Fetch data
    data_df = pre_calculations("./training_data/tech/IBM.csv")
    data_index = 0

    for id, g in genomes:
        net = neat.nn.FeedForwardNetwork.create(g, config)
        nets.append(net)
        g.fitness = 0

        # Init my cars
        traders.append(Trader())

        global generation
        generation += 1

    while True:

        # print(data_index)
        cur_data = data_df.iloc[[data_index]].values[0]
        # print(cur_data)
        remaining_traders = 0

        # Input my data and get result from network
        for index, trader in enumerate(traders):
            if (trader.get_alive()):
                trader_input = cur_data[2:]
                trader_input = np.insert(trader_input, 0, trader.own_stock())
                
                # Get trade decision
                outputs = nets[index].activate(trader_input)

                # Do buy or Sell
                if trader.own_stock():
                    if sigmoid(outputs[1]) > 0.5:
                        trader.sell_stock(cur_data[1])
                else:
                    if sigmoid(outputs[0]) > 0.5:
                        trader.buy_stock(cur_data[1])

                # Set fitness
                genomes[index][1].fitness = trader.get_reward()

            # Remove trader from list if dead
            if not trader.get_alive():
                remaining_traders += 1

        if remaining_traders == 0 or data_index > (len(data_df) - 200):
            break

        data_index += 1

def main(config_file):

    config = neat.Config(neat.DefaultGenome, neat.DefaultReproduction,
                         neat.DefaultSpeciesSet, neat.DefaultStagnation,
                         config_file)

    # Create the population, which is the top-level object for a NEAT run.
    p = neat.Population(config)

    # Add a stdout reporter to show progress in the terminal.
    p.add_reporter(neat.StdOutReporter(True))
    stats = neat.StatisticsReporter()
    p.add_reporter(stats)
    p.add_reporter(neat.Checkpointer(5))

    # Run for up to 300 generations.
    winner = p.run(run_sim, 1000)
    
    

if __name__ == "__main__":
    main("neatconfig.txt")