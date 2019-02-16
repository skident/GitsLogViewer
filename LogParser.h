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
    QList<LogLine> parse(const std::string& filename)
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

            LogLine logLine = parseLine(line);
            if (!logLine.m_line.empty())
            {
                logs << logLine;
            }
        }

        return logs;
    }

    void setRegex(const std::string& rawRegex)
    {
        m_rawRegex = rawRegex;
    }

private:
    LogLine parseLine(const std::string& line)
    {
        std::regex re(m_rawRegex);
        std::smatch match;

        if (std::regex_search(line, match, re))
        {
            LogLine line;
            for (size_t i = 1; i < match.size(); i++)
            {
                line.m_line << match.str(i).c_str();
            }
            return line;
        }
        return {};
    }

private:
    std::string m_rawRegex = R"(\[(\d{4}\-\d{2}\-\d{2} \d{2}:\d{2}:\d{2}\.\d{3})\] \[(0x[\dabcdef]{1,})\] \[(DEBUG|ERROR|WARNING|INFO)\] (.*))";
};
