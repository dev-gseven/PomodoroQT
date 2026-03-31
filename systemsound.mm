#ifdef __APPLE__
#include "systemsound.h"
#import <Cocoa/Cocoa.h>

// TODO: testar para ver se funciona sem SystemSOund.

void playSystemSound_macOS() {
    NSBeep();
}

#endif
