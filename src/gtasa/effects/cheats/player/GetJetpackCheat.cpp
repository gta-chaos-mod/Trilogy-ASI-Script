#include "GetJetpackCheat.h"

GetJetpackCheat::GetJetpackCheat () : EffectPlaceholder ("cheat_get_jetpack") {}

void
GetJetpackCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CCheat::JetpackCheat ();
}
