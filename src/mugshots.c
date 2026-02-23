#include "global.h"
#include "blit.h"
#include "window.h"
#include "menu.h"
#include "palette.h"
#include "event_data.h"
#include "constants/mugshots.h"

#define MUGSHOT_PALETTE_NUM 13

struct Mugshot {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    const u32* image;
    const u16* palette;
};

// ========= RECURSOS GRÁFICOS (Fusión) =========
//static const u32 sImg_Axel_Sad[] = INCBIN_U32("graphics/mugshots/axel/axel_sad.4bpp.smol");
//static const u16 sPal_Axel_Sad[] = INCBIN_U16("graphics/mugshots/axel/axel_sad.gbapal");

static const u32 sImg_Kael_Normal[] = INCBIN_U32("graphics/mugshots/kael_normal.4bpp.smol");
static const u16 sPal_Kael_Normal[] = INCBIN_U16("graphics/mugshots/kael_normal.gbapal");
static const u32 sImg_Kael_Happy[] = INCBIN_U32("graphics/mugshots/kael_happy.4bpp.smol");
static const u16 sPal_Kael_Happy[] = INCBIN_U16("graphics/mugshots/kael_happy.gbapal");
static const u32 sImg_Kael_Sad[] = INCBIN_U32("graphics/mugshots/kael_sad.4bpp.smol");
static const u16 sPal_Kael_Sad[] = INCBIN_U16("graphics/mugshots/kael_sad.gbapal");
static const u32 sImg_Kael_Angry[] = INCBIN_U32("graphics/mugshots/kael_angry.4bpp.smol");
static const u16 sPal_Kael_Angry[] = INCBIN_U16("graphics/mugshots/kael_angry.gbapal");

static const u32 sImg_Kaida_Normal[] = INCBIN_U32("graphics/mugshots/kaida_normal.4bpp.smol");
static const u16 sPal_Kaida_Normal[] = INCBIN_U16("graphics/mugshots/kaida_normal.gbapal");
static const u32 sImg_Kaida_Happy[] = INCBIN_U32("graphics/mugshots/kaida_happy.4bpp.smol");
static const u16 sPal_Kaida_Happy[] = INCBIN_U16("graphics/mugshots/kaida_happy.gbapal");
static const u32 sImg_Kaida_Sad[] = INCBIN_U32("graphics/mugshots/kaida_sad.4bpp.smol");
static const u16 sPal_Kaida_Sad[] = INCBIN_U16("graphics/mugshots/kaida_sad.gbapal");
static const u32 sImg_Kaida_Angry[] = INCBIN_U32("graphics/mugshots/kaida_angry.4bpp.smol");
static const u16 sPal_Kaida_Angry[] = INCBIN_U16("graphics/mugshots/kaida_angry.gbapal");

// ========= TABLA DE DATOS =========
static const struct Mugshot sMugshots[] = {
    [MUGSHOT_KAEL_NORMAL] = {
        .x = 16,
        .y = 5,
        .width = 64,
        .height = 64,
        .image = sImg_Kael_Normal,
        .palette = sPal_Kael_Normal
    },
    [MUGSHOT_KAEL_HAPPY] = {
        .x = 16,
        .y = 5,
        .width = 64,
        .height = 64,
        .image = sImg_Kael_Happy,
        .palette = sPal_Kael_Happy
    },
    [MUGSHOT_KAEL_SAD] = {
        .x = 16,
        .y = 5,
        .width = 64,
        .height = 64,
        .image = sImg_Kael_Sad,
        .palette = sPal_Kael_Sad
    },
    [MUGSHOT_KAEL_ANGRY] = {
        .x = 16,
        .y = 5,
        .width = 64,
        .height = 64,
        .image = sImg_Kael_Angry,
        .palette = sPal_Kael_Angry
    },
    [MUGSHOT_KAIDA_NORMAL] = {
        .x = 16,
        .y = 5,
        .width = 64,
        .height = 64,
        .image = sImg_Kaida_Normal,
        .palette = sPal_Kaida_Normal
    },
    [MUGSHOT_KAIDA_HAPPY] = {
        .x = 16,
        .y = 5,
        .width = 64,
        .height = 64,
        .image = sImg_Kaida_Happy,
        .palette = sPal_Kaida_Happy
    },
    [MUGSHOT_KAIDA_SAD] = {
        .x = 16,
        .y = 5,
        .width = 64,
        .height = 64,
        .image = sImg_Kaida_Sad,
        .palette = sPal_Kaida_Sad
    },
    [MUGSHOT_KAIDA_ANGRY] = {
        .x = 16,
        .y = 5,
        .width = 64,
        .height = 64,
        .image = sImg_Kaida_Angry,
        .palette = sPal_Kaida_Angry
    },
};

static EWRAM_DATA u8 sMugshotWindow = 0;

void ClearMugshot(void) {
    if (sMugshotWindow != 0) {
        ClearStdWindowAndFrameToTransparent(sMugshotWindow - 1, 0);
        CopyWindowToVram(sMugshotWindow - 1, 3);
        RemoveWindow(sMugshotWindow - 1);
        sMugshotWindow = 0;
    }
}

static void DrawMugshotCore(const struct Mugshot* const mugshot, int x, int y) {
    struct WindowTemplate t;
    u8 windowId;
    
    if (sMugshotWindow != 0) ClearMugshot();
    
    // Configuración de la ventana basada en tiles (8x8 px)
    #if GAME_VERSION == VERSION_EMERALD
        SetWindowTemplateFields(&t, 0, x, y, mugshot->width / 8, mugshot->height / 8, MUGSHOT_PALETTE_NUM, 0x40);
    #else
        t = SetWindowTemplateFields(0, x, y, mugshot->width / 8, mugshot->height / 8, MUGSHOT_PALETTE_NUM, 0x40);
    #endif

    windowId = AddWindow(&t);
    sMugshotWindow = windowId + 1;
    
    LoadPalette(mugshot->palette, 16 * MUGSHOT_PALETTE_NUM, 32);
    CopyToWindowPixelBuffer(windowId, (const void*)mugshot->image, 0, 0);
    PutWindowRectTilemap(windowId, 0, 0, mugshot->width / 8, mugshot->height / 8);
    CopyWindowToVram(windowId, 3);
}

// Función principal para callnative
void DrawMugshotByID(u16 mugshotId) // Ahora acepta un parámetro
{
    if (mugshotId < ARRAY_COUNT(sMugshots)) {
        DrawMugshotCore(&sMugshots[mugshotId], sMugshots[mugshotId].x, sMugshots[mugshotId].y);
    }
}
