#ifndef GUARD_CONSTANTS_MULTIJUGADOR_H
#define GUARD_CONSTANTS_MULTIJUGADOR_H

//#define OBJ_EVENT_ID_PLAYER_GHOST 2
//#define LOCALID_GHOST 2

struct GhostPacket
{
    s16 x;
    s16 y;
    u8 direction;
    u8 mapNum;
    u8 mapGroup;
};

// Declaramos las funciones para que overworld.c pueda verlas
void ToggleGhostMultiplayer(void);
void UpdateGhostMultiplayer(void);


#endif // GUARD_CONSTANTS_MULTIJUGADOR_H