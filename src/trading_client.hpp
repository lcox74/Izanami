#ifndef IZANAMI_TRADING_CLIENT_H_
#define IZANAMI_TRADING_CLIENT_H_

#include "share_data.hpp"

struct trade_log_entry {
    date_d buy_date, sell_date;
    double buy_price, sell_price;
    int number_shares;
    double gain;
};

class trading_client {
public:
    trading_client(float initial_money) {
        this->initial_money_pool = initial_money;
        this->money_pool = initial_money;
    }

    int buy_shares(date_d date, double bought_price, int num_shares) {
        if (this->money_pool > (bought_price * num_shares) && !this->holding_shares) {

            /* Amend Money Pool */
            this->money_pool -= (bought_price * num_shares);
            this->bought_price = bought_price;
            this->num_bought_shares = num_shares;
            this->holding_shares = true;

            /* Log Trade Data */
            trade_log_entry entry;
            entry.buy_date = date;
            entry.buy_price = bought_price;
            entry.number_shares = num_shares;
            this->log.push_back(entry);
            this->money_pool_alteratons.push_back(std::make_pair(date, this->money_pool));

            printf("=========================== Trade (%d) ===========================\n", this->log.size());
            printf("Buying (%d) at (%lf): %lf\n", num_shares, bought_price, bought_price * num_shares);

            return 0;
        }
        return 1;
    }

    int sell_shares(date_d date, double sell_price) {
        if (this->holding_shares) {

            /* Calculate Gain/Loss Rate */
            double gain = (sell_price - this->bought_price) / this->bought_price;
            printf("Selling (%d) at (%lf) for a %.2f%% gain: %lf\n", this->num_bought_shares, sell_price, gain * 100, sell_price * this->num_bought_shares);
            
            /* Amend Money Pool */
            this->money_pool += (sell_price * this->num_bought_shares);
            this->holding_shares = false;

            /* Log Trade Data */
            trade_log_entry entry = this->log.back();
            entry.sell_date = date;
            entry.sell_price = sell_price;
            entry.gain = gain;
            this->log.pop_back();
            this->log.push_back(entry);
            this->money_pool_alteratons.push_back(std::make_pair(date, this->money_pool));

            printf("Money Pool $%.2lf\n\n", this->money_pool);

            return 0;
        }
        return 1;
    }

    void set_stop_loss_size(double size) {
        if (this->holding_shares) {
            this->stoploss = bought_price - size;
        } else {
            this->stoploss = 0.0;
        }
    }
    double get_stop_loss() { return this->stoploss; }
    std::vector<trade_log_entry> get_logs() { return this->log; }

    bool currently_bought() { return this->holding_shares; }

    float money_pool;

private:
    double stoploss = 0.0;
    float initial_money_pool;
    double bought_price = 0.0;
    int num_bought_shares = 0;
    bool holding_shares = false;

    std::vector<trade_log_entry> log;
    std::vector<std::pair<date_d, float>> money_pool_alteratons;
};


#endif /* IZANAMI_TRADING_CLIENT_H_ */