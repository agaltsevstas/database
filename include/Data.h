#ifndef Data_h
#define Data_h

#include <iostream>

class IEmployee;

class DataProxy
{
    friend class Director;
    friend class HRManager;
    
public:
    
    /*!
     * @brief Загрузка базы данных.
     * Считывание данных из txt/xml файлов
     * @param iDirectoryPath - Путь к каталогу, где хранятся файлы
     */
    static void LoadDatabase(const std::string &iDirectoryPath);
    
    /*!
     * @brief Вход в аккаунт.
     * Требуется ввести почту/логин и пароль
     */
    static void AccountLogin();
    
    /*!
     * @brief Изменение личных/чужих данных
     * @param iObject - Объект, который в данный момент используется
     * @param ioOtherObject - Чужой объект, в котором изменяются данные
     */
    static void ChangeData(const IEmployee *iObject, IEmployee *ioOtherObject = nullptr);
    
private:
    
    /*!
     * @brief Поиск объекта по одному из полей
     * @param iObject - Объект, который в данный момент используется
     * @return Найденный объект
     */
    static std::shared_ptr<IEmployee> Find(const IEmployee *iObject);
    
    /*!
     * @brief Обертка для изменения чужих данных
     * @param iObject - Объект, который в данный момент используется
     */
    static void ChangeOtherData(const IEmployee *iObject);
    
    /*!
     * @brief Обертка для удаления данных сотрудника
     * @param iObject - Объект, который в данный момент используется
     */
    static void DeleteEmployeeData(const IEmployee *iObject);
    
    /*!
     * @brief Вывод всех данных из вектора объектов на экран
     */
    static void GetAllOtherData();
    
    /*!
     * @brief Добавление нового сотрудника. Заполнение полей нового объекта
     * @param iObject - Объект, который в данный момент используется
     */
    static void NewEmployeeData(const IEmployee *iObject);
    
    /*!
     * @brief Установление режима записи данных
     * @param iObject - Объект, который в данный момент используется
     */
    static void SetModeOutputData(const IEmployee *iObject);
};

#endif // Data_h

