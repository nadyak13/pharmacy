#pragma once

#include <unordered_set>
#include <string>
#include <vector>
#include <set>
#include <random>
#include <memory>

#include "application_for_medicament.h"
#include "model_generator.h"


class TPharmFirm {
public:
    TPharmFirm();

    void CreateApplication(const TMedicamentId &medName, size_t count);

    std::set<TApplicationForMedicament> ProcessApplications();
    std::set<TApplicationForMedicament> GetNotProcessedApplications();
    void Clear();

    void PrintApplications() const;

private:
    std::set<TApplicationForMedicament> Applications;
    std::mt19937 RandGen;
    std::uniform_int_distribution<size_t> Dist;
};
