#include "Logger.h"

Logger::Logger(const std::string& filename) {
    std::remove(filename.c_str());
    logfile.open(filename, std::ios::out | std::ios::app);
    if (!logfile.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

Logger::~Logger() {
    if (logfile.is_open()) {
        logfile.close();
    }
}

void Logger::log(const std::string& message, LogLevel level) {
    if (logfile.is_open()) {
        logfile << getLabel(level) << ": " << message << std::endl;
    }
}

void Logger::debug(const std::string& message) {
    log(message, DEBUG);
}

void Logger::error(const std::string& message) {
    log(message, ERROR);
}

std::string Logger::getLabel(LogLevel level) {
    switch (level) {
        case INFO: return "INFO";
        case DEBUG: return "DEBUG";
        case ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}
