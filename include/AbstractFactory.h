#ifndef ObjectFactory_h
#define ObjectFactory_h

#include <iostream>
#include <map>

#define CREATOR_REGISTRATION(className)\
        static className _instance##className;


/*!
 * @brief Абстрактная Фабрика Классов
 * Требуется для создания объектов классов
 */
template<class ID, class Base, typename ...Args>
class IAbstractFactory
{
    using ClassUniquePtr = std::unique_ptr<Base>;
    using ClassSharedPtr = std::shared_ptr<Base>;
    using TBase = std::function<ClassSharedPtr(Args&&...)>;
    using FactoryMap = std::map<ID, TBase>;
    
protected:
    IAbstractFactory() = default;
    ~IAbstractFactory() = default;
    IAbstractFactory(const IAbstractFactory&) = delete;
    IAbstractFactory& operator =(const IAbstractFactory&) = delete;

public:
    
    /*!
     * @brief Удаление класса
     * @param iID - Идентификатор  класса
     */
    static void Remove(const ID& iID) noexcept
    {
        typename FactoryMap::iterator it = _classes.find(iID);
        if (it != _classes.end())
            _classes.erase(it);
    }
    
    /*!
     * @brief Проверка на наличие класса по Id
     * @param iID - Идентификатор  зарегистрированного класса
     * @return true - зарегистрированный класс найден, иначе - false
     */
    static bool IsRegistered(const ID& iID) noexcept
    {
        return _classes.find(iID) != _classes.end();
    }

    /*!
     * @brief Создание объекта зарегистрированного класса
     * @param iID - Идентификатор зарегистрированного класса
     * @param iArgs - Аргументы зарегистрированного класса
     * @return Созданный объект зарегистрированного класса
     */
    static std::shared_ptr<Base> Create(const ID& iID, Args&&... iArgs)
    {
        if (auto it = _classes.find(iID); it != _classes.end())
        {
            auto& [_id, _class] = *it;
            return _class(iArgs...); // Вызывается метод Register
        }

        return nullptr;
    }

    /*!
     * @brief Создание объекта зарегистрированного класса
     * @param iID - Идентификатор зарегистрированного класса
     * @return Созданный объект зарегистрированного класса
     */
    static TBase Get(const ID& iID)
    {
        return _classes[iID];
    }
    
protected:
    /*!
     * @brief Добавление класса в карту классов
     * Derived - Класс, который фабрике необходимо зарегистрировать
     * @param iID - Идентификатор  класса
     */
    template<class Derived>
    void Add(ID&& iID)
    {
        static_assert(std::is_base_of<Base, Derived>::value, "Factory::registerType doesn't accept this type because doesn't derive from base class"); // Проверка Derived на принадлежность к Base
        _classes[std::forward<ID>(iID)] = &Register<Derived>; // Сохраняем адрес метода Register
    }

private:
    /*!
     * @brief Создание объекта  класса
     * Derived - Класс, который фабрике необходимо зарегистрировать
     * @return Созданный объект класса
     */
    template<class Derived>
    static ClassSharedPtr Register(Args&&... iArgs)
    {
        return std::make_shared<Derived>(std::forward<Args>(iArgs)...);
    }

private:
    static inline FactoryMap _classes; // Хранится id и адрес метода Register с аргументами
};

#endif /* ObjectFactory_h */
