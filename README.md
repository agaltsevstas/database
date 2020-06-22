# Аннотация
Кроссплатформенный консольный проект, содержащий базу данных сотрудников торговой компании. Каждый сотрудник имеет определенную должность. У каждой должности есть свой ряд полномочий. Более подробно представлено на рисунке.
<p align="center">
<img src="images/database.png" align="center"/></p>

## Поддерживаемые платформы
* Linux 
  * Среда разработки Qt Creator
* macOS
  * Среда разработки Xcode

## Требования:
* cmake
* qt5-qmake
* boost (не ниже версии 1.56)

## Загрузка, установка и запуск
Установку можно выполнить 2 способами:
* cmake
* qmake

### Загрузка
```
git clone https://gitlab.com/agaltsev.stas/database.git
cd database
```
### Установка с помощью cmake
```
cmake CMakeLists.txt
make
```
### Установка с помощью qmake
```
qmake database.pro
make
```
### Запуск
```
cd bin/
./database --directory=data/
```

## Запуск юнит-тестов
Запуск можно выполнить 2 способами:
* cmake
* qmake
```
cd tests/UtilsTest/
```
### Установка с помощью cmake
```
cmake CMakeLists.txt
make
```
### Установка с помощью qmake
```
qmake database.pro
make
```
### Запуск
```
cd ../../bin/tests/
./UtilsTest
```

# Описание
Запуск осуществляется командой:
```
./database --directory=<path>
```
```<path>``` - путь к базе данных. Пример входа в программу привиден на рисунке.
<p align="center">
<img src="images/accountlogin.png" align="center"/></p>

Данные каждой должности находится в отдельном файле. Пример файла хранения данных c должностью "Директор".
<p align="center">
<img src="images/director.png" align="center"/></p>

## Используемые паттерны:
* Фабрика объектов
* Фасад
* Декоратор
* Синглтон
