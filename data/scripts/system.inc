EventScript_CoopMultiplayerSave:
    msgbox Text_QuieresConectarte, MSGBOX_YESNO
    compare VAR_RESULT, NO
    goto_if_eq EventScript_CancelCoop
    
    // El comando 'call Native_DoSaveGame' o similar inicia el guardado oficial
    special SaveGame // Este comando gestiona todo el diálogo de guardado
    waitstate // ESTO ES CLAVE: Espera a que el guardado termine de verdad
    
    // Una vez guardado, llamamos a tu función de C
    special ActivateCoopMode 
    release
    end

EventScript_CancelCoop:
    release
    end

Text_QuieresConectarte:
    .string "¿Deseas guardar la partida para\n"
    .string "activar el modo CO-OP?$"