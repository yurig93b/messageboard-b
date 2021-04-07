//
// Created by Yuri Grigorian on 06/04/2021.
//

#include "Board.hpp"
#include "limits.h"
#include <iomanip>
#include <memory>
#include <iostream>
#include <memory>

using namespace ariel;

Board::Board() : min_row(0), max_row(0), min_column(0), max_column(0), has_data(false), CHAR_EMPTY("_") {}

Board::~Board() {
    this->msgs.clear();
}

void Board::set_empty_char(std::string empty) {
    this->CHAR_EMPTY = std::move(empty);
}

void
Board::validate(const unsigned int &row, const unsigned int &column, const Direction &dir, const std::string &msg) {
    if (msg.length()!= 0 && dir == Direction::Vertical && (row + msg.length() - 1 < row)) {
        throw std::out_of_range("Msg length overflow for column.");
    }
}

void Board::post(const unsigned int &row, const unsigned int &column, const Direction &dir, const std::string &msg) {
    Board::validate(row, column, dir, msg);

    unsigned int tracking = (dir == Direction::Horizontal) ? column : row;

    for (auto it = msg.cbegin(); it != msg.cend(); ++it) {
        unsigned int actual_row = dir == Direction::Horizontal ? row : tracking;
        unsigned int actual_column = dir == Direction::Vertical ? column : tracking;

        // Init row
        if (this->msgs.find(actual_row) == this->msgs.cend()) {
            this->msgs.insert(
                    {actual_row, std::make_shared < std::unordered_map < unsigned int, std::shared_ptr < char>>>()});
        }

        // Insert column
        this->msgs[actual_row].get()->operator[](actual_column) = std::make_shared<char>((char) *it);

        // Update board metadata
        this->min_row = (!this->has_data || actual_row < this->min_row) ? actual_row : this->min_row;
        this->max_row = (!this->has_data || actual_row > this->max_row) ? actual_row : this->max_row;
        this->min_column = (!this->has_data || actual_column < this->min_column) ? actual_column : this->min_column;
        this->max_column = (!this->has_data || actual_column > this->max_column) ? actual_column : this->max_column;

        this->has_data = true;
        ++tracking;
    }

}

std::string
Board::read(const unsigned int &row, const unsigned int &column, const Direction &dir, const unsigned int &len) {
    std::string result{};

    unsigned int tracking = (dir == Direction::Horizontal) ? column : row;
    unsigned int total_len = len + tracking;

    for (; tracking < total_len; ++tracking) {
        unsigned int actual_row = dir == Direction::Horizontal ? row : tracking;
        unsigned int actual_column = dir == Direction::Vertical ? column : tracking;

        // Find row
        row_col_dict::iterator obj_row = this->msgs.find(actual_row);
        if (obj_row == this->msgs.cend()) {
            result.append(this->CHAR_EMPTY);
            continue;
        }

        // Find col
        col_dict::iterator obj_col = obj_row->second->find(actual_column);
        if (obj_col == obj_row->second->cend()) {
            result.append(this->CHAR_EMPTY);
            continue;
        }

        result += *(obj_col->second.get());
    }

    return result;
}

void Board::show() {
    if(!this->has_data){
        return;
    }

    for(unsigned int row = this->min_row; row <= this->max_row ; ++row){
        row_col_dict::iterator it_row = this->msgs.find(row);

        if(it_row == this->msgs.cend()){
            continue;
        }

        for(unsigned int col = this->min_column; col <= this->max_column ; ++col){
            col_dict::iterator it_col = it_row->second->find(col);
            if(it_col == it_row->second->cend()){
                std::cout << this->CHAR_EMPTY;
            }
            else{
                std::cout << *(it_col->second);
            }
        }

        std::cout << std::endl;
    }
}