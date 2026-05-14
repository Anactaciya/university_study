#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <mutex>
#include <iostream>

enum LogLevel {
    LOG_NORMAL = 0,
    LOG_WARNING = 1,
    LOG_ERROR = 2
};

struct LogEvent {
    std::time_t timestamp;
    LogLevel level;
    std::string message;
    
    LogEvent(LogLevel lvl, const std::string& msg) 
        : timestamp(std::time(nullptr)), level(lvl), message(msg) {}
    
    std::string levelToString() const {
        switch(level) {
            case LOG_NORMAL:  return " NORMAL  ";
            case LOG_WARNING: return " WARNING ";
            case LOG_ERROR:   return " ERROR   ";
            default: return "UNKNOWN";
        }
    }
    
    std::string toString() const {
        std::stringstream ss;
        ss << "[" << std::put_time(std::localtime(&timestamp), "%Y-%m-%d %H:%M:%S")
           << "] [" << levelToString() << "] " << message;
        return ss.str();
    }
};

class Log {
private:
    static Log* instance_;
    static std::mutex mutex_;
    
    std::vector<LogEvent> events_;
    static const size_t MAX_EVENTS = 10;
    
    // Приватный конструктор (Singleton)
    Log() {}
    
    // Запрещаем копирование и присваивание
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;
    
public:
    // Получить единственный экземпляр
    static Log* Instance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance_ == nullptr) {
            instance_ = new Log();
        }
        return instance_;
    }
    
    // Зафиксировать событие
    void message(LogLevel level, const std::string& msg) {
        std::lock_guard<std::mutex> lock(mutex_);
        
        events_.emplace_back(level, msg);
        
        if (events_.size() > MAX_EVENTS) {
            events_.erase(events_.begin());
        }
    }
    
    void print() {
        std::lock_guard<std::mutex> lock(mutex_);
        
        std::cout << "\nLast " << events_.size() << " events: \n" << std::endl;
        
        for (const auto& event : events_) {
            std::cout << event.toString() << std::endl;
        }
    }
    
    size_t getEventCount() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return events_.size();
    }


    ~Log() {
        // Ничего не делаем, т.к. instance_ удаляется отдельно
    }
};

// Инициализация статических членов
Log* Log::instance_ = nullptr;
std::mutex Log::mutex_;

#endif // LOG_H_