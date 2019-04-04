#include "dose.h"

TDose::TDose(double value, EUnitOfMeasure unitOfMeasure)
    : Value(value), UnitOfMeasure(unitOfMeasure)
{}

double TDose::GetValue() const {
    return Value;
}

EUnitOfMeasure TDose::GetUnitOfMeasure() const {
    return UnitOfMeasure;
}

bool operator==(const TDose& lhs, const TDose& rhs) {
    return static_cast<uint32_t>(lhs.GetValue()) == static_cast<uint32_t>(rhs.GetValue()) && lhs.GetUnitOfMeasure() == rhs.GetUnitOfMeasure();
}

std::string ToString(EUnitOfMeasure unit) {
    switch (unit) {
        case EUnitOfMeasure::Milligrams : {
            return "мг";
        }
        case EUnitOfMeasure::Gram : {
            return "г";
        }
        case EUnitOfMeasure::Milliliters : {
            return "мл";
        }
        case EUnitOfMeasure::Liters : {
            return "л";
        }
        default: {
            return "unknown";
        }
    }
}
