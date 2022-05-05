#ifndef ObjectFactory_h
#define ObjectFactory_h

#include <iostream>
#include <map>

/*!
 * @brief Фабрика объектов
 * Требуется для создания объектов классов
 */
template<class ID, class Base> class ObjectFactory
{
private:
    typedef Base* (*fInstantiator)(); /// Указатель на функцию, возвращающий указатель на объект типа Base
    
    /*!
     * @brief Создание объекта определенного класса
     * @return Созданный объект определенного класса
     */
    template<class Derived> static Base* Instantiator()
    {
        return new Derived();
    }
    std::map<ID, fInstantiator> classes; /// Карта классов
    
public:
    ObjectFactory() {}
    
    /*!
     * @brief Добавление классов в карту классов.
     * Derived - Определенный класс, который фабрике необходимо зарегистрировать
     * @param id - Строка-идентификатор определенного класса
     */
    template<class Derived> void Add(ID id)
    {
        classes[id] = &Instantiator<Derived>;
    }
    
    /*!
     * @brief Получение объекта определенного класса
     * @param id - Строка-идентификатор определенного класса
     * @return Найденный объект по идентификатору определенного класса
     */
    fInstantiator Get(ID id)
    {
        return classes[id];
    }
};
#endif /* ObjectFactory_h */
