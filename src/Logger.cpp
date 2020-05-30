#include <boost/filesystem.hpp>

#include "Logger.h"
#include "TradingCompany.h"

/// creates logger that will write to log.txt
void Logger::createInstance()
{
    namespace bs = boost::filesystem;
    
    delete logger_;
    logger_ = new Logger;
    debugLevel_ = DEBUG_LEVEL_INFO;
    
    uint number = 0;
    bs::path fileName = "log_0.txt";
    bs::path path = "log/";
    bs::create_directory(path);
    while (bs::is_regular_file(path.string() + fileName.string()))
    {
        fileName = "log_" + std::to_string(number) + ".txt";
        ++number;
    }
    logFile_.open(path.string() + fileName.string());
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
void Logger::writeError(const std::string &message)
{
    // if level of error is greator than set debug level
    if (debugLevel_ >= DEBUG_LEVEL_ERROR)
    {
        // type out [Error]
        const std::string type = "[Error] ";
        std::string str = type + message;
        // write out message
        thread_ = std::thread([this, &str]() { this->writeToFile(str); });
        writeToBuffer(message, MessageType::MESSAGE_ERROR);
        thread_.join();
    }
}

/// can signify warning while writing message
void Logger::writeWarning(const std::string &message)
{
    // if level of warning is greator than set debug level
    if (debugLevel_ >= DEBUG_LEVEL_WARNING)
    {
        // type out [Error]
        const std::string type = "[Warning] ";
        std::string str = type + message;
        // write out message
        thread_ = std::thread([this, &str]() { this->writeToFile(str); });
        writeToBuffer(message, MessageType::MESSAGE_WARNING);
        thread_.join();
    }
}

/// Write out message to logger of type MESSAGE_INFO if debug level allows it
void Logger::writeInfo(const std::string &message)
{
    if (debugLevel_ >= DEBUG_LEVEL_INFO)
    {
        thread_ = std::thread([this, &message]() { this->writeToFile(message); });
        writeToBuffer(message, MessageType::MESSAGE_INFO);
        thread_.join();
    }
}

/// Write out message to logger with the inputted message type
void Logger::writeToBuffer(const std::string &message, MessageType messageType)
{
    // std::replace(message.begin(), message.end(), '\n', ' '); // Fix it later
    // Send message to standard console out
    // std::cout << message;
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
void Logger::writeToFile(const std::string &message)
{
    mutex_.lock();
    logFile_ << message << std::flush;
    mutex_.unlock();
}

void Logger::printInfo()
{
    std::cout << infoBuffer_ << std::endl;
}

void Logger::printWarning()
{
    std::cout << warningBuffer_ << std::endl;
}

void Logger::printError()
{
    std::cout << errorBuffer_ << std::endl;
}

void Logger::printAllMessages()
{
    std::cout << allMessagesBuffer_ << std::endl;
}

void Logger::printLog(const TradingCompany *object)
{
    Logger::info << " ********** Вход в Logger ********** " << std::endl;
    std::cout << "Хотите вывести все сообщения - нажмите 1" << std::endl;
    std::cout << "Хотите вывести все предупреждения - нажмите 2" << std::endl;
    std::cout << "Хотите вывести все ошибки - нажмите 3" << std::endl;
    std::cout << "Хотите вывести весь лог - нажмите 4" << std::endl;
    std::cout << "Хотите вернуться назад? - введите B: " << std::endl;
    std::cout << "Хотите выйти из программы? - введите ESC: " << std::endl;
    std::cout << "Ввод: ";

    std::string input;
    std::cin >> input;
    try
    {
        switch (utils::str(input.c_str()))
        {
            case utils::str("1") :
                printInfo();
                Logger::info << " >> Вывод обычной информации << " << std::endl;
                break;

            case utils::str("2") :
                printWarning();
                Logger::info << " >> Вывод всех предупреждений << " << std::endl;
                break;

            case utils::str("3") :
                printError();
                Logger::info << " >> Вывод всех ошибок << " << std::endl;
                break;

            case utils::str("4") :
                printAllMessages();
                Logger::info << " >> Вывод всех сообщений << " << std::endl;
                break;

            case utils::str("b") :
                return;

            case utils::str("esc") :
                EXIT(object);

            default:
                throw input;
        }
    }
    catch (const std::string &exception)
    {
        Logger::error << "Введена >> " << exception << " - неверная команда!" << std::endl;
        std::cerr << "Вы ввели >> " << exception
                  << " - неверная команда! Попробуйте ввести заново: " << std::endl;
        printLog(object);
    }
    catch(const std::exception &ex)
    {
        Logger::error << "Ошибка >> " << ex.what() << std::endl;
        std::cerr << "Ошибка >> " << ex.what() << std::endl;
    }
    catch(...)
    {
        Logger::error << "Неизвестная ошибка!" << std::endl;
        std::cerr << "Неизвестная ошибка!" << std::endl;
        std::exit(0);
    }
    Logger::info << " ********** Выход из Logger ********** " << std::endl;
}

/// Constructor - must send in message type
Logger::Streamer::Streamer(Logger::MessageType messageType)
: std::ostream(new StringBuffer(messageType))
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

/// Writes out any unwritten characters to output if std::string buffers not synchronized, else does nothing
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
    std::string text(str());
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
std::string Logger::infoBuffer_;
std::string Logger::warningBuffer_;
std::string Logger::errorBuffer_;
std::string Logger::allMessagesBuffer_;

