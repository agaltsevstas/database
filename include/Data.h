#ifndef Data_h
#define Data_h

#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/variant.hpp>

#include "ObjectFactory.h"
#include "TradingCompany.h"
#include "Director.h"
#include "HRManager.h"

/// Карта ID должностей
const std::map<std::string, uint> idPositions =
{
    {"Бухгалтер", 900},
    {"Водитель", 1400},
    {"Главный_бухгалтер", 200},
    {"Главный_юрист-консультант", 300},
    {"Грузчик", 1300},
    {"Директор", 100},
    {"Логист", 1000},
    {"Менеджер_по_закупкам", 1200},
    {"Менеджер_по_персоналу", 400},
    {"Менеджер_по_продажам", 700},
    {"Кассир", 800},
    {"Начальник_отдела_закупок", 500},
    {"Начальник_склада", 600},
    {"Юрист", 1100}
};

/// Вектор предупреждений, номер элемента соответствует номеру поля класса TradingCompany
const std::vector<std::string> warnings
{
    "Ваш id не удовлетворяет требованиям!\n",
    "Ваша должность не удовлетворяет требованиям!\n",
    "Ваша фамилия не удовлетворяет требованиям!\n",
    "Ваше имя не удовлетворяет требованиям!\n",
    "Ваше отчество не удовлетворяет требованиям!\n",
    "Ваш пол не удовлетворяет требованиям!\n",
    "Ваша дата рождения не удовлетворяет требованиям!\n",
    "Ваш паспорт не удовлетворяет требованиям!\n",
    "Ваш телефон не удовлетворяет требованиям!\n",
    "Ваша почта не удовлетворяет требованиям!\n",
    "Ваша дата принятия на работу не удовлетворяет требованиям!\n",
    "Ваши часы работы не удовлетворяет требованиям!\n",
    "Ваша зарплата не удовлетворяет требованиям!\n",
    "Ваш пароль не удовлетворяет требованиям!\n"
};

/*!
 * @brief Класс-синглтон, предназначенный для чтения/записи/хранения объектов производных классов от TradingCompany
 */
class Data
{
    friend class Director;
    
private:
    /// Режимы записи данных
    enum Mode
    {
        TXT = 1,
        XML,
        Postgres,
        ALL
    };
    
    /*!
     * @brief Структура, предназначенная для проверки полей объекта
     * getParameter - Получение значения поля с типом (uint32_t/uint64_t/string)
     * checkParameter - Проверка полей на повреждение/перезапись данных
     * changeStatusParameter - Изменение статуса полей на перезапись/дублирование данных
     * object - Интересующий объект, который проверяется на валидность полей
     * isMatchCheck - Проверка совпадения поля объекта с другим полем другого объекта
     */
    template <class Class>
    struct Parameter
    {
        boost::variant<std::function<uint(TradingCompany&)>,
                       std::function<uint64_t(TradingCompany&)>,
                       std::function<std::string(TradingCompany&)>> getParameter;
        std::function<void()> checkParameter = nullptr;
        std::function<void()> changeStatusParameter = nullptr;
        Class *object = nullptr;
        bool isMatchCheck = false;
    };
    
public:
    /*!
     * @brief Создание единственного объекта
     */
    static Data &instance();

    /*!
     * @brief Загрузка базы данных.
     * Считывание данных из txt/xml файлов
     * @param directoryPath - Путь к каталогу, где хранятся файлы
     */
    void loadDatabase(const std::string &directoryPath);

    /*!
     * @brief Вход в аккаунт.
     * Требуется ввести почту/логин и пароль
     */
    void accountLogin();

    /*!
     * @brief Вывод личных данных на экран
     * @param object - Объект, который в данный момент используется
     */
    void printPersonalData(TradingCompany *object);

    /*!
     * @brief Изменение личных/чужих данных
     * @param object - Объект, который в данный момент используется
     * @param otherObject - Чужой объект, в котором изменяются данные
     */
    void changeData(TradingCompany *object, TradingCompany *otherObject = nullptr);
    
    /*!
     * @brief Обертка для добавления нового сотрудника
     */
    friend void Director::addNewEmployeeData();
    friend void HRManager::addNewEmployeeData();
    
private:
    Mode mode_ = TXT; /// Режим записи данных
    std::string directoryPath_; /// Путь к каталогу с файлами
    std::list<std::string> filePaths_; /// Список путей к файлам
    ObjectFactory<std::string, TradingCompany> objectFactory_; /// Фабрика объектов производных классов от TradingCompany
    std::vector<std::shared_ptr<TradingCompany>> vectorObjects_; /// Вектор объектов производных классов от TradingCompany
    
    Data() {}

    /*!
     * @brief Деструктор вызывает методы записи данных в файлы
     */
    ~Data();

    /*!
     * @brief Запрет копирования
     */
    Data(const Data&) = delete;

    /*!
     * @brief Запрет оператора присваивания
     */
    Data& operator=(Data&) = delete;

    /*!
     * @brief Чтение txt файла. Происходит построковое считывание файла.
     * Поля объекта заполняются данными, после объект добавляется в вектор объектов.
     * В случае дубликата, объект удалется.
     * @param filePath - Путь к txt файлу
     * @param id - ID должности в соответствии с названием файла
     */
    void readingTxtFile(const boost::filesystem::path &filePath, uint id);
    
    /*!
     * @brief Чтение xml файла. Происходит считывание файла.
     * Поля объекта заполняются данными, после объект добавляется в вектор объектов.
     * В случае дубликата, объект удалется.
     * @param filePath - Путь к txt файлу
     * @param id - ID должности в соответствии с названием файла
     */
    void readingXmlFile(const boost::filesystem::path &filePath, uint id);
    
    /*!
     * @brief Сортировка вектора объектов по ID в порядке возрастания
     */
    void sort();
    
    /*!
     * @brief Проверка полей на повреждение/перезапись/дублирование данных.
     * Каждое поле проверяется отдельно.
     * @param parameter - Структура, предназначенная для проверки полей объекта
     */
    template<class Class> void checkParameter(Parameter<Class> &parameter);
    
    /*!
     * @brief Проверка поля на повреждение/перезапись/дублирование данных.
     * Каждое поле проверяется отдельно.
     * @param field - Номер поля
     * @param object - Проверяемый объект
     * @param message - Передаваемое сообщение
     * @return Структура, предназначенная для проверки полей объекта
     */
    template<class Class> Parameter<Class> selectParameter(const Field field,
                                                           Class *object,
                                                           const std::string &message = {});
    
    /*!
     * @brief Обертка для проверки всех полей на повреждение/перезапись/дублирование данных
     * @param object - Объект, который в данный момент используется
     * @param isWarning - Передаваемое предупреждение о невалидности данных поля
     */
    template<class C> void checkParameters(C *object, const bool isWarning = false);
    
    /*!
     * @brief Поиск объекта по одному из полей
     * @param object - Объект, который в данный момент используется
     * @return Найденный объект
     */
    TradingCompany *find(TradingCompany *object);
    
    /*!
     * @brief Обертка для изменения чужих данных
     * @param object - Объект, который в данный момент используется
     */
    void changeOtherData(TradingCompany *object);
    
    /*!
     * @brief Обертка для удаления данных сотрудника
     * @param object - Объект, который в данный момент используется
     */
    void deleteEmployeeData(TradingCompany *object);
    
    /*!
     * @brief Вывод всех данных из вектора объектов на экран
     */
    void getAllOtherData() const;
    
    /*!
     * @brief Добавление объекта в вектор объектов
     * @param object - Добавляемый объект
     */
    template<class C> void pushBack(C &object);
    
    /*!
     * @brief Удаление объекта из вектора объектов
     * @param object - Удаляемый объект
     */
    template<class C> void deleteObject(C *object);
    
    /*!
     * @brief Добавление нового сотрудника. Заполнение полей нового объекта
     * @param object - Объект, который в данный момент используется
     */
    void newEmployeeData(const TradingCompany *object);
    
    /*!
     * @brief Установление режима записи данных
     * @param object - Объект, который в данный момент используется
     */
    void setModeOutputData(const TradingCompany *object);
    
    /*!
     * @brief Запись всех данных в txt файлы
     */
    void writeToTxtFile();
    
    /*!
     * @brief Запись всех данных в xml файлы
     */
    void writeToXmlFile();
    
    /*!
     * @brief Запись всех данных в PostgresSQL
     */
    void writeToPostgresSQL();
};

#endif // Data_h

