#ifndef IZANAMI_PARSER_STRUCTURE_H
#define IZANAMI_PARSER_STRUCTURE_H

struct date_entity {
    union {
        int stamp;
        struct {
            unsigned char day, month;
            unsigned short year;
        } data;
    };
};

struct training_data_entity {
    unsigned char t_invalid;
    struct date_entity t_date;
    double t_open, t_high, t_low, t_close, t_adj_close;
    signed int t_volume;
};

#endif /* IZANAMI_PARSER_STRUCTURE_H */