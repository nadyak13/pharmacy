#pragma once

#include <string>
#include <sstream>
#include "date.h"
#include "dose.h"
#include <map>

constexpr size_t DAYS_FOR_CUTPRICE = 30;

enum class EMedType {
    Tablets = 0,
    Spray = 1,
    Suspension = 2,
    Solution = 3,
    Drops = 4,
    Powder = 5,
    Unknown = 6
};

std::string ToString(EMedType medType);

enum class EMedGroup {
    Homeopathy = 0,
    CardiovascularAgent = 1,
    Antibiotic = 2,
    Antiviral = 3,
    Anesthetic = 4,
    Unknown = 5
};

std::string ToString(EMedGroup medType);

struct TMedicamentId {
    std::string MedName;
    EMedType Type;
    TDose Dose;
};

namespace std {
    template <>
    struct hash<TMedicamentId> {
        size_t operator()(const TMedicamentId &medId) const;
    };
}

bool operator<(const TMedicamentId& lhs, const TMedicamentId& rhs);

bool operator==(const TMedicamentId& lhs, const TMedicamentId& rhs);

class TMedicamentParty {
public:
    TMedicamentParty();

    TMedicamentParty(size_t count, TDate dateOfManufacture, TDate dateOfExpiration);

    size_t GetCount() const;

    void ReduceCount(size_t count);

    TDate GetDateOfManufacture() const;

    TDate GetDateOfExpiration() const;

private:
    size_t Count;
    TDate DateOfManufacture;
    TDate DateOfExpiration;
};

class TMedicamentInfo {
public:
    TMedicamentInfo();

    TMedicamentInfo(EMedGroup group, double tradePrice, size_t storageLife, size_t updateCount, size_t count = 0, std::map<TDate, TMedicamentParty> parties = {});

    double GetTradePrice() const;

    double DoBuy(size_t count, double marginPercentage, TDate curDay, double discount, size_t& realCount);

    EMedGroup GetGroup() const;

    std::map<TDate, TMedicamentParty> GetParties() const;

    TMedicamentParty GetFirstParty() const;

    double RemoveFirstParty();

    void AddParty(const TMedicamentParty& party);

    size_t GetCount() const;

    size_t GetStorageLife() const;

    size_t GetUpdateCount() const;

    void SetCount(size_t newCount);

    bool HasParties() const;

private:
    EMedGroup Group;
    double TradePrice;
    size_t StorageLife;
    size_t UpdateCount;
    size_t Count;
    std::map<TDate, TMedicamentParty> Parties;
};
