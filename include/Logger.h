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

/*!
 * @brief Класс-синглтон, предназначенный для сбора и сохранения информации о работе программы.
 * Информация записывается в буфер и файлы
 */
class Logger
{
    friend class Director;
    
public:
    
    /*!
     * @brief Четыре уровня подробности лога:
     * DEBUG_LEVEL_DISABLED - Полное отключение лога
     * DEBUG_LEVEL_ERROR - Вывод только ошибок
     * DEBUG_LEVEL_WARNING - Вывод предупреждений и ошибок
     * DEBUG_LEVEL_INFO - Вывод сообщений
     */
    enum DebugLevel
    {
        DEBUG_LEVEL_DISABLED = 0,
        DEBUG_LEVEL_ERROR = 1,
        DEBUG_LEVEL_WARNING = 2,
        DEBUG_LEVEL_INFO = 3,
    };
    
    /*!
     * @brief Четыре уровня вида сообщений:
     * MESSAGE_INFO - Информационное сообщение
     * MESSAGE_WARNING - Предупреждение
     * MESSAGE_ERROR - Ошибка
     * MESSAGE_ALL - Сообщения всех видов (информационное сообщение, предупреждение, ошибка)
     */
    enum MessageType
    {
        MESSAGE_INFO = 1,
        MESSAGE_WARNING,
        MESSAGE_ERROR,
        MESSAGE_ALL
    };
    
    
    /*!
     * @brief Создание единственного объекта
     */
    static void Instance();
    
    /*!
     * @brief Удаление объекта и закрытия лог файла
     */
    static void Delete();
    
    /*!
     * @TODO: Установление уровня подробности лога
     * @param iLevel - Уровень лога
     */
    static void SetDebugLevel(DebugLevel iLevel);
    
    /*!
     * @details Производный класс от класссов стандартной библиотеки.
     * Для каждого вида потока создается объект, поэтому конструкторы принимают параметр MessageType.
     * Класс вывода наследуется от ostream, за формирование строки отвечает вложенный класс StringBuffer, который унаследован от stringbuf.
     * После завершениия формирования сообщения, автоматически вызвается метод sync, в котором выполняется непосредственный вывод.
     * Завершение вывода сообщается стандартными для буферизируемых потоков с помощью вызова метода flush
     */
    class Streamer : public std::ostream
    {
    public:
        /*!
         * @brief Консруктор для связывания потока вывода со строковым буфером
         * @param iMessageType - Тип сообщения
         */
        Streamer(Logger::MessageType iMessageType);
        
        /*!
         * @brief Деструктор для удаление потока буфера
         */
        ~Streamer();
        
    private:
        class StringBuffer : public std::stringbuf
        {
        public:
            
            /*!
             * @brief Конструктор для отправление типа сообщения
             * @param iMessageType - Тип сообщения
             */
            StringBuffer(Logger::MessageType iMessageType);
            
            /*!
             * @brief Деструктор.
             * При разрушении буфера вызывается на всякий случай его синхронизация.
             * Это действие предотвратит «пропадание» сообщения, если забыть вызвать flush или endl.
             */
            ~StringBuffer();
            
            /*!
             * @brief Синхронизация строкового буфера потока
             */
            virtual int Sync();
            
        private:
            Logger::MessageType messageType_;
        };
    };
    
    static Streamer info;    /// Объект потока для информационных сообщений
    static Streamer warning; /// Объект потока для предупреждений
    static Streamer error;   /// Объект потока для ошибок
    
protected:
    Logger() {}
    ~Logger();
    
    /*!
     * @brief Запрет копирования
     */
    Logger(const Logger&) = delete;
    
    /*!
     * @brief Запрет оператора присваивания
     */
    Logger& operator=(Logger&) = delete;
    
private:
    static std::string _infoBuffer;        /// Буфер для хранения информационных сообщений
    static std::string _warningBuffer;     /// Буфер для хранения предупреждений
    static std::string _errorBuffer;       /// Буфер для хранения ошибок
    static std::string _allMessagesBuffer; /// Буфер для хранения всех видов сообщений
    static Logger *_logger;                /// Объект-одиночка
    static DebugLevel _debugLevel;         /// Уровень подробности лога
    static std::ofstream _logFile;         /// Выходной файловый поток
    std::thread _thread;                   /// Отдельный поток, в котром осуществляется запись в файл
    
    /*!
     * @brief Запись информационных сообщений.
     * Запись производится одновременно в файл и буфер в двух потоках
     * @param iMessage - Записываемое сообщение
     */
    void WriteInfo(const std::string &iMessage);
    
    /*!
     * @brief Запись предупреждений.
     * Запись производится одновременно в файл и буфер в двух потоках
     * @param iMessage - Записываемое сообщение
     */
    void WriteWarning(const std::string &iMessage);
    
    /*!
     * @brief Запись ошибок.
     * Запись производится одновременно в файл и буфер в двух потоках
     * @param iMessage - Записываемое сообщение
     */
    void WriteError(const std::string &iMessage);
    
    /*!
     * @brief Запись в буфер.
     * Запись производится в определенный буфер в зависимости от уровня вида сообщения
     * @param iMessage - Записываемое сообщение
     * @param iMessageType - Уровень вида сообщений
     */
    static void WriteToBuffer(const std::string &iMessage, MessageType iMessageType);
    
    /*!
     * @brief Запись в файл
     * @param iMessage - Записываемое сообщение
     */
    void WriteToFile(const std::string &iMessage);
    
    /*!
     * @brief Вывод информационных сообщений на экран
     */
    static void PrintInfo();
    
    /*!
     * @brief Вывод предупреждений на экран
     */
    static void PrintWarning();
    
    /*!
     * @brief Вывод ошибок на экран
     */
    static void PrintError();
    
    /*!
     * @brief Вывод всех сообщений (информационные сообщений, предупреждения, ошибки) на экран
     */
    static void PrintAllMessages();
    
    /*!
     * @brief Обертка для вывода разных видов сообщений
     * @param iObject - Объект, который в данный момент используется
     */
    static void PrintLog(const TradingCompany *iObject);
};

#endif /* Logger_h */
