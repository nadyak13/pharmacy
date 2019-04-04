#pragma once

#include <string>
#include "medicament.h"

class TRegularMedicament {
public:
    TRegularMedicament(const TMedicamentId& medName, size_t period, size_t count);

    TMedicamentId GetMedName() const;

    size_t GetPeriod() const;

    size_t GetCount() const;
    
private:
    TMedicamentId MedName;
    size_t Period;
    size_t Count;
};