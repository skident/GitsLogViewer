#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include <regex>

#include <QList>
#include "LogLine.h"

class LogParser
{
public:
    static QList<LogLine> parse(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Couldn't open a log file");
        }

        QList<LogLine> logs;

        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty())
            {
                continue;
            }

            logs << parseLine(line);
        }

        return logs;
    }

private:
    static LogLine parseLine(const std::string& line)
    {
        std::string raw_regex = R"(\[(\d{4}\-\d{2}\-\d{2} \d{2}:\d{2}:\d{2}\.\d{3})\] \[(0x[\dabcdef]{1,})\] \[(DEBUG|ERROR|WARNING|INFO)\] (.*))";
        std::regex re(raw_regex);
        std::smatch match;

        if (std::regex_search(line, match, re))
        {
            if (match.size() >= 4)
            {
                return LogLine(match.str(1).c_str(), match.str(2).c_str(),
                               match.str(3).c_str(), match.str(4).c_str());
            }
        }
        return {};
    }
};
