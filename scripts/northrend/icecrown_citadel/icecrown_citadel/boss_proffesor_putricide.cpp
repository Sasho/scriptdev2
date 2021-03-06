/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: boss_proffesor_putricide
SD%Complete: 20%
SDComment: by /dev/rsa
SDCategory: Icecrown Citadel
EndScriptData */

#include "precompiled.h"
#include "def_spire.h"

enum BossSpells
{
    SPELL_SLIME_PUDDLE            = 70346,
    SPELL_UNSTABLE_EXPERIMENT     = 71968,
    SPELL_TEAR_GAS                = 71617,
    SPELL_TEAR_GAS_1              = 71618,
    SPELL_CREATE_CONCOCTION       = 71621,
    SPELL_CHOKING_GAS             = 71278,
    SPELL_CHOKING_GAS_EXPLODE     = 71279,
    SPELL_MALLEABLE_GOO           = 70852,
    SPELL_GUZZLE_POTIONS          = 73122,
    SPELL_MUTATED_STRENGTH        = 71603,
    SPELL_MUTATED_PLAGUE          = 72672,
//
    NPC_GAS_CLOUD                 = 37562,
    SPELL_GASEOUS_BLOAT           = 70672,
    SPELL_EXPUNGED_GAS            = 70701,
    SPELL_SOUL_FEAST              = 71203,
//
    NPC_VOLATILE_OOZE             = 37697,
    SPELL_OOZE_ADHESIVE           = 70447,
    SPELL_OOZE_ERUPTION           = 70492,
//
    NPC_MUTATED_ABOMINATION       = 37672,
    SPELL_MUTATED_TRANSFORMATION  = 70311,
    SPELL_EAT_OOZE                = 72527,
    SPELL_REGURGITATED_OOZE       = 70539,
    SPELL_MUTATED_SLASH           = 70542,
    SPELL_MUTATED_AURA            = 70405,

    SPELL_BERSERK                 = 47008,
//
//    VIEW_1                        = 30881,
//    VIEW_2                        = 38216,
//    VIEW_3                        = 38216,
};

static Locations SpawnLoc[]=
{
    {4356.779785f, 3263.510010f, 389.398010f},  // 0 Putricide start point o=1.586
    {4295.081055f, 3188.883545f, 389.330261f},  // 1 Puticide Festergut say, o=4.27
    {4417.302246f, 3188.219971f, 389.332520f},  // 2 Putricide Rotface say o=5.102
};

struct MANGOS_DLL_DECL boss_proffesor_putricideAI : public ScriptedAI
{
    boss_proffesor_putricideAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        bsw = new BossSpellWorker(this);
        Reset();
    }

    ScriptedInstance *pInstance;
    BossSpellWorker* bsw;
    uint8 stage;
    bool intro;
    uint32 UpdateTimer;

    void Reset()
    {
        if (!pInstance) return;
        pInstance->SetData(TYPE_PUTRICIDE, NOT_STARTED);
        stage = 0;
        intro = false;
        UpdateTimer = 1000;
    }

    void MoveInLineOfSight(Unit* pWho) 
    {
        if (!pInstance || intro) return;
        if (pInstance->GetData(TYPE_EVENT_NPC) == NPC_PROFESSOR_PUTRICIDE
            || !pWho->IsWithinDistInMap(m_creature, 40.0f)) return;

        DoScriptText(-1631249,m_creature, pWho);
        intro = true;
    }

    void KilledUnit(Unit* pVictim)
    {
    switch (urand(0,1)) {
        case 0:
               DoScriptText(-1631241,m_creature,pVictim);
               break;
        case 1:
               DoScriptText(-1631242,m_creature,pVictim);
               break;
        }
    }

    void Aggro(Unit *who) 
    {
        if (!pInstance) return;
        pInstance->SetData(TYPE_PUTRICIDE, IN_PROGRESS);
        DoScriptText(-1631240,m_creature, who);
    }

    void JustDied(Unit *killer)
    {
        if (!pInstance) return;
        pInstance->SetData(TYPE_PUTRICIDE, DONE);
        DoScriptText(-1631243,m_creature, killer);
    }

    void JustReachedHome()
    {
        if (pInstance) pInstance->SetData(TYPE_PUTRICIDE, FAIL);
    }

    void UpdateAI(const uint32 diff)
    {
        if (pInstance->GetData(TYPE_EVENT_NPC) == NPC_PROFESSOR_PUTRICIDE)
        {
            UpdateTimer = pInstance->GetData(TYPE_EVENT_TIMER);
            if (UpdateTimer <= diff)
            {
            debug_log("EventMGR: creature %u received signal %u ",m_creature->GetEntry(),pInstance->GetData(TYPE_EVENT));
            switch (pInstance->GetData(TYPE_EVENT))
                {
                case 500:
                          m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                          m_creature->NearTeleportTo(SpawnLoc[1].x, SpawnLoc[1].y, SpawnLoc[1].z, 4.27f);
                          DoScriptText(-1631201, m_creature);
                          UpdateTimer = 10000;
                          pInstance->SetData(TYPE_EVENT,510);
                          break;
                case 510:
                          m_creature->NearTeleportTo(SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, 1.586f);
                          m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                          UpdateTimer = 2000;
                          pInstance->SetData(TYPE_EVENT,520);
                          break;
                case 550:
                          m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                          m_creature->NearTeleportTo(SpawnLoc[1].x, SpawnLoc[1].y, SpawnLoc[1].z, 4.27f);
                          DoScriptText(-1631202, m_creature);
                          UpdateTimer = 10000;
                          pInstance->SetData(TYPE_EVENT,560);
                          break;
                case 560:
                          m_creature->NearTeleportTo(SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, 1.586f);
                          m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                          UpdateTimer = 2000;
                          pInstance->SetData(TYPE_EVENT,570);
                          break;
                case 600:
                          m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                          m_creature->NearTeleportTo(SpawnLoc[2].x, SpawnLoc[2].y, SpawnLoc[2].z, 5.102f);
                          DoScriptText(-1631220, m_creature);
                          UpdateTimer = 10000;
                          pInstance->SetData(TYPE_EVENT,610);
                          break;
                case 610:
                          m_creature->NearTeleportTo(SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, 1.586f);
                          m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                          UpdateTimer = 2000;
                          pInstance->SetData(TYPE_EVENT,620);
                          break;
                default:
                          break;
                }
             } else UpdateTimer -= diff;
             pInstance->SetData(TYPE_EVENT_TIMER, UpdateTimer);
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        switch(stage)
        {
            case 0: 
                    bsw->timedCast(SPELL_SLIME_PUDDLE, diff);

                    if (bsw->timedQuery(SPELL_UNSTABLE_EXPERIMENT, diff))
                        switch(urand(0,1))
                          {
                          case 0:
                                 bsw->doSummon(NPC_VOLATILE_OOZE);
                                 break;
                          case 1:
                                 bsw->doSummon(NPC_GAS_CLOUD);
                                 break;
                          }

                    break;
            case 1: 
                    bsw->doCast(SPELL_TEAR_GAS);
                    bsw->doCast(SPELL_CREATE_CONCOCTION);
                    stage = 2;
                    break;
            case 2: 
                    bsw->timedCast(SPELL_SLIME_PUDDLE, diff);

                    if (bsw->timedQuery(SPELL_UNSTABLE_EXPERIMENT, diff))
                        switch(urand(0,1))
                          {
                          case 0:
                                 bsw->doSummon(NPC_VOLATILE_OOZE);
                                 break;
                          case 1:
                                 bsw->doSummon(NPC_GAS_CLOUD);
                                 break;
                          }

                    bsw->timedCast(SPELL_CHOKING_GAS, diff);

                    bsw->timedCast(SPELL_MALLEABLE_GOO, diff);

                    break;
            case 3: 
                    bsw->doCast(SPELL_TEAR_GAS);
                    bsw->doCast(SPELL_GUZZLE_POTIONS);
                    bsw->doCast(SPELL_MUTATED_STRENGTH);
                    bsw->doCast(SPELL_MUTATED_PLAGUE);
                    stage = 4;
                    break;
            case 4: 
                    if (bsw->timedQuery(SPELL_UNSTABLE_EXPERIMENT, diff))
                        switch(urand(0,1))
                          {
                          case 0:
                                 bsw->doSummon(NPC_VOLATILE_OOZE);
                                 break;
                          case 1:
                                 bsw->doSummon(NPC_GAS_CLOUD);
                                 break;
                          }

                    break;
            }

                    bsw->timedCast(SPELL_CHOKING_GAS, diff);

                    if (bsw->timedQuery(SPELL_MALLEABLE_GOO, diff))
                       {
                          bsw->doCast(SPELL_MALLEABLE_GOO);
                       }


        if ( stage ==0 && m_creature->GetHealthPercent() < 80.0f ) stage = 1;
        if ( stage ==2 && m_creature->GetHealthPercent() < 35.0f ) stage = 3;

        if (bsw->timedQuery(SPELL_BERSERK, diff)){
                 bsw->doCast(SPELL_BERSERK);
                 DoScriptText(-1631244,m_creature);
                 }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_proffesor_putricide(Creature* pCreature)
{
    return new boss_proffesor_putricideAI(pCreature);
}

struct MANGOS_DLL_DECL mob_icc_gas_cloudAI : public ScriptedAI
{
    mob_icc_gas_cloudAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        bsw = new BossSpellWorker(this);
        Reset();
    }

    ScriptedInstance* m_pInstance;
    BossSpellWorker* bsw;

    void Reset()
    {
        m_creature->SetInCombatWithZone();
        m_creature->SetRespawnDelay(DAY);
    }

    void Aggro(Unit *who)
    {
        if (!m_pInstance) return;
    }

    void JustReachedHome()
    {
        if (!m_pInstance) return;
            m_creature->ForcedDespawn();
    }

    void UpdateAI(const uint32 uiDiff)
    {

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        bsw->timedCast(SPELL_GASEOUS_BLOAT, uiDiff);
        bsw->timedCast(SPELL_SOUL_FEAST, uiDiff);
        if (m_creature->getVictim()->IsWithinDistInMap(m_creature, 1.0f)
            && bsw->hasAura(SPELL_GASEOUS_BLOAT, m_creature->getVictim()))
            {
               bsw->doCast(SPELL_EXPUNGED_GAS);
               m_creature->ForcedDespawn();
            };
    }
};

CreatureAI* GetAI_mob_icc_gas_cloud(Creature* pCreature)
{
    return new mob_icc_gas_cloudAI(pCreature);
}

struct MANGOS_DLL_DECL mob_icc_volatile_oozeAI : public ScriptedAI
{
    mob_icc_volatile_oozeAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        bsw = new BossSpellWorker(this);
        Reset();
    }

    ScriptedInstance* m_pInstance;
    BossSpellWorker* bsw;

    void Reset()
    {
        m_creature->SetInCombatWithZone();
        m_creature->SetRespawnDelay(DAY);
    }

    void Aggro(Unit *who)
    {
        if (!m_pInstance) return;
    }

    void JustReachedHome()
    {
        if (!m_pInstance) return;
             m_creature->ForcedDespawn();
    }

    void UpdateAI(const uint32 uiDiff)
    {

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        bsw->timedCast(SPELL_OOZE_ADHESIVE, uiDiff, m_creature->getVictim());
        bsw->timedCast(SPELL_SOUL_FEAST, uiDiff);
        if (bsw->timedQuery(SPELL_OOZE_ERUPTION, uiDiff))
             if (m_creature->getVictim()->IsWithinDistInMap(m_creature, 1.0f))
                {
                 bsw->doCast(SPELL_OOZE_ERUPTION);
//               m_creature->ForcedDespawn();
                };
    }
};

CreatureAI* GetAI_mob_icc_volatile_ooze(Creature* pCreature)
{
    return new mob_icc_volatile_oozeAI(pCreature);
}

void AddSC_boss_proffesor_putricide()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_proffesor_putricide";
    newscript->GetAI = &GetAI_boss_proffesor_putricide;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_icc_volatile_ooze";
    newscript->GetAI = &GetAI_mob_icc_volatile_ooze;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_icc_gas_cloud";
    newscript->GetAI = &GetAI_mob_icc_gas_cloud;
    newscript->RegisterSelf();
}
