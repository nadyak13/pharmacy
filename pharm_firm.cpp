#include "pharm_firm.h"

#include <iostream>

TPharmFirm::TPharmFirm()
    : Dist(1, 3)
{}

void TPharmFirm::CreateApplication(const TMedicamentId& medId, size_t count) {
    TDate executionDate(TModelGenerator::Instance().GetCurrentDay() + Dist(RandGen));
    Applications.insert(TApplicationForMedicament(medId, count, executionDate));
}

std::set<TApplicationForMedicament> TPharmFirm::GetNotProcessedApplications() {
    return Applications;
}

std::set<TApplicationForMedicament> TPharmFirm::ProcessApplications() {
    std::set<TApplicationForMedicament> completedApplications;
    for (const auto& application : Applications) {
        if (application.GetExecutionDate() == TModelGenerator::Instance().GetCurrentDay()) {
            completedApplications.insert(application);
        }
    }
    for (const auto& application : completedApplications) {
        Applications.erase(Applications.find(application));
    }
    return completedApplications;
}

void TPharmFirm::Clear() {
    Applications.clear();
}

void TPharmFirm::PrintApplications() const {
    std::cout << "Applications:" << std::endl;
    for (const auto& application : Applications) {
        std::cout << application.GetMedId().MedName << " : " <<
            application.GetCount() << ", EXEC DATE: " << application.GetExecutionDate().GetDaysFromStart() << std::endl;
    }
}
