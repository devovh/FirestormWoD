#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "dread_wastes.h"

class mob_ik_ik_the_nimble : public CreatureScript
{
    public:
        mob_ik_ik_the_nimble() : CreatureScript("mob_ik_ik_the_nimble")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_ik_ik_the_nimbleAI(creature);
        }

        struct mob_ik_ik_the_nimbleAI : public ScriptedAI
        {
            mob_ik_ik_the_nimbleAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_BANANARANG, 10000);
                events.ScheduleEvent(EVENT_GOING_BANANAS, 17000);
                events.ScheduleEvent(EVENT_TOSS_FILTH, 22000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 30000);
            }

            void JustSummoned(Creature* summon)
            {
                summon->DespawnOrUnsummon(15000);
                summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BANANARANG:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_BANANARANG, false);
                            events.ScheduleEvent(EVENT_BANANARANG, 40000);
                            break;
                        case EVENT_GOING_BANANAS:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_GOING_BANANAS, false);
                            events.ScheduleEvent(EVENT_GOING_BANANAS, 40000);
                            break;
                        case EVENT_TOSS_FILTH:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_TOSS_FILTH, false);
                            events.ScheduleEvent(EVENT_TOSS_FILTH, 40000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 40000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_adjunct_kree_zot : public CreatureScript
{
    public:
        mob_adjunct_kree_zot() : CreatureScript("mob_adjunct_kree_zot")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_adjunct_kree_zotAI(creature);
        }

        struct mob_adjunct_kree_zotAI : public ScriptedAI
        {
            mob_adjunct_kree_zotAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_SHA_SPIT, 10000);
                events.ScheduleEvent(EVENT_SHA_SPIT_2, 20000);
                events.ScheduleEvent(EVENT_SLICING_STRIKE, 25000);
                events.ScheduleEvent(EVENT_WRATH_OF_THE_EMPRESS, 35000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SHA_SPIT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_SHA_SPIT, false);
                            events.ScheduleEvent(EVENT_SHA_SPIT, 40000);
                            break;
                        case EVENT_SHA_SPIT_2:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_SHA_SPIT_2, false);
                            events.ScheduleEvent(EVENT_SHA_SPIT_2, 45000);
                            break;
                        case EVENT_SLICING_STRIKE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_SLICING_STRIKE, false);
                            events.ScheduleEvent(EVENT_SLICING_STRIKE,      40000);
                            break;
                        case EVENT_WRATH_OF_THE_EMPRESS:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_WRATH_OF_THE_EMPRESS, false);
                            events.ScheduleEvent(EVENT_WRATH_OF_THE_EMPRESS, 40000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_dread_fearbringer : public CreatureScript
{
    public:
        mob_dread_fearbringer() : CreatureScript("mob_dread_fearbringer")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_dread_fearbringerAI(creature);
        }

        struct mob_dread_fearbringerAI : public ScriptedAI
        {
            mob_dread_fearbringerAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 10000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    if (eventId == EVENT_UNSTABLE_SERUM)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                            me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                        events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 10000);
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_dread_kunchong : public CreatureScript
{
    public:
        mob_dread_kunchong() : CreatureScript("mob_dread_kunchong")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_dread_kunchongAI(creature);
        }

        struct mob_dread_kunchongAI : public ScriptedAI
        {
            mob_dread_kunchongAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 10000);
                events.ScheduleEvent(EVENT_DREAD_SLASH, 25000);
            }

            void EnterCombat(Unit* who)
            {
                Player* player = who->ToPlayer();

                if (!player)
                    return;

                switch (player->GetSpecializationId(player->GetActiveSpec()))
                {
                    case SPEC_DK_BLOOD:
                    case SPEC_DK_FROST:
                    case SPEC_DK_UNHOLY:
                    case SPEC_PALADIN_PROTECTION:
                    case SPEC_PALADIN_RETRIBUTION:
                    case SPEC_WARRIOR_ARMS:
                    case SPEC_WARRIOR_FURY:
                    case SPEC_WARRIOR_PROTECTION:
                    case SPEC_MONK_BREWMASTER:
                    default:
                        DoCast(me, SPELL_SEEK_AND_DESTROY,   true);
                        break;
                    case SPEC_MAGE_ARCANE:
                    case SPEC_MAGE_FIRE:
                    case SPEC_MAGE_FROST:
                    case SPEC_PALADIN_HOLY:
                    case SPEC_DROOD_BALANCE:
                    case SPEC_PRIEST_DISCIPLINE:
                    case SPEC_PRIEST_HOLY:
                    case SPEC_PRIEST_SHADOW:
                    case SPEC_DROOD_RESTORATION:
                    case SPEC_SHAMAN_ELEMENTAL:
                    case SPEC_SHAMAN_RESTORATION:
                    case SPEC_WARLOCK_AFFLICTION:
                    case SPEC_WARLOCK_DEMONOLOGY:
                    case SPEC_WARLOCK_DESTRUCTION:
                    case SPEC_MONK_MISTWEAVER:
                        DoCast(me, SPELL_SEEK_AND_DESTROY_2, true);
                        break;
                    case SPEC_DROOD_CAT:
                    case SPEC_DROOD_BEAR:
                    case SPEC_HUNTER_BEASTMASTER:
                    case SPEC_HUNTER_MARKSMAN:
                    case SPEC_HUNTER_SURVIVAL:
                    case SPEC_ROGUE_ASSASSINATION:
                    case SPEC_ROGUE_COMBAT:
                    case SPEC_ROGUE_SUBTLETY:
                    case SPEC_SHAMAN_ENHANCEMENT:
                    case SPEC_MONK_WINDWALKER:
                        DoCast(me, SPELL_SEEK_AND_DESTROY_3, true);
                        break;
                }
            }

            void JustDied(Unit* killer)
            {
                if (me->HasAura(SPELL_SEEK_AND_DESTROY))
                    me->CastSpell(killer, SPELL_SEEK_AND_DESTROY_POWER, true);

                if (me->HasAura(SPELL_SEEK_AND_DESTROY_2))
                    me->CastSpell(killer, SPELL_SEEK_AND_DESTROY_WISDOM, true);

                if (me->HasAura(SPELL_SEEK_AND_DESTROY_3))
                    me->CastSpell(killer, SPELL_SEEK_AND_DESTROY_VELOCITY, true);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_DREAD_SLASH:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_DREAD_SLASH, false);
                            events.ScheduleEvent(EVENT_DREAD_SLASH, 30000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 30000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_dread_matriarch : public CreatureScript
{
    public:
        mob_dread_matriarch() : CreatureScript("mob_dread_matriarch")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_dread_matriarchAI(creature);
        }

        struct mob_dread_matriarchAI : public ScriptedAI
        {
            mob_dread_matriarchAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 10000);
                events.ScheduleEvent(EVENT_POUNCE, 17000);
                events.ScheduleEvent(EVENT_RAVAGE, 23000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_POUNCE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                            {
                                me->CastSpell(target, SPELL_POUNCE, false);
                                me->CastSpell(target, SPELL_POUNCE_DAMAGE, false);
                            }
                            events.ScheduleEvent(EVENT_POUNCE, 230000);
                            break;
                        case EVENT_RAVAGE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_RAVAGE, false);
                            events.ScheduleEvent(EVENT_RAVAGE, 30000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 30000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_elder_spindlegrin : public CreatureScript
{
    public:
        mob_elder_spindlegrin() : CreatureScript("mob_elder_spindlegrin")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_elder_spindlegrinAI(creature);
        }

        struct mob_elder_spindlegrinAI : public ScriptedAI
        {
            mob_elder_spindlegrinAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_REND, 8000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 12000);
                events.ScheduleEvent(EVENT_CHARGE_2, 17000);
                events.ScheduleEvent(EVENT_MONSTROUS_UNDERBITE, 23000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CHARGE_2:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_CHARGE, false);
                            events.ScheduleEvent(EVENT_CHARGE_2, 30000);
                            break;
                        case EVENT_MONSTROUS_UNDERBITE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_MONSTROUS_UNDERBITE, false);
                            events.ScheduleEvent(EVENT_MONSTROUS_UNDERBITE, 30000);
                            break;
                        case EVENT_REND:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_REND, false);
                            events.ScheduleEvent(EVENT_REND, 30000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 30000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_hulking_kor_thik_fleshrender : public CreatureScript
{
    public:
        mob_hulking_kor_thik_fleshrender() : CreatureScript("mob_hulking_kor_thik_fleshrender")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_hulking_kor_thik_fleshrenderAI(creature);
        }

        struct mob_hulking_kor_thik_fleshrenderAI : public ScriptedAI
        {
            mob_hulking_kor_thik_fleshrenderAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 12000);
                events.ScheduleEvent(EVENT_PINCH_LIMB, 17000);
                events.ScheduleEvent(EVENT_VICIOUS_STRIKES, 23000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_PINCH_LIMB:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_PINCH_LIMB, false);
                            events.ScheduleEvent(EVENT_PINCH_LIMB, 30000);
                            break;
                        case EVENT_VICIOUS_STRIKES:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_VICIOUS_STRIKES, false);
                            events.ScheduleEvent(EVENT_VICIOUS_STRIKES, 30000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 30000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_ik_thik_amberstinger : public CreatureScript
{
    public:
        mob_ik_thik_amberstinger() : CreatureScript("mob_ik_thik_amberstinger")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_ik_thik_amberstingerAI(creature);
        }

        struct mob_ik_thik_amberstingerAI : public ScriptedAI
        {
            mob_ik_thik_amberstingerAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 15000);
                events.ScheduleEvent(EVENT_CLAW, 20000);
                events.ScheduleEvent(EVENT_SONIC_SHOCK, 27000);
                events.ScheduleEvent(EVENT_TAIL_STRIKE, 32000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CLAW:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_CLAW, false);
                            events.ScheduleEvent(EVENT_CLAW, 40000);
                            break;
                        case EVENT_SONIC_SHOCK:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_SONIC_SHOCK, false);
                            events.ScheduleEvent(EVENT_SONIC_SHOCK, 40000);
                            break;
                        case EVENT_TAIL_STRIKE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_TAIL_STRIKE, false);
                            events.ScheduleEvent(EVENT_TAIL_STRIKE, 40000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 40000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_ik_thik_kunchong : public CreatureScript
{
    public:
        mob_ik_thik_kunchong() : CreatureScript("mob_ik_thik_kunchong")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_ik_thik_kunchongAI(creature);
        }

        struct mob_ik_thik_kunchongAI : public ScriptedAI
        {
            mob_ik_thik_kunchongAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 10000);
                events.ScheduleEvent(EVENT_DREAD_SLASH_2, 17000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_DREAD_SLASH_2:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_DREAD_SLASH, false);
                            events.ScheduleEvent(EVENT_DREAD_SLASH_2, 20000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 20000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_ik_thik_terrorclaw : public CreatureScript
{
    public:
        mob_ik_thik_terrorclaw() : CreatureScript("mob_ik_thik_terrorclaw")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_ik_thik_terrorclawAI(creature);
        }

        struct mob_ik_thik_terrorclawAI : public ScriptedAI
        {
            mob_ik_thik_terrorclawAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 8000);
                events.ScheduleEvent(EVENT_TAIL_STRIKE, 22000);
                events.ScheduleEvent(EVENT_CLAW, 17000);
            }

            void EnterCombat(Unit* who)
            {
                Player* player = who->ToPlayer();

                if (!player)
                    return;

                switch (player->GetSpecializationId(player->GetActiveSpec()))
                {
                    case SPEC_DK_BLOOD:
                    case SPEC_DK_FROST:
                    case SPEC_DK_UNHOLY:
                    case SPEC_PALADIN_PROTECTION:
                    case SPEC_PALADIN_RETRIBUTION:
                    case SPEC_WARRIOR_ARMS:
                    case SPEC_WARRIOR_FURY:
                    case SPEC_WARRIOR_PROTECTION:
                    case SPEC_MONK_BREWMASTER:
                    default:
                        DoCast(me, SPELL_SEEK_AND_DESTROY, true);
                        break;
                    case SPEC_MAGE_ARCANE:
                    case SPEC_MAGE_FIRE:
                    case SPEC_MAGE_FROST:
                    case SPEC_PALADIN_HOLY:
                    case SPEC_DROOD_BALANCE:
                    case SPEC_PRIEST_DISCIPLINE:
                    case SPEC_PRIEST_HOLY:
                    case SPEC_PRIEST_SHADOW:
                    case SPEC_DROOD_RESTORATION:
                    case SPEC_SHAMAN_ELEMENTAL:
                    case SPEC_SHAMAN_RESTORATION:
                    case SPEC_WARLOCK_AFFLICTION:
                    case SPEC_WARLOCK_DEMONOLOGY:
                    case SPEC_WARLOCK_DESTRUCTION:
                    case SPEC_MONK_MISTWEAVER:
                        DoCast(me, SPELL_SEEK_AND_DESTROY_2, true);
                        break;
                    case SPEC_DROOD_CAT:
                    case SPEC_DROOD_BEAR:
                    case SPEC_HUNTER_BEASTMASTER:
                    case SPEC_HUNTER_MARKSMAN:
                    case SPEC_HUNTER_SURVIVAL:
                    case SPEC_ROGUE_ASSASSINATION:
                    case SPEC_ROGUE_COMBAT:
                    case SPEC_ROGUE_SUBTLETY:
                    case SPEC_SHAMAN_ENHANCEMENT:
                    case SPEC_MONK_WINDWALKER:
                        DoCast(me, SPELL_SEEK_AND_DESTROY_3, true);
                        break;
                }
            }

            void JustDied(Unit* killer)
            {
                if (me->HasAura(SPELL_SEEK_AND_DESTROY))
                    me->CastSpell(killer, SPELL_SEEK_AND_DESTROY_POWER, true);

                if (me->HasAura(SPELL_SEEK_AND_DESTROY_2))
                    me->CastSpell(killer, SPELL_SEEK_AND_DESTROY_WISDOM, true);

                if (me->HasAura(SPELL_SEEK_AND_DESTROY_3))
                    me->CastSpell(killer, SPELL_SEEK_AND_DESTROY_VELOCITY, true);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_TAIL_STRIKE_2:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_TAIL_STRIKE, false);
                            events.ScheduleEvent(EVENT_TAIL_STRIKE_2, 25000);
                            break;
                        case EVENT_CLAW_2:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_CLAW, false);
                            events.ScheduleEvent(EVENT_CLAW_2, 25000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 25000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_karanosh : public CreatureScript
{
    public:
        mob_karanosh() : CreatureScript("mob_karanosh")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_karanoshAI(creature);
        }

        struct mob_karanoshAI : public ScriptedAI
        {
            mob_karanoshAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 12000);
                events.ScheduleEvent(EVENT_CORROSIVE_RESIN, 17000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CORROSIVE_RESIN:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_CORROSIVE_RESIN, false);
                            events.ScheduleEvent(EVENT_CORROSIVE_RESIN, 20000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 20000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_kypa_rak : public CreatureScript
{
    public:
        mob_kypa_rak() : CreatureScript("mob_kypa_rak")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_kypa_rakAI(creature);
        }

        struct mob_kypa_rakAI : public ScriptedAI
        {
            mob_kypa_rakAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_BURROW, 8000);
                events.ScheduleEvent(EVENT_RAISE_EARTH, 12000);
                events.ScheduleEvent(EVENT_UNAURA_BURROW, 26000);
                events.ScheduleEvent(EVENT_CRACKING_STONE, 27000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 33000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BURROW:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_BURROW, false);
                            events.ScheduleEvent(EVENT_RAISE_EARTH, 23000);
                            events.ScheduleEvent(EVENT_UNAURA_BURROW, 15000);
                            events.ScheduleEvent(EVENT_BURROW, 20000);
                            break;
                        case EVENT_UNAURA_BURROW:
                                me->RemoveAura(SPELL_BURROW);
                            break;
                        case EVENT_CRACKING_STONE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_CRACKING_STONE, false);
                            events.ScheduleEvent(EVENT_CRACKING_STONE, 10000);
                            break;
                        case EVENT_RAISE_EARTH:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_RAISE_EARTH, false);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 14000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_manifestation_of_terror : public CreatureScript
{
    public:
        mob_manifestation_of_terror() : CreatureScript("mob_manifestation_of_terror")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_manifestation_of_terrorAI(creature);
        }

        struct mob_manifestation_of_terrorAI : public ScriptedAI
        {
            mob_manifestation_of_terrorAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_DREAD_CLAW, 8000);
                events.ScheduleEvent(EVENT_LASH_OUT_IN_FEAR, 12000);
                events.ScheduleEvent(EVENT_SHA_BOLT, 17000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 25000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_DREAD_CLAW:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_DREAD_CLAW, false); // Nonfunctional
                            events.ScheduleEvent(EVENT_DREAD_CLAW, 40000);
                            break;
                        case EVENT_LASH_OUT_IN_FEAR:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_LASH_OUT_IN_FEAR, false);
                            events.ScheduleEvent(EVENT_LASH_OUT_IN_FEAR, 40000);
                            break;
                        case EVENT_SHA_BOLT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_SHA_BOLT, false);
                            events.ScheduleEvent(EVENT_SHA_BOLT, 40000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 40000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_shox_tik : public CreatureScript
{
    public:
        mob_shox_tik() : CreatureScript("mob_shox_tik")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_shox_tikAI(creature);
        }

        struct mob_shox_tikAI : public ScriptedAI
        {
            mob_shox_tikAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_RAPID_SHOT, 8000);
                events.ScheduleEvent(EVENT_SHOOT, 12000);
                events.ScheduleEvent(EVENT_TOXIC_SHOT, 17000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 25000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_RAPID_SHOT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_RAPID_SHOT, false); // Nonfunctional
                            events.ScheduleEvent(EVENT_RAPID_SHOT, 30000);
                            break;
                        case EVENT_SHOOT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_SHOOT, false);
                            events.ScheduleEvent(EVENT_SHOOT, 30000);
                            break;
                        case EVENT_TOXIC_SHOT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_TOXIC_SHOT, false);
                            events.ScheduleEvent(EVENT_TOXIC_SHOT, 30000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 30000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_wake_of_horror : public CreatureScript
{
    public:
        mob_wake_of_horror() : CreatureScript("mob_wake_of_horror")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_wake_of_horrorAI(creature);
        }

        struct mob_wake_of_horrorAI : public ScriptedAI
        {
            mob_wake_of_horrorAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_SHA_CORRUPTION, 10000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 20000);
            }

            void EnterCombat(Unit* who)
            {
                Player* player = who->ToPlayer();

                if (!player)
                    return;

                switch (player->GetSpecializationId(player->GetActiveSpec()))
                {
                    case SPEC_DK_BLOOD:
                    case SPEC_DK_FROST:
                    case SPEC_DK_UNHOLY:
                    case SPEC_PALADIN_PROTECTION:
                    case SPEC_PALADIN_RETRIBUTION:
                    case SPEC_WARRIOR_ARMS:
                    case SPEC_WARRIOR_FURY:
                    case SPEC_WARRIOR_PROTECTION:
                    case SPEC_MONK_BREWMASTER:
                    default:
                        DoCast(me, SPELL_SEEK_AND_DESTROY,   true);
                        break;
                    case SPEC_MAGE_ARCANE:
                    case SPEC_MAGE_FIRE:
                    case SPEC_MAGE_FROST:
                    case SPEC_PALADIN_HOLY:
                    case SPEC_DROOD_BALANCE:
                    case SPEC_PRIEST_DISCIPLINE:
                    case SPEC_PRIEST_HOLY:
                    case SPEC_PRIEST_SHADOW:
                    case SPEC_DROOD_RESTORATION:
                    case SPEC_SHAMAN_ELEMENTAL:
                    case SPEC_SHAMAN_RESTORATION:
                    case SPEC_WARLOCK_AFFLICTION:
                    case SPEC_WARLOCK_DEMONOLOGY:
                    case SPEC_WARLOCK_DESTRUCTION:
                    case SPEC_MONK_MISTWEAVER:
                        DoCast(me, SPELL_SEEK_AND_DESTROY_2, true);
                        break;
                    case SPEC_DROOD_CAT:
                    case SPEC_DROOD_BEAR:
                    case SPEC_HUNTER_BEASTMASTER:
                    case SPEC_HUNTER_MARKSMAN:
                    case SPEC_HUNTER_SURVIVAL:
                    case SPEC_ROGUE_ASSASSINATION:
                    case SPEC_ROGUE_COMBAT:
                    case SPEC_ROGUE_SUBTLETY:
                    case SPEC_SHAMAN_ENHANCEMENT:
                    case SPEC_MONK_WINDWALKER:
                        DoCast(me, SPELL_SEEK_AND_DESTROY_3, true);
                        break;
                }
            }

            void JustDied(Unit* killer)
            {
                if (me->HasAura(SPELL_SEEK_AND_DESTROY))
                    me->CastSpell(killer, SPELL_SEEK_AND_DESTROY_POWER, true);

                if (me->HasAura(SPELL_SEEK_AND_DESTROY_2))
                    me->CastSpell(killer, SPELL_SEEK_AND_DESTROY_WISDOM, true);

                if (me->HasAura(SPELL_SEEK_AND_DESTROY_3))
                    me->CastSpell(killer, SPELL_SEEK_AND_DESTROY_VELOCITY, true);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SHA_CORRUPTION:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_SHA_CORRUPTION, false);
                            events.ScheduleEvent(EVENT_SHA_CORRUPTION, 20000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 20000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_warlord_gurthan : public CreatureScript
{
    public:
        mob_warlord_gurthan() : CreatureScript("mob_warlord_gurthan")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_warlord_gurthanAI(creature);
        }

        struct mob_warlord_gurthanAI : public ScriptedAI
        {
            mob_warlord_gurthanAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_CRUSHING_SHADOWS, 8000);
                events.ScheduleEvent(EVENT_RUNE_OF_SHADOWS, 12000);
                events.ScheduleEvent(EVENT_SHADOW_POWER, 17000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 25000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CRUSHING_SHADOWS:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_CRUSHING_SHADOWS, false); // Nonfunctional
                            events.ScheduleEvent(EVENT_CRUSHING_SHADOWS, 30000);
                            break;
                        case EVENT_RUNE_OF_SHADOWS:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_RUNE_OF_SHADOWS, false);
                            events.ScheduleEvent(EVENT_RUNE_OF_SHADOWS, 30000);
                            break;
                        case EVENT_SHADOW_POWER:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_SHADOW_POWER, false);
                            events.ScheduleEvent(EVENT_SHADOW_POWER, 30000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 30000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

 class mob_ai_li_skymirror : public CreatureScript
 {
     public:
         mob_ai_li_skymirror() : CreatureScript("mob_ai_li_skymirror")
         {
         }

         CreatureAI* GetAI(Creature* creature) const
         {
             return new mob_ai_li_skymirrorAI(creature);
         }

         struct mob_ai_li_skymirrorAI : public ScriptedAI
         {
             mob_ai_li_skymirrorAI(Creature* creature) : ScriptedAI(creature)
             {
             }

             EventMap events;

             void Reset()
             {
                 events.Reset();

                 events.ScheduleEvent(EVENT_CHI_BURST, 8000);
                 events.ScheduleEvent(EVENT_HEALING_MISTS, 12000);
                 events.ScheduleEvent(EVENT_SPINNING_CRANE_KICK, 17000);
                 events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 25000);
             }

             void UpdateAI(const uint32 diff)
             {
                 if (!UpdateVictim())
                     return;

                 if (me->HasUnitState(UNIT_STATE_CASTING))
                     return;

                 events.Update(diff);

                 while (uint32 eventId = events.ExecuteEvent())
                 {
                     switch (eventId)
                     {
                         case EVENT_CHI_BURST:
                             if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                 me->CastSpell(target, SPELL_CHI_BURST, false);
                             events.ScheduleEvent(EVENT_CHI_BURST, 30000);
                             break;
                         case EVENT_HEALING_MISTS:
                             if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                 me->CastSpell(me, SPELL_HEALING_MISTS, false);
                             events.ScheduleEvent(EVENT_HEALING_MISTS, 30000);
                             break;
                         case EVENT_SPINNING_CRANE_KICK:
                             if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                 me->CastSpell(target, SPELL_SPINNING_CRANE_KICK, false);
                             events.ScheduleEvent(EVENT_SPINNING_CRANE_KICK, 30000);
                             break;
                         case EVENT_UNSTABLE_SERUM:
                             if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                 me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                             events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 30000);
                             break;
                         default:
                             break;
                     }
                 }

                 DoMeleeAttackIfReady();
             }
         };
};

class mob_overgrown_seacarp : public CreatureScript
{
    public:
        mob_overgrown_seacarp() : CreatureScript("mob_overgrown_seacarp")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_overgrown_seacarpAI(creature);
        }

        struct mob_overgrown_seacarpAI : public ScriptedAI
        {
            mob_overgrown_seacarpAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_SNAPJAW, 8000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 12000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SNAPJAW:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_SNAPJAW,        false);
                            events.ScheduleEvent(EVENT_SNAPJAW, 15000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 15000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_gar_lok : public CreatureScript
{
    public:
        mob_gar_lok() : CreatureScript("mob_gar_lok")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_gar_lokAI(creature);
        }

        struct mob_gar_lokAI : public ScriptedAI
        {
            mob_gar_lokAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_SNAPJAW, 8000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 12000);
                events.ScheduleEvent(EVENT_BLADE_FURRY, 20000);
                events.ScheduleEvent(EVENT_TORNADO, 27000);
            }

            void JustSummoned(Creature* summon)
            {
                if (summon->GetEntry() == MOB_TORNADO)
                {
                    summon->DespawnOrUnsummon(15000);
                    summon->AddAura(SPELL_TORNADO_DMG, summon);
                    summon->SetReactState(REACT_PASSIVE);
                    summon->GetMotionMaster()->MoveRandom(20.0f);
                }

            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SNAPJAW:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_SNAPJAW, false);
                            events.ScheduleEvent(EVENT_SNAPJAW, 35000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 35000);
                            break;
                        case EVENT_BLADE_FURRY:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_BLADE_FURRY, false);
                            events.ScheduleEvent(EVENT_BLADE_FURRY, 35000);
                            break;
                        case EVENT_TORNADO:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_TORNADO, false);
                            events.ScheduleEvent(EVENT_TORNADO, 35000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_dak_the_breaker : public CreatureScript
{
    public:
        mob_dak_the_breaker() : CreatureScript("mob_dak_the_breaker")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_dak_the_breakerAI(creature);
        }

        struct mob_dak_the_breakerAI : public ScriptedAI
        {
            mob_dak_the_breakerAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_RUSHING_RAGE, 5000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 12000);
                events.ScheduleEvent(EVENT_YAUNGOL_STOMP, 20000);
                events.ScheduleEvent(EVENT_BELLOWING_RAGE, 28000);
            }

            void JustSummoned(Creature* summon)
            {
                summon->DespawnOrUnsummon(12000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BELLOWING_RAGE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_BELLOWING_RAGE, false);
                            events.ScheduleEvent(EVENT_BELLOWING_RAGE, 32000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 32000);
                            break;
                        case EVENT_RUSHING_RAGE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_RUSHING_RAGE, false);
                            events.ScheduleEvent(EVENT_RUSHING_RAGE, 32000);
                            break;
                        case EVENT_YAUNGOL_STOMP:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_YAUNGOL_STOMP, false);
                            events.ScheduleEvent(EVENT_YAUNGOL_STOMP, 32000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_nalash_verdantis : public CreatureScript
{
    public:
        mob_nalash_verdantis() : CreatureScript("mob_nalash_verdantis")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_nalash_verdantisAI(creature);
        }

        struct mob_nalash_verdantisAI : public ScriptedAI
        {
            mob_nalash_verdantisAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_RUSHING_RAGE, 5000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 12000);
                events.ScheduleEvent(EVENT_YAUNGOL_STOMP, 20000);
                events.ScheduleEvent(EVENT_BELLOWING_RAGE, 28000);
            }

            void JustSummoned(Creature* summon)
            {
                summon->DespawnOrUnsummon(12000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 35000);
                            break;
                        case EVENT_RAIN_DANCE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_RAIN_DANCE, false);
                            events.ScheduleEvent(EVENT_RAIN_DANCE, 35000);
                            break;
                        case EVENT_TORRENT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_TORRENT, false);
                            events.ScheduleEvent(EVENT_TORRENT, 35000);
                            break;
                        case EVENT_WATER_BOLT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_WATER_BOLT, false);
                            events.ScheduleEvent(EVENT_WATER_BOLT, 35000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_vengeful_spirit : public CreatureScript
{
    public:
        mob_vengeful_spirit() : CreatureScript("mob_vengeful_spirit")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_vengeful_spiritAI(creature);
        }

        struct mob_vengeful_spiritAI : public ScriptedAI
        {
            mob_vengeful_spiritAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_RAIN_DANCE_2, 5000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 12000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 15000);
                            break;
                        case EVENT_RAIN_DANCE_2:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_RAIN_DANCE, false);
                            events.ScheduleEvent(EVENT_RAIN_DANCE_2, 15000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_hisek_the_swarmkeeper : public CreatureScript
{
    public:
        mob_hisek_the_swarmkeeper() : CreatureScript("mob_hisek_the_swarmkeeper")
        {
        }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_CORRUPTION_RUNS_DEEP)
            {
                creature->SummonCreature(MOB_HISEK_THE_SWARMKEEPER, creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(), creature->GetOrientation());
                creature->AI()->SetGUID(player ? player->GetGUID() : 1);
            }

            return true;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_hisek_the_swarmkeeperAI(creature);
        }

        struct mob_hisek_the_swarmkeeperAI : public ScriptedAI
        {
            mob_hisek_the_swarmkeeperAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void JustSummoned(Creature* summoned)
            {
                summoned->GetMotionMaster()->MovePoint(1, -644.502f, 3133.263f, 146.412f);
            }
        };
};

class mob_hisek_the_swarmkeeper_two : public CreatureScript
{
    public:
        mob_hisek_the_swarmkeeper_two() : CreatureScript("mob_hisek_the_swarmkeeper_two")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_hisek_the_swarmkeeper_twoAI(creature);
        }

        struct mob_hisek_the_swarmkeeper_twoAI : public ScriptedAI
        {
            mob_hisek_the_swarmkeeper_twoAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void IsSummonedBy(Unit* owner)
            {
                if (owner->ToCreature()->GetEntry() == MOB_SECOND_HISEK_THE_SWARMKEEPER)
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            }

            void MovementInform (uint32 type, uint32 id)
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                if (id = 1)
                {
                    DoAction(ACTION_START_SPEAKING);
                    me->SummonCreature(MOB_KLAXXI_TRAITOR, -637.653f, 3134.079f, 146.444f, 3.333f); // Klaxxi Traitor
                }
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                    case ACTION_START_SPEAKING:
                        events.ScheduleEvent(EVENT_HISEK_TALK_1, 2000);
                        events.ScheduleEvent(EVENT_HISEK_TALK_2, 5000);
                        events.ScheduleEvent(EVENT_TRAITOR_TALK_1, 8000);
                        events.ScheduleEvent(EVENT_HISEK_TALK_3, 11000);
                        events.ScheduleEvent(EVENT_TRAITOR_TALK_2, 15000);
                        events.ScheduleEvent(EVENT_TRAITOR_TALK_3, 19000);
                        events.ScheduleEvent(EVENT_HISEK_TALK_4, 23000);
                        events.ScheduleEvent(EVENT_HISEK_TALK_5, 27000);
                        events.ScheduleEvent(EVENT_TRAITOR_TALK_4, 31000);
                        events.ScheduleEvent(EVENT_TRAITOR_TALK_5, 36000);
                        break;
                    case ACTION_START_COMBAT:
                        events.ScheduleEvent(EVENT_START_COMBAT, 2000);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(const uint32 diff)
            {
                std::list<Creature*> traitorList;
                GetCreatureListWithEntryInGrid(traitorList, me, MOB_KLAXXI_TRAITOR, 15.0f);

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_HISEK_TALK_1:
                            Talk(0);
                            break;
                        case EVENT_HISEK_TALK_2:
                            Talk(1);
                            break;
                        case EVENT_TRAITOR_TALK_1:
                            for (auto traitor: traitorList)
                                if (traitor->AI())
                                    traitor->AI()->Talk(0);
                            break;
                        case EVENT_HISEK_TALK_3:
                            Talk(2);
                            break;
                        case EVENT_TRAITOR_TALK_2:
                            for (auto traitor: traitorList)
                                if (traitor->AI())
                                    traitor->AI()->Talk(1);
                            break;
                        case EVENT_TRAITOR_TALK_3:
                            for (auto traitor: traitorList)
                                if (traitor->AI())
                                    traitor->AI()->Talk(2);
                            break;
                        case EVENT_HISEK_TALK_4:
                            Talk(3);
                            break;
                        case EVENT_HISEK_TALK_5:
                            Talk(4);
                            break;
                        case EVENT_TRAITOR_TALK_4:
                            for (auto traitor: traitorList)
                                if (traitor->AI())
                                    traitor->AI()->Talk(3);
                            break;
                        case EVENT_TRAITOR_TALK_5:
                            for (auto traitor: traitorList)
                                if (traitor->AI())
                                    traitor->AI()->Talk(4);
                            DoAction(ACTION_START_COMBAT);
                            break;
                        case EVENT_START_COMBAT:
                            for (auto traitor: traitorList)
                                if (traitor->AI())
                                    traitor->AI()->DoAction(ACTION_START_COMBAT);
                            me->DespawnOrUnsummon();
                            break;
                        default:
                            break;
                    }
                }
            }
        };
};

class mob_klaxxi_traitor : public CreatureScript
{
    public:
        mob_klaxxi_traitor() : CreatureScript("mob_klaxxi_traitor")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_klaxxi_traitorAI(creature);
        }

        struct mob_klaxxi_traitorAI : public ScriptedAI
        {
            mob_klaxxi_traitorAI(Creature* creature) : ScriptedAI(creature)
            {
                playerGuid = 0;
            }

            uint64 playerGuid;

            void MovementInform (uint32 type, uint32 id)
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                if (id = 1)
                {
                    DoAction(ACTION_START_SPEAKING);
                    me->SummonCreature(MOB_KLAXXI_TRAITOR, -637.653f, 3134.079f, 146.444f, 3.333f); // Klaxxi Traitor
                }
            }

            void JustDied(Unit* killer)
            {
                if (Player* player = killer->ToPlayer())
                    player->KilledMonsterCredit(MOB_KLAXXI_TRAITOR);
            }

            void SetGUID(uint64 guid, int32 data = 1)
            {
                playerGuid = guid;
            }

            void DoAction(const int32 action)
            {
                if (action == ACTION_START_COMBAT)
                {
                    me->setFaction(14);

                    if (Player* player = Player::GetPlayer(*me, playerGuid))
                        AttackStart(player);
                }
            }
        };
};

class go_ancient_amber_chunk : public GameObjectScript
{
    public:
        go_ancient_amber_chunk() : GameObjectScript("go_ancient_amber_chunk")
        {
        }

        bool OnGossipHello(Player* player, GameObject* go)
        {
            if (player->GetQuestStatus(QUEST_DROPPING_OUR_SIGNAL) == QUEST_STATUS_INCOMPLETE)
                player->KilledMonsterCredit(MOB_HISEK_THE_SWARMKEEPER_KILL_CREDIT);

            else if (player->GetQuestStatus(QUEST_PRESERVED_IN_AMBER) == QUEST_STATUS_INCOMPLETE)
                player->KilledMonsterCredit(MOB_KIL_RUK_THE_WIND_REAVER);

            else if (player->GetQuestStatus(QUEST_SKEER_THE_BLOODSEEKER) == QUEST_STATUS_INCOMPLETE)
                player->KilledMonsterCredit(MOB_SKEER_THE_BLOODSEEKER);

            else if (player->GetQuestStatus(QUEST_IN_HER_CLUTCH) == QUEST_STATUS_INCOMPLETE)
                player->KilledMonsterCredit(62752);

            go->DestroyForPlayer(player, false);
            return true;
        }
};

class mob_discover_amberglow_bunny : public CreatureScript
{
    public:
        mob_discover_amberglow_bunny() : CreatureScript("mob_discover_amberglow_bunny")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_discover_amberglow_bunnyAI(creature);
        }

        struct mob_discover_amberglow_bunnyAI : public ScriptedAI
        {
            mob_discover_amberglow_bunnyAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void UpdateAI(const uint32 diff)
            {
                std::list<Player*> playerList;
                GetPlayerListInGrid(playerList, me, 10.0f);

                for (auto player: playerList)
                    if (player->GetQuestStatus(QUEST_EXTENDING_OUR_COVERAGE) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(31679) == QUEST_STATUS_INCOMPLETE)
                        player->KilledMonsterCredit(MOB_DISCOVER_AMBERGLOW_BUNNY);
            }
        };
};

class mob_kaz_tik_the_manipulator : public CreatureScript
{
    public:
        mob_kaz_tik_the_manipulator() : CreatureScript("mob_kaz_tik_the_manipulator")
        {
        }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            if (quest->GetQuestId() == 31091) // Reunited
            {
                creature->SummonCreature(MOB_KAZ_TIK_THE_MANIPULATOR, creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(), creature->GetOrientation());

                if (Creature* kazTik2 = GetClosestCreatureWithEntry(creature, MOB_KAZ_TIK_THE_MANIPULATOR, 2.0f, true))
                    kazTik2->AI()->SetGUID(player ? player->GetGUID() : 2);
            }

            return true;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_kaz_tik_the_manipulatorAI(creature);
        }

        struct mob_kaz_tik_the_manipulatorAI : public ScriptedAI
        {
            mob_kaz_tik_the_manipulatorAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void reset()
            {
                events.Reset();
                events.ScheduleEvent(EVENT_CHECK_PLAYERS, 2000);
            }

            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    if (eventId == EVENT_CHECK_PLAYERS)
                    {
                        std::list<Player*> playerList;
                        GetPlayerListInGrid(playerList, me, 5.0f);

                        for (auto player: playerList)
                            if (player->GetQuestStatus(QUEST_BY_THE_SEA_NEVERMORE) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_BY_THE_SEA_NEVERMORE_2) == QUEST_STATUS_INCOMPLETE)
                                player->KilledMonsterCredit(MOB_SECOND_KAZ_TIK_THE_MANIPULATOR);

                        events.ScheduleEvent(EVENT_CHECK_PLAYERS, 2000);
                    }
                }
            }
        };
};

class go_kunchong_cage : public GameObjectScript
{
public:
    go_kunchong_cage() : GameObjectScript("go_kunchong_cage")
    {
    }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_FREE_FROM_HER_CLUTCHES) == QUEST_STATUS_INCOMPLETE)
            player->KilledMonsterCredit(MOB_KUNCHONG_HATCHLING);

        go->DestroyForPlayer(player, false);
        return true;
    }
};

class mob_second_kaz_tik_the_manipulator : public CreatureScript
{
    public:
        mob_second_kaz_tik_the_manipulator() : CreatureScript("mob_second_kaz_tik_the_manipulator")
        {
        }

        bool OnQuestReward(Player* player, Creature* creature, const Quest *quest, uint32 /*slot*/)
        {
            if (quest->GetQuestId() == QUEST_REUNITED)
                creature->DespawnOrUnsummon();

            return true;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_second_kaz_tik_the_manipulatorAI(creature);
        }

        struct mob_second_kaz_tik_the_manipulatorAI : public npc_escortAI
        {
            mob_second_kaz_tik_the_manipulatorAI(Creature* creature) : npc_escortAI(creature)
            {
                playerGuid = 0;
            }

            EventMap events;
            uint64 playerGuid;

            void Reset()
            {
                events.Reset();
                SetDespawnAtFar(false);
                SetDespawnAtEnd(false);
            }

            void SetGUID(uint64 guid, int32 data = 2)
            {
                playerGuid = guid;
            }

            void WaypointReached(uint32 waypointId)
            {
                Player* player = GetPlayerForEscort();

                if (!player)
                    return;

                switch (waypointId)
                {
                    case 8:
                    {
                        SetEscortPaused(true);
                        me->SummonCreature(MOB_MUCKSCALE_RIPPER, -950.895f, 3883.264f, -0.088f);
                        me->SummonCreature(MOB_MUCKSCALE_RIPPER, -975.193f, 3890.734f, -0.340f);

                        std::list<Creature*> muckscaleList;
                        GetCreatureListWithEntryInGrid(muckscaleList, me, MOB_MUCKSCALE_RIPPER, 40.0f);

                        if (Player* player = Player::GetPlayer(*me, playerGuid))
                            for (auto muckscale: muckscaleList)
                                muckscale->AI()->SetGUID(player ? player->GetGUID() : 2);
                    }
                        break;
                    case 11:
                    {
                        SetEscortPaused(true);
                        me->SummonCreature(MOB_MUCKSCALE_RIPPER, -1062.049f, 3918.263f, -0.076f);
                        me->SummonCreature(MOB_MUCKSCALE_RIPPER, -1071.315f, 3948.803f, -0.048f);
                    }
                        break;
                    case 12:
                    {
                        SetEscortPaused(true);
                        me->SummonCreature(MOB_MUCKSCALE_RIPPER, -1117.472f, 3952.810f, 0.356f);
                        me->SummonCreature(MOB_MUCKSCALE_RIPPER, -1115.047f, 3919.017f, 0.489f);
                    }
                        break;
                    case 14:
                    {
                        player->KilledMonsterCredit(MOB_KAZ_TIK_THE_MANIPULATOR);
                        player->KilledMonsterCredit(MOB_KOVOK);

                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    }
                        break;
                }
            }

            void IsSummonedBy(Unit* summoner)
            {
                if (Creature* creature = summoner->ToCreature())
                    if (creature->GetEntry() == MOB_THIRD_KAZ_TIK_THE_MANIPULATOR)
                        events.ScheduleEvent(EVENT_START_WALKING, 2000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (Player* player = Player::GetPlayer(*me, playerGuid))
                {
                    if (player->GetQuestStatus(QUEST_REUNITED) == QUEST_STATUS_INCOMPLETE)
                    {
                        npc_escortAI::UpdateAI(diff);

                        events.Update(diff);

                        if (me->GetPositionX() == -961.59f && me->GetPositionY() == 3876.36f)
                        {
                            Creature* muckscale = GetClosestCreatureWithEntry(me, MOB_MUCKSCALE_RIPPER, 40.0f, true);

                            if (!muckscale)
                                SetEscortPaused(false);
                        }

                        if (me->GetPositionX() == -1044.31f && me->GetPositionY() == 3928.69f)
                        {
                            Creature* muckscale = GetClosestCreatureWithEntry(me, MOB_MUCKSCALE_RIPPER, 40.0f, true);

                            if (!muckscale)
                                SetEscortPaused(false);
                        }

                        if (me->GetPositionX() == -1103.34f && me->GetPositionY() == 3943.14f)
                        {
                            Creature* muckscale = GetClosestCreatureWithEntry(me, MOB_MUCKSCALE_RIPPER, 40.0f, true);

                            if (!muckscale)
                                SetEscortPaused(false);
                        }

                        while (uint32 eventId = events.ExecuteEvent())
                        {
                            switch (eventId)
                            {
                                case EVENT_START_WALKING:
                                    Start(false, false, playerGuid);
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }
            }
        };
};

class mob_muckscale_ripper : public CreatureScript
{
    public:
        mob_muckscale_ripper() : CreatureScript("mob_muckscale_ripper")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_muckscale_ripperAI(creature);
        }

        struct mob_muckscale_ripperAI : public ScriptedAI
        {
            mob_muckscale_ripperAI(Creature* creature) : ScriptedAI(creature)
            {
                playerGuid = 0;
            }

            EventMap events;
            uint64 playerGuid;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_RUPTURE, 5000);
                events.ScheduleEvent(EVENT_SPRINT, 12000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 18000);
            }

            void SetGUID(uint64 guid, int32 data = 2)
            {
                playerGuid = guid;
            }

            void JustDied(Unit* killer)
            {
                me->DespawnOrUnsummon();
            }

            void IsSummonedBy(Unit* summoner)
            {
                if (Player* player = Player::GetPlayer(*me, playerGuid))
                    AttackStart(player);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_RUPTURE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_RUPTURE, false);
                            events.ScheduleEvent(EVENT_RUPTURE, 20000);
                            break;
                        case EVENT_SPRINT:
                            me->CastSpell(me, SPELL_SPRINT, false);
                            events.ScheduleEvent(EVENT_SPRINT, 20000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 20000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_skeer_the_bloodseeker : public CreatureScript
{
    public:
        mob_skeer_the_bloodseeker() : CreatureScript("mob_skeer_the_bloodseeker")
        {
        }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_THE_SCENT_OF_BLOOD) // The Scent of Blood
            {
                creature->AI()->SetGUID(player ? player->GetGUID() : 3);
                creature->AI()->DoAction(ACTION_SPAWNS);

            }

            return true;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_skeer_the_bloodseekerAI(creature);
        }

        struct mob_skeer_the_bloodseekerAI : public ScriptedAI
        {
            mob_skeer_the_bloodseekerAI(Creature* creature) : ScriptedAI(creature)
            {
                playerGuid = 0;
                firstPhaseDone = false;
                secondPhaseDone = false;
                thirdPhaseDone = false;
                fourthPhaseDone = false;
                firstPhaseTimer = 0;
                secondPhaseTimer = 0;
                thirdPhaseTimer = 0;
            }

            uint64 playerGuid;
            bool firstPhaseDone;
            bool secondPhaseDone;
            bool thirdPhaseDone;
            bool fourthPhaseDone;
            uint32 firstPhaseTimer;
            uint32 secondPhaseTimer;
            uint32 thirdPhaseTimer;

            void SetGUID(uint64 guid, int32 data = 3)
            {
                playerGuid = guid;
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                    case ACTION_SPAWNS:
                        if (Player* player = Player::GetPlayer(*me, playerGuid))
                        {
                            if (player->GetQuestStatus(QUEST_THE_SCENT_OF_BLOOD) == QUEST_STATUS_INCOMPLETE)
                            {
                                me->SummonCreature(MOB_MUCKSCALE_FLESHEATER, -406.158f, 4779.366f, -29.553f);
                                me->SummonCreature(MOB_MUCKSCALE_FLESHEATER, -395.112f, 4779.408f, -29.574f);
                                me->SummonCreature(MOB_MUCKSCALE_FLESHEATER, -408.258f, 4755.872f, -29.853f);
                                me->SummonCreature(MOB_MUCKSCALE_FLESHEATER, -395.859f, 4759.430f, -29.952f);

                                firstPhaseDone = true;
                                firstPhaseTimer = 10000;
                            }
                        }
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(const uint32 diff)
            {
                if (Player* player = Player::GetPlayer(*me, playerGuid))
                {
                    if (player->GetQuestStatus(QUEST_THE_SCENT_OF_BLOOD) == QUEST_STATUS_INCOMPLETE)
                    {
                        if (firstPhaseTimer)
                        {
                            if (firstPhaseTimer <= diff)
                            {
                                if (firstPhaseDone && !secondPhaseDone)
                                {
                                    Creature* muckscale = GetClosestCreatureWithEntry(me, MOB_MUCKSCALE_FLESHEATER, 40.0f, true);

                                    if (!muckscale)
                                    {
                                        std::list<Creature*> muckscaleList;
                                        GetCreatureListWithEntryInGrid(muckscaleList, me, MOB_MUCKSCALE_FLESHEATER, 30.0);

                                        for (auto muckscale: muckscaleList)
                                            muckscale->AI()->SetGUID(player ? player->GetGUID() : 3);

                                        me->SummonCreature(MOB_MUCKSCALE_FLESHEATER, -406.158f, 4779.366f, -29.553f);
                                        me->SummonCreature(MOB_MUCKSCALE_FLESHEATER, -395.112f, 4779.408f, -29.574f);
                                        me->SummonCreature(MOB_MUCKSCALE_FLESHEATER, -408.258f, 4755.872f, -29.853f);
                                        me->SummonCreature(MOB_MUCKSCALE_FLESHEATER, -395.859f, 4759.430f, -29.952f);

                                        secondPhaseDone = true;
                                        secondPhaseTimer = 3000;
                                    }
                                }
                                firstPhaseTimer = 3000;
                            }
                            else
                                firstPhaseTimer -= diff;
                        }

                        if (secondPhaseTimer)
                        {
                            if (secondPhaseTimer <= diff)
                            {
                                if (secondPhaseDone && !thirdPhaseDone)
                                {
                                    Creature* muckscale = GetClosestCreatureWithEntry(me, MOB_MUCKSCALE_FLESHEATER, 40.0f, true);

                                    if (!muckscale)
                                    {
                                        me->SummonCreature(MOB_MUCKSCALE_FLESHEATER, -406.158f, 4779.366f, -29.553f);
                                        me->SummonCreature(MOB_MUCKSCALE_FLESHEATER, -395.112f, 4779.408f, -29.574f);
                                        me->SummonCreature(MOB_MUCKSCALE_FLESHEATER, -408.258f, 4755.872f, -29.853f);
                                        me->SummonCreature(MOB_MUCKSCALE_FLESHEATER, -395.859f, 4759.430f, -29.952f);

                                        thirdPhaseDone = true;
                                        thirdPhaseTimer = 3000;
                                    }
                                }
                                secondPhaseTimer = 3000;
                            }
                            else
                                secondPhaseTimer -= diff;
                        }

                        if (thirdPhaseTimer)
                        {
                            if (thirdPhaseTimer <= diff)
                            {
                                if (thirdPhaseDone && !fourthPhaseDone)
                                {
                                    Creature* creature = GetClosestCreatureWithEntry(me, MOB_MUCKSCALE_FLESHEATER, 40.0f, true);

                                    if (!creature)
                                    {
                                        me->SummonCreature(MOB_MUCKSCALE_SERPENTUS, -406.158f, 4779.366f, -29.553f);

                                        if (creature)
                                            creature->AI()->SetGUID(player ? player->GetGUID() : 3);

                                        fourthPhaseDone = true;
                                    }
                                }

                                thirdPhaseTimer = 3000;
                            }
                            else
                                thirdPhaseTimer -= diff;
                        }
                    }
                }
            }
        };
};

class mob_muckscale_flesheater : public CreatureScript
{
    public:
        mob_muckscale_flesheater() : CreatureScript("mob_muckscale_flesheater")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_muckscale_flesheaterAI(creature);
        }

        struct mob_muckscale_flesheaterAI : public ScriptedAI
        {
            mob_muckscale_flesheaterAI(Creature* creature) : ScriptedAI(creature)
            {
                playerGuid = 0;
            }

            EventMap events;
            uint64 playerGuid;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_CONSUME_FLESH, 5000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 12000);
            }

            void SetGUID(uint64 guid, int32 data = 3)
            {
                playerGuid = guid;
            }

            void JustDied(Unit* killer)
            {
                me->DespawnOrUnsummon();
            }

            void IsSummonedBy(Unit* summoner)
            {
                if (Player* player = Player::GetPlayer(*me, playerGuid))
                    AttackStart(player);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CONSUME_FLESH:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_RUPTURE, false);
                            events.ScheduleEvent(EVENT_CONSUME_FLESH, 20000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_CONSUME_FLESH, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 20000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_muckscale_serpentus : public CreatureScript
{
    public:
        mob_muckscale_serpentus() : CreatureScript("mob_muckscale_serpentus")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_muckscale_serpentusAI(creature);
        }

        struct mob_muckscale_serpentusAI : public ScriptedAI
        {
            mob_muckscale_serpentusAI(Creature* creature) : ScriptedAI(creature)
            {
                playerGuid = 0;
            }

            EventMap events;
            uint64 playerGuid;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_FLAME_SHOCK, 5000);
                events.ScheduleEvent(EVENT_LIGHTNING_BOLT, 12000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 18000);
            }

            void SetGUID(uint64 guid, int32 data = 3)
            {
                playerGuid = guid;
            }

            void JustDied(Unit* killer)
            {
                me->DespawnOrUnsummon();
            }

            void IsSummonedBy(Unit* summoner)
            {
                if (Player* player = Player::GetPlayer(*me, playerGuid))
                    AttackStart(player);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FLAME_SHOCK:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_FLAME_SHOCK, false);
                            events.ScheduleEvent(EVENT_FLAME_SHOCK, 20000);
                            break;
                        case EVENT_LIGHTNING_BOLT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_LIGHTNING_BOLT, false);
                            events.ScheduleEvent(EVENT_LIGHTNING_BOLT, 20000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 20000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_oracle_hiss_ir : public CreatureScript
{
    public:
        mob_oracle_hiss_ir() : CreatureScript("mob_oracle_hiss_ir")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_oracle_hiss_irAI(creature);
        }

        struct mob_oracle_hiss_irAI : public ScriptedAI
        {
            mob_oracle_hiss_irAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 5000);
                events.ScheduleEvent(EVENT_CRY_OF_THE_SKY, 12000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 18000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CHAIN_LIGHTNING:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_CHAIN_LIGHTNING, false);
                            events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 20000);
                            break;
                        case EVENT_CRY_OF_THE_SKY:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_CRY_OF_THE_SKY, false);
                            events.ScheduleEvent(EVENT_CRY_OF_THE_SKY, 20000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 20000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_muckscale_flesh_hunter : public CreatureScript
{
    public:
        mob_muckscale_flesh_hunter() : CreatureScript("mob_muckscale_flesh_hunter")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_muckscale_flesh_hunterAI(creature);
        }

        struct mob_muckscale_flesh_hunterAI : public ScriptedAI
        {
            mob_muckscale_flesh_hunterAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_LIGHTNING_BOLT_2, 5000);
                events.ScheduleEvent(EVENT_WATER_SHIELD, 12000);
                events.ScheduleEvent(EVENT_WATER_SHIELD_2, 18000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 18000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_LIGHTNING_BOLT_2:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_LIGHTNING_BOLT_2, false);
                            events.ScheduleEvent(EVENT_LIGHTNING_BOLT_2, 32000);
                            break;
                        case EVENT_WATER_SHIELD:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_WATER_SHIELD, false);
                            events.ScheduleEvent(EVENT_WATER_SHIELD, 32000);
                            break;
                        case EVENT_WATER_SHIELD_2:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_WATER_SHIELD_2, false);
                            events.ScheduleEvent(EVENT_WATER_SHIELD_2, 32000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 32000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_muckscale_slayer : public CreatureScript
{
    public:
        mob_muckscale_slayer() : CreatureScript("mob_muckscale_slayer")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_muckscale_slayerAI(creature);
        }

        struct mob_muckscale_slayerAI : public ScriptedAI
        {
            mob_muckscale_slayerAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_BLOODY_RAGE, 5000);
                events.ScheduleEvent(EVENT_SKIN_FLAY, 12000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 18000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BLOODY_RAGE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_BLOODY_RAGE, false);
                            events.ScheduleEvent(EVENT_BLOODY_RAGE, 32000);
                            break;
                        case EVENT_SKIN_FLAY:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_SKIN_FLAY, false);
                            events.ScheduleEvent(EVENT_SKIN_FLAY, 32000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 32000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_muckscale_shaman : public CreatureScript
{
    public:
        mob_muckscale_shaman() : CreatureScript("mob_muckscale_shaman")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_muckscale_shamanAI(creature);
        }

        struct mob_muckscale_shamanAI : public ScriptedAI
        {
            mob_muckscale_shamanAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_BLOODY_RAGE, 5000);
                events.ScheduleEvent(EVENT_SKIN_FLAY, 12000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 18000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BLOODY_RAGE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_BLOODY_RAGE, false);
                            events.ScheduleEvent(EVENT_BLOODY_RAGE, 32000);
                            break;
                        case EVENT_SKIN_FLAY:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_SKIN_FLAY, false);
                            events.ScheduleEvent(EVENT_SKIN_FLAY, 32000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 32000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_zandalari_warbringer : public CreatureScript
{
    public:
        mob_zandalari_warbringer() : CreatureScript("mob_zandalari_warbringer")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_zandalari_warbringerAI(creature);
        }

        struct mob_zandalari_warbringerAI : public ScriptedAI
        {
            mob_zandalari_warbringerAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();
                me->AddAura(138046, me);
                me->AddAura(138047, me);
                me->AddAura(138048, me);
                me->AddAura(138050, me);
                me->AddAura(138049, me);

                events.ScheduleEvent(EVENT_HORIFIC_VISAGE, 5000);
                events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 14000);
                events.ScheduleEvent(EVENT_METEOR_SHOWER, 18000);
                events.ScheduleEvent(EVENT_SCARAB_SWARM, 30000);
                events.ScheduleEvent(EVENT_THUNDER_CRUSH, 55000);
                events.ScheduleEvent(EVENT_VENGEFUL_SPIRIT, 60000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_HORIFIC_VISAGE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_HORIFIC_VISAGE, false);
                            events.ScheduleEvent(EVENT_HORIFIC_VISAGE, 65000);
                            break;
                        case EVENT_METEOR_SHOWER:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_METEOR_SHOWER, false);
                            events.ScheduleEvent(EVENT_METEOR_SHOWER, 65000);
                            break;
                        case EVENT_SCARAB_SWARM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                            {
                                std::list<Creature*> creatureList;
                                GetCreatureListWithEntryInGrid(creatureList, me, 69773, 50.0f);

                                if (!creatureList.empty()) // Checks if the creatures spawned while the last time this event has been executed have been killed
                                    return;

                                me->CastSpell(target, SPELL_SCARAB_SWARM, false);
                            }
                            events.ScheduleEvent(EVENT_SCARAB_SWARM, 65000);
                            break;
                        case EVENT_THUNDER_CRUSH:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_THUNDER_CRUSH, false);
                            events.ScheduleEvent(EVENT_THUNDER_CRUSH, 65000);
                            break;
                        case EVENT_VENGEFUL_SPIRIT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_VENGEFUL_SPIRIT, false);
                            events.ScheduleEvent(EVENT_VENGEFUL_SPIRIT, 65000);
                            break;
                        case EVENT_UNSTABLE_SERUM:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_UNSTABLE_SERUM, false);
                            events.ScheduleEvent(EVENT_UNSTABLE_SERUM, 65000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

void AddSC_dread_wastes()
{
    // Rare Elite Mobs
    new mob_zandalari_warbringer();
    // Rare Mobs
    new mob_ik_ik_the_nimble();
    new mob_ai_li_skymirror();
    new mob_gar_lok();
    new mob_dak_the_breaker();
    new mob_nalash_verdantis();
    // Elite Mobs
    new mob_adjunct_kree_zot();
    new mob_dread_fearbringer();
    new mob_dread_kunchong();
    new mob_dread_matriarch();
    new mob_elder_spindlegrin();
    new mob_hulking_kor_thik_fleshrender();
    new mob_ik_thik_amberstinger();
    new mob_ik_thik_kunchong();
    new mob_ik_thik_terrorclaw();
    new mob_karanosh();
    new mob_kypa_rak();
    new mob_manifestation_of_terror();
    new mob_shox_tik();
    new mob_wake_of_horror();
    new mob_warlord_gurthan();
    new mob_vengeful_spirit();
    // Standard Mobs
    new mob_overgrown_seacarp();
    new mob_hisek_the_swarmkeeper();
    new mob_hisek_the_swarmkeeper_two();
    new mob_klaxxi_traitor();
    new mob_discover_amberglow_bunny();
    new mob_kaz_tik_the_manipulator();
    new mob_second_kaz_tik_the_manipulator();
    new mob_muckscale_ripper();
    new mob_skeer_the_bloodseeker();
    new mob_muckscale_flesheater();
    new mob_muckscale_serpentus();
    new mob_oracle_hiss_ir();
    new mob_muckscale_flesh_hunter();
    new mob_muckscale_slayer();
    new mob_muckscale_shaman();
    // Game Objects
    new go_ancient_amber_chunk();
    new go_kunchong_cage();
}