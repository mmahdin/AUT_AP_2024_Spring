#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>

class Logger {
public:
    enum LogLevel { INFO, DEBUG, ERROR };

    Logger(const std::string& filename);
    ~Logger();

    void log(const std::string& message, LogLevel level = INFO);
    void debug(const std::string& message);
    void error(const std::string& message);

private:
    std::ofstream logfile;
    std::string getLabel(LogLevel level);
};

#endif // LOGGER_H
