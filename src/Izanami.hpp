#ifndef IZANAMI_H_
#define IZANAMI_H_

#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;
typedef unsigned long   u64;

struct date_iz {
    union {
        u64 stamp;
        struct {
            u8 day, month;
            u16 year;
        };
    };
};

enum PRICE_TYPE {
    OPEN, CLOSE,
    HIGH, LOW,
    ADJ_CLOSE, VOLUME
};

struct trade_log_entry {
    date_iz buy_date, sell_date;
    float buy_price, sell_price;
    float gain;
    int days_dif;
};

struct OHLCV_d {
    date_iz date;
    float open, high, low, close, adj_close;
    int volume;
};

class Izanami_Client {
public:
    Izanami_Client(float initial_capital, u8 shares_per_trade) {
        this->initial_capital = initial_capital;
        this->current_capital = initial_capital;
        this->shares_per_trade = shares_per_trade;
        this->current_index = 0;
    }

    virtual bool buy_trigger() = 0;
    virtual bool sell_trigger() = 0;

    void load_history(const char* csv_file) {
        printf("File %s\n", csv_file);
        std::ifstream data_file(csv_file);

        if (data_file.is_open()) {
            std::string entry;

            unsigned int row = 0;
            OHLCV_d entry_data;
            date_iz d;
            float o, h, l, ac, c;
            int v; 
            
            while(std::getline(data_file, entry)) {
                if (!(row++)) continue;

                sscanf(entry.c_str(), "%hu-%hhu-%hhu,%f,%f,%f,%f,%f,%d\n", 
                    &entry_data.date.year, 
                    &entry_data.date.month, 
                    &entry_data.date.day, 
                    &entry_data.open, &entry_data.high, &entry_data.low,
                    &entry_data.adj_close, &entry_data.close, 
                    &entry_data.volume);
                
                // printf("%f %f %f %f %f %d\n", entry_data.open, entry_data.high, entry_data.low, entry_data.adj_close, entry_data.close, entry_data.volume);
                this->data.push_back(entry_data);
            }
            data_file.close();
            printf("Created Share Data, %d entries\n", row - 1);
        } else {
            printf("Failed to Open %s\n", csv_file);
        }
    }

    void update() {
        if (this->mark_buy) {
            this->mark_buy = false;
            this->buy_share();
            this->days_since_buy = 0;
        }

        if (this->mark_sell) {
            this->mark_sell = false;
            this->sell_share();
        }

        if (this->buy_trigger() && !this->holding_positon) {
            // Mark for Buy Stock
            this->mark_buy = true;
        }

        if ((this->sell_trigger() || this->stop_loss >= ref(CLOSE)) && this->holding_positon) {
            // Mark for Sell Stock
            this->mark_sell = true;

            // Pop Position and Stop Loss
            this->stop_loss = 0.0f;
        }

        this->current_index++;
        this->days_since_buy++;
    }

    void buy_share() { 
        this->current_capital -= (this->shares_per_trade * ref(OPEN));
        this->bought_price = ref(OPEN);
        this->holding_positon = true;

        trade_log_entry entry;
        entry.buy_date = this->get_date();
        entry.buy_price = ref(OPEN);
        this->logs.push_back(entry);

        printf("=========================== Trade (%d) ===========================\n", this->logs.size());
        printf("Buying (%d) at Open (%f) -> %f\n", this->shares_per_trade, bought_price, bought_price * this->shares_per_trade);
    }

    void sell_share() { 
        this->current_capital += (this->shares_per_trade * ref(OPEN));
        this->holding_positon = false;

        float gain = (ref(OPEN) - this->bought_price) / this->bought_price;
        
        trade_log_entry entry = this->logs.back();
        entry.sell_date = this->get_date();
        entry.sell_price = ref(OPEN);
        entry.gain = gain;
        entry.days_dif = this->days_since_buy;
        this->logs.pop_back();
        this->logs.push_back(entry);
    
        printf("Selling (%d) at Open (%f) -> %f\n", this->shares_per_trade, ref(OPEN), ref(OPEN) * this->shares_per_trade);
        printf("Held for (%d) days\n", this->days_since_buy);
        printf("Total Capital $%.2f\n\n", this->current_capital);
    }

    void set_stop_loss(float val) { this->stop_loss = val; }

    void backtest() {
        this->current_index = 0;
        for (u64 x = 0; x < data.size(); ++x) {
            this->update();
        }
    }

    void backtest(u64 start, u64 period) {
        this->current_index = start;
        for (u64 x = 0; (x < period && this->current_index < data.size()); ++x) {
            this->update();
        }
    }

    void backtest_report() {
        printf("===========================  RESULT  ===========================\n");
        printf("Initial Capital $%.2f\n", this->initial_capital);
        printf("Total Capital $%.2f\n", this->current_capital);
        printf("Net Profit $%.2f\n", this->current_capital - this->initial_capital);
        printf("Number of Trades %d\n", this->logs.size());
    }

    float ref(PRICE_TYPE type, int offset = 0) {
        return this->ref(type, this->current_index, offset); 
    }

    float ref(PRICE_TYPE type, int index, int offset) {
        u64 i = index + offset;

        if (i < 0 || i > this->data.size()) return 0.0f;
        switch (type)
        {
        case OPEN:            return this->data[i].open;
        case CLOSE:           return this->data[i].close;
        case ADJ_CLOSE:       return this->data[i].adj_close;
        case HIGH:            return this->data[i].high;
        case LOW:             return this->data[i].low;
        case VOLUME:          return (float)data[i].volume;
        }
        return 0.0f;
    }

public:
    float SMA(PRICE_TYPE type, u16 period, int offset = 0);
    float EMA(PRICE_TYPE type, u16 period, int offset = 0);
    float MACD(PRICE_TYPE type, int offset = 0);
    float RSI(PRICE_TYPE type, u16 period = 14, int offset = 0);
    float ATR(u16 period, int offset = 0);
    float HHV(u16 period, int offset = 0);
    float LLV(u16 period, int offset = 0);

protected:

    date_iz get_date() { return this->data[this->current_index].date; }

    float initial_capital, current_capital;
    u64 current_index;

    u8 shares_per_trade = 10;

    float bought_price = 0.0f;
    int days_since_buy = 0;
    float stop_loss = 0.0f;
    bool holding_positon = false;

    bool mark_buy = false;
    bool mark_sell = false;

    std::vector<OHLCV_d> data;
    std::vector<trade_log_entry> logs;
};


float Izanami_Client::SMA(PRICE_TYPE type, u16 period, int offset) {
    u64 index = this->current_index - offset;
    if (index < period || offset > 0 || period == 0) return 0.0f;

    float sum = 0.0f;
    for (u64 x = (index - period); x < index; ++x) {
        sum += ref(type, x, 0);
    }

    return sum / period;
}

float Izanami_Client::EMA(PRICE_TYPE type, u16 period, int offset) {
    u64 index = this->current_index - offset;
    if (index < period || offset > 0 || period == 0) return 0.0f;

    // Calculate Initial EMA
    float sum = 0.0f;
    for (u64 x = 0; x < period; ++x) {
        sum += ref(type, x);
    }
    float ema = sum / period;
    if (index == period) return ema;

    // Calculate Remaining EMA
    const float smoothing = 2.0f;
    for (u64 x = period; x < index; ++x) {
        ema = (ref(type, x, 0) * (smoothing / (1 + period))) + 
              (ema * (1 - (smoothing / (1 + period))));
    }

    return ema;
}

float Izanami_Client::MACD(PRICE_TYPE type, int offset) {
    u64 index = this->current_index - offset;
    if (index < 26) return 0.0f;

    return EMA(type, 12, offset) - EMA(type, 26, offset);
}

float Izanami_Client::RSI(PRICE_TYPE type, u16 period, int offset) {
    u64 index = this->current_index - offset;
    if (index < period || offset > 0 || period == 0) return 0.0f;

    float sumUp = 0.0f, sumDown = 0.0f;
    for (u64 x = (index - period); x < index; ++x) {
        // Calculate RS
        sumUp += std::max(0.0f, ref(type, x, 0) - ref(type, x, -1));
        sumDown += std::max(0.0f, ref(type, x, -1)  - ref(type, x, 0));
    }
    float RS = (sumUp / (float)period) / (sumDown / (float)period);

    // Calculate Index
    return 100 - (100 / (1 + RS));
}

float Izanami_Client::ATR(u16 period, int offset) {
    u64 index = this->current_index - offset;
    if (index < period || offset > 0 || period == 0) return 0.0f;

    double sum = 0.0f;
    for (u16 x = 0; x < period; ++x) {
        if (index - x <= 0) continue;

        // Calculate TR
        sum += std::max(ref(HIGH, index, (-x)) - ref(LOW, index, (-x)), 
               std::max(ref(LOW, index, (-x)) - ref(CLOSE, index, (-x) - 1), 
                        ref(HIGH, index, (-x)) - ref(CLOSE, index, (-x) - 1)));
    }

    // Average TR over period
    return sum / period;
}

float Izanami_Client::HHV(u16 period, int offset) {
    u64 index = this->current_index - offset;
    if (index < 0 || offset > 0 || period == 0) return 0.0f;

    float val = 0.0f;
    for (u64 x = std::max(0, ((int)index - (int)period)); x < index; ++x)
        val = std::max(val, ref(HIGH, x, 0));
    
    return val;
}

float Izanami_Client::LLV(u16 period, int offset) {
    u64 index = this->current_index - offset;
    if (index < 0 || offset > 0 || period == 0) return 0.0f;

    float val = std::numeric_limits<float>::max();
    for (u64 x = std::max(0, ((int)index - (int)period)); x < index; ++x) 
        val = std::min(val, ref(LOW, x, 0));

    return val;
}


#endif /* IZANAMI_H_ */