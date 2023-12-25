#include "Logger.h"
#include "Utils.h"
#include "Employee.h"

#include <fstream>
#include <boost/filesystem.hpp>

std::unique_ptr<Logger> Logger::_logger = nullptr;                                                 // Определение уровня подробности лога
Logger::DebugLevel Logger::_debugLevel = Logger::DebugLevel::DEBUG_LEVEL_DISABLED; // Определение уровня подробности лога
std::ofstream Logger::_logFile;                                                    // Определение выходного файлового потока
Logger::Streamer Logger::info(Logger::MESSAGE_INFO);                               // Определение поля информационного сообщения для Logger
Logger::Streamer Logger::warning(Logger::MESSAGE_WARNING);                         // Определение поля предупреждения для Logger
Logger::Streamer Logger::error(Logger::MESSAGE_ERROR);                             // Определение поля ошибки для Logger
std::string Logger::_infoBuffer;                                                   // Определение буфер хранения информационных сообщений
std::string Logger::_warningBuffer;                                                // Определение буфер хранения предупреждений
std::string Logger::_errorBuffer;                                                  // Определение буфер хранения ошибок
std::string Logger::_allMessagesBuffer;                                            // Определение буфер хранения всех видов сообщений


void Logger::Instance()
{
    namespace bs = boost::filesystem;
    
    _logger.reset(new Logger());
    _debugLevel = DEBUG_LEVEL_INFO;
    
    bs::path fileName = Utils::LocalTime() + ".log";
    bs::path directory = "log/";
    bs::create_directory(directory); // Проверка на существование каталога. В случае отсутсвия, создается каталог
    std::string filePath = directory.string() + fileName.string();
    _logFile.open(filePath);
}

void Logger::SetDebugLevel(Logger::DebugLevel iDebugLevel) noexcept
{
    _debugLevel = iDebugLevel;
}

Logger::Streamer::Streamer(Logger::MessageType iMessageType) noexcept
: std::ostream(new StringBuffer(iMessageType))
{
}

Logger::Streamer::~Streamer()
{
    delete rdbuf();
}

Logger::Streamer::StringBuffer::StringBuffer(Logger::MessageType iMessageType) noexcept
: messageType_(iMessageType)
{
}

Logger::Streamer::StringBuffer::~StringBuffer()
{
    pubsync();
}

int Logger::Streamer::StringBuffer::sync()
{
    std::string text(str()); // Получение текста из буфера
    if (Logger::_logger == nullptr || text.empty())
    {
        return 0;
    }
    str(""); // Очищение буфера
    switch (messageType_)
    {
        case MESSAGE_INFO:
            Logger::_logger->WriteInfo(text);
            break;
            
        case MESSAGE_WARNING:
            Logger::_logger->WriteWarning(text);
            break;
            
        case MESSAGE_ERROR:
            Logger::_logger->WriteError(text);
            break;
    }
    
    return 0;
};

void Logger::WriteInfo(const std::string &iMessage)
{
    if (_debugLevel >= DEBUG_LEVEL_INFO)
    {
        const std::string localTime = "[" + Utils::LocalTime() + "] ";
        const std::string str = localTime + iMessage;
        _thread = std::thread([this, &str]() { this->WriteToFile(str); });
        WriteToBuffer(str, MessageType::MESSAGE_INFO);
        _thread.join();
    }
}

void Logger::WriteWarning(const std::string &iMessage)
{
    if (_debugLevel >= DEBUG_LEVEL_WARNING)
    {
        const std::string localTime = "[" + Utils::LocalTime() + "] ";
        const std::string type = "[Warning] ";
        const std::string str = localTime + type + iMessage;
        _thread = std::thread([this, &str]() { this->WriteToFile(str); });
        WriteToBuffer(str, MessageType::MESSAGE_WARNING);
        _thread.join();
    }
}

void Logger::WriteError(const std::string &iMessage)
{
    if (_debugLevel >= DEBUG_LEVEL_ERROR)
    {
        const std::string localTime = "[" + Utils::LocalTime() + "] ";
        const std::string type = "[Error] ";
        const std::string str = localTime + type + iMessage;
        _thread = std::thread([this, &str]() { this->WriteToFile(str); });
        WriteToBuffer(str, MessageType::MESSAGE_ERROR);
        _thread.join();
    }
}

void Logger::WriteToBuffer(const std::string &message, MessageType iMessageType)
{
    _allMessagesBuffer += message;
    switch (iMessageType)
    {
        case MESSAGE_INFO:
            _infoBuffer += message;
            break;
            
        case MESSAGE_WARNING:
            _warningBuffer += message;
            break;
            
        case MESSAGE_ERROR:
            _errorBuffer += message;
            break;
    }
}

void Logger::WriteToFile(const std::string &iMessage) noexcept
{
    _logFile << iMessage << std::flush; // Принудительный сброс буфера
}

void Logger::PrintInfo() noexcept
{
    _infoBuffer.empty() ? std::cout << "Cообщения отсутствуют" << std::endl : std::cout << _infoBuffer;
}

void Logger::PrintWarning() noexcept
{
    _warningBuffer.empty() ? std::cout << "Предупреждения отсутствуют" << std::endl : std::cout << _warningBuffer;
}

void Logger::PrintError() noexcept
{
    _errorBuffer.empty() ? std::cout << "Ошибки отсутствуют" << std::endl : std::cout << _errorBuffer;
}

void Logger::PrintAllMessages() noexcept
{
    std::cout << _allMessagesBuffer << std::endl;
}

void Logger::PrintLog(const Employee *iObject)
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
                    EXIT(iObject);

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
    _logFile.flush();
    _logFile.close();
}

