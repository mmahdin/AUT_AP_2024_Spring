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

class LoggerMinimax {
public:
    LoggerMinimax(const std::string& filename) {
        file.open(filename, std::ios::out | std::ios::app);  // Open file in append mode
        if (!file.is_open()) {
            throw std::ios_base::failure("Failed to open log file");
        }
    }

    ~LoggerMinimax() {
        if (file.is_open()) {
            file.close();
        }
    }

    template<typename T>
    LoggerMinimax& operator<<(const T& value) {
        if (file.is_open()) {
            file << value;
        }
        return *this;
    }

    // To support std::endl and other manipulators
    LoggerMinimax& operator<<(std::ostream& (*manip)(std::ostream&)) {
        if (file.is_open()) {
            manip(file);
        }
        return *this;
    }
    LoggerMinimax& operator=(const LoggerMinimax& other) {
        if (this == &other) {
            return *this; // Self-assignment, no work needed
        }
        if (file.is_open()) {
            file.close();
        }
        filename = other.filename;
        file.open(filename, std::ios::out | std::ios::app);  // Open file in append mode
        if (!file.is_open()) {
            throw std::ios_base::failure("Failed to open log file");
        }
        return *this;
    }
private:
    std::string filename;
    std::ofstream file;
};

#endif // LOGGER_H
