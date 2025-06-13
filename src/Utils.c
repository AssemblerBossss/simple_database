#include "../include/Utils.h"

void print_prompt(){
    printf("db > ");
};

void print_row(Row *row) {
    printf("(%d, %s, %s) \n", row->id, row->username, row->email);
}