#include "date.h"

TDate::TDate(int32_t daysFromStart)
    : DaysFromStart(daysFromStart)
{}


int32_t TDate::GetDaysFromStart() const {
    return DaysFromStart;
}

bool operator<(const TDate& lhs, const TDate& rhs) {
    return lhs.GetDaysFromStart() < rhs.GetDaysFromStart();
}

bool operator==(const TDate& lhs, const TDate& rhs) {
    return lhs.GetDaysFromStart() == rhs.GetDaysFromStart();
}

TDate operator+(const TDate& date, int32_t shift) {
    return TDate(date.GetDaysFromStart() + shift);
}
