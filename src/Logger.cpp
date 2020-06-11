#include <boost/filesystem.hpp>

#include "Logger.h"
#include "TradingCompany.h"

Logger* Logger::logger_ = nullptr;                                                 // Определение уровня подробности лога
Logger::DebugLevel Logger::debugLevel_ = Logger::DebugLevel::DEBUG_LEVEL_DISABLED; // Определение уровня подробности лога
std::ofstream Logger::logFile_;                                                    // Определение выходного файлового потока
Logger::Streamer Logger::info(Logger::MESSAGE_INFO);                               // Определение поля информационного сообщения для Logger
Logger::Streamer Logger::warning(Logger::MESSAGE_WARNING);                         // Определение поля предупреждения для Logger
Logger::Streamer Logger::error(Logger::MESSAGE_ERROR);                             // Определение поля ошибки для Logger
std::string Logger::infoBuffer_;                                                   // Определение буфер хранения информационных сообщений
std::string Logger::warningBuffer_;                                                // Определение буфер хранения предупреждений
std::string Logger::errorBuffer_;                                                  // Определение буфер хранения ошибок
std::string Logger::allMessagesBuffer_;                                            // Определение буфер хранения всех видов сообщений


void Logger::instance()
{
    namespace bs = boost::filesystem;
    
    delete logger_; // Очищение указателя на случай двойной инициализации
    logger_ = new Logger;
    debugLevel_ = DEBUG_LEVEL_INFO;
    
    uint number = 0;
    bs::path fileName = "log_0.txt";
    bs::path directory = "log/";
    bs::create_directory(directory); // Проверка на существование каталога. В случае отсутсвия, создается каталог
    // Проверка на существование файла. В случае наличия, создается новый файл с новым именем
    while (bs::is_regular_file(directory.string() + fileName.string()))
    {
        fileName = "log_" + std::to_string(number) + ".txt";
        ++number;
    }
    std::string filePath = directory.string() + fileName.string();
    logFile_.open(filePath);
}

void Logger::setDebugLevel(Logger::DebugLevel debugLevel)
{
    debugLevel_ = debugLevel;
}

Logger::Streamer::Streamer(Logger::MessageType messageType)
: std::ostream(new StringBuffer(messageType))
{
}

Logger::Streamer::~Streamer()
{
    delete rdbuf();
}

Logger::Streamer::StringBuffer::StringBuffer(Logger::MessageType messageType)
: messageType_(messageType)
{
}

Logger::Streamer::StringBuffer::~StringBuffer()
{
    pubsync();
}

int Logger::Streamer::StringBuffer::sync()
{
    std::string text(str()); // Получение текста из буфера
    if (Logger::logger_ == nullptr || text.empty())
    {
        return 0;
    }
    str(""); // Очищение буфера
    switch (messageType_)
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

void Logger::writeInfo(const std::string &message)
{
    if (debugLevel_ >= DEBUG_LEVEL_INFO)
    {
        thread_ = std::thread([this, &message]() { this->writeToFile(message); });
        writeToBuffer(message, MessageType::MESSAGE_INFO);
        thread_.join();
    }
}

void Logger::writeWarning(const std::string &message)
{
    if (debugLevel_ >= DEBUG_LEVEL_WARNING)
    {
        const std::string type = "[Warning] ";
        std::string str = type + message;
        thread_ = std::thread([this, &str]() { this->writeToFile(str); });
        writeToBuffer(message, MessageType::MESSAGE_WARNING);
        thread_.join();
    }
}

void Logger::writeError(const std::string &message)
{
    if (debugLevel_ >= DEBUG_LEVEL_ERROR)
    {
        const std::string type = "[Error] ";
        std::string str = type + message;
        thread_ = std::thread([this, &str]() { this->writeToFile(str); });
        writeToBuffer(message, MessageType::MESSAGE_ERROR);
        thread_.join();
    }
}

void Logger::writeToBuffer(const std::string &message, MessageType messageType)
{
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

void Logger::writeToFile(const std::string &message)
{
    logFile_ << message << std::flush; // Принудительный сброс буфера
}

void Logger::printInfo()
{
    infoBuffer_.empty() ? std::cout << "Cообщения отсутствуют" << std::endl : std::cout << infoBuffer_;
}

void Logger::printWarning()
{
    warningBuffer_.empty() ? std::cout << "Предупреждения отсутствуют" << std::endl : std::cout << warningBuffer_;
}

void Logger::printError()
{
    errorBuffer_.empty() ? std::cout << "Ошибки отсутствуют" << std::endl : std::cout << errorBuffer_;
}

void Logger::printAllMessages()
{
    std::cout << allMessagesBuffer_ << std::endl;
}

void Logger::printLog(const TradingCompany *object)
{
    Logger::info << "*********************** Logger *************************" << std::endl;
    while (true)
    {
        std::cout << std::endl;
        std::cout << "*********************** Logger *************************" << std::endl;
        std::cout << "Хотите вывести все информационные сообщения - нажмите 1" << std::endl;
        std::cout << "Хотите вывести все предупреждения - нажмите 2" << std::endl;
        std::cout << "Хотите вывести все ошибки - нажмите 3" << std::endl;
        std::cout << "Хотите вывести весь лог - нажмите 4" << std::endl;
        std::cout << "Хотите вернуться назад? - введите B(англ.) или Н(рус.)" << std::endl;
        std::cout << "Хотите выйти из программы? - введите ESC или ВЫХОД" << std::endl;
        std::cout << "Ввод: ";
        try
        {
            std::string input;
            std::cin >> input;
            switch (utils::str(input.c_str()))
            {
                case utils::str("1") :
                    printInfo();
                    Logger::info << ">> Вывод всех информационных сообщений <<" << std::endl;
                    break;

                case utils::str("2") :
                    printWarning();
                    Logger::info << ">> Вывод всех предупреждений << " << std::endl;
                    break;

                case utils::str("3") :
                    printError();
                    Logger::info << ">> Вывод всех ошибок <<" << std::endl;
                    break;

                case utils::str("4") :
                    printAllMessages();
                    Logger::info << ">> Вывод всех сообщений <<" << std::endl;
                    break;

                case utils::str("b") :
                case utils::str("н") :
                    return;

                case utils::str("esc") :
                case utils::str("выход") :
                    EXIT(object);

                default:
                    throw input;
            }
        }
        catch (const std::string &exception)
        {
            Logger::error << "Введена >> " << exception << " - неверная команда!" << std::endl;
            std::cerr << "Вы ввели >> " << exception << " - неверная команда!" << std::endl;
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
    }
}

Logger::~Logger()
{
    delete logger_;
    logFile_.flush();
    logFile_.close();
}

