#pragma once

#include "List.hpp"

#include <string>
#include <fstream>
#include <queue>
#include <cmath>

const std::string INPUTFILE = "../inlet.in";
const std::string OUTPUTFILE = "../outlet.out";

void read(List& lst)
{
    std::ifstream file(INPUTFILE);
    if (!file.is_open()) return;

    lst.clear();
    std::string line;
    std::priority_queue<std::pair<int, int>, 
        std::vector<std::pair<int, int>>, 
        std::greater<std::pair<int, int>>> 
    rands; // очередь с приоритетом наименьшему значению

    for (int i = 0; i < 1'000'000 && std::getline(file, line); i++)
    {
        if (line.empty()) continue;

        size_t sep_pos = line.rfind(';');

        std::string data;
        if (sep_pos > 1000) data = line.substr(0, 1000);
        else data = line.substr(0, sep_pos);

        int rand_index;
        try {
            rand_index = std::stoi(line.substr(sep_pos + 1));
        } catch (const std::exception& e) { continue; }
        if (rand_index > 1'000'000) rand_index = -1;

        if (rand_index <= (int)lst.size()) lst.push_back(std::move(data), rand_index);
        else
        {
            lst.push_back(std::move(data));
            rands.push(std::pair(i, rand_index));
        }

        if (!rands.empty() && i == rands.top().second) {
            lst.add_rand(rands.top().first, rands.top().second);
            rands.pop();
        }
    }
}

void write(const List& lst)
{
    std::ofstream file(OUTPUTFILE);
    if (!file.is_open()) return;

    int i = 0;
    for (auto it = lst.begin(); it != lst.end(); ++it, ++i)
    {
        file << "- Node " << i << ": \""
             << *it << "\" -> rand ";

        int rand_index = lst.get_rand_index(it);
        if (rand_index != -1) {
            file << "on node " << rand_index << '\n';
        } else {
            file << "= nullptr\n";
        }
    }
}
