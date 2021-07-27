# Izanami - Algo Trading

Project Izanami is planned to be an Algo Trading Strategy tester and platform.
Designed to be a single header file that can be included in the project and have
as simple syntax for designing strategies and algorithms.

## Strategy Syntax

The following is an example of how to use Izanami to develop your trading 
strategy. The `Izanami_Client` requires an initial captial (starting money pool)
and the number of shares to buy & sell each trade. Other requirements are the
`buy_trigger` and `sell_trigger` which is how your algorithm knows when to 
trade. If you return `true` then it schedules to buy on the *Open* price for the
next iteration (eg. next day). You can set up your own variables in your 
strategy class allowing you to build state machine like strategies.

```C++
#include "src/Izanami.hpp"

class myStrategy : public Izanami_Client {
public:
    // Required: Constructor
    myStrategy(float initial, u8 shares) : Izanami_Client(initial, shares) {}

    // Required: Buy Trigger
    bool buy_trigger() override {
        bool rule1 = ref(CLOSE) <= LLV(7, -1);
        bool rule2 = ref(CLOSE) > SMA(CLOSE, 200);

        // Set Stop Loss (Only applies if actually buys)
        set_stop_loss(ref(CLOSE) - (2 * ATR(20)));

        return rule1 && rule2;
    }

    // Required: Sell Trigger
    bool sell_trigger() override {
       bool rule1 = ref(CLOSE) >= HHV(7, -1);
        
        return rule1;
    }
};

int main(int argc, char *argv[]) {
    auto strat = myStrategy(100.0f, 10);

    strat.load_history("./training_data/GOOG.csv");
    strat.backtest();

    return 0;
}
```

To get the current day's price, you need to use `ref` for reference. This 
function requires a type being; `OPEN, HIGH, LOW, ADJ_CLOSE, CLOSE, VOLUME` and
an optional `offset` value where negative numbers allows you to get the 
reference point from previous days. By defauly it will get the current day with 
the offset of `0`.

### Indicators

Indicators will use their standard abbreviation to call. Some will require a 
desired `type`, `period` and `offset`. The following indicators have been made
and currently work in the system:

- `SMA(type, period, offset = 0)` eg. `SMA(CLOSE, 200)`
- `EMA(type, period, offset = 0)` eg. `EMA(CLOSE, 200)`
- `MACD(type, offset = 0)` eg. `MACD(CLOSE)`
- `RSI(type, period = 14, offset = 0)` eg. `RSI(CLOSE)`
- `ATR(period, offset = 0` eg. `ATR(14)`
- `HHV(period, offset = 0` eg. `HHV(14)`
- `LLV(period, offset = 0` eg. `LLV(14)`

### Back Testing Report
> TODO

**Done:**
- Initial Capital
- Ending Capital
- Net Profit
- Total Trades

**Requirements:**
- Net Profit %
- Exposure %
- Net Risk Adjusted Return %
- Annual Return %
- Risk Adjusted Return %
- Total Transaction Costs (Commision on trade)
- Avg. Profit/Loss
- Avg. Profit/Loss %
- Avg. Held Time
- Avg. Profit
