#ifndef Logger_h
#define Logger_h

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <thread>
#include <mutex>

using namespace std;

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
    
    class Streamer : public ostream
    {
    public:
        Streamer(Logger::MessageType messageType);
        ~Streamer();
        
    private:
        class StringBuffer : public stringbuf
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
    static string infoBuffer_;
    static string warningBuffer_;
    static string errorBuffer_;
    static string allMessagesBuffer_;
    thread thread_;
    mutex mutex_;
    
    static DebugLevel debugLevel_;
    static Logger* logger_;
    static ofstream logFile_;
    
    void writeInfo(const string &message);
    void writeWarning(const string &message);
    void writeError(const string &message);
    static void writeToBuffer(const string &message, MessageType type);
    void writeToFile(const string &message);
    static void printInfo();
    static void printWarning();
    static void printError();
    static void printAllMessages();
    static void printLog();
};

#endif /* Logger_h */
