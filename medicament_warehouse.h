#pragma once

#include "medicament.h"
#include "model_generator.h"
#include "computer_manager.h"
#include "pharm_firm.h"
#include <unordered_map>
#include <map>

constexpr size_t COEF_FOR_COUNT_IN_APPLICATION = 5;

class TPharmFirm;

class TMedicamentWarehouse {
public:
    TMedicamentWarehouse();

    void Init(const std::unordered_map<TMedicamentId, TMedicamentInfo>& medicaments, std::shared_ptr<TPharmFirm> pharmfirm);

    TMedicamentInfo& GetMedicamentInfo(const TMedicamentId& medId);

    double WriteOffOverdue();

    void HandleCompletedApplications(const std::set<TApplicationForMedicament>& applications);

    void CheckMedicamentsCount();

    std::unordered_map<TMedicamentId, TMedicamentInfo> GetMedicaments() const;

private:
    std::unordered_map<TMedicamentId, TMedicamentInfo> Medicaments;
    std::shared_ptr<TPharmFirm> PharmFirm;
    std::unordered_set<TMedicamentId> MedicamentsInApplications;
};
