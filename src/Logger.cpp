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


void Logger::Instance()
{
    namespace bs = boost::filesystem;
    
    delete logger_; // Очищение указателя на случай двойной инициализации
    logger_ = new Logger;
    debugLevel_ = DEBUG_LEVEL_INFO;
    
    bs::path fileName = Utils::LocalTime() + ".log";
    bs::path directory = "log/";
    bs::create_directory(directory); // Проверка на существование каталога. В случае отсутсвия, создается каталог
    std::string filePath = directory.string() + fileName.string();
    logFile_.open(filePath);
}

void Logger::SetDebugLevel(Logger::DebugLevel debugLevel)
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

int Logger::Streamer::StringBuffer::Sync()
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
            Logger::logger_->WriteInfo(text);
            break;
            
        case MESSAGE_WARNING:
            Logger::logger_->WriteWarning(text);
            break;
            
        case MESSAGE_ERROR:
            Logger::logger_->WriteError(text);
            break;
    }
    return 0;
};

void Logger::WriteInfo(const std::string &message)
{
    if (debugLevel_ >= DEBUG_LEVEL_INFO)
    {
        const std::string localTime = "[" + Utils::LocalTime() + "] ";
        const std::string str = localTime + message;
        thread_ = std::thread([this, &str]() { this->WriteToFile(str); });
        WriteToBuffer(str, MessageType::MESSAGE_INFO);
        thread_.join();
    }
}

void Logger::WriteWarning(const std::string &message)
{
    if (debugLevel_ >= DEBUG_LEVEL_WARNING)
    {
        const std::string localTime = "[" + Utils::LocalTime() + "] ";
        const std::string type = "[Warning] ";
        const std::string str = localTime + type + message;
        thread_ = std::thread([this, &str]() { this->WriteToFile(str); });
        WriteToBuffer(str, MessageType::MESSAGE_WARNING);
        thread_.join();
    }
}

void Logger::WriteError(const std::string &message)
{
    if (debugLevel_ >= DEBUG_LEVEL_ERROR)
    {
        const std::string localTime = "[" + Utils::LocalTime() + "] ";
        const std::string type = "[Error] ";
        const std::string str = localTime + type + message;
        thread_ = std::thread([this, &str]() { this->WriteToFile(str); });
        WriteToBuffer(str, MessageType::MESSAGE_ERROR);
        thread_.join();
    }
}

void Logger::WriteToBuffer(const std::string &message, MessageType messageType)
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

void Logger::WriteToFile(const std::string &message)
{
    logFile_ << message << std::flush; // Принудительный сброс буфера
}

void Logger::PrintInfo()
{
    infoBuffer_.empty() ? std::cout << "Cообщения отсутствуют" << std::endl : std::cout << infoBuffer_;
}

void Logger::PrintWarning()
{
    warningBuffer_.empty() ? std::cout << "Предупреждения отсутствуют" << std::endl : std::cout << warningBuffer_;
}

void Logger::PrintError()
{
    errorBuffer_.empty() ? std::cout << "Ошибки отсутствуют" << std::endl : std::cout << errorBuffer_;
}

void Logger::PrintAllMessages()
{
    std::cout << allMessagesBuffer_ << std::endl;
}

void Logger::PrintLog(const TradingCompany *object)
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
            switch (Utils::Hash(input.c_str()))
            {
                case Utils::Hash("1") :
                    PrintInfo();
                    Logger::info << ">> Вывод всех информационных сообщений <<" << std::endl;
                    break;

                case Utils::Hash("2") :
                    PrintWarning();
                    Logger::info << ">> Вывод всех предупреждений << " << std::endl;
                    break;

                case Utils::Hash("3") :
                    PrintError();
                    Logger::info << ">> Вывод всех ошибок <<" << std::endl;
                    break;

                case Utils::Hash("4") :
                    PrintAllMessages();
                    Logger::info << ">> Вывод всех сообщений <<" << std::endl;
                    break;

                case Utils::Hash("b") :
                case Utils::Hash("н") :
                    return;

                case Utils::Hash("esc") :
                case Utils::Hash("выход") :
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

