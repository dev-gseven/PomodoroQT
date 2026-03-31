#include "systemsound.h"

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
void playSystemSound_macOS();
#endif

SystemSound::SystemSound()
{
}

void SystemSound::playSystemSound()
{
#ifdef __APPLE__
    playSystemSound_macOS();
#endif
#ifdef _WIN32
    MessageBeep(MB_OK);
//#elif
//    qDebug() << "Linux";
#endif
}
