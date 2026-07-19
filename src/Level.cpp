#include "Level.hpp"

Level::Level(const Species S, int mob_cap, int MinGold, int MaxGold, int MinXP, int MaxXP) : 

NpcType(S),
mob_cap(mob_cap),
Min_Npc_Gold_Drop(MinGold),
Max_Npc_Gold_Drop(MaxGold),
Min_Npc_Xp_Drop(MinXP),
Max_Npc_Xp_Drop(MaxXP)

{}

int Level::getNpcGoldDrop() const{
    return GetRandomValue(Max_Npc_Gold_Drop, Min_Npc_Gold_Drop);
}
int Level::getNpcXpDrop() const{
    return GetRandomValue(Max_Npc_Xp_Drop, Min_Npc_Xp_Drop);
}

int Level::getMob_cap() const{
    return mob_cap;
}
Species Level::getNpctype() const{
    return NpcType;
}