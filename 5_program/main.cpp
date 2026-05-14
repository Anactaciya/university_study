#include "log.h"
#include <iostream>

int main() {
    Log* log = Log::Instance();
    
    log->message(LOG_NORMAL, "program loaded");
    log->message(LOG_NORMAL, "initializing components");
    log->message(LOG_WARNING, "low memory warning");
    log->message(LOG_NORMAL, "user logged in");
    log->message(LOG_NORMAL, "processing data");
    log->message(LOG_WARNING, "high CPU usage detected");
    

    for (int i = 1; i <= 5; ++i) {
        log->message(LOG_NORMAL, "iteration " + std::to_string(i));
    }
    
    log->message(LOG_ERROR, "another error!");
    log->message(LOG_ERROR, "system malfunction detected");
    
    log->print();
    
    Log* same_log = Log::Instance();
    std::cout << "\n" << (log == same_log ? "log == same_log" : "log != same_log") << std::endl;
    std::cout << "Total events stored: " << same_log->getEventCount() << std::endl;
    
    return 0;
}