#pragma once

#include <string>
#include "medicament.h"
#include <optional>

class TMedInOrder {
public:
    TMedInOrder(const TMedicamentId& medId, size_t count);

    TMedicamentId GetMedId() const;

    size_t GetCount() const;

    void SetCount(size_t count);

private:
    TMedicamentId MedId;
    size_t Count;
};
