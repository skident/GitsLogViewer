#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include <regex>

class LogParser
{
public:
    static void parse(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Couldn't open a log file");
        }

        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty())
            {
                continue;
            }

            parseLine(line);
        }
    }

private:
    static void parseLine(const std::string& line)
    {
        std::string raw_regex = R"(\[(\d{4}\-\d{2}\-\d{2} \d{2}:\d{2}:\d{2}\.\d{3})\] \[(0x[\dabcdef]{1,})\] \[(DEBUG|ERROR|WARNING|INFO)\] (.*))";
        std::regex re(raw_regex);
        std::smatch match;

        if (std::regex_search(line, match, re))
        {
            if (match.size() < 4)
            {
                return;
            }

            std::cout << match.str(1) << " | " << match.str(2) << " | " << match.str(3) << " | " << match.str(4) <<  std::endl;

        }

    }
};
