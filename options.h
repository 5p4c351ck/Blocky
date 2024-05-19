#ifndef OPTIONS_H
#define OPTIONS_H

struct user_options {
    bool fn;
    char filename[20];
    bool sn;
    char snapname[20];
    bool rn;
    char rule[20];
};


void userOptions(int argc, char* argv[], struct user_options* uo);
#endif