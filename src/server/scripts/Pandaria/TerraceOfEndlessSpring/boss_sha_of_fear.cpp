/*
 * Copyright (C) 2012-2013 JadeCore <http://www.pandashan.com/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "GameObjectAI.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "terrace_of_endless_spring.h"

enum eShaOfFearSpells
{
    // Sha of Fear
    SPELL_BERSERK                   = 47008,
    SPELL_REACHING_ATTACK           = 119775,
    SPELL_EERIE_SKULL               = 119519,
    SPELL_ENERGY_TO_ZERO            = 119417,
    SPELL_BREATH_OF_FEAR            = 119414,
    SPELL_THRASH_AURA               = 131996,
    SPELL_THRASH_EXTRA_ATTACKS      = 131994,
    SPELL_CONJURE_TERROR_SPAWN_TICK = 119108,
    // 4 spells for spawn, cauz' of different spawn coordinates
    SPELL_CONJURE_TERROR_SPAWN_01   = 119312,
    SPELL_CONJURE_TERROR_SPAWN_02   = 119370,
    SPELL_CONJURE_TERROR_SPAWN_03   = 119371,
    SPELL_CONJURE_TERROR_SPAWN_04   = 119372,
    SPELL_OMINOUS_CACKLE_CAST       = 119593,
    SPELL_OMINOUS_CACKLE_TRANSFORM  = 129147,
    SPELL_TELEPORT_TO_SHRINE_1      = 129234,
    SPELL_TELEPORT_TO_SHRINE_2      = 129235,
    SPELL_TELEPORT_TO_SHRINE_3      = 129236,

    // Heroic Mode
    SPELL_LEI_SHIS_HOPE             = 129368,
    SPELL_DREAD_EXPANSE_AURA        = 120289,
    SPELL_FADING_LIGHT              = 129378,
    SPELL_CHAMPION_OF_LIGHT_HEROIC  = 120268,
    SPELL_DREAD_THRASH_AURA         = 132007,
    SPELL_DREAD_THRASH_EXTRA_ATT    = 132000,
    SPELL_IMPLACABLE_STRIKE         = 120672,
    SPELL_NAKED_AND_AFRAID          = 120669,
    SPELL_HUDDLE_IN_TERROR          = 120629,
    SPELL_SUBMERGE_TRANSFORM        = 120455,
    SPELL_EMERGE_DAMAGE             = 120458,
    SPELL_EMERGE_STUN_ONE_SECOND    = 120475,

    // Other mobs
    SPELL_LIGHT_WALL                = 117865,
    SPELL_CHAMPION_OF_LIGHT         = 117866,
    SPELL_LIGHT_WALL_READY          = 117770,
    SPELL_LIGHT_WALL_VISUAL         = 107141,
    SPELL_FEARLESS                  = 118977,
    SPELL_WALL_OF_LIGHT_BUFF        = 117999,
    SPELL_PENETRATING_BOLT          = 129075,
    SPELL_PENETRATING_BOLT_MISSILE  = 129077,
    SPELL_DARK_BULWARK              = 119083,
    SPELL_PURE_LIGHT_VISUAL         = 120216,
    SPELL_SHOT                      = 119862,
    SPELL_DEATH_BLOSSOM             = 119888,
    SPELL_DEATH_BLOSSOM_RAND_ARROW  = 119890,
    SPELL_DREAD_SPRAY               = 120047,
    SPELL_DREAD_SPRAY_STACKS        = 119983,
    SPELL_DREAD_SPRAY_FEAR_ROOT     = 119985,
    SPELL_DREAD_SPRAY_TRIGGERED     = 119958,
    SPELL_DREAD_SPRAY_VISUAL        = 119956,
    SPELL_SHA_GLOBE_SPAWN           = 129178,
    SPELL_SHA_GLOBE_PERIODIC_VISUAL = 129187,
    SPELL_SHA_GLOBE_HEAL_SUMMONER   = 129190,
    SPELL_SHA_CORRUPTION            = 120000,
    SPELL_ETERNAL_DARKNESS          = 120394,
    SPELL_GATHERING_SPEED           = 128419,
    SPELL_SHA_SPINES                = 120438
};

enum eShaOfFearEvents
{
    EVENT_CHECK_MELEE       = 1,
    EVENT_EERIE_SKULL       = 2,
    EVENT_CHECK_ENERGY      = 3,
    EVENT_FIRST_TERRORS     = 4,
    EVENT_PENETRATING_BOLT  = 5,
    EVENT_OMINOUS_CACKLE    = 6,
    EVENT_ENRAGE            = 7,
    EVENT_CHECK_GUARDIAN    = 8,
    EVENT_SHOT              = 9,
    EVENT_DEATH_BLOSSOM     = 10,
    EVENT_DREAD_SPRAY       = 11,
    EVENT_DESPAWN_SHA_GLOBE = 12,

    // Heroic
    EVENT_IMPLACABLE_STRIKE = 13,
    EVENT_NAKED_AND_AFRAID  = 14,
    EVENT_WATERSPOUT        = 15,
    EVENT_HUDDLE_IN_TERROR  = 16,
    EVENT_SUBMERGE          = 17,
    EVENT_GATHERING_SPEED   = 18
};

enum eShaOfFearActions
{
    ACTION_ACTIVATE_WALL_OF_LIGHT,
    ACTION_DESACTIVATE_WALL_OF_LIGHT,
    ACTION_SPAWN_TERROR,
    ACTION_ACTIVATE_SHRINE_1,
    ACTION_ACTIVATE_SHRINE_2,
    ACTION_ACTIVATE_SHRINE_3,
    ACTION_DESACTIVATE_SHRINE_1,
    ACTION_DESACTIVATE_SHRINE_2,
    ACTION_DESACTIVATE_SHRINE_3,
    ACTION_TRANSFERT_OF_LIGHT
};

enum eShaOfFearSays
{
    TALK_INTRO,
    TALK_AGGRO,
    TALK_BREATH_OF_FEAR,
    TALK_SLAY,
    TALK_HEROIC,
    TALK_SUBMERGE,
    TALK_HUDDLE
};

enum eEquipsId
{
    EQUIP_ID_GUARDIAN   = 72283
};

Player* GetChampionOfLight(Creature* me)
{
    if (!me)
        return NULL;

    Map::PlayerList const& playerList = me->GetMap()->GetPlayers();
    for (Map::PlayerList::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
        if (Player* player = itr->getSource())
            if (player->HasAura(SPELL_CHAMPION_OF_LIGHT))
                return player;

    return NULL;
}

Position spawnTerrorPos[4] =
{
    { -1052.588f, -2788.164f, 38.268f, 0.0f },
    { -983.4550f, -2787.942f, 38.269f, 0.0f },
    { -989.6860f, -2772.245f, 38.303f, 0.0f },
    { -1046.274f, -2772.215f, 38.303f, 0.0f }
};

Position shrinesPos[3] =
{
    { -832.076f,  -2745.400f, 31.678f, 0.0f }, // North
    { -1075.200f, -2577.820f, 15.852f, 0.0f }, // South/West
    { -1214.801f, -2824.821f, 41.243f, 0.0f }  // South
};

Position returnPos[2] =
{
    { -1057.645f, -2706.035f, 37.736f, 5.261f },
    { -978.451f,  -2706.773f, 37.737f, 4.134f }
};

Position heroicPos = { -1848.261f, -3916.670f, -279.502f, 0.990f };

class boss_sha_of_fear : public CreatureScript
{
    public:
        boss_sha_of_fear() : CreatureScript("boss_sha_of_fear") { }

        struct boss_sha_of_fearAI : public BossAI
        {
            boss_sha_of_fearAI(Creature* creature) : BossAI(creature, DATA_SHA_OF_FEAR)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            EventMap events;

            uint8 attacksCounter;
            uint8 thrashsCounter;

            uint8 terrorCounter;
            uint8 submergeCounter;

            bool shrine1;
            bool shrine2;
            bool shrine3;

            uint8 healthPctForSecondPhase;
            bool isInSecondPhase;

            void Reset()
            {
                if (pInstance && pInstance->GetBossState(DATA_PROTECTORS) != DONE)
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 35);

                if (pInstance && pInstance->GetBossState(DATA_LEI_SHI) != DONE)
                {
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->SetReactState(REACT_PASSIVE);
                    return;
                }

                _Reset();

                me->ReenableEvadeMode();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_DISABLE_TURN);
                me->SetPower(POWER_ENERGY, 0);
                me->SetMaxPower(POWER_ENERGY, 100);
                me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_REGENERATE_POWER);
                me->CastSpell(me, SPELL_ENERGY_TO_ZERO, true);
 
                summons.DespawnAll();

                me->RemoveAura(SPELL_CONJURE_TERROR_SPAWN_TICK);
                me->RemoveAura(SPELL_THRASH_AURA);

                events.Reset();

                events.ScheduleEvent(EVENT_CHECK_MELEE, 1000);
                events.ScheduleEvent(EVENT_EERIE_SKULL, 5000);
                events.ScheduleEvent(EVENT_CHECK_ENERGY, 1000);
                events.ScheduleEvent(EVENT_FIRST_TERRORS, 30000);
                events.ScheduleEvent(EVENT_OMINOUS_CACKLE, 25500);
                events.ScheduleEvent(EVENT_ENRAGE, 900000);

                attacksCounter  = 0;
                thrashsCounter  = 0;
                terrorCounter   = 0;
                submergeCounter = 0;
                shrine1         = false;
                shrine2         = false;
                shrine3         = false;
                isInSecondPhase = false;
                healthPctForSecondPhase = 50;
 
                if (pInstance)
                {
                    pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                    pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_DREAD_EXPANSE_AURA);
                    pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_LEI_SHIS_HOPE);
 
                    if (pInstance->GetData(SPELL_RITUAL_OF_PURIFICATION))
                        me->AddAura(SPELL_RITUAL_OF_PURIFICATION, me);

                    if (Creature* wallOfLight = Creature::GetCreature(*me, pInstance->GetData64(NPC_PURE_LIGHT_TERRACE)))
                        wallOfLight->AI()->DoAction(ACTION_DESACTIVATE_WALL_OF_LIGHT);
                }
            }

            void JustReachedHome()
            {
                _JustReachedHome();
 
                if (pInstance)
                    pInstance->SetBossState(DATA_SHA_OF_FEAR, FAIL);
            }

            void EnterCombat(Unit* attacker)
            {
                if (pInstance)
                {
                    if (pInstance->GetBossState(DATA_LEI_SHI) != DONE)
                    {
                        EnterEvadeMode();
                        return;
                    }

                    pInstance->SetBossState(DATA_SHA_OF_FEAR, IN_PROGRESS);
                    pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                    DoZoneInCombat();
                    Talk(TALK_AGGRO);
                }
            }

            void JustDied(Unit* killer)
            {
                if (pInstance)
                {
                    summons.DespawnAll();
                    pInstance->SetBossState(DATA_SHA_OF_FEAR, DONE);
                    pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                    _JustDied();
                }
            }

            void JustSummoned(Creature* summon)
            {
                if (summon->GetEntry() == NPC_TERROR_SPAWN)
                    ++terrorCounter;

                summons.Summon(summon);
            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                if (summon->GetEntry() == NPC_TERROR_SPAWN)
                    --terrorCounter;

                summons.Despawn(summon);
            }

            void KilledUnit(Unit* who)
            {
                if (who->GetTypeId() == TYPEID_PLAYER)
                    Talk(TALK_SLAY);
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                    case ACTION_SPAWN_TERROR:
                    {
                        if (!terrorCounter)
                        {
                            me->CastSpell(spawnTerrorPos[0].GetPositionX(), spawnTerrorPos[0].GetPositionY(),
                                          spawnTerrorPos[0].GetPositionZ(), SPELL_CONJURE_TERROR_SPAWN_01, true);
                            me->CastSpell(spawnTerrorPos[1].GetPositionX(), spawnTerrorPos[1].GetPositionY(),
                                          spawnTerrorPos[1].GetPositionZ(), SPELL_CONJURE_TERROR_SPAWN_02, true);
                        }
                        else
                        {
                            me->CastSpell(spawnTerrorPos[2].GetPositionX(), spawnTerrorPos[2].GetPositionY(),
                                          spawnTerrorPos[2].GetPositionZ(), SPELL_CONJURE_TERROR_SPAWN_03, true);
                            me->CastSpell(spawnTerrorPos[3].GetPositionX(), spawnTerrorPos[3].GetPositionY(),
                                          spawnTerrorPos[3].GetPositionZ(), SPELL_CONJURE_TERROR_SPAWN_04, true);
                        }

                        break;
                    }
                    case ACTION_ACTIVATE_SHRINE_1:
                    {
                        if (shrine1)
                            DoAction(ACTION_ACTIVATE_SHRINE_1 + urand(1, 2));

                        shrine1 = true;
                        me->SummonCreature(NPC_YANG_GUOSHI + (urand(0, 2) * 4), shrinesPos[0].GetPositionX(), shrinesPos[0].GetPositionY(), shrinesPos[0].GetPositionZ());
                        me->SummonCreature(NPC_RETURN_TO_THE_TERRACE, shrinesPos[0].GetPositionX(), shrinesPos[0].GetPositionY(), shrinesPos[0].GetPositionZ());
                        break;
                    }
                    case ACTION_ACTIVATE_SHRINE_2:
                    {
                        if (shrine2)
                        {
                            if (urand(0, 1))
                                DoAction(ACTION_ACTIVATE_SHRINE_1);
                            else
                                DoAction(ACTION_ACTIVATE_SHRINE_3);
                        }

                        shrine2 = true;
                        me->SummonCreature(NPC_YANG_GUOSHI + (urand(0, 2) * 4), shrinesPos[1].GetPositionX(), shrinesPos[1].GetPositionY(), shrinesPos[1].GetPositionZ());
                        me->SummonCreature(NPC_RETURN_TO_THE_TERRACE, shrinesPos[1].GetPositionX(), shrinesPos[1].GetPositionY(), shrinesPos[1].GetPositionZ());
                        break;
                    }
                    case ACTION_ACTIVATE_SHRINE_3:
                    {
                        if (shrine3)
                            DoAction(ACTION_ACTIVATE_SHRINE_1 + urand(0, 1));

                        shrine3 = true;
                        me->SummonCreature(NPC_YANG_GUOSHI + (urand(0, 2) * 4), shrinesPos[2].GetPositionX(), shrinesPos[2].GetPositionY(), shrinesPos[2].GetPositionZ());
                        me->SummonCreature(NPC_RETURN_TO_THE_TERRACE, shrinesPos[2].GetPositionX(), shrinesPos[2].GetPositionY(), shrinesPos[2].GetPositionZ());
                        break;
                    }
                    case ACTION_DESACTIVATE_SHRINE_1:
                        shrine1 = false;
                        break;
                    case ACTION_DESACTIVATE_SHRINE_2:
                        shrine2 = false;
                        break;
                    case ACTION_DESACTIVATE_SHRINE_3:
                        shrine3 = false;
                        break;
                    case ACTION_ACTIVATE_SHA_OF_FEAR:
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->SetReactState(REACT_AGGRESSIVE);
                        break;
                    default:
                        break;
                }
            }

            void DamageTaken(Unit* attacker, uint32& damage)
            {
                if (!IsHeroic())
                    return;

                // Heroic
                if (me->HealthBelowPctDamaged(healthPctForSecondPhase, damage))
                {
                    events.Reset();
                    summons.DespawnAll();

                    isInSecondPhase = true;
                    Talk(TALK_HEROIC);

                    pInstance->DoAddAuraOnPlayers(SPELL_LEI_SHIS_HOPE);
                    pInstance->DoAddAuraOnPlayers(SPELL_DREAD_EXPANSE_AURA);
                    pInstance->DoAddAuraOnPlayers(SPELL_FADING_LIGHT);

                    if (Player* champion = GetChampionOfLight(me))
                        champion->CastSpell(champion, SPELL_CHAMPION_OF_LIGHT_HEROIC, true);

                    events.ScheduleEvent(EVENT_IMPLACABLE_STRIKE, 10000);
                    events.ScheduleEvent(EVENT_WATERSPOUT, 12000);
                    events.ScheduleEvent(EVENT_HUDDLE_IN_TERROR, 15000);
                    events.ScheduleEvent(EVENT_NAKED_AND_AFRAID, 20000);
                    events.ScheduleEvent(EVENT_SUBMERGE, 40000);
                }
            }

            void DamageDealt(Unit* /*victim*/, uint32& /*damage*/, DamageEffectType damageType)
            {
                if (damageType == DIRECT_DAMAGE)
                {
                    if (attacksCounter >= 3 && !me->m_extraAttacks)
                    {
                        me->CastSpell(me, SPELL_THRASH_EXTRA_ATTACKS, true);
                        attacksCounter = 0;
                    }
                    else if (attacksCounter >= 2 && !me->m_extraAttacks)
                    {
                        me->CastSpell(me, SPELL_THRASH_AURA, true);
                        ++thrashsCounter;
                        ++attacksCounter;
                    }
                    else if (!me->m_extraAttacks)
                    {
                        me->RemoveAura(SPELL_THRASH_AURA);
                        me->RemoveAura(SPELL_DREAD_THRASH_AURA);
                        ++attacksCounter;
                    }

                    if (thrashsCounter >= 3 && IsHeroic())
                    {
                        me->RemoveAura(SPELL_THRASH_AURA);
                        me->RemoveAura(SPELL_THRASH_EXTRA_ATTACKS);
                        me->CastSpell(me, SPELL_DREAD_THRASH_EXTRA_ATT, true);
                        thrashsCounter = 0;
                    }
                    else if (thrashsCounter >= 2 && IsHeroic())
                    {
                        me->RemoveAura(SPELL_THRASH_AURA);
                        me->RemoveAura(SPELL_THRASH_EXTRA_ATTACKS);
                        me->CastSpell(me, SPELL_DREAD_THRASH_AURA, true);
                    }
                }
            }

            void OnAddThreat(Unit* victim, float& fThreat, SpellSchoolMask /*schoolMask*/, SpellInfo const* /*threatSpell*/)
            {
                if (!victim || victim->GetTypeId() != TYPEID_PLAYER || victim->ToPlayer() != GetChampionOfLight(me))
                {
                    fThreat = 0;
                    return;
                }
            }

            void RegeneratePower(Powers power, int32& value)
            {
                if (power != POWER_ENERGY)
                    return;

                if (!me->isInCombat())
                {
                    value = 0;
                    return;
                }

                // Sha of Fear regenerates 6 energy every 2s (15 energy for 5s)
                value = 6;
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                {
                    if (pInstance && pInstance->GetData(SPELL_RITUAL_OF_PURIFICATION) == false)
                        me->RemoveAura(SPELL_RITUAL_OF_PURIFICATION);

                    if (me->isInCombat())
                        EnterEvadeMode();

                    return;
                }

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
 
                events.Update(diff);
 
                switch (events.ExecuteEvent())
                {
                    case EVENT_CHECK_MELEE:
                    {
                        if (!me->IsWithinMeleeRange(me->getVictim(), 2.0f))
                        {
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0f))
                                me->CastSpell(target, SPELL_REACHING_ATTACK, false);
                        }
                        else
                        {
                            // Always attack champion of light
                            if (Player* target = GetChampionOfLight(me))
                                if (me->getVictim() && me->getVictim()->GetGUID() != target->GetGUID())
                                    AttackStart(target);
                        }
                        events.ScheduleEvent(EVENT_CHECK_MELEE, 1000);
                        break;
                    }
                    case EVENT_EERIE_SKULL:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 60.0f))
                            me->CastSpell(target, SPELL_EERIE_SKULL, false);
                        events.ScheduleEvent(EVENT_EERIE_SKULL, 5000);
                        break;
                    }
                    case EVENT_CHECK_ENERGY:
                    {
                        if (!pInstance)
                        {
                            events.ScheduleEvent(EVENT_CHECK_ENERGY, 1000);
                            break;
                        }

                        if (me->GetPower(POWER_ENERGY) >= me->GetMaxPower(POWER_ENERGY))
                        {
                            if (Creature* pureLight = Creature::GetCreature(*me, pInstance->GetData64(NPC_PURE_LIGHT_TERRACE)))
                                me->CastSpell(pureLight, SPELL_BREATH_OF_FEAR, false);
                            Talk(TALK_BREATH_OF_FEAR);
                            me->SetPower(POWER_ENERGY, 0);
                            me->SetInt32Value(UNIT_FIELD_POWER1, 0);
                        }

                        events.ScheduleEvent(EVENT_CHECK_ENERGY, 1000);
                        break;
                    }
                    case EVENT_FIRST_TERRORS:
                    {
                        me->CastSpell(me, SPELL_CONJURE_TERROR_SPAWN_TICK, true);
                        break;
                    }
                    case EVENT_OMINOUS_CACKLE:
                    {
                        me->CastSpell(me, SPELL_OMINOUS_CACKLE_CAST, false);
                        events.ScheduleEvent(EVENT_OMINOUS_CACKLE, 45500);
                        break;
                    }
                    case EVENT_ENRAGE:
                    {
                        me->CastSpell(me, SPELL_BERSERK, true);
                        break;
                    }
                    case EVENT_IMPLACABLE_STRIKE:
                    {
                        if (!IsHeroic())
                            break;

                        me->CastSpell(me, SPELL_IMPLACABLE_STRIKE, false);
                        events.ScheduleEvent(EVENT_IMPLACABLE_STRIKE, 10000);
                        break;
                    }
                    case EVENT_NAKED_AND_AFRAID:
                    {
                        if (!IsHeroic())
                            break;

                        if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 0, 50.0f, true))
                            me->CastSpell(target, SPELL_NAKED_AND_AFRAID, false);
                        events.ScheduleEvent(EVENT_NAKED_AND_AFRAID, 30000);
                        break;
                    }
                    case EVENT_WATERSPOUT:
                    {
                        if (!IsHeroic())
                            break;

                        events.ScheduleEvent(EVENT_WATERSPOUT, 10000);
                        break;
                    }
                    case EVENT_HUDDLE_IN_TERROR:
                    {
                        if (!IsHeroic())
                            break;

                        Talk(TALK_HUDDLE);
                        me->CastSpell(me, SPELL_HUDDLE_IN_TERROR, false);
                        events.ScheduleEvent(EVENT_HUDDLE_IN_TERROR, 10000);
                        break;
                    }
                    case EVENT_SUBMERGE:
                    {
                        if (!IsHeroic())
                            break;

                        Talk(TALK_SUBMERGE);
                        ++submergeCounter;

                        for (int i = 0; i < submergeCounter; ++i)
                        {
                            float rotation = frand(0, 2 * M_PI);
                            float x = me->GetPositionX() + ((40.0f) * cos(rotation));
                            float y = me->GetPositionY() + ((40.0f) * sin(rotation));

                            me->SummonCreature(NPC_DREAD_SPAWN, x, y, me->GetPositionZ(), rotation);
                        }

                        me->CastSpell(me, SPELL_SUBMERGE_TRANSFORM, false);
                        events.ScheduleEvent(EVENT_SUBMERGE, 51500);
                        break;
                    }
                    default:
                        break;
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_sha_of_fearAI(creature);
        }
};

// Pure Light Terrace - 60788
class mob_pure_light_terrace : public CreatureScript
{
    public:
        mob_pure_light_terrace() : CreatureScript("mob_pure_light_terrace") { }

        struct mob_pure_light_terraceAI : public ScriptedAI
        {
            mob_pure_light_terraceAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
                wallActivated = false;
            }

            InstanceScript* pInstance;

            bool wallActivated;

            void Reset()
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE|UNIT_FLAG_NON_ATTACKABLE);
                me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_DISABLE_TURN);
                me->CastSpell(me, SPELL_LIGHT_WALL, true);
                me->CastSpell(me, SPELL_LIGHT_WALL_READY, true);
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                    case ACTION_ACTIVATE_WALL_OF_LIGHT:
                    {
                        if (wallActivated)
                            break;

                        wallActivated = true;
                        me->CastSpell(me, SPELL_LIGHT_WALL_VISUAL, true);
                        me->RemoveAura(SPELL_LIGHT_WALL_READY);
                        break;
                    }
                    case ACTION_DESACTIVATE_WALL_OF_LIGHT:
                    {
                        if (!wallActivated)
                            break;

                        wallActivated = false;
                        me->CastSpell(me, SPELL_LIGHT_WALL_READY, true);
                        me->RemoveAura(SPELL_LIGHT_WALL_VISUAL);
                        break;
                    }
                    default:
                        break;
                }
            }

            void DamageTaken(Unit* attacker, uint32& damage)
            {
                damage = 0;
                return;
            }

            void UpdateAI(const uint32 diff)
            {
                Map::PlayerList const& playerList = me->GetMap()->GetPlayers();
                for (Map::PlayerList::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                {
                    if (Player* player = itr->getSource())
                    {
                        if (wallActivated && me->isInBack(player, M_PI / 3) && !player->HasAura(SPELL_WALL_OF_LIGHT_BUFF))
                            player->AddAura(SPELL_WALL_OF_LIGHT_BUFF, player);
                        else if ((!me->isInBack(player, M_PI / 3) && player->HasAura(SPELL_WALL_OF_LIGHT_BUFF)) || !wallActivated)
                            player->RemoveAura(SPELL_WALL_OF_LIGHT_BUFF);

                        if (player->GetDistance(me) <= 3.0f)
                        {
                            if (pInstance)
                            {
                                if (!player->HasAura(SPELL_CHAMPION_OF_LIGHT))
                                {
                                    pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CHAMPION_OF_LIGHT);
                                    player->AddAura(SPELL_CHAMPION_OF_LIGHT, player);
                                    DoAction(ACTION_ACTIVATE_WALL_OF_LIGHT);

                                    if (Player* champion = GetChampionOfLight(me))
                                    {
                                        if (Creature* sha = Creature::GetCreature(*me, pInstance->GetData64(NPC_SHA_OF_FEAR)))
                                        {
                                            sha->AddThreat(champion, 1000000.0f);
                                            sha->AI()->AttackStart(champion);
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (player->HasAura(SPELL_CHAMPION_OF_LIGHT))
                                player->RemoveAura(SPELL_CHAMPION_OF_LIGHT);

                            Player* champion = GetChampionOfLight(me);
                            if (!champion)
                                DoAction(ACTION_DESACTIVATE_WALL_OF_LIGHT);
                        }
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_pure_light_terraceAI(creature);
        }
};

// Return to the Terrace - 65736
class mob_return_to_the_terrace : public CreatureScript
{
    public:
        mob_return_to_the_terrace() : CreatureScript("mob_return_to_the_terrace") { }

        struct mob_return_to_the_terraceAI : public ScriptedAI
        {
            mob_return_to_the_terraceAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            EventMap events;

            void Reset()
            {
                events.Reset();
                events.ScheduleEvent(EVENT_CHECK_GUARDIAN, 1000);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                me->RemoveFlag(UNIT_FIELD_INTERACT_SPELL_ID, SPELL_FEARLESS);
                me->RemoveAura(SPELL_PURE_LIGHT_VISUAL);
            }

            void OnSpellClick(Unit* clicker)
            {
                if (clicker->GetTypeId() != TYPEID_PLAYER)
                    return;

                std::list<Player*> playersToRecall;

                me->GetPlayerListInGrid(playersToRecall, 50.0f);

                uint8 pos = urand(0, 1);

                for (auto itr : playersToRecall)
                {
                    itr->CastSpell(itr, SPELL_FEARLESS, true);
                    itr->NearTeleportTo(returnPos[pos].GetPositionX(), returnPos[pos].GetPositionY(), returnPos[pos].GetPositionZ(), returnPos[pos].GetOrientation());
                }
            }

            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);

                switch (events.ExecuteEvent())
                {
                    case EVENT_CHECK_GUARDIAN:
                    {
                        std::list<Creature*> guardianList;
                        me->GetCreatureListWithEntryInGrid(guardianList, NPC_YANG_GUOSHI, 10.0f);
                        if (guardianList.empty())
                            me->GetCreatureListWithEntryInGrid(guardianList, NPC_CHENG_KANG, 10.0f);
                        if (guardianList.empty())
                            me->GetCreatureListWithEntryInGrid(guardianList, NPC_JINLUN_KUN, 10.0f);

                        bool died = false;
                        if (guardianList.empty())
                            died = true;
                        else
                        {
                            for (auto itr : guardianList)
                            {
                                if (itr->isDead())
                                    died = true;
                                else
                                    died = false;
                            }
                        }

                        if (died)
                        {
                            events.ScheduleEvent(EVENT_CHECK_GUARDIAN, 1000);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                            me->SetFlag(UNIT_FIELD_INTERACT_SPELL_ID, SPELL_FEARLESS);
                            me->CastSpell(me, SPELL_PURE_LIGHT_VISUAL, true);
                            me->DespawnOrUnsummon(10000);
                        }
                        else
                        {
                            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                            me->RemoveFlag(UNIT_FIELD_INTERACT_SPELL_ID, SPELL_FEARLESS);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            me->RemoveAura(SPELL_PURE_LIGHT_VISUAL);
                        }

                        events.ScheduleEvent(EVENT_CHECK_GUARDIAN, 1000);
                        break;
                    }
                    default:
                        break;
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_return_to_the_terraceAI(creature);
        }
};

// Terror Spawn - 61034
class mob_terror_spawn : public CreatureScript
{
    public:
        mob_terror_spawn() : CreatureScript("mob_terror_spawn") { }

        struct mob_terror_spawnAI : public ScriptedAI
        {
            mob_terror_spawnAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            EventMap events;

            void Reset()
            {
                if (pInstance)
                    if (Creature* pureLight = Creature::GetCreature(*me, pInstance->GetData64(NPC_PURE_LIGHT_TERRACE)))
                        me->SetFacingToObject(pureLight);

                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_DISABLE_TURN);

                me->CastSpell(me, SPELL_DARK_BULWARK, true);

                events.Reset();
                events.ScheduleEvent(EVENT_PENETRATING_BOLT, 1500);
            }

            void UpdateAI(const uint32 diff)
            {
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                switch (events.ExecuteEvent())
                {
                    case EVENT_PENETRATING_BOLT:
                    {
                        me->CastSpell(me, SPELL_PENETRATING_BOLT, false);
                        events.ScheduleEvent(EVENT_PENETRATING_BOLT, 1500);
                        break;
                    }
                    default:
                        break;
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_terror_spawnAI(creature);
        }
};

#define GUARDIAN_SAY_AGGRO 0

// Yang Guoshi - 61038
// Cheng Kang - 61042
// Jinlun Kun - 61046
class mob_shrine_guardian : public CreatureScript
{
    public:
        mob_shrine_guardian() : CreatureScript("mob_shrine_guardian") { }

        struct mob_shrine_guardianAI : public ScriptedAI
        {
            mob_shrine_guardianAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            EventMap events;
            uint8 nextGlobePct;

            void Reset()
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->ReenableEvadeMode();
                me->CastSpell(me, SPELL_SHA_CORRUPTION, true);
                SetEquipmentSlots(false, EQUIP_NO_CHANGE, EQUIP_NO_CHANGE, EQUIP_ID_GUARDIAN);

                events.Reset();

                events.ScheduleEvent(EVENT_SHOT, 500);
                events.ScheduleEvent(EVENT_DEATH_BLOSSOM, 10000);
                events.ScheduleEvent(EVENT_DREAD_SPRAY, 20000);

                me->SetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE, me->GetFloatValue(UNIT_FIELD_MINDAMAGE));
                me->SetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE, me->GetFloatValue(UNIT_FIELD_MAXDAMAGE));

                nextGlobePct = 95;
            }

            void EnterCombat(Unit* /*attacker*/)
            {
                Talk(GUARDIAN_SAY_AGGRO);
            }

            void DamageTaken(Unit* attacker, uint32& damage)
            {
                if (nextGlobePct < 5)
                    return;

                if (me->HealthBelowPctDamaged(nextGlobePct, damage))
                {
                    nextGlobePct -= 5;
                    me->CastSpell(me, SPELL_SHA_GLOBE_SPAWN, true);
                }
            }

            void JustDied(Unit* /*killer*/)
            {
                if (!pInstance)
                    return;

                Creature* sha = me->GetMap()->GetCreature(pInstance->GetData64(NPC_SHA_OF_FEAR));
                if (!sha)
                    return;

                if (me->GetPositionX() == shrinesPos[0].GetPositionX() &&
                    me->GetPositionY() == shrinesPos[0].GetPositionY() &&
                    me->GetPositionZ() == shrinesPos[0].GetPositionZ())
                {
                    sha->AI()->DoAction(ACTION_DESACTIVATE_SHRINE_1);
                }
                else if (me->GetPositionX() == shrinesPos[1].GetPositionX() &&
                         me->GetPositionY() == shrinesPos[1].GetPositionY() &&
                         me->GetPositionZ() == shrinesPos[1].GetPositionZ())
                {
                    sha->AI()->DoAction(ACTION_DESACTIVATE_SHRINE_2);
                }
                else
                    sha->AI()->DoAction(ACTION_DESACTIVATE_SHRINE_3);

                me->DespawnOrUnsummon();
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                switch (events.ExecuteEvent())
                {
                    case EVENT_SHOT:
                    {
                        if (me->HasUnitState(UNIT_STATE_CASTING))
                        {
                            events.ScheduleEvent(EVENT_SHOT, 500);
                            break;
                        }

                        if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 0, 30.0f))
                            me->CastSpell(target, SPELL_SHOT, false);
                        events.ScheduleEvent(EVENT_SHOT, 500);
                        break;
                    }
                    case EVENT_DEATH_BLOSSOM:
                    {
                        if (me->HasUnitState(UNIT_STATE_CASTING))
                        {
                            events.ScheduleEvent(EVENT_DEATH_BLOSSOM, 0);
                            break;
                        }

                        me->CastSpell(me, SPELL_DEATH_BLOSSOM, false);
                        events.ScheduleEvent(EVENT_DEATH_BLOSSOM, 20000);
                        break;
                    }
                    case EVENT_DREAD_SPRAY:
                    {
                        if (me->HasUnitState(UNIT_STATE_CASTING))
                        {
                            events.ScheduleEvent(EVENT_DREAD_SPRAY, 0);
                            break;
                        }

                        me->CastSpell(me, SPELL_DREAD_SPRAY, false);
                        events.ScheduleEvent(EVENT_DREAD_SPRAY, 30000);
                        break;
                    }
                    default:
                        break;
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_shrine_guardianAI(creature);
        }
};

// Sha Globe - 65691
class mob_sha_globe : public CreatureScript
{
    public:
        mob_sha_globe() : CreatureScript("mob_sha_globe") { }

        struct mob_sha_globeAI : public ScriptedAI
        {
            mob_sha_globeAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            EventMap events;

            void Reset()
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE|UNIT_FLAG_NOT_SELECTABLE);
                me->CastSpell(me, SPELL_SHA_GLOBE_PERIODIC_VISUAL, true);

                events.Reset();
                events.ScheduleEvent(EVENT_DESPAWN_SHA_GLOBE, 8000);
            }

            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);

                switch (events.ExecuteEvent())
                {
                    case EVENT_DESPAWN_SHA_GLOBE:
                    {
                        Unit* guardian = me->ToTempSummon()->GetSummoner();
                        if (!guardian)
                            return;

                        me->HealBySpell(guardian, sSpellMgr->GetSpellInfo(SPELL_SHA_GLOBE_HEAL_SUMMONER),
                                        guardian->CountPctFromMaxHealth(IsHeroic() ? 8 : 5));
                        me->CastSpell(me, SPELL_SHA_GLOBE_HEAL_SUMMONER, true);
                        me->DespawnOrUnsummon();
                        break;
                    }
                    default:
                        break;
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_sha_globeAI(creature);
        }
};

// Dread Spawn - 61003
class mob_dread_spawn : public CreatureScript
{
    public:
        mob_dread_spawn() : CreatureScript("mob_dread_spawn") { }

        struct mob_dread_spawnAI : public ScriptedAI
        {
            mob_dread_spawnAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_GATHERING_SPEED, 5000);
            }

            void DamageDealt(Unit* victim, uint32& /*damage*/, DamageEffectType damageType)
            {
                if (damageType == DIRECT_DAMAGE)
                    me->CastSpell(victim, SPELL_ETERNAL_DARKNESS, false);
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                    case ACTION_TRANSFERT_OF_LIGHT:
                    {
                        me->RemoveAura(SPELL_GATHERING_SPEED);
                        me->CastSpell(me, SPELL_SHA_SPINES, false);
                        break;
                    }
                    default:
                        break;
                }
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                switch (events.ExecuteEvent())
                {
                    case EVENT_GATHERING_SPEED:
                    {
                        me->CastSpell(me, SPELL_GATHERING_SPEED, true);
                        events.ScheduleEvent(EVENT_GATHERING_SPEED, 5000);
                        break;
                    }
                    default:
                        break;
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_dread_spawnAI(creature);
        }
};

// Breath of Fear - 119414 / 125786
class spell_breath_of_fear : public SpellScriptLoader
{
    public:
        spell_breath_of_fear() : SpellScriptLoader("spell_breath_of_fear") { }

        class spell_breath_of_fear_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_breath_of_fear_SpellScript);

            void CorrectRange(std::list<WorldObject*>& targets)
            {
                if (targets.empty())
                    return;

                // All targets on the platform, who are not afflicted by Wall of Light or Fearless will be hit by this spell.
                targets.remove_if(JadeCore::UnitAuraCheck(true, SPELL_WALL_OF_LIGHT_BUFF));
                targets.remove_if(JadeCore::UnitAuraCheck(true, SPELL_FEARLESS));
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_breath_of_fear_SpellScript::CorrectRange, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_breath_of_fear_SpellScript();
        }
};

// Conjure Terror Spawn - 119108
class spell_conjure_terror_spawn : public SpellScriptLoader
{
    public:
        spell_conjure_terror_spawn() : SpellScriptLoader("spell_conjure_terror_spawn") { }

        class spell_conjure_terror_spawn_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_conjure_terror_spawn_AuraScript);

            void OnTick(constAuraEffectPtr /*aurEff*/)
            {
                if (Creature* caster = GetCaster()->ToCreature())
                    caster->AI()->DoAction(ACTION_SPAWN_TERROR);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_conjure_terror_spawn_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_conjure_terror_spawn_AuraScript();
        }
};

// Penetrating Bolt - 129075
class spell_penetrating_bolt : public SpellScriptLoader
{
    public:
        spell_penetrating_bolt() : SpellScriptLoader("spell_penetrating_bolt") { }

        class spell_penetrating_bolt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_penetrating_bolt_SpellScript);

            uint64 targetGuid;

            void CorrectRange(std::list<WorldObject*>& targets)
            {
                targetGuid = 0;

                if (!targets.empty())
                    JadeCore::Containers::RandomResizeList(targets, 1);

                for (auto itr : targets)
                    if (itr->GetGUID())
                        targetGuid = itr->GetGUID();
            }

            void HandleDummy(SpellEffIndex index)
            {
                if (Unit* caster = GetCaster())
                {
                    if (InstanceScript* instance = caster->GetInstanceScript())
                    {
                        if (Player* target = Player::GetPlayer(*caster, targetGuid))
                            caster->CastSpell(target, SPELL_PENETRATING_BOLT_MISSILE, true, NULL, NULLAURA_EFFECT, instance->GetData64(NPC_SHA_OF_FEAR));
                    }
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_penetrating_bolt_SpellScript::CorrectRange, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnEffectLaunch += SpellEffectFn(spell_penetrating_bolt_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_penetrating_bolt_SpellScript();
        }
};

// Ominous Cackle - 119593
class spell_ominous_cackle_cast : public SpellScriptLoader
{
    public:
        spell_ominous_cackle_cast() : SpellScriptLoader("spell_ominous_cackle_cast") { }

        class spell_ominous_cackle_cast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ominous_cackle_cast_SpellScript);

            bool activationDone;
            uint32 shrineTeleport;
            uint8 shrine;

            void CorrectTargets(std::list<WorldObject*>& targets)
            {
                if (targets.empty())
                    return;

                Creature* caster = GetCaster()->ToCreature();
                if (!caster)
                    return;

                std::list<WorldObject*> realTargets;
                bool tankDone = false;
                bool healerDone = false;
                uint8 targetsToAdd = 5;

                for (auto itr : targets)
                {
                    if (!targetsToAdd)
                        break;

                    Player* player = itr->ToPlayer();
                    if (!player)
                        continue;

                    // Don't send player to shrine if he is already in one
                    std::list<Creature*> shrineMobs;
                    player->GetCreatureListWithEntryInGrid(shrineMobs, NPC_YANG_GUOSHI, 50.0f);
                    if (shrineMobs.size() > 0)
                        continue;
                    player->GetCreatureListWithEntryInGrid(shrineMobs, NPC_CHENG_KANG, 50.0f);
                    if (shrineMobs.size() > 0)
                        continue;
                    player->GetCreatureListWithEntryInGrid(shrineMobs, NPC_JINLUN_KUN, 50.0f);
                    if (shrineMobs.size() > 0)
                        continue;
                    player->GetCreatureListWithEntryInGrid(shrineMobs, NPC_RETURN_TO_THE_TERRACE, 50.0f);
                    if (shrineMobs.size() > 0)
                        continue;

                    if (!tankDone && player->GetRoleForGroup(player->GetSpecializationId(player->GetActiveSpec())) == ROLES_TANK)
                    {
                        if (player != GetChampionOfLight(caster))
                            continue;

                        tankDone = true;
                        targetsToAdd--;
                        realTargets.push_back(itr);
                        continue;
                    }

                    if (!healerDone && player->GetRoleForGroup(player->GetSpecializationId(player->GetActiveSpec())) == ROLES_HEALER)
                    {
                        healerDone = true;
                        targetsToAdd--;
                        realTargets.push_back(itr);
                        continue;
                    }

                    targetsToAdd--;
                    realTargets.push_back(itr);
                }

                activationDone = false;
                shrineTeleport = SPELL_TELEPORT_TO_SHRINE_1;
                shrine         = urand(0, 2);
                shrineTeleport += shrine;

                for (auto itr : realTargets)
                {
                    if (Creature* caster = GetCaster()->ToCreature())
                    {
                        if (Unit* target = itr->ToUnit())
                        {
                            target->CastSpell(target, shrineTeleport, true);

                            if (!activationDone)
                                caster->AI()->DoAction(ACTION_ACTIVATE_SHRINE_1 + shrine);
                            activationDone = true;
                        }
                    }
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ominous_cackle_cast_SpellScript::CorrectTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ominous_cackle_cast_SpellScript();
        }
};

// Dread Spray - 120047
class spell_dread_spray : public SpellScriptLoader
{
    public:
        spell_dread_spray() : SpellScriptLoader("spell_dread_spray") { }

        class spell_dread_spray_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dread_spray_AuraScript);

            void OnTick(constAuraEffectPtr /*aurEff*/)
            {
                if (Unit* caster = GetCaster())
                {
                    float rotation = frand(0, 2 * M_PI);
                    float x = caster->GetPositionX() + ((35.0f) * cos(rotation));
                    float y = caster->GetPositionY() + ((35.0f) * sin(rotation));

                    caster->CastSpell(x, y, caster->GetPositionZ(), SPELL_DREAD_SPRAY_TRIGGERED, true);
                    caster->SetFacingTo(rotation);
                    caster->SetOrientation(rotation);
                    caster->CastSpell(x, y, caster->GetPositionZ(), SPELL_DREAD_SPRAY_VISUAL, true);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_dread_spray_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dread_spray_AuraScript();
        }
};

// Dread Spray (stacks) - 119983
class spell_dread_spray_stacks : public SpellScriptLoader
{
    public:
        spell_dread_spray_stacks() : SpellScriptLoader("spell_dread_spray_stacks") { }

        class spell_dread_spray_stacks_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dread_spray_stacks_SpellScript);

            void CorrectTargets(std::list<WorldObject*>& targets)
            {
                if (targets.empty())
                    return;

                Unit* caster = GetCaster();
                if (!caster)
                    return;

                std::list<WorldObject*> targetsToErase;

                for (auto itr : targets)
                    if (!caster->isInFront(itr, (M_PI / 2)))
                        targetsToErase.push_back(itr);

                for (auto itr : targetsToErase)
                    targets.remove(itr);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dread_spray_stacks_SpellScript::CorrectTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dread_spray_stacks_SpellScript::CorrectTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dread_spray_stacks_SpellScript::CorrectTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dread_spray_stacks_SpellScript();
        }

        class spell_dread_spray_stacks_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dread_spray_stacks_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                {
                    if (AuraPtr dreadSpray = target->GetAura(SPELL_DREAD_SPRAY_STACKS))
                    {
                        if (dreadSpray->GetStackAmount() > 1)
                        {
                            target->RemoveAura(SPELL_DREAD_SPRAY_STACKS);
                            target->CastSpell(target, SPELL_DREAD_SPRAY_FEAR_ROOT, true);
                        }
                    }
                }
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dread_spray_stacks_AuraScript::OnApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dread_spray_stacks_AuraScript();
        }
};

// Sha Globe (periodic) - 129189
class spell_sha_globe_periodic : public SpellScriptLoader
{
    public:
        spell_sha_globe_periodic() : SpellScriptLoader("spell_sha_globe_periodic") { }

        class spell_sha_globe_periodic_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_globe_periodic_SpellScript);

            void HandleOnHit()
            {
                if (Creature* caster = GetCaster()->ToCreature())
                {
                    caster->RemoveAura(SPELL_SHA_GLOBE_PERIODIC_VISUAL);
                    caster->DespawnOrUnsummon();
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_sha_globe_periodic_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_globe_periodic_SpellScript();
        }
};

// Death Blossom - 119888
class spell_death_blossom_periodic : public SpellScriptLoader
{
    public:
        spell_death_blossom_periodic() : SpellScriptLoader("spell_death_blossom_periodic") { }

        class spell_death_blossom_periodic_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_death_blossom_periodic_AuraScript);

            void OnTick(constAuraEffectPtr /*aurEff*/)
            {
                if (Unit* caster = GetCaster())
                {
                    float rotation = frand(0, 2 * M_PI);
                    float x = caster->GetPositionX() + ((35.0f) * cos(rotation));
                    float y = caster->GetPositionY() + ((35.0f) * sin(rotation));

                    caster->CastSpell(x, y, caster->GetPositionZ(), SPELL_DEATH_BLOSSOM_RAND_ARROW, true);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_death_blossom_periodic_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_death_blossom_periodic_AuraScript();
        }
};

// Death Blossom (damage) - 119887
class spell_death_blossom_damage : public SpellScriptLoader
{
    public:
        spell_death_blossom_damage() : SpellScriptLoader("spell_death_blossom_damage") { }

        class spell_death_blossom_damage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_death_blossom_damage_SpellScript);

            void CorrectTargets(std::list<WorldObject*>& targets)
            {
                if (targets.empty())
                    return;

                Unit* caster = GetCaster();
                if (!caster)
                    return;

                std::list<WorldObject*> targetsToErase;

                for (auto itr : targets)
                    if (!caster->IsWithinLOSInMap(itr))
                        targetsToErase.push_back(itr);

                for (auto itr : targetsToErase)
                    targets.remove(itr);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_death_blossom_damage_SpellScript::CorrectTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_death_blossom_damage_SpellScript();
        }
};

// Submerge - 120455
class spell_submerge : public SpellScriptLoader
{
    public:
        spell_submerge() : SpellScriptLoader("spell_submerge") { }

        class spell_submerge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_submerge_SpellScript);

            void HandleOnHit()
            {
                if (Creature* caster = GetCaster()->ToCreature())
                {
                    if (Unit* target = caster->AI()->SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                    {
                        caster->NearTeleportTo(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), target->GetOrientation());
                        caster->CastSpell(caster, SPELL_EMERGE_DAMAGE, false);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_submerge_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_submerge_SpellScript();
        }
};

// Emerge - 120458
class spell_emerge : public SpellScriptLoader
{
    public:
        spell_emerge() : SpellScriptLoader("spell_emerge") { }

        class spell_emerge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_emerge_SpellScript);

            void HandleAfterCast()
            {
                if (Creature* caster = GetCaster()->ToCreature())
                {
                    caster->RemoveAura(SPELL_SUBMERGE_TRANSFORM);
                    caster->CastSpell(caster, SPELL_EMERGE_STUN_ONE_SECOND, true);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_emerge_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_emerge_SpellScript();
        }
};

void AddSC_boss_sha_of_fear()
{
    new boss_sha_of_fear();
    new mob_pure_light_terrace();
    new mob_return_to_the_terrace();
    new mob_terror_spawn();
    new mob_shrine_guardian();
    new mob_sha_globe();
    new mob_dread_spawn();
    new spell_breath_of_fear();
    new spell_conjure_terror_spawn();
    new spell_penetrating_bolt();
    new spell_ominous_cackle_cast();
    new spell_dread_spray();
    new spell_dread_spray_stacks();
    new spell_sha_globe_periodic();
    new spell_death_blossom_periodic();
    new spell_death_blossom_damage();
    new spell_submerge();
    new spell_emerge();
}