#ifndef Logger_h
#define Logger_h

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <thread>
#include <mutex>

#include "Utils.h"

class TradingCompany;

class Logger
{
    friend class Director;
    
public:
    
    enum DebugLevel
    {
        DEBUG_LEVEL_DISABLED = 0,
        DEBUG_LEVEL_ERROR = 1,
        DEBUG_LEVEL_WARNING = 2,
        DEBUG_LEVEL_INFO = 3,
    };
    
    enum MessageType
    {
        MESSAGE_INFO = 1,
        MESSAGE_WARNING,
        MESSAGE_ERROR,
        MESSAGE_ALL
    };
    
    static void createInstance();
    static void deleteInstance();
    static void setDebugLevel(DebugLevel level);
    
    class Streamer : public std::ostream
    {
    public:
        Streamer(Logger::MessageType messageType);
        ~Streamer();
        
    private:
        class StringBuffer : public std::stringbuf
        {
        public:
            StringBuffer(Logger::MessageType messageType);
            ~StringBuffer();
            virtual int sync();
            
        private:
            Logger::MessageType messageType;
        };
    };
    
    static Streamer info;
    static Streamer warning;
    static Streamer error;
    
protected:
    Logger() {}
    Logger(const Logger&);
    Logger& operator=(Logger&);
    ~Logger() {}
    
private:
    static std::string infoBuffer_;
    static std::string warningBuffer_;
    static std::string errorBuffer_;
    static std::string allMessagesBuffer_;
    std::thread thread_;
    
    static DebugLevel debugLevel_;
    static Logger* logger_;
    static std::ofstream logFile_;
    
    void writeInfo(const std::string &message);
    void writeWarning(const std::string &message);
    void writeError(const std::string &message);
    static void writeToBuffer(const std::string &message, MessageType type);
    void writeToFile(const std::string &message);
    static void printInfo();
    static void printWarning();
    static void printError();
    static void printAllMessages();
    static void printLog(const TradingCompany *object);
};

#endif /* Logger_h */
