#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

template <eWeaponType weaponType> class RecruitAnyoneEffect : public EffectBase
{
    static constexpr unsigned int RECRUIT_ANYONE_CHEAT_ADDR = 0x96917C;
    bool                         *address                   = nullptr;

public:
    RecruitAnyoneEffect ()
    {
        address = reinterpret_cast<bool *> (RECRUIT_ANYONE_CHEAT_ADDR);
    }

    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_CPed_GiveWeaponWhenJoiningGang,
                          void (CPed *), 0x5e8be0);
    }

    static void
    Hooked_CPed_GiveWeaponWhenJoiningGang (auto &&cb, CPed *self)
    {
        if (!self) return;

        self->GiveDelayedWeapon (weaponType, 500);
        const auto *info = CWeaponInfo::GetWeaponInfo (weaponType, 1);
        self->SetCurrentWeapon (info->m_nSlot);
    }

    void
    OnEnd (EffectInstance *instance) override
    {
        if (address) *address = false;
    }

    void
    OnTick (EffectInstance *instance) override
    {
        if (address) *address = true;
    }
};

using RecruitAnyonePistol       = RecruitAnyoneEffect<WEAPONTYPE_PISTOL>;
using RecruitAnyoneDeserEagle   = RecruitAnyoneEffect<WEAPONTYPE_DESERT_EAGLE>;
using RecruitAnyoneSuperShotgun = RecruitAnyoneEffect<WEAPONTYPE_SPAS12>;
using RecruitAnyoneMinigun      = RecruitAnyoneEffect<WEAPONTYPE_MINIGUN>;
using RecruitAnyoneSpray        = RecruitAnyoneEffect<WEAPONTYPE_SPRAYCAN>;

DEFINE_EFFECT (RecruitAnyonePistol, "effect_recruit_anyone_9mm",
               GROUP_NPC_SPAWNS | GROUP_NPCS_RECRUIT);
DEFINE_EFFECT (RecruitAnyoneDeserEagle, "effect_recruit_anyone_desert_eagle",
               GROUP_NPC_SPAWNS | GROUP_NPCS_RECRUIT);
DEFINE_EFFECT (RecruitAnyoneSuperShotgun, "effect_recruit_anyone_super_shotgun",
               GROUP_NPC_SPAWNS | GROUP_NPCS_RECRUIT);
DEFINE_EFFECT (RecruitAnyoneMinigun, "effect_recruit_anyone_minigun",
               GROUP_NPC_SPAWNS | GROUP_NPCS_RECRUIT);
DEFINE_EFFECT (RecruitAnyoneSpray, "effect_recruit_anyone_spray",
               GROUP_NPC_SPAWNS | GROUP_NPCS_RECRUIT);