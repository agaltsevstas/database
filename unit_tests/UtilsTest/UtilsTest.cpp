#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE UtilsTest

#include <iostream>
#include <fstream>

#include <boost/test/unit_test.hpp>

#include "Utils.h"

/// Оборачивает строку именем функции, из которой вызвана
#define WRAP(s) (std::string(boost::core::demangle(typeid(*this).name())) + "::" + std::string(__FUNCTION__) + "(): " + (s))
#define PRINT(s) std::cout << (s) << std::endl

struct LogToFile
{
    LogToFile()
    {
        logFile.open(logFileName.c_str(), std::ios_base::out);
        boost::unit_test::unit_test_log.set_stream(logFile);
        boost::unit_test::unit_test_log.set_threshold_level(boost::unit_test::log_all_errors);
        boost::unit_test::unit_test_log.set_format(boost::unit_test::OF_CLF);
    }

    ~LogToFile()
    {
        boost::unit_test::unit_test_log.test_finish();
        logFile.close();
        logFile.open(logFileName, std::ios_base::in);
        std::stringstream strStream;
        strStream << logFile.rdbuf();
        std::cout << strStream.str() << std::endl;
    }

    std::string logFileName = "errors.txt";
    std::fstream logFile;
};

BOOST_GLOBAL_FIXTURE(LogToFile);

BOOST_AUTO_TEST_SUITE(UtilsTest)

BOOST_AUTO_TEST_CASE(translitOne)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(utils::translit(""), "");
}

BOOST_AUTO_TEST_CASE(translitTwo)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(utils::translit(" "), " ");
}

BOOST_AUTO_TEST_CASE(translitThree)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(utils::translit("`~!@#$%^&*()_+{}:<>?/|\"№;-=,'.[]\\1234567890"
                                      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"), "");
}

BOOST_AUTO_TEST_CASE(translitFour)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(utils::translit("AБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"), "");
}

BOOST_AUTO_TEST_CASE(translitFive)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(utils::translit("абвгдеёжзийклмнопрстуфхцчшщъыьэюя"),
                                      "abvgdeezhzijklmnoprstufhtschshschjejuja");
}

BOOST_AUTO_TEST_CASE(translitSix)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(utils::translit(" 0Ая "), " ja ");
}

BOOST_AUTO_TEST_CASE(createEmailOne)
{
    PRINT(WRAP("..."));

    const std::vector<std::string> anthroponym = {"surname"};

    BOOST_CHECK(utils::createEmail(anthroponym) != "surname@tradingcompany.ru");
}

BOOST_AUTO_TEST_CASE(createEmailTwo)
{
    PRINT(WRAP("..."));

    const std::vector<std::string> anthroponym = {"surname", "name", "patronymic"};

    BOOST_CHECK(utils::createEmail(anthroponym) != "surname.name.patronymic@tradingcompany.ru");
}

BOOST_AUTO_TEST_CASE(createEmailThree)
{
    PRINT(WRAP("..."));

    const std::vector<std::string> anthroponym = {"фамилия"};

    BOOST_CHECK_EQUAL(utils::createEmail(anthroponym), "familija@tradingcompany.ru");
}

BOOST_AUTO_TEST_CASE(createEmailFour)
{
    PRINT(WRAP("..."));

    const std::vector<std::string> anthroponym = {"фамилия", "имя", "отчество"};

    BOOST_CHECK_EQUAL(utils::createEmail(anthroponym), "familija.imja.otchestvo@tradingcompany.ru");
}

BOOST_AUTO_TEST_CASE(hashOne)
{
    PRINT(WRAP("..."));

    BOOST_CHECK(utils::hash("0") == utils::hash("0"));
}

BOOST_AUTO_TEST_CASE(hashTwo)
{
    PRINT(WRAP("..."));

    BOOST_CHECK(utils::hash("01") == utils::hash("01"));
}

BOOST_AUTO_TEST_CASE(hashThree)
{
    PRINT(WRAP("..."));

    BOOST_CHECK(utils::hash("01") != utils::hash("10"));
}

BOOST_AUTO_TEST_CASE(hashFour)
{
    PRINT(WRAP("..."));

    BOOST_CHECK(utils::hash("b") == utils::hash("b"));
}

BOOST_AUTO_TEST_CASE(hashFive)
{
    PRINT(WRAP("..."));

    BOOST_CHECK(utils::hash("back") == utils::hash("back"));
}

BOOST_AUTO_TEST_CASE(toLowerOne)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(utils::toLower("test"), "test");
}

BOOST_AUTO_TEST_CASE(toLowerTwo)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(utils::toLower("Test"), "test");
}

BOOST_AUTO_TEST_CASE(toLowerThree)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(utils::toLower("TesT"), "test");
}

BOOST_AUTO_TEST_CASE(toLowerFour)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(utils::toLower("TEST"), "test");
}

BOOST_AUTO_TEST_CASE(toLowerFive)
{
    PRINT(WRAP("..."));

    std::string source = "`~!@#$%^&*()_+{}:<>?/|\"№;-=,'.[]\\1234567890"
                         "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result = "`~!@#$%^&*()_+{}:<>?/|\"№;-=,'.[]\\1234567890"
                         "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";

    BOOST_CHECK_EQUAL(utils::toLower(source), result);
}

BOOST_AUTO_TEST_CASE(tolowerOne)
{
    PRINT(WRAP("..."));

    std::string source, result;
    source = result = "test";

    BOOST_CHECK_NO_THROW(utils::tolower(source));
    BOOST_CHECK(source == result);
}

BOOST_AUTO_TEST_CASE(tolowerTwo)
{
    PRINT(WRAP("..."));

    std::string source = "Test";
    std::string result = "test";

    BOOST_CHECK_NO_THROW(utils::tolower(source));
    BOOST_CHECK(source == result);
}

BOOST_AUTO_TEST_CASE(tolowerThree)
{
    PRINT(WRAP("..."));

    std::string source = "TesT";
    std::string result = "test";

    BOOST_CHECK_NO_THROW(utils::tolower(source));
    BOOST_CHECK(source == result);
}

BOOST_AUTO_TEST_CASE(tolowerFour)
{
    PRINT(WRAP("..."));

    std::string source = "TEST";
    std::string result = "test";

    BOOST_CHECK_NO_THROW(utils::tolower(source));
    BOOST_CHECK(source == result);
}

BOOST_AUTO_TEST_CASE(tolowerFive)
{
    PRINT(WRAP("..."));

    std::string source = "`~!@#$%^&*()_+{}:<>?/|\"№;-=,'.[]\\1234567890"
                         "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result = "`~!@#$%^&*()_+{}:<>?/|\"№;-=,'.[]\\1234567890"
                         "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";

    BOOST_CHECK_NO_THROW(utils::tolower(source));
    BOOST_CHECK(source == result);
}

BOOST_AUTO_TEST_CASE(splitStringOne)
{
    PRINT(WRAP("..."));

    std::string source = "`~!@#$%^&*()_+{}:<>?/|\"№;-=,'.[]\\1234567890"
                         "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result = "`~!@#$%^&*()_+{}:<>?/|\"№;-=,'.[]\\1234567890"
                         "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";

    BOOST_CHECK_NO_THROW(utils::tolower(source));
    BOOST_CHECK_EQUAL(utils::toLower(source), result);
    BOOST_CHECK(source == result);
}
//BOOST_AUTO_TEST_CASE(Two)
//{
//    PRINT(WRAP("..."));

//    detectedObject.objectness = -0.1;
//    detectedObject.classness = -0.1;

//    BOOST_CHECK_CLOSE_FRACTION(detectedObject.confidence(), 0.01, 0.0000001);
//}

//BOOST_AUTO_TEST_CASE(Three)
//{
//    PRINT(WRAP("..."));

//    Rect rect(-1, -1, -1, -1);

//    BOOST_CHECK_THROW(detectedObject.setBounds(rect), std::exception);
//}

//BOOST_AUTO_TEST_CASE(Four)
//{
//    PRINT(WRAP("..."));

//    Rect rect(0, 0, 1, 1);

//    BOOST_CHECK_NO_THROW(detectedObject.setBounds(rect));
//}

//BOOST_AUTO_TEST_CASE(Five)
//{
//    PRINT(WRAP("..."));

//    Point point, pointResult(0, 0);
//    Rect rect(0, 0, 1, 1);
//    detectedObject.setBounds(rect);

//    BOOST_CHECK_NO_THROW(point = detectedObject.center());
//    BOOST_CHECK_EQUAL(point, pointResult);
//}

//BOOST_AUTO_TEST_CASE(Six)
//{
//    PRINT(WRAP("..."));

//    uint64_t time = static_cast<uint64_t>(chrono::duration_cast< chrono::microseconds >
//                                       (chrono::system_clock::now().time_since_epoch()).count());
//    uint64_t timeResult = nutils::nowMillisecs();
//    BOOST_CHECK_CLOSE(1.0 * time, 1.0 * timeResult, 100000);
//}

//BOOST_AUTO_TEST_CASE(Seven)
//{
//    PRINT(WRAP("..."));

//    source = "1,2", delim = ";";
//    result = {{"1"}, {"2"}};

//    BOOST_CHECK(splitString(source, delim) != result);
//    BOOST_REQUIRE_EQUAL(utils::translit(""), "");
//}

BOOST_AUTO_TEST_SUITE_END()
