#include "src/trading_client.hpp"

auto client = trading_client(100);
auto data = share_data("./training_data/AMP.AX.csv");
const int num_shares = 10;

void trading_strategy(OHLCV_d day_data, int index) {
    double sevendlow = LLV(data, index - 1, 7);
    double sevendhigh = HHV(data, index - 1, 7);
    double sma200 = SMA(data, index, 200);

    /* Entry Rules */
    if (day_data.Close <= sevendlow && day_data.Close > sma200 && !client.currently_bought()) { 
        client.buy_shares(day_data.date, day_data.Close, num_shares);
        client.set_stop_loss_size(2 * ATR(data, index, 20));
    }

    /* Exit Rules */
    if (day_data.Close >= sevendhigh || day_data.Close < client.get_stop_loss()) {
        client.sell_shares(day_data.date, day_data.Close);
    }
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < data.get_data().size(); ++i) {
        trading_strategy(data.get_data()[i], i);
    }

    printf("===========================  FINAL  ===========================\n");
    printf("Money Pool $%.2f\n", client.money_pool);
    printf("Number of Trades %d\n", client.get_logs().size());

    return 0;
}