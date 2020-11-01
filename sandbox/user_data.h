#ifndef IZANAMI_USER_DATA_H
#define IZANAMI_USER_DATA_H

struct trade_data {
    int t_bought_date;                  /* Date Bought */
    int t_sold_date;                    /* Date Sold */

    double t_bought_price;              /* Bought Price */
    double t_sold_price;                /* Sold Price */
    double t_difference;                /* Pre-calc difference */
};

#define STARTING_POOL 100

struct bot_data {
    double b_pool;                      /* Money Pool */
    double b_fitness;                   /* The Bot's Performance Score */
    
    struct trade_data b_current;        /* Current Trade */
    struct trade_data *b_trades;        /* Historic Trades */
    int b_total;                        /* Total Trades */
};

int initialise_bot_data (struct bot_data *);
int delete_bot_data (struct bot_data *);
int buy_share (struct bot_data *, int, int);
int sell_share (struct bot_data *, int, int);

/* export trade data to csv */

#endif /* IZANAMI_USER_DATA_H */