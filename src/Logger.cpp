#include "Logger.h"
#include "Utils.h"
#include "IEmployee.h"

#include <filesystem>
#include <fstream>
#include <thread>


/*
 Сайты:  https://stackoverflow.com/questions/26143930/xcode-how-to-set-current-working-directory-to-a-relative-path-for-an-executable
    
 Установить путь к проекту: Xcode-> Product-> Scheme-> Edit Scheme-> Run-> Options -> Working Directory-> Use custom working-> $(SOURCE_ROOT)
 */


std::unique_ptr<Logger> Logger::_logger = nullptr;
std::ofstream Logger::_logFile; // Определение выходного файлового потока

void Logger::Instance()
{
    if (!_logger)
    {
        _logger.reset(new Logger());
        static Logger instance; // Объект-одиночка
        _debugLevel = DEBUG_LEVEL_INFO;
        
        const std::string currrentPath = std::filesystem::current_path().string();
        const std::string fileName = Utils::LocalTime() + ".log";
        const std::string directory = "/log/";
        auto del = currrentPath + directory;
        std::filesystem::create_directory(currrentPath + directory); // Проверка на существование каталога. В случае отсутсвия, создается каталог
        std::string filePath = currrentPath + directory + fileName;
        _logFile.open(filePath);
        if (!_logFile.is_open())
            throw std::ofstream::failure("Невозможно открыть директорию >> " + currrentPath + directory);
    }
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
: _messageType(iMessageType)
{
}

Logger::Streamer::StringBuffer::~StringBuffer()
{
    pubsync();
}

int Logger::Streamer::StringBuffer::sync()
{
    std::string text(str()); // Получение текста из буфера
    if (text.empty())
    {
        return 0;
    }
    str(""); // Очищение буфера
    switch (_messageType)
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
        auto thread = std::thread([this, &str]() { this->WriteToFile(str); }); // Отдельный поток, в котром осуществляется запись в файл
        WriteToBuffer(str, MessageType::MESSAGE_INFO);
        thread.join();
    }
}

void Logger::WriteWarning(const std::string &iMessage)
{
    if (_debugLevel >= DEBUG_LEVEL_WARNING)
    {
        const std::string localTime = "[" + Utils::LocalTime() + "] ";
        const std::string type = "[Warning] ";
        const std::string str = localTime + type + iMessage;
        auto thread = std::thread([this, &str]() { this->WriteToFile(str); }); // Отдельный поток, в котром осуществляется запись в файл
        WriteToBuffer(str, MessageType::MESSAGE_WARNING);
        thread.join();
    }
}

void Logger::WriteError(const std::string &iMessage)
{
    if (_debugLevel >= DEBUG_LEVEL_ERROR)
    {
        const std::string localTime = "[" + Utils::LocalTime() + "] ";
        const std::string type = "[Error] ";
        const std::string str = localTime + type + iMessage;
        auto thread = std::thread([this, &str]() { this->WriteToFile(str); }); // Отдельный поток, в котром осуществляется запись в файл
        WriteToBuffer(str, MessageType::MESSAGE_ERROR);
        thread.join();
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

void Logger::PrintLog(const IEmployee *iObject)
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

