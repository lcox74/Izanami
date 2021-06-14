import os

import numpy as np
import pandas as pd

import matplotlib.pyplot as plt
from matplotlib import style
import matplotlib as mpl

#from neat import neat

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

pre_calculations("./training_data/tech/IBM.csv")

# def main():
#     brain = 0

#     # Lead Brain
#     if os.path.isfile('izanami.neat'):
#         brain = neat.Brain.load('izanami')
#     else:
#         hyperparams = neat.Hyperparameters()
#         hyperparams.delta_threshold = 0.75

#         hyperparams.mutation_probabilities['node'] = 0.05
#         hyperparams.mutation_probabilities['edge'] = 0.05

#         brain = neat.Brain(4, 1, 100, hyperparams)
#         brain.generate()
    
    

# if __name__ == "__main__":
#     main()