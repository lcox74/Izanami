# Izanami - Trading Bot
The Izanami project is my first attempt on a unsupervised ML trading bot. The
project. I will be using an algorithm/technique called 
[NEAT](http://nn.cs.utexas.edu/downloads/papers/stanley.ec02.pdf) (Neural
Evolution of Augmenting Topologies). I plan to use python as a testing platform 
to quickly mock up what I want to do then will re-write the project in C or C++ 
for extra performance. This project was inspired by my boss as a challenge to 
beat his current trading algorithm that he is currently using.

## The Plan

To start this project **NEAT** requires a couple things planned our before you 
can start using it. These things are the following:
- Inputs
- Outputs
- Fitness Function
- Training Data
- Rules
- Hyper Parameters

I've had changed the spec on this project a number of times as I couldn't figure
out how exactly I want the bot to work. But now after fine tuning the base 
design I have a solid idea of the requirements.

- **Inputs**: The bot will get the `amount of money` it has in its pool. The 
current day `OHLCV percent change` and the simple moving average of 3 time 
seperate time periods `SMA(5), SMA(20), SMA(50)`. Additionally it also recieves
the number of active stocks it has.
- **Outputs**: The bot will have `2` binary outputs. One being a 
`trigger to buy` and the other being a `trigger to sell`.
- **Fitness Function**: The fitness function will be the `most money` made by 
the bot with the `less amount of loss`.
- **Training Data**: This is fetched directly from 
[Yahoo Finance](https://finance.yahoo.com) grabbing the full daily history of a
variety tickers.
- **Rules**: For the bot to work, it will be governed by a series of rules.
  - The bot can only `buy` **or** `sell` in a single day
  - If both `buy` and `sell` outputs are above `50%` nothing will happen that 
  day
  - The bot dies if:
    - Spends more than it has in it's pool
    - Sells what it doesn't have
    - Has over a `90%` loss

## Pseudo Trading Environment
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
complete history of single ticker on the ASX. 

### Simulation Process
The bot will have a pool of money which it can spend on stocks, the
environment will keep track of how many stocks the bot buys and sells. It
won't allow the bot to spend more than its avaliable money or sell anything
the bot doesn't own. If the bot breaks any of these rules, it dies.
