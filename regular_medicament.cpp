#include "regular_medicament.h"

TRegularMedicament::TRegularMedicament(const TMedicamentId& medName, size_t period, size_t count)
    : MedName(medName)
    , Period(period)
    , Count(count)
{}

TMedicamentId TRegularMedicament::GetMedName() const {
    return MedName;
}

size_t TRegularMedicament::GetPeriod() const {
    return Period;
}

size_t TRegularMedicament::GetCount() const {
    return Count;
}