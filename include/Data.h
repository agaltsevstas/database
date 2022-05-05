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
    static Data &Instance();

    /*!
     * @brief Загрузка базы данных.
     * Считывание данных из txt/xml файлов
     * @param iDirectoryPath - Путь к каталогу, где хранятся файлы
     */
    void LoadDatabase(const std::string &iDirectoryPath);

    /*!
     * @brief Вход в аккаунт.
     * Требуется ввести почту/логин и пароль
     */
    void AccountLogin();

    /*!
     * @brief Вывод личных данных на экран
     * @param iObject - Объект, который в данный момент используется
     */
    void PrintPersonalData(TradingCompany *iObject);

    /*!
     * @brief Изменение личных/чужих данных
     * @param iObject - Объект, который в данный момент используется
     * @param ioOtherObject - Чужой объект, в котором изменяются данные
     */
    void ChangeData(TradingCompany *iObject, TradingCompany *ioOtherObject = nullptr);
    
    /*!
     * @brief Обертка для добавления нового сотрудника
     */
    friend void Director::AddNewEmployeeData();
    friend void HRManager::AddNewEmployeeData();
    
private:
    Mode _mode = TXT; /// Режим записи данных
    std::string _directoryPath; /// Путь к каталогу с файлами
    std::list<std::string> _filePaths; /// Список путей к файлам
    ObjectFactory<std::string, TradingCompany> _objectFactory; /// Фабрика объектов производных классов от TradingCompany
    std::vector<std::shared_ptr<TradingCompany>> _vectorObjects; /// Вектор объектов производных классов от TradingCompany
    
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
     * @param iFilePath - Путь к txt файлу
     * @param iID - ID должности в соответствии с названием файла
     */
    void ReadingTxtFile(const boost::filesystem::path &iFilePath, uint iID);
    
    /*!
     * @brief Чтение xml файла. Происходит считывание файла.
     * Поля объекта заполняются данными, после объект добавляется в вектор объектов.
     * В случае дубликата, объект удалется.
     * @param iFilePath - Путь к txt файлу
     * @param iID - ID должности в соответствии с названием файла
     */
    void ReadingXmlFile(const boost::filesystem::path &iFilePath, uint iID);
    
    /*!
     * @brief Сортировка вектора объектов по ID в порядке возрастания
     */
    void Sort();
    
    /*!
     * @brief Проверка полей на повреждение/перезапись/дублирование данных.
     * Каждое поле проверяется отдельно.
     * @param iParameter - Структура, предназначенная для проверки полей объекта
     */
    template<class Class> void CheckParameter(Parameter<Class> &iParameter);
    
    /*!
     * @brief Проверка поля на повреждение/перезапись/дублирование данных.
     * Каждое поле проверяется отдельно.
     * @param iField - Номер поля
     * @param iObject - Проверяемый объект
     * @param iMessage - Передаваемое сообщение
     * @return Структура, предназначенная для проверки полей объекта
     */
    template<class Class> Parameter<Class> SelectParameter(const Field iField,
                                                           Class *iObject,
                                                           const std::string &iMessage = {});
    
    /*!
     * @brief Обертка для проверки всех полей на повреждение/перезапись/дублирование данных
     * @param iObject - Объект, который в данный момент используется
     * @param iWarning - Передаваемое предупреждение о невалидности данных поля
     */
    template<class C> void CheckParameters(C *iObject, const bool iWarning = false);
    
    /*!
     * @brief Поиск объекта по одному из полей
     * @param iObject - Объект, который в данный момент используется
     * @return Найденный объект
     */
    TradingCompany *Find(TradingCompany *iObject);
    
    /*!
     * @brief Обертка для изменения чужих данных
     * @param iObject - Объект, который в данный момент используется
     */
    void ChangeOtherData(TradingCompany *iObject);
    
    /*!
     * @brief Обертка для удаления данных сотрудника
     * @param iObject - Объект, который в данный момент используется
     */
    void DeleteEmployeeData(TradingCompany *iObject);
    
    /*!
     * @brief Вывод всех данных из вектора объектов на экран
     */
    void GetAllOtherData() const;
    
    /*!
     * @brief Добавление объекта в вектор объектов
     * @param iObject - Добавляемый объект
     */
    template<class C> void PushBack(C &iObject);
    
    /*!
     * @brief Удаление объекта из вектора объектов
     * @param iObject - Удаляемый объект
     */
    template<class C> void DeleteObject(C *iObject);
    
    /*!
     * @brief Добавление нового сотрудника. Заполнение полей нового объекта
     * @param iObject - Объект, который в данный момент используется
     */
    void NewEmployeeData(const TradingCompany *iObject);
    
    /*!
     * @brief Установление режима записи данных
     * @param iObject - Объект, который в данный момент используется
     */
    void SetModeOutputData(const TradingCompany *iObject);
    
    /*!
     * @brief Запись всех данных в txt файлы
     */
    void WriteToTxtFile();
    
    /*!
     * @brief Запись всех данных в xml файлы
     */
    void WriteToXmlFile();
};

#endif // Data_h

