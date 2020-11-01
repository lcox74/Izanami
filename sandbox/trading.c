#include <stdlib.h>

#include "user_data.h"

int initialise_bot_data (struct bot_data *bot)
{
    bot->b_trades = (struct trade_data *) calloc(1, sizeof(struct trade_data));
    bot->b_pool = STARTING_POOL;
    return 0;
}

int delete_bot_data (struct bot_data *bot)
{
    free (bot->b_trades);
    return 0;
}

int buy_share (struct bot_data *bot, int date, int price) 
{
    bot->b_trades = (struct trade_data*) realloc(bot->b_trades, 
        sizeof(struct trade_data) * (++bot->b_total));

    bot->b_current.t_bought_date = date;
    bot->b_current.t_bought_price = price;
    bot->b_pool -= price;

    return (bot->b_pool < 0) ? 1 : 0;
}

int sell_share (struct bot_data *bot, int date, int price)
{
    bot->b_current.t_sold_date = date;
    bot->b_current.t_sold_price = price;
    bot->b_current.t_difference = price - bot->b_current.t_bought_price;

    bot->b_trades[bot->b_total] = bot->b_current;

    return 0;
}