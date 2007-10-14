/* Copyright (C) 2006,2007 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

#include "../../sc_defines.h"

#define SPELL_ARCINGSMASH           39144
#define SPELL_KNOCKAWAY             22893
#define SPELL_WSTOMP                16727

#define SAY_AGGRO           "None may steal the secrets of the makers!"
#define SOUND_AGGRO         5851


struct MANGOS_DLL_DECL boss_ironayaAI : public ScriptedAI
{
    boss_ironayaAI(Creature *c) : ScriptedAI(c) {EnterEvadeMode();}

    uint32 Arcing_Timer;
    bool hasCastedWstomp;
    bool hasCastedKnockaway;
    bool InCombat;

    void EnterEvadeMode()
    {
        Arcing_Timer = 3000;
        hasCastedKnockaway = false;
        hasCastedWstomp = false;
        InCombat = false;

        m_creature->RemoveAllAuras();
        m_creature->DeleteThreatList();
        m_creature->CombatStop();
        DoGoHome();
    }

    void AttackStart(Unit *who)
    {
        if (!who)
            return;

        if (who->isTargetableForAttack() && who!= m_creature)
        {
            //Say our dialog
            if(!InCombat)
            {
                DoYell(SAY_AGGRO,LANG_UNIVERSAL,NULL);
                DoPlaySoundToSet(m_creature,SOUND_AGGRO);

                InCombat = true;
            }

            DoStartMeleeAttack(who);
        }
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (!who || m_creature->getVictim())
            return;

        if (who->isTargetableForAttack() && who->isInAccessablePlaceFor(m_creature) && m_creature->IsHostileTo(who))
        {
            float attackRadius = m_creature->GetAttackDistance(who);
            if (m_creature->IsWithinDistInMap(who, attackRadius) && m_creature->GetDistanceZ(who) <= CREATURE_Z_ATTACK_RANGE && m_creature->IsWithinLOSInMap(who))
            {
                if(who->HasStealthAura())
                    who->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);

                //Begin melee attack if we are within range
                DoStartMeleeAttack(who);
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim())
            return;

        //If we are <50% hp do knockaway ONCE
        if (!hasCastedKnockaway && m_creature->GetHealth()*2 < m_creature->GetMaxHealth())
        {		
            m_creature->CastSpell(m_creature->getVictim(),SPELL_KNOCKAWAY, true);

            // current aggro target is knocked away pick new target
            Unit* Target = SelectUnit(SELECT_TARGET_TOPAGGRO, 0);

            if (!Target || Target == m_creature->getVictim())
                Target = SelectUnit(SELECT_TARGET_TOPAGGRO, 1);

            if (Target)
                m_creature->TauntApply(Target);

            //Shouldn't cast this agian
            hasCastedKnockaway = true;
        }

        //Arcing_Timer
        if (Arcing_Timer < diff)
        {
            //Cast
            DoCast(m_creature,SPELL_ARCINGSMASH);

            //10 seconds until we should cast this agian
            Arcing_Timer = 13000;
        }else Arcing_Timer -= diff;

        if (!hasCastedWstomp && m_creature->GetHealth()*4 < m_creature->GetMaxHealth())
        {
            //Cast
            DoCast(m_creature,SPELL_WSTOMP);
            hasCastedWstomp = true;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_ironaya(Creature *_Creature)
{
    return new boss_ironayaAI (_Creature);
}

void AddSC_boss_ironaya()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="boss_ironaya";
    newscript->GetAI = GetAI_boss_ironaya;
    m_scripts[nrscripts++] = newscript;
}