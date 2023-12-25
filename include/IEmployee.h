#ifndef IEmployee_h
#define IEmployee_h

#include <map>

/*!
 * @brief Абстрактный класс
 */
class IEmployee
{
    friend class Data;
    friend class Director;
    
public:
    /// Номера полей класса Employee
    enum Field
    {
        FIELD_ID = 0,
        FIELD_POSITION,
        FIELD_SURNAME,
        FIELD_NAME,
        FIELD_PATRONYMIC,
        FIELD_SEX,
        FIELD_DATE_OF_BIRTH,
        FIELD_PASSPORT,
        FIELD_PHONE,
        FIELD_EMAIL,
        FIELD_DATE_OF_HIRING,
        FIELD_WORKING_HOURS,
        FIELD_SALARY,
        FIELD_PASSWORD,
    };

    /// Статус данных
    enum Status
    {
        /// Успех
        ST_OK = 0,
        
        /// Перезаписывание данных
        ST_OVERWRITEDATA,

        /// Пусто
        ST_EMPTY,

        /// Проблема с данными
        ST_WRONGDATA,

        /// Дублирование данных
        ST_DUBLICATE
    };
    
protected:
    
    /// Карта параметров и оберток инициализаций полей
    const std::map<std::string, std::function<void(IEmployee&, std::string&)>> _setParameters =
    {
        {"id",           nullptr},
        {"position",     &IEmployee::SetPosition},
        {"surname",      &IEmployee::SetSurname},
        {"name",         &IEmployee::SetName},
        {"patronymic",   &IEmployee::SetPatronymic},
        {"sex",          &IEmployee::SetSex},
        {"dateOfBirth",  &IEmployee::SetDateOfBirth},
        {"passport",     &IEmployee::SetPassport},
        {"phone",        &IEmployee::SetPhone},
        {"email",        &IEmployee::SetEmail},
        {"dateOfHiring", &IEmployee::SetDateOfHiring},
        {"workingHours", &IEmployee::SetWorkingHours},
        {"salary",       &IEmployee::SetSalary},
        {"password",     &IEmployee::SetPassword}
    };
    
    /// Карта полей с их статусом
    std::map<Field, Status> _fieldStatus
    {
        {FIELD_ID,             ST_EMPTY},
        {FIELD_POSITION,       ST_EMPTY},
        {FIELD_SURNAME,        ST_EMPTY},
        {FIELD_NAME,           ST_EMPTY},
        {FIELD_PATRONYMIC,     ST_EMPTY},
        {FIELD_SEX,            ST_EMPTY},
        {FIELD_DATE_OF_BIRTH,  ST_EMPTY},
        {FIELD_PASSPORT,       ST_EMPTY},
        {FIELD_PHONE,          ST_EMPTY},
        {FIELD_EMAIL,          ST_EMPTY},
        {FIELD_DATE_OF_HIRING, ST_EMPTY},
        {FIELD_WORKING_HOURS,  ST_EMPTY},
        {FIELD_SALARY,         ST_EMPTY},
        {FIELD_PASSWORD,       ST_EMPTY},
    };

public:
    virtual ~IEmployee() {}

    /*!
     * @brief Перегрузка оператора = (присваивания).
     * Запись данных из одного объекта в другой
     * @param object - объект
     * @return Измененный объект
     */
    virtual const IEmployee& operator = (const IEmployee &object) = 0;

    /*!
     * @brief Перегрузка оператора >> (ввода).
     * Запись данных в поля объекта
     * @param iLine - строка
     */
    virtual void operator >> (const std::string &iLine) = 0;

    /*!
     * @brief Перегрузка оператора << (вывода).
     * Вывод полей объекта
     * @param ioOut - поток вывода
     * @return Поток вывода
     */
    virtual std::ostream& operator << (std::ostream &ioOut) const noexcept = 0;

    /*!
     * @brief Перегрузка оператора == (сравнения).
     * Сравнение двух объектов на равенство
     * @param other - сравниваемый объект
     * @return Логическое значение
     */
    virtual bool operator == (const IEmployee &other) const noexcept = 0;

    /// Функционал каждого производного класса
    virtual void Functional() = 0;

    /*!
     * @brief Получение значений полей
     * @return Значение поля
     */
    virtual std::string GetPosition() const noexcept = 0;
    virtual std::string GetSurname() const noexcept = 0;
    virtual std::string GetName() const noexcept = 0;
    virtual std::string GetPatronymic() const noexcept = 0;
    
protected:
    /*!
     * @brief Получение значений полей
     * @return Значение поля
     */
    virtual uint32_t    GetId() const noexcept = 0;
    virtual std::string GetSex() const noexcept = 0;
    virtual std::string GetDateOfBirth() const noexcept = 0;
    virtual uint64_t    GetPassport() const noexcept = 0;
    virtual uint64_t    GetPhone() const noexcept = 0;
    virtual std::string GetEmail() const noexcept = 0;
    virtual std::string GetDateOfHiring() const noexcept = 0;
    virtual std::string GetWorkingHours() const noexcept = 0;
    virtual uint32_t    GetSalary() const noexcept = 0;
    virtual std::string GetPassword() const noexcept = 0;

private:
    
    /*!
     * @brief Инициализация полей
     * @param Значение поля
     */
    virtual void SetId(const std::string &iID) = 0;
    virtual void SetPosition(const std::string &iPosition) = 0;
    virtual void SetSurname(const std::string &iSurname) = 0;
    virtual void SetName(const std::string &iName) = 0;
    virtual void SetPatronymic(const std::string &iPatronymic) = 0;
    virtual void SetSex(const std::string &iSex) = 0;
    virtual void SetDateOfBirth(const std::string &iDateOfBirth) = 0;
    virtual void SetPhone(const std::string &iPhone) = 0;
    virtual void SetEmail(const std::string &iEmail) = 0;
    virtual void SetDateOfHiring(const std::string &iDateOfHiring) = 0;
    virtual void SetWorkingHours(const std::string &iWorkingHours) = 0;
    virtual void SetPassport(const std::string &iPassport) = 0;
    virtual void SetSalary(const std::string &iSalary) = 0;
    virtual void SetPassword(const std::string &iPassword) = 0;

    /*!
     * @brief Проверка полей на повреждение/перезапись данных
     * @param iWarning - Предупреждение о невалидности данных поля
     */
    virtual void CheckId(const std::string &iWarning = {}) = 0; /// Не используется!
    virtual void CheckPosition(const std::string &iWarning = {}) = 0;
    virtual void CheckSurname(const std::string &iWarning = {}) = 0;
    virtual void CheckName(const std::string &iWarning = {}) = 0;
    virtual void CheckPatronymic(const std::string &iWarning = {}) = 0;
    virtual void CheckSex(const std::string &iWarning = {}) = 0;
    virtual void CheckDateOfBirth(const std::string &iWarning = {}) = 0;
    virtual void CheckPassport(const std::string &iWarning = {}) = 0;
    virtual void CheckPhone(const std::string &iWarning = {}) = 0;
    virtual void CheckEmail(const std::string &iWarning = {}) = 0;
    virtual void CheckDateOfHiring(const std::string &iWarning = {}) = 0;
    virtual void CheckWorkingHours(const std::string &iWarning = {}) = 0;
    virtual void CheckSalary(const std::string &iWarning = {}) = 0;
    virtual void CheckPassword(const std::string &iWarning = {}) = 0;

    /*!
     * @brief Изменение статуса полей на перезапись/дублирование данных
     */
    virtual void ChangeStatusPosition()= 0 ;
    virtual void ChangeStatusSurname() = 0;
    virtual void ChangeStatusName() = 0;
    virtual void ChangeStatusPatronymic() = 0;
    virtual void ChangeStatusSex() = 0;
    virtual void ChangeStatusDateOfBirth() = 0;
    /// @param canOverwrite - true-перезапись/false-дублирование
    virtual void ChangeStatusPassport(const bool canOverwrite = false) = 0;
    /// @param canOverwrite - true-перезапись/false-дублирование
    virtual void ChangeStatusPhone(const bool canOverwrite = false) = 0;
    /// @param canOverwrite - true-перезапись/false-дублирование
    virtual void ChangeStatusEmail(const bool canOverwrite) = 0;
    virtual void ChangeStatusDateOfHiring() = 0;
    virtual void ChangeStatusWorkingHours() = 0;
    virtual void ChangeStatusSalary() = 0;
    virtual void ChangeStatusPassword() = 0;
};


#endif /* IEmployee_h */
