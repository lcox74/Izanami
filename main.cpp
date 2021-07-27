#include "src/Izanami.hpp"

class myStrategy : public Izanami_Client {
public:
    myStrategy(float initial, u8 shares) : Izanami_Client(initial, shares) {}

    bool buy_trigger() override {
        bool rule1 = ref(CLOSE) <= LLV(7, -1);
        bool rule2 = ref(CLOSE) > SMA(CLOSE, 200);

        // Set Stop Loss (Only applies if actually buys)
        set_stop_loss(ref(CLOSE) - (2 * ATR(20)));

        return rule1 && rule2;
    }
    bool sell_trigger() override {
       bool rule1 = ref(CLOSE) >= HHV(7, -1);
        
        return rule1;
    }
};

int main(int argc, char *argv[]) {
    auto strat = myStrategy(100.0f, 10);

    strat.load_history("./training_data/GOOG.csv");
    strat.backtest();
    strat.backtest_report();

    return 0;
}