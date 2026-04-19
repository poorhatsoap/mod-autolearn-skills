#include "Player.h"
#include "ScriptMgr.h"
#include "Config.h"

#include <unordered_map>
#include <vector>

class AutoLearnSkills : public PlayerScript
{
public:
    AutoLearnSkills() : PlayerScript("AutoLearnSkills") { }

    void OnPlayerLevelChanged(Player* player, uint8 /*oldLevel*/) override
    {
        if (!sConfigMgr->GetOption<bool>("AutoLearnSkills.Enable", true))
            return;

        HandleLevelUp(player);
    }

private:

    static const std::unordered_map<uint8, std::vector<uint32>> classWeaponSkills;
    static const std::vector<uint32> combatSkillIds;

    void HandleLevelUp(Player* player)
    {
        LearnWeaponSkills(player);
        LearnRidingAndMounts(player);
        MaxCombatSkills(player);
    }

    void MaxCombatSkills(Player* player)
    {
        if (!sConfigMgr->GetOption<bool>("AutoLearnSkills.MaxWeaponSkills", true))
            return;

        uint32 maxSkill = player->GetLevel() * 5;

        for (uint32 skillId : combatSkillIds)
        {
            if (player->HasSkill(skillId))
                player->SetSkill(skillId, 1, maxSkill, maxSkill);
        }
    }

    void LearnWeaponSkills(Player* player)
    {
        if (!sConfigMgr->GetOption<bool>("AutoLearnSkills.AutoLearnWeaponSkills", true))
            return;

        auto it = classWeaponSkills.find(player->getClass());
        if (it == classWeaponSkills.end())
            return;

        for (uint32 spellId : it->second)
            if (!player->HasSpell(spellId))
                player->learnSpell(spellId);
    }

    void LearnRidingAndMounts(Player* player)
    {
        if (!sConfigMgr->GetOption<bool>("AutoLearnSkills.AutoLearnRiding", true))
            return;

        uint8 level = player->GetLevel();

        bool apprentice       = sConfigMgr->GetOption<bool>("AutoLearnSkills.Riding.Apprentice", true);
        bool grantApprentice  = sConfigMgr->GetOption<bool>("AutoLearnSkills.Riding.GrantApprenticeMount", true);

        bool journeyman       = sConfigMgr->GetOption<bool>("AutoLearnSkills.Riding.Journeyman", false);
        bool grantJourneyman  = sConfigMgr->GetOption<bool>("AutoLearnSkills.Riding.GrantJourneymanMount", false);

        bool expert           = sConfigMgr->GetOption<bool>("AutoLearnSkills.Riding.Expert", false);
        bool grantExpert      = sConfigMgr->GetOption<bool>("AutoLearnSkills.Riding.GrantExpertMount", false);

        bool artisan          = sConfigMgr->GetOption<bool>("AutoLearnSkills.Riding.Artisan", false);
        bool grantArtisan     = sConfigMgr->GetOption<bool>("AutoLearnSkills.Riding.GrantArtisanMount", false);

        bool coldWeather      = sConfigMgr->GetOption<bool>("AutoLearnSkills.Riding.ColdWeather", false);

        // Apprentice Riding (20)
        if (apprentice && level >= 20 && !player->HasSpell(33388))
        {
            player->learnSpell(33388);
            if (grantApprentice)
                GiveSlowGroundMounts(player);
        }

        // Journeyman Riding (40)
        if (journeyman && level >= 40 && !player->HasSpell(33391))
        {
            player->learnSpell(33391);
            if (grantJourneyman)
                GiveEpicGroundMounts(player);
        }

        // Expert Riding (60)
        if (expert && level >= 60 && !player->HasSpell(34090))
        {
            player->learnSpell(34090);
            if (grantExpert)
                GiveBasicFlyingMount(player);
        }

        // Artisan Riding (70)
        if (artisan && level >= 70 && !player->HasSpell(34091))
        {
            player->learnSpell(34091);
            if (grantArtisan)
                GiveEpicFlyingMount(player);
        }

        // Cold Weather Flying (77)
        if (coldWeather && level >= 77 && !player->HasSpell(54197))
        {
            player->learnSpell(54197);
        }
    }

    void GiveSlowGroundMounts(Player* player)
    {
        std::vector<uint32> mounts;

        switch (player->getRace())
        {
            case RACE_HUMAN:         mounts = {458, 472, 6648, 16082}; break;
            case RACE_DWARF:         mounts = {6777, 6898, 6899}; break;
            case RACE_NIGHTELF:      mounts = {8394, 10789, 10793}; break;
            case RACE_GNOME:         mounts = {10969, 10873, 10967}; break;
            case RACE_DRAENEI:       mounts = {34406, 35710, 35711}; break;
            case RACE_ORC:           mounts = {580, 6653, 6654}; break;
            case RACE_TROLL:         mounts = {8395, 10796, 10799}; break;
            case RACE_TAUREN:        mounts = {6899, 18989, 18990}; break;
            case RACE_UNDEAD_PLAYER: mounts = {17462, 17463, 17464}; break;
            case RACE_BLOODELF:      mounts = {34795, 35020, 35022}; break;
            default: break;
        }

        for (uint32 spellId : mounts)
            if (!player->HasSpell(spellId))
                player->learnSpell(spellId);
    }

    void GiveEpicGroundMounts(Player* player)
    {
        std::vector<uint32> mounts;

        switch (player->getRace())
        {
            case RACE_HUMAN:         mounts = {23227, 23228, 23229}; break;
            case RACE_DWARF:         mounts = {23238, 23239, 23240}; break;
            case RACE_NIGHTELF:      mounts = {23221, 23219, 23220}; break;
            case RACE_GNOME:         mounts = {23223, 23222, 23224}; break;
            case RACE_DRAENEI:       mounts = {35713, 35712, 35714}; break;
            case RACE_ORC:           mounts = {23250, 23251}; break;
            case RACE_TROLL:         mounts = {23241, 23242, 23243}; break;
            case RACE_TAUREN:        mounts = {23248, 23249}; break;
            case RACE_UNDEAD_PLAYER: mounts = {17481}; break;
            case RACE_BLOODELF:      mounts = {35025, 35027}; break;
            default: break;
        }

        for (uint32 spellId : mounts)
            if (!player->HasSpell(spellId))
                player->learnSpell(spellId);
    }

    void GiveBasicFlyingMount(Player* player)
    {
        uint32 spellId = (player->GetTeamId() == TEAM_ALLIANCE)
            ? 32235  // Brown Gryphon
            : 32243; // Tawny Wind Rider

        if (!player->HasSpell(spellId))
            player->learnSpell(spellId);
    }

    void GiveEpicFlyingMount(Player* player)
    {
        uint32 spellId = (player->GetTeamId() == TEAM_ALLIANCE)
            ? 32242  // Swift Blue Gryphon
            : 32246; // Swift Green Wind Rider

        if (!player->HasSpell(spellId))
            player->learnSpell(spellId);
    }
};

// ---------------------------
// Static mappings
// ---------------------------

const std::unordered_map<uint8, std::vector<uint32>> AutoLearnSkills::classWeaponSkills =
{
    { CLASS_WARRIOR,      {196,197,198,199,200,201,202,227,264,266,5011,1180,15590} },
    { CLASS_PALADIN,      {198,199,200,201,202,227} },
    { CLASS_HUNTER,       {196,197,200,227,264,266,5011} },
    { CLASS_ROGUE,        {196,201,1180,15590} },
    { CLASS_SHAMAN,       {196,197,198,199,200,227} },
    { CLASS_DRUID,        {198,200,227,1180,15590} },
    { CLASS_DEATH_KNIGHT, {198,199,200,201,202,227} },
    { CLASS_PRIEST,       {198,227,1180} }
};

const std::vector<uint32> AutoLearnSkills::combatSkillIds =
{
    43, 44, 45, 46, 54, 55, 95, 136, 160,
    162, 172, 173, 176, 226, 229, 473
};

void AddSC_AutoLearnSkills()
{
    new AutoLearnSkills();
}
