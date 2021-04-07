//
// Created by Yuri Grigorian on 06/04/2021.
//

#include "Board.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace ariel;

#define X 30
#define Y 30
#define CLEAR " "
#define SLEEP_IMG 3
#define USLEEP_LINES 50000


std::istringstream cat("                                               .--.\n"
                       "                                               `.  \\\n"
                       "                                                 \\  \\\n"
                       "                                                  .  \\\n"
                       "                                                  :   .\n"
                       "                                                  |    .\n"
                       "                                                  |    :\n"
                       "                                                  |    |\n"
                       "  ..._  ___                                       |    |\n"
                       " `.\"\".`''''\"\"--..___                              |    |\n"
                       " ,-\\  \\             \"\"-...__         _____________/    |\n"
                       " / ` \" '                    `\"\"\"\"\"\"\"\"                  .\n"
                       " \\                                                      L\n"
                       " (>                                                      \\\n"
                       "/                                                         \\\n"
                       "\\_    ___..---.                                            L\n"
                       "  `--'         '.                                           \\\n"
                       "                 .                                           \\_\n"
                       "                _/`.                                           `.._\n"
                       "             .'     -.                                             `.\n"
                       "            /     __.-Y     /''''''-...___,...--------.._            |\n"
                       "           /   _.\"    |    /                ' .      \\   '---..._    |\n"
                       "          /   /      /    /                _,. '    ,/           |   |\n"
                       "          \\_,'     _.'   /              /''     _,-'            _|   |\n"
                       "                  '     /               `-----''               /     |\n"
                       "                  `...-'     dp                                `...-'");

std::istringstream puma("            /)\n"
                        "           //\n"
                        "          //\n"
                        "         ((\n"
                        "          \\\\\n"
                        "           ))\n"
                        "          //\n"
                        "      _,-'\"._\n"
                        "     /_  ,   \\\n"
                        "     |   '   /\n"
                        "     \\)    ,\\'\n"
                        "     '|      \\\n"
                        "     /   |   )\n"
                        "    /_   ,  /\n"
                        "   /  _  % (\n"
                        "   ) /    ' \\\n"
                        "  /        \\_)\n"
                        "  ),    )_   \\_  ,\n"
                        " _/    _/%     \\/)\n"
                        "('  __/ \\ ___    \\,\n"
                        " \\   (   `\"-  __  /\n"
                        "  '\\  \\   ((   >  \\\n"
                        "    )  \\   '-.-,_='~~~  ~\n"
                        "   ('  /         ' ~~ ~  ~~ ~~ b'ger\n"
                        "   \" \"\"");

static Board b;

void clear_board() {
    for (unsigned int x = 0; x < X; ++x) {
        for (unsigned int y = 0; y < Y; ++y) {
            b.post(x, y, Direction::Horizontal, CLEAR);
        }
    }
}

void clear_screen() {
    for (int y = 0; y <= Y * 100; ++y) {
        std::cout << std::endl;
    }
}

int main() {
    std::string line;

    unsigned int row = 0;
    while (std::getline(puma, line)) {
        clear_screen();

        b.post(row, 0, Direction::Horizontal, line);
        ++row;
        b.show();
        usleep(USLEEP_LINES);

    }
    sleep(SLEEP_IMG);

    row = 0;
    while (std::getline(cat, line)) {
        clear_screen();
        b.post(row, 0, Direction::Horizontal, line);
        ++row;
        b.show();
        usleep(USLEEP_LINES);
    }
}