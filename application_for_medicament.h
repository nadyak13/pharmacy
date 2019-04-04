#include <string>
#include "date.h"
#include "medicament.h"

class TApplicationForMedicament {
public:
    TApplicationForMedicament(const TMedicamentId& medName, size_t count, TDate executionDate);

    TMedicamentId GetMedId() const;

    size_t GetCount() const;

    TDate GetExecutionDate() const;

private:
    TMedicamentId MedId;
    size_t Count;
    TDate ExecutionDate;
};

bool operator<(const TApplicationForMedicament& lhs, const TApplicationForMedicament& rhs);