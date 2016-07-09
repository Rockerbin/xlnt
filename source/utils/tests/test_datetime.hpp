#pragma once

#include <iostream>
#include <cxxtest/TestSuite.h>

#include <xlnt/xlnt.hpp>

class test_datetime : public CxxTest::TestSuite
{
public:
    void test_from_string()
    {
        xlnt::time t("10:35:45");
        TS_ASSERT_EQUALS(t.hour, 10);
        TS_ASSERT_EQUALS(t.minute, 35);
        TS_ASSERT_EQUALS(t.second, 45);
    }

    void test_carry()
    {
        // We want a time that rolls over to the next second, minute, and hour
        // Start off with a time 1 microsecond before the next hour
        xlnt::datetime dt(2016, 7, 9, 10, 59, 59, 999999);
        auto number = dt.to_number(xlnt::calendar::windows_1900);

        // Add 600 nanoseconds to the raw number which represents time as a fraction of a day
        // In other words, 6 tenths of a millionth of a sixtieth of a sixtieth of a twenty-fourth of a day
        number += (0.6 / 1000000) / 60 / 60 / 24;
        auto rollover = xlnt::datetime::from_number(number, xlnt::calendar::windows_1900);

        TS_ASSERT_EQUALS(rollover.hour, 11);
        TS_ASSERT_EQUALS(rollover.minute, 00);
        TS_ASSERT_EQUALS(rollover.second, 00);
        TS_ASSERT_EQUALS(rollover.microsecond, 00);
    }
};
