#include "global.h"
#include "constants/multijugador.h"
#include "link.h"
#include "field_player_avatar.h"
#include "event_object_movement.h"
#include "constants/event_objects.h"

bool8 gCoopModeActive = FALSE;

void ToggleGhostMultiplayer(void)
{
    gCoopModeActive = !gCoopModeActive;
}

void UpdateGhostMultiplayer(void)
{
    u16 sendData[4];
    u16 recvData[4];
    u8 partnerId;
    u8 ghostSpriteId;

    if (!gCoopModeActive)
        return;

    // Solo procedemos si el cable está conectado y LISTO para enviar
    if ((gLinkStatus & LINK_STAT_CONN_ESTABLISHED) && IsLinkTaskFinished())
    {
        sendData[0] = gSaveBlock1Ptr->pos.x;
        sendData[1] = gSaveBlock1Ptr->pos.y;
        sendData[2] = gObjectEvents[gPlayerAvatar.objectEventId].facingDirection;
        sendData[3] = 0; 

        SendBlock(0, sendData, sizeof(sendData));
    }

    partnerId = GetMultiplayerId() ^ 1;

    if (GetBlockReceivedStatus() & (1 << partnerId))
    {
        memcpy(recvData, gBlockRecvBuffer[partnerId], sizeof(recvData));

        // LOCALID_GHOST debe estar definido como 15 en tu .h o usar el ID directo
        ghostSpriteId = GetObjectEventIdByLocalIdAndMap(LOCALID_GHOST, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);

        if (ghostSpriteId != OBJECT_EVENTS_COUNT)
        {
            struct ObjectEvent *ghost = &gObjectEvents[ghostSpriteId];
            
            // EL AJUSTE +7: En el motor de Emerald, las coordenadas de red y de mapa
            // tienen un desfase. Sin esto, el NPC existe pero está fuera de la pantalla.
            u16 targetX = recvData[0] + 7;
            u16 targetY = recvData[1] + 7;

            // Forzamos la posición inmediata
            ghost->currentCoords.x = targetX;
            ghost->currentCoords.y = targetY;
            ghost->initialCoords.x = targetX;
            ghost->initialCoords.y = targetY;
            
            ghost->invisible = FALSE;
            ObjectEventSetHeldMovement(ghost, GetFaceDirectionAnimNum(recvData[2]));
        }
        
        // La función que encontraste en link.c para vaciar el buzón
        ResetBlockReceivedFlag(partnerId);
    }
}