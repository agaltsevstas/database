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

BOOST_AUTO_TEST_CASE(One)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(detectedObject.confidence(), 0);
}

BOOST_AUTO_TEST_CASE(Two)
{
    PRINT(WRAP("..."));

    detectedObject.objectness = -0.1;
    detectedObject.classness = -0.1;

    BOOST_CHECK_CLOSE_FRACTION(detectedObject.confidence(), 0.01, 0.0000001);
}

BOOST_AUTO_TEST_CASE(Three)
{
    PRINT(WRAP("..."));

    Rect rect(-1, -1, -1, -1);

    BOOST_CHECK_THROW(detectedObject.setBounds(rect), std::exception);
}

BOOST_AUTO_TEST_CASE(Four)
{
    PRINT(WRAP("..."));

    Rect rect(0, 0, 1, 1);

    BOOST_CHECK_NO_THROW(detectedObject.setBounds(rect));
}

BOOST_AUTO_TEST_CASE(Five)
{
    PRINT(WRAP("..."));

    Point point, pointResult(0, 0);
    Rect rect(0, 0, 1, 1);
    detectedObject.setBounds(rect);

    BOOST_CHECK_NO_THROW(point = detectedObject.center());
    BOOST_CHECK_EQUAL(point, pointResult);
}

BOOST_AUTO_TEST_CASE(Six)
{
    PRINT(WRAP("..."));

    uint64_t time = static_cast<uint64_t>(chrono::duration_cast< chrono::microseconds >
                                       (chrono::system_clock::now().time_since_epoch()).count());
    uint64_t timeResult = nutils::nowMillisecs();
    BOOST_CHECK_CLOSE(1.0 * time, 1.0 * timeResult, 100000);
}

BOOST_AUTO_TEST_CASE(Seven)
{
    PRINT(WRAP("..."));

    source = "1,2", delim = ";";
    result = {{"1"}, {"2"}};

    BOOST_CHECK(splitString(source, delim) != result);
}

BOOST_AUTO_TEST_SUITE_END()
