#include "controls.hpp"

bool cntrl::isKeyPressed(char key)
{
    if(GetKeyState(key) & 0x8000)
        return true;
    return false;
}
