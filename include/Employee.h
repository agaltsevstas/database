#ifndef Employee_h
#define Employee_h

#include "Logger.h"
#include "IEmployee.h"

#include <map>


class Employee : public IEmployee
{
    friend class Data;
    friend class Director;
    
private:
    /*!
     * @brief Структура данных
     */
    struct Type
    {
        /// Статус данных
        Status status;

        /*!
         * @brief Тип данных
         */
        
        /// 32-разрядное целое значение без знака
        uint32_t uintValue = 0;
        
        /// 64-разрядное целое значение без знака
        uint64_t uint64Value = 0;
        
        /// Строковое значение
        std::string stringValue;
    };

public:

    /*!
     * @brief Перегрузка оператора = (присваивания).
     * Запись данных из одного объекта в другой
     * @param other - объект
     * @return Измененный объект
     */
    const IEmployee& operator = (const IEmployee &other) override;

    /*!
     * @brief Перегрузка оператора >> (ввода).
     * Запись данных в поля объекта
     * @param iLine - строка
     */
    void operator >> (const std::string &iLine) override;

    /*!
     * @brief Перегрузка оператора << (вывода).
     * Вывод полей объекта
     * @param ioOut - поток вывода
     * @return Поток вывода
     */
    std::ostream& operator << (std::ostream &ioOut) const noexcept override;

    /*!
     * @brief Перегрузка оператора == (сравнения).
     * Сравнение двух объектов на равенство
     * @param other - сравниваемый объект
     * @return Логическое значение
     */
    bool operator == (const IEmployee &other) const noexcept override;

    /*!
     * @brief Получение значений полей
     * @return Значение поля
     */
    std::string GetPosition() const noexcept override;
    std::string GetSurname() const noexcept override;
    std::string GetName() const noexcept override;
    std::string GetPatronymic() const noexcept override;
    
protected:
    /*!
     * @brief Получение значений полей
     * @return Значение поля
     */
    uint32_t    GetId() const noexcept override;
    std::string GetSex() const noexcept override;
    std::string GetDateOfBirth() const noexcept override;
    uint64_t    GetPassport() const noexcept override;
    uint64_t    GetPhone() const noexcept override;
    std::string GetEmail() const noexcept override;
    std::string GetDateOfHiring() const noexcept override;
    std::string GetWorkingHours() const noexcept override;
    uint32_t    GetSalary() const noexcept override;
    std::string GetPassword() const noexcept override;
    
    /*!
     * @brief Вывод личных данных на экран
     */
    virtual void PrintPersonalData() noexcept;

private:
    uint32_t    _id = 0;       /// ID
    std::string _position;     /// Должность
    std::string _surname;      /// Фамилия
    std::string _name;         /// Имя
    std::string _patronymic;   /// Отчество
    std::string _sex;          /// Пол
    std::string _dateOfBirth;  /// Дата рождения
    uint64_t    _passport = 0; /// Паспорт
    uint64_t    _phone = 0;    /// Телефон
    std::string _email;        /// Почта
    std::string _dateOfHiring; /// Дата принятия на работу
    std::string _workingHours; /// Часы работы
    uint32_t    _salary = 0;   /// Зарплата
    std::string _password;     /// Пароль
    
    /*!
     * @brief Инициализация полей
     * @param Значение поля
     */
    void SetId(const std::string &iID) override;
    void SetPosition(const std::string &iPosition) override;
    void SetSurname(const std::string &iSurname) override;
    void SetName(const std::string &iName) override;
    void SetPatronymic(const std::string &iPatronymic) override;
    void SetSex(const std::string &iSex) override;
    void SetDateOfBirth(const std::string &iDateOfBirth) override;
    void SetPhone(const std::string &iPhone) override;
    void SetEmail(const std::string &iEmail) override;
    void SetDateOfHiring(const std::string &iDateOfHiring) override;
    void SetWorkingHours(const std::string &iWorkingHours) override;
    void SetPassport(const std::string &iPassport) override;
    void SetSalary(const std::string &iSalary) override;
    void SetPassword(const std::string &iPassword) override;

    /*!
     * @brief Проверка полей на повреждение/перезапись данных
     * @param iWarning - Предупреждение о невалидности данных поля
     */
    void CheckId(const std::string &iWarning = {}) override; /// Не используется!
    void CheckPosition(const std::string &iWarning = {}) override;
    void CheckSurname(const std::string &iWarning = {}) override;
    void CheckName(const std::string &iWarning = {}) override;
    void CheckPatronymic(const std::string &iWarning = {}) override;
    void CheckSex(const std::string &iWarning = {}) override;
    void CheckDateOfBirth(const std::string &iWarning = {}) override;
    void CheckPassport(const std::string &iWarning = {}) override;
    void CheckPhone(const std::string &iWarning = {}) override;
    void CheckEmail(const std::string &iWarning = {}) override;
    void CheckDateOfHiring(const std::string &iWarning = {}) override;
    void CheckWorkingHours(const std::string &iWarning = {}) override;
    void CheckSalary(const std::string &iWarning = {}) override;
    void CheckPassword(const std::string &iWarning = {}) override;

    /*!
     * @brief Изменение статуса полей на перезапись/дублирование данных
     */
    void ChangeStatusPosition() override;
    void ChangeStatusSurname() override;
    void ChangeStatusName() override;
    void ChangeStatusPatronymic() override;
    void ChangeStatusSex() override;
    void ChangeStatusDateOfBirth() override;
    /// @param canOverwrite - true-перезапись/false-дублирование
    void ChangeStatusPassport(const bool canOverwrite = false) override;
    /// @param canOverwrite - true-перезапись/false-дублирование
    void ChangeStatusPhone(const bool canOverwrite = false) override;
    /// @param canOverwrite - true-перезапись/false-дублирование
    void ChangeStatusEmail(const bool canOverwrite) override;
    void ChangeStatusDateOfHiring() override;
    void ChangeStatusWorkingHours() override;
    void ChangeStatusSalary() override;
    void ChangeStatusPassword() override;

    /*!
     * @brief Рекурсия, которая вызывается в случае неверного введения данных.
     * Валидация ввода данных
     * @param iField - Номер поля
     * @param setParameter - Инициализация одного из полей
     * @param iMessage - Сообщение, которое подказывает в каком формате вводить данные
     */
    void Recursion(const Field iField,
                   std::function<void(Employee&, std::string&)> setParameter,
                   const std::string &iMessage);
    /*!
     * @brief Получение определенного типа данных (uint32_t/uint64_t/string)
     * @param iValue - Значение поля
     * @param iField - Номер поля
     * @return Значение поля с определенным типом (uint32_t/uint64_t/string)
     */
    template<typename T> T Get(const std::string &iValue, const Field iField);

    /// Пустая структура для возврата из метода в случае неудачи (затычка)
    const Type empty = Type();

    /*!
     * @details Валидация данных.
     * Проверка данных каждого поля в соответствии с требованиями
     * в зависимости от номера поля. Значение поля устанавливается
     * в одно из полей струтуры данных (uint32_t/uint64_t/string).
     * Устанавливается статус поля (ST_EMPTY/ST_WRONGDATA/ST_OK)
     * @param iValue - Значение поля
     * @param iField - Номер поля
     * @return Структура данных
     */
    const Type CheckField(std::string iValue, const Field iField);
    
    /// TODO:
private:

    /*!
     * @TODO: Установление премии
     * @param premium - Премия
     */
    void SetPremium(int premium);

    /*!
     * @TODO: Установление штрафа
     * @param fine - Штраф
     */
    void SetFine(int fine);

    /*!
     * @TODO: Получение премии
     * @return Премия
     */
    uint GetPremium() const noexcept;
    /*!
     * @TODO: Получение штрафа
     * @return Штраф
     */
    uint GetFine() const noexcept;
};

#endif // Employee_h
