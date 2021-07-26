#ifndef IZANAMI_SHARE_DATA_H_
#define IZANAMI_SHARE_DATA_H_

#include <vector>
#include <fstream>
#include <string>
#include <cstdio>

struct date_d {
    union {
        int stamp;
        struct {
            unsigned char day, month;
            unsigned short year;
        };
    };
};

struct OHLCV_d {
    date_d date;
    double Open, High, Low, Close, Adj_Close;
    int Volume;
};

class share_data {
public:
    share_data(const char* csv_file) {
        printf("File %s\n", csv_file);
        std::ifstream data_file;
        data_file.open(csv_file);

        if (data_file.is_open()) {
            std::string entry;

            unsigned int row = 0;
            OHLCV_d entry_data;
            
            while(getline(data_file, entry)) {
                if (!(row++)) continue;

                sscanf(entry.c_str(), "%hu-%hhu-%hhu,%lf,%lf,%lf,%lf,%lf,%d\n", 
                    &entry_data.date.year, 
                    &entry_data.date.month, 
                    &entry_data.date.day, 
                    &entry_data.Open, &entry_data.High, &entry_data.Low,
                    &entry_data.Adj_Close, &entry_data.Close, 
                    &entry_data.Volume);
                
                this->add_day(entry_data);
            }
            data_file.close();
            printf("Created Share Data, %d entries\n", row - 1);
        } else {
            printf("Failed to Open %s\n", csv_file);
        }
    }

    void add_day(OHLCV_d d) {
        this->data.push_back(d);
    }

    std::vector<OHLCV_d> get_data() { return this->data; }

private:
    std::vector<OHLCV_d> data;
};

/* Calculations (Indicators) */

double SMA(share_data data, unsigned int index, unsigned int period) {
    if (index < period || period == 0 || index <= 0) return 0.0;
    auto d = data.get_data();
    double sum = 0.0;
    for (unsigned int x = 0; x < period; ++x) {
        sum += d[index - x].Close;
    }

    return sum / period;
}

double LLV(share_data data, int index, unsigned int period) {
    if (period == 0 || index <= 0) return 0.0;

    auto d = data.get_data();
    double val = 1000000.0;
    if (index < period) {
        for (unsigned int x = 0; x < period; ++x) {
            val = std::min(val, d[x].Low);
        }
    } else {
        for (unsigned int x = 0; x < period; ++x) {
            val = std::min(val, d[index - x].Low);
        }
    }
    return val;
}

double HHV(share_data data, int index, unsigned int period) {
    if (period == 0 || index <= 0) return 0.0;

    auto d = data.get_data();
    double val = -100000000.0;
    if (index < period) {
        for (unsigned int x = 0; x < period; ++x) {
            val = std::max(val, d[x].High);
        }
    } else {
        for (unsigned int x = 0; x < period; ++x) {
            val = std::max(val, d[index - x].High);
        }
    }
    return val;
}

double TR(share_data data, int index) {
    if (index <= 0) return 0.0;

    auto d = data.get_data();
    return std::max(d[index].High - d[index].Low, std::max(d[index].Low - d[index - 1].Close, d[index].High - d[index - 1].Close));
}


double ATR(share_data data, int index, unsigned int period) {
    if (index < period || index <= 0) return 0.0;

    double sum = 0.0;
    for (unsigned int x = 0; x < period; ++x) {
        sum += TR(data, index - x);
    }

    return sum / period;
}

#endif /* IZANAMI_SHARE_DATA_H_ */