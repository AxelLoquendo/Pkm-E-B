#ifndef GUARD_CONSTANTS_MUGSHOTS_H
#define GUARD_CONSTANTS_MUGSHOTS_H

// IDs para los scripts
#define MUGSHOT_KAEL_NORMAL  0
#define MUGSHOT_KAEL_HAPPY   1
#define MUGSHOT_KAEL_SAD     2
#define MUGSHOT_KAEL_ANGRY   3
#define MUGSHOT_KAIDA_NORMAL 4
#define MUGSHOT_KAIDA_HAPPY  5
#define MUGSHOT_KAIDA_SAD    6
#define MUGSHOT_KAIDA_ANGRY  7

// Prototipos de las funciones en mugshot.c
void DrawMugshotByID(u16 mugshotId);
void ClearMugshot(void);

struct ScriptContext;

// Prototipos de los COMANDOS NATIVOS para scrcmd.c
bool8 ScrCmd_showmugshot(struct ScriptContext *ctx);
bool8 ScrCmd_hidemugshot(struct ScriptContext *ctx);

#endif