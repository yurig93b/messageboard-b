//
// Created by Yuri Grigorian on 24/03/2021.
//

#ifndef MESSAGEBOARD_A_BOARD_HPP
#define MESSAGEBOARD_A_BOARD_HPP

#include <iostream>
#include "Direction.hpp"
#include <unordered_map>
#include <string>
#include <iomanip>
#include <memory>

typedef std::unordered_map<unsigned int, std::shared_ptr<char>> col_dict;
typedef std::unordered_map<unsigned int, std::shared_ptr<col_dict>> row_col_dict;

namespace ariel{

    class Board{
        row_col_dict msgs;

        unsigned int min_row;
        unsigned int max_row;
        unsigned int min_column;
        unsigned int max_column;
        bool has_data;
        std::string CHAR_EMPTY;

        static void validate(const unsigned int &row, const unsigned int &column, const Direction &dir, const std::string &msg);

        public:
            Board();
            ~Board();
            void set_empty_char(std::string);
            void post(const unsigned int &row, const unsigned int &column,const Direction &dir, const std::string &msg);
            std::string read(const unsigned int &row,  const unsigned int &column, const Direction &dir, const unsigned int &len);
            void show();
    };
}

#endif //MESSAGEBOARD_A_BOARD_HPP
