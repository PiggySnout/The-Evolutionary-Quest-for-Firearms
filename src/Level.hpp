#pragma once
#include "Species.hpp"
#include <raylib.h>
class Level{
    public:

    Level(const Species S, int mob_cap, int MinGold, int MaxGold, int MinXP, int MaxXP, int Npc_evo_level);


    int getNpcGoldDrop() const;
    int getNpcXpDrop() const;

    int getMob_cap() const;

    int getNpc_evo_level() const;
    Species getNpctype() const;

    private:

    const int mob_cap;
    const Species NpcType;

    const int Min_Npc_Gold_Drop;
    const int Max_Npc_Gold_Drop;

    const int Min_Npc_Xp_Drop;
    const int Max_Npc_Xp_Drop;

    const int Npc_evo_level;
};