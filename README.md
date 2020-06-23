# Аннотация
Кроссплатформенный консольный проект, содержащий базу данных сотрудников торговой компании. Каждый сотрудник имеет определенную должность. У каждой должности есть свой ряд полномочий. Более подробно представлено на рисунке.
<p align="center">
<img src="images/database.png"/>
</p>

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
<img src="images/accountlogin.png"/>
</p>

Данные каждой должности находится в отдельном файле. Пример файла хранения данных c должностью "Директор".
<p align="center">
<img src="images/director.png"/>
</p>

## Используемые паттерны:
* Фабрика объектов
* Фасад
* Декоратор
* Синглтон

# Continuous Integration — CI (интеграция с разными системами)

## Runner
Runner — это агент, который используется для запуска определенных задач (jobs), их выполнения и отправки результатов обратно в GitLab. Задачи описаны в специальном файле .gitlab-ci.yml. 
<p align="center">
<img src="images/runner.png"/>
</p>

## Container Registry
Container Registry — это безопасный приватный реестр для хранения images (образов) docker. При помощи Runner можно использовать готовые docker-образы для CI.
<p align="center">
<img src="images/containerregistry.png"/>
</p>

## Pipeline
Pipeline - это последовательность выполнения stages (стадий), каждая из которых включает jobs (задачи). От момента внесения изменений в код до выхода в production (производство) приложение по очереди проходит все этапы — подобному тому, как это происходит на конвейере.
<p align="center">
<img src="images/pipeline.png"/>
</p>

Краткие пояснения по стадиям:
* Build — сборка приложения
* Test — юнит-тесты
* Deploy - развёртывание на production

## CI (интеграция с разными системами)
<p align="center">
<img src="images/ci.png"/>
</p>