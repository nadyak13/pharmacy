#pragma once

#include <string>

enum class EUnitOfMeasure {
    Milligrams = 0,
    Gram = 1,
    Milliliters = 2,
    Liters = 3
};

std::string ToString(EUnitOfMeasure unit);

class TDose {
public:
    TDose(double value, EUnitOfMeasure UnitOfMeasure = EUnitOfMeasure::Milligrams);

    double GetValue() const;

    EUnitOfMeasure GetUnitOfMeasure() const;

private:
    double Value;
    EUnitOfMeasure UnitOfMeasure = EUnitOfMeasure::Milligrams;
};

bool operator==(const TDose& lhs, const TDose& rhs);
