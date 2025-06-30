// sampuix.inc
// Version: 1.0
// Author: PrizDC
// Credits: PrizDC
// Description: Basic modern UI system using ShowPlayerDialog for SA-MP

#if defined _sampuix_included
    #endinput
#endif
#define _sampuix_included

#include <a_samp>

#define MAX_UIX_FORMS 256

enum UIX_FORM {
    uix_playerid,
    uix_dialogid,
    uix_callback[32]
};

new UIX_Forms[MAX_UIX_FORMS][UIX_FORM];
new UIX_DialogCounter = 6000;

forward UIX_Internal_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);

// Creates a UIX form
public UIX_CreateForm(playerid, title[], message[], buttons[], const callbackFunc[])
{
    new did;
    did = UIX_DialogCounter;
    UIX_DialogCounter++;
    if (UIX_DialogCounter > 64999)
        UIX_DialogCounter = 6000;

    new i = 0;
    while (i < MAX_UIX_FORMS)
    {
        if (!UIX_Forms[i][uix_dialogid])
        {
            UIX_Forms[i][uix_playerid] = playerid;
            UIX_Forms[i][uix_dialogid] = did;
            format(UIX_Forms[i][uix_callback], 32, callbackFunc);
            break;
        }
        i++;
    }

    if (i == MAX_UIX_FORMS) return -1;

    ShowPlayerDialog(playerid, did, DIALOG_STYLE_MSGBOX, title, message, buttons, "");
    return did;
}

// Main dialog handler
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    new i;
    for (i = 0; i < MAX_UIX_FORMS; ++i)
    {
        if (UIX_Forms[i][uix_dialogid] == dialogid)
        {
            if (UIX_Forms[i][uix_playerid] == playerid)
            {
                CallLocalFunction(UIX_Forms[i][uix_callback], "dd", playerid, response);
                UIX_Forms[i][uix_dialogid] = 0;
                break;
            }
        }
    }
    return 0;
}

#define UIX_BUTTONS(%0,%1,%2) (%0 #\0 %1 #\0 %2)
