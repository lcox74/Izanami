# Izanami - Trading Bot
The Izanami project is my first attempt on a unsupervised ML trading bot. The
project will be split up into two main parts:

- The bot's brain
	- Convolutional Neural Network (CNN)
	- Long Short Term Memory (LSTM)
- Trade environment
	- Stock emulation with historic data
	- Buying & Selling based on brain output
	- Testing bot performance

## The Brain
The brain of the bot will need to do a multiple things outside of being a
Neural Network (NN) architecture. These include data pre-calculations,
normalisation, brain exportation, API implementation etc.

The NN architecture proposed for this project is heavily based on Yaping
Hao and Qiang Gao's paper on stock market trend prediction [1]. As I have no idea
what I am doing, basing the architecture off an existing method is a good
place to start. There will be some alterations to the design, for example
using bi-directional LSTMs and the fact that I am trying to implement
unsupervised learning.

### Exportation
Something I want to implement in the brains API is a way to export the
structure to create an exact replica into a file. Neural Networks can
be huge, and having multiple will be multitudes bigger. So a compression
algorithm will need to be created and the data to be written in bytes to
save on all the storage space I can.

### External API
Of course the brain will need to have some external API to add and create
new structures, mutate weights and nodes, I/O and also the exportation method
mentioned above. But I also want to implement analytics of the brain as well
Get realtime data from modules, nodes, data trends, most fired sections,
generation etc. Though I don't know how useful this would be, it would be cool
to implment realtime data from the bot to a website/app to monitor the bot.

### Architecture
This is still up for debate, but as mentioned before the design will be
heavily influenced by Yaping Hao and Quang Gao's paper [1]. But I will have
to change the approach as I'm making a bot to buy and sell stocks rather than
to predict the trend. The requirements are as follows:
- 3 Bi-directional LSTMS
- 2 1D Convolution layers with Max Pooling
	- Features will vary with bot evolutions
- 2 Deep Neural networks

Now that we know roughly what is going to be in the bot, I should mention the
I/O expected.
#### Input
- Money in pool
- Number of stocks
- OHLCV of past `x` days excluding the "current" day

#### Output
- Buy trigger
- Sell trigger
- Hold trigger
- Current day predicted
	- Close
	- High
	- Low

The triggers will have to follow a set of rules. If `hold` is greater than
`0.5` then it doesn't matter what `buy` or `sell` are, it must hold the stock.
If `hold` is less than `0.5` and both `buy` and `sell` are greater than `0.5`
then do what ever has a higher probability. If for whatever reason they are
the same, then hold the stock.

#### Structure
Below is a the general structure for the bot. Due to size limitations I
simplified everything down to symbols. At the bottom of it is a `key` that
explains what each symbol means. Symbols like `|`, `-`, `+`, `>` or `^`
represent data flow, while text inside `[]` are networks.

```
   
                     [OUTPUT]
                         ^
                         |
           +----------->[D]
           |             ^
           |             |
           |            [D]
           |             ^
           |             |
           |      +------+------+
           |      |      |      |
           |     [L]    [L]    [L]
           |      ^      ^      ^
           |      |      |      |
           |      |     [C]--->[C]
           |      |      ^
           |      |      |
           |      +------+
           |             |
         [IN 1]        [IN 2]

__________________________________________________________

  OUTPUT - The produced output from the network
  IN 1 - Bot's data ie. money in the pool and no. stocks
  IN 2 - Normalised OHLCV data
  D - Deep Neural Network
  L - Bi-directional LSTM
  C - 1D Convolution Layer

```

## Trading Environment
The pseudo trading environment is important to develop for the unsupervised
learnig to work effectively. This will need to emulate a proper trading
space where the prices will alter based on historic trading data. The bot
will also need to be able to buy and sell a stock and the environment needs
to keep track of the bot's overall cash including percentage of profit, loss,
number of trades, behaviour issues etc. This along with some rules will serve
as the bot's fitness function.

### Simulation Data
By using [Yahoo Finance](https://finance.yahoo.com) I can make a simple web
scraper to bulk fetch alot of data. I've actually done this already. I have
roughly 1.8 thousand csv files in OHLCV format with each file being the
complete history of single ticker on the ASX. These files won't be included
in the repo.

### Simulation Process
The bot will have a pool of money which it can spend on stocks, the
environment will keep track of how many stocks the bot buys and sells. It
won't allow the bot to spend more than its avaliable money or sell anything
the bot doesn't own. If the bot breaks any of these rules, it dies and a the
next bot will start the simulation from scratch.

The environment will suply the bot with the following inputs:
- Current money in the pool
- Current number of stocks owned
- OHLCV of past `x` number off days. (`x` requested by bot?)

### Fitness Function
The environment will need to test the bot on how well it does. This is defined
by a few set rules and modifiers, some rules have been previously mentioned.
Unlike rules, modifiers will help tweak the bots behaviour. The total fitness
of the bot is its how much the bot has in its pool, multiplied by the sum of
the modifiers. Bots how have died also have a fitness function and will be
compared to the performance of the bots that survived.

#### Rules
1. If the bot spends more than what it has, the bot dies.
2. If the bot sells what it does not own, the bot dies.
3. The bot can only buy 1 stock per day and sell 1 stock per day.
4. The bot can either buy or sell in the day, not both.

#### Modifiers
- Buy/day Ratio (Smaller the better, this will vary)
- Sell/day Ratio (Smaller the better, this will vary)
- Buy/sell Ratio (Larger the better, this will vary)
- How close the prediction was to the actual next day
 
> Modifiers will require tweaking as I don't actually know what is good.

## References
```
[1]   Hao, Y.; Gao, Q. Predicting the Trend of Stock Market Index Using the
      Hybrid Neural Network Based on Multiple Time Scale Feature Learning.
      Appl. Sci. 2020, 10, 3961. 
```
