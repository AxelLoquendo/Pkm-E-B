PradoNatal_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PradoNatal_OnTransition
	.byte 0

PradoNatal_OnTransition:
	setflag FLAG_VISITED_PRADO_NATAL
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, PradoNatal_SetRivalMay    @ Si eres chico, rival es May
    goto_if_eq VAR_RESULT, FEMALE, PradoNatal_SetRivalBrendan @ Si eres chica, rival es Brendan
    end

PradoNatal_SetRivalMay:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
    end

PradoNatal_SetRivalBrendan:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
    end

