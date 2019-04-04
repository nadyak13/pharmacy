#include "application_for_medicament.h"

TApplicationForMedicament::TApplicationForMedicament(const TMedicamentId& medId, size_t count, TDate executionDate)
    : MedId(medId)
    , Count(count)
    , ExecutionDate(executionDate)
{}

TMedicamentId TApplicationForMedicament::GetMedId() const {
    return MedId;
}

size_t TApplicationForMedicament::GetCount() const {
    return Count;
}

TDate TApplicationForMedicament::GetExecutionDate() const {
    return ExecutionDate;
}

bool operator<(const TApplicationForMedicament& lhs, const TApplicationForMedicament& rhs) {
    if (!(lhs.GetExecutionDate() == rhs.GetExecutionDate())) {
        return lhs.GetExecutionDate() < rhs.GetExecutionDate();
    }
    return lhs.GetMedId() < rhs.GetMedId();
}