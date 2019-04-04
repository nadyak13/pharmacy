#include "medicament_warehouse.h"

TMedicamentWarehouse::TMedicamentWarehouse()
{}

void TMedicamentWarehouse::Init(const std::unordered_map<TMedicamentId, TMedicamentInfo>& medicaments,
                                std::shared_ptr<TPharmFirm> pharmFirm) {
    Medicaments = medicaments;
    PharmFirm = pharmFirm;
}

std::unordered_map<TMedicamentId, TMedicamentInfo> TMedicamentWarehouse::GetMedicaments() const {
    return Medicaments;
}

TMedicamentInfo& TMedicamentWarehouse::GetMedicamentInfo(const TMedicamentId& medId) {
    return Medicaments[medId];
}

double TMedicamentWarehouse::WriteOffOverdue() {
    double writtenOffCost = 0;
    for (auto& med : Medicaments) {
        if (med.second.HasParties() && med.second.GetFirstParty().GetDateOfExpiration() < TModelGenerator::Instance().GetCurrentDay()) {
            writtenOffCost += med.second.RemoveFirstParty();
        }
    }
    return writtenOffCost;
}

void TMedicamentWarehouse::HandleCompletedApplications(const std::set<TApplicationForMedicament>& applications) {
    for (const auto& application : applications) {
        const TDate& curDay = TModelGenerator::Instance().GetCurrentDay();
        const TMedicamentId& medId = application.GetMedId();
        Medicaments[medId].AddParty(TMedicamentParty(application.GetCount(), curDay, curDay + Medicaments[medId].GetStorageLife()));
        Medicaments[medId].SetCount(Medicaments[medId].GetCount() + application.GetCount());
        MedicamentsInApplications.erase(medId);
    }
}

void TMedicamentWarehouse::CheckMedicamentsCount() {
    for (const auto& med : Medicaments) {
        if (med.second.GetCount() <= med.second.GetUpdateCount()
                && MedicamentsInApplications.find(med.first) == MedicamentsInApplications.end()) {
            PharmFirm->CreateApplication(med.first, med.second.GetUpdateCount() * COEF_FOR_COUNT_IN_APPLICATION);
            MedicamentsInApplications.insert(med.first);
        }
    }
}
