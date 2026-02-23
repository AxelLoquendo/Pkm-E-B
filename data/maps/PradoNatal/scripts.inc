PradoNatal_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, PradoNatal_OnTransition
    map_script MAP_SCRIPT_ON_FRAME_TABLE, PradoNatal_OnFrameTable
    .byte 0

PradoNatal_OnTransition:
    setflag FLAG_VISITED_PRADO_NATAL
    checkplayergender
    goto_if_eq VAR_RESULT, MALE, PradoNatal_SetRivalMay
    goto_if_eq VAR_RESULT, FEMALE, PradoNatal_SetRivalBrendan
    end

PradoNatal_OnFrameTable:
    map_script_2 VAR_TEMP_0, 0, PradoNatal_IntroEscena
    .2byte 0

PradoNatal_IntroEscena:
    lockall              @ Bloquea al jugador
    setvar VAR_TEMP_0, 1 @ Evita que el script se repita
    
    checkplayergender
    goto_if_eq VAR_RESULT, MALE, PradoNatal_IntroKaida
    goto_if_eq VAR_RESULT, FEMALE, PradoNatal_IntroKael
    end

PradoNatal_IntroKaida:
    showmugshot MUGSHOT_KAIDA_NORMAL
    msgbox PradoNatal_Texto_Kaida, MSGBOX_DEFAULT
    hidemugshot
    releaseall
    end

PradoNatal_IntroKael:
    showmugshot MUGSHOT_KAEL_NORMAL
    msgbox PradoNatal_Texto_Kael, MSGBOX_DEFAULT
    hidemugshot
    releaseall
    end

PradoNatal_SetRivalMay:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
    end

PradoNatal_SetRivalBrendan:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
    end

PradoNatal_Texto_Kaida:
    .string "KAIDA: ¡Vaya, por fin llegas!\n"
    .string "Prado Natal es hermoso, ¿verdad?$"

PradoNatal_Texto_Kael:
    .string "KAEL: Ey, te estaba esperando.\n"
    .string "Este lugar tiene un aire especial.$"
