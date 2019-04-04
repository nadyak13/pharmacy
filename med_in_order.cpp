#include "med_in_order.h"

TMedInOrder::TMedInOrder(const TMedicamentId& medId, size_t count)
    : MedId(medId), Count(count)
{}

TMedicamentId TMedInOrder::GetMedId() const {
    return MedId;
}

size_t TMedInOrder::GetCount() const {
    return Count;
}

void TMedInOrder::SetCount(size_t count) {
    Count = count;
}
