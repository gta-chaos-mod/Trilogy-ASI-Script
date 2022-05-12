#include <MinHook.h>

struct MinHookInitialiser
{
    MinHookInitialiser ()
    {
        MH_Initialize ();
    }

    ~MinHookInitialiser ()
    {
        MH_Uninitialize ();
    }
} m_MinHook;
