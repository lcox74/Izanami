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
mentioned above. But I also want to implement analytics of the brain as well.
Get realtime data from modules, nodes, data trends, most fired sections, 
generation etc. Though I don't know how useful this would be, it would be cool 
to implment realtime data from the bot to a website/app to monitor the bot.

## Trading Environment
The pseudo trading environment is important to develop for the unsupervised 
learnig to work effectively. This will need to emulate a proper trading 
space where the prices will alter based on historic trading data. The bot 
will also need to be able to buy and sell a stock and the environment needs 
to keep track of the bot's overall cash including percentage of profit, loss, 
number of trades, behaviour issues etc. This along with some rules will surve
as the bot's fitness function.

## References
```
[1] 	Hao, Y.; Gao, Q. Predicting the Trend of Stock Market Index Using the 
	Hybrid Neural Network Based on Multiple Time Scale Feature Learning. 
	Appl. Sci. 2020, 10, 3961. 
```
