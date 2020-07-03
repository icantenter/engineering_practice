#pragma once
#include <fstream>
#include <algorithm>
#include <cstring>
#include "error.h"

enum
{
    ACCORDING_ALPHA,
    ACCORDING_HIGHEST_SCORE,

};

const int NOT_FIND = -1;
const int DATA_BEGIN = 0;

typedef struct
{
    char password[30];
    char name[30];
} ACCOUNT;

typedef struct Player
{
    ACCOUNT account;
    int number;
    int time;
    int high_score = 0;
    Player *next;

} PLAYER;

class DataBase
{
private:
    PLAYER *head = NULL;
    int data_size = 0;

public:
    int get_highest_score();
    int get_data_size();
    void push_back(ACCOUNT *new_account);
    void kill(int index);
    int find(const std::string &search_name, int index);
    PLAYER* get_player(int index);
    bool append_from_file(const std::string &append_path);
    void save(const std::string &save_path);
    PLAYER* sort(int sort_type, bool descending_order);
    DataBase();
    ~DataBase();
};
