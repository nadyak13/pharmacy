#pragma once

#include <string>

class TDate {
public:
    TDate(int32_t daysFromStart = 0);

    int32_t GetDaysFromStart() const;

private:
    int32_t DaysFromStart;
};

bool operator<(const TDate& lhs, const TDate& rhs);

bool operator==(const TDate& lhs, const TDate& rhs);

TDate operator+(const TDate& date, int32_t shift);
