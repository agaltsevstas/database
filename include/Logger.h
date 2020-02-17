#ifndef Logger_h
#define Logger_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <assert.h>
#include <thread>
#include <mutex>

using namespace std;

class Logger
{
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
        MESSAGE_INFO,
        MESSAGE_WARNING,
        MESSAGE_ERROR,
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
    Logger() {};
    Logger(const Logger&);
    Logger& operator=(Logger&);
    ~Logger() {};
    
private:
    string infoBuffer;
    string warningBuffer;
    string errorBuffer;
    thread thread_;
    mutex mutex_;
    
    static DebugLevel debugLevel_;
    static Logger* logger_;
    static ofstream logFile_;
    
    void writeInfo(const string &message);
    void writeWarning(const string &message);
    void writeError(const string &message);
    void writeToBuffer(const string &message, MessageType type);
    void writeToFile(const string &message);
};

#endif /* Logger_h */
