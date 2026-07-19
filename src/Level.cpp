#include "Level.hpp"

Level::Level(const Species S, int mob_cap, int MinGold, int MaxGold, int MinXP, int MaxXP, int Npc_evo_level) : 

NpcType(S),
mob_cap(mob_cap),
Min_Npc_Gold_Drop(MinGold),
Max_Npc_Gold_Drop(MaxGold),
Min_Npc_Xp_Drop(MinXP),
Max_Npc_Xp_Drop(MaxXP),
Npc_evo_level(Npc_evo_level)

{}

int Level::getNpcGoldDrop() const{
    return GetRandomValue(Min_Npc_Gold_Drop, Max_Npc_Gold_Drop);
}
int Level::getNpcXpDrop() const{
    return GetRandomValue(Min_Npc_Xp_Drop, Max_Npc_Xp_Drop);
}

int Level::getMob_cap() const{
    return mob_cap;
}
Species Level::getNpctype() const{
    return NpcType;
}
int Level::getNpc_evo_level() const{
    return Npc_evo_level;
}