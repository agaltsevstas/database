#include "Logger.h"
#include "Utils.h"

using namespace utils;

/// creates logger that will write to log.txt
void Logger::createInstance()
{
    delete logger_;
    logger_ = new Logger;
    debugLevel_ = DEBUG_LEVEL_INFO;
    logFile_.open("log.txt");
}

/// deletes instance of logger and closes log file ('log.txt')
void Logger::deleteInstance()
{
    delete logger_;
    logFile_.flush();
    logFile_.close();
}

/// Can set the Debug Level
void Logger::setDebugLevel(Logger::DebugLevel debugLevel)
{
    debugLevel_ = debugLevel;
}

/// can signify errors while writing message
void Logger::writeError(const string &message)
{
    // if level of error is greator than set debug level
    if (debugLevel_ >= DEBUG_LEVEL_ERROR)
    {
        // type out [Error]
        const string type = "[Error] ";
        string str = type + message;
        // write out message
        thread_ = thread([this, &str]() { this->writeToFile(str); });
        writeToBuffer(message, MessageType::MESSAGE_ERROR);
        thread_.join();
    }
}

/// can signify warning while writing message
void Logger::writeWarning(const string &message)
{
    // if level of warning is greator than set debug level
    if (debugLevel_ >= DEBUG_LEVEL_WARNING)
    {
        // type out [Error]
        const string type = "[Warning] ";
        string str = type + message;
        // write out message
        thread_ = thread([this, &str]() { this->writeToFile(str); });
        writeToBuffer(message, MessageType::MESSAGE_WARNING);
        thread_.join();
    }
}

/// Write out message to logger of type MESSAGE_INFO if debug level allows it
void Logger::writeInfo(const string &message)
{
    if (debugLevel_ >= DEBUG_LEVEL_INFO)
    {
        thread_ = thread([this, &message]() { this->writeToFile(message); });
        writeToBuffer(message, MessageType::MESSAGE_INFO);
        thread_.join();
    }
}

/// Write out message to logger with the inputted message type
void Logger::writeToBuffer(const string &message, MessageType messageType)
{
    // std::replace(message.begin(), message.end(), '\n', ' '); // Fix it later
    // Send message to standard console out
    // cout << message;
    // add message to end of buffer
    allMessagesBuffer_ += message;
    switch (messageType)
    {
        case MESSAGE_INFO:
            infoBuffer_ += message;
            break;
            
        case MESSAGE_WARNING:
            warningBuffer_ += message;
            break;
            
        case MESSAGE_ERROR:
            errorBuffer_ += message;
            break;
    }
}

/// Add message directly to the end of a file
void Logger::writeToFile(const string &message)
{
    mutex_.lock();
    logFile_ << message << flush;
    mutex_.unlock();
}

void Logger::printInfo()
{
    cout << infoBuffer_ << endl;
}

void Logger::printWarning()
{
    cout << warningBuffer_ << endl;
}

void Logger::printError()
{
    cout << errorBuffer_ << endl;
}

void Logger::printAllMessages()
{
    cout << allMessagesBuffer_ << endl;
}

void Logger::printLog()
{
    cout << "Хотите вывести все сообщения - нажмите 1" << endl;
    cout << "Хотите вывести все предупреждения - нажмите 2" << endl;
    cout << "Хотите вывести все ошибки - нажмите 3" << endl;
    cout << "Хотите вывести весь лог - нажмите 4" << endl;
    cout << "Хотите вернуться назад? - введите B: " << endl;
    cout << "Хотите выйти из программы? - введите ESC: " << endl;

    string input;
    cin >> input;
    try
    {
        switch (str(input.c_str()))
        {
            case str("1") :
                printInfo();
                break;

            case str("2") :
                printWarning();
                break;

            case str("3") :
                printError();
                break;

            case str("4") :
                printAllMessages();
                break;

            case str("b") :
                return;

            case str("esc") :
                Logger::info << "Выход из программы." << endl;
                cout << "Вы вышли из программы!" << endl;
                exit(0);

            default:
                throw input;
        }
    }
    catch (const string &exception)
    {
        Logger::error << "Введена >> " << exception
                      << " - неверная команда!" << endl;
        cerr << "Вы ввели >> " << exception
             << " - неверная команда! Попробуйте ввести заново: "
             << endl;
    }
    catch(const exception &ex)
    {
        Logger::error << "Ошибка >> " << ex.what() << endl;
        cerr << "Ошибка >> " << ex.what() << endl;
    }
    catch(...)
    {
        Logger::error << "Неизвестная ошибка!" << endl;
        cerr << "Неизвестная ошибка!" << endl;
        exit(0);
    }
    printLog();
}

/// Constructor - must send in message type
Logger::Streamer::Streamer(Logger::MessageType messageType)
: ostream(new StringBuffer(messageType))
{
}

/// Deconstructor - deletes stream buffer
Logger::Streamer::~Streamer()
{
    delete rdbuf();
}

/// Constructor for StinrgBuffer- must send in message type
Logger::Streamer::StringBuffer::StringBuffer(Logger::MessageType messageType)
: messageType(messageType)
{
}

/// Writes out any unwritten characters to output if string buffers not synchronized, else does nothing
Logger::Streamer::StringBuffer::~StringBuffer()
{
    pubsync();
}

// Creates message, warning and error variables for Logger
Logger::Streamer Logger::info(Logger::MESSAGE_INFO);
Logger::Streamer Logger::warning(Logger::MESSAGE_WARNING);
Logger::Streamer Logger::error(Logger::MESSAGE_ERROR);

/// Checks to make sure Logger instance is in sync with correct message type
int Logger::Streamer::StringBuffer::sync()
{
    if (Logger::logger_ == NULL)
    {
        return 0;
    }
    string text(str());
    if (text.empty())
    {
        return 0;
    }
    str("");
    switch (messageType)
    {
        case MESSAGE_INFO:
            Logger::logger_->writeInfo(text);
            break;
            
        case MESSAGE_WARNING:
            Logger::logger_->writeWarning(text);
            break;
            
        case MESSAGE_ERROR:
            Logger::logger_->writeError(text);
            break;
    }
    return 0;
};

Logger* Logger::logger_ = nullptr;
Logger::DebugLevel Logger::debugLevel_ = Logger::DebugLevel::DEBUG_LEVEL_DISABLED;
std::ofstream Logger::logFile_;
string Logger::infoBuffer_;
string Logger::warningBuffer_;
string Logger::errorBuffer_;
string Logger::allMessagesBuffer_;

