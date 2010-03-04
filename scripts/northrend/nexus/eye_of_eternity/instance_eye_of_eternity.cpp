/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Instance_Eye_of_Eternity
SD%Complete: 90%
SDComment:
SDAuthor: Tassadar
SDCategory: Nexus, Eye of Eternity
EndScriptData */

#include "precompiled.h"
#include "eye_of_eternity.h"

#define DISABLED_ENTER_MESSAGE "You cannot enter Eye of Eternity now"
#define EXIT_MAP 571
#define EXIT_X 3864
#define EXIT_Z 6987
#define EXIT_Y 152


struct MANGOS_DLL_DECL instance_eye_of_eternity : public ScriptedInstance
{
    instance_eye_of_eternity(Map* pMap) : ScriptedInstance(pMap) {Initialize();}

    std::string strInstData;
    uint32 m_auiEncounter[MAX_ENCOUNTER];
    uint8 m_uiInstanceEnterRules;
    std::list<uint64> m_lLeavePlayerList;
    uint32 m_uiKickPlayersTimer;

    void Initialize()
    {
        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
        m_uiInstanceEnterRules = DATA_ALLOW_ENTER_VEHICLE;
        m_lLeavePlayerList.clear();
        m_uiKickPlayersTimer = 3000;
    }

    void OnPlayerEnter(Player* pPlayer)
    {
        if(m_uiInstanceEnterRules == DATA_ALLOW_ENTER)
            return;
        else if(m_uiInstanceEnterRules == DATA_ALLOW_ENTER_VEHICLE)
        {
            Vehicle *pTemp = pPlayer->SummonVehicle(NPC_WYRMREST_SKYTALON, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0);
            if(!pTemp)
                return;
            ((Creature*)pTemp)->SetCreatorGUID(pPlayer->GetGUID());
            uint32 health = 100000 + (pPlayer->GetMaxHealth()*2); // may be wrong
            ((Creature*)pTemp)->SetMaxHealth(health);
            ((Creature*)pTemp)->SetHealth(health);
            pPlayer->EnterVehicle(pTemp, 0, false);
            pPlayer->SendInitialPacketsAfterAddToMap();
        }
        else if(m_uiInstanceEnterRules == DATA_DISABLE_ENTER)
            m_lLeavePlayerList.push_back(pPlayer->GetGUID());
    }
    void OnCreatureCreate(Creature* pCreature)
    {
        switch(pCreature->GetEntry())
        {
            default:
                break;
        }
    }
    
    void OnObjectCreate(GameObject* pGo)
    {
        switch(pGo->GetEntry())
        {
            default:
                break;
        }
    }

    bool IsEncounterInProgress() const
    {
        for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            if (m_auiEncounter[i] == IN_PROGRESS)
                return true;

        return false;
    }

    void SetData(uint32 uiType, uint32 uiData)
    {
        switch(uiType)
        {
            case TYPE_MALYGOS:
                m_auiEncounter[0] = uiData;
                break;
            case TYPE_INSTANCE_ENTER_RULES:
                m_uiInstanceEnterRules = uiData;
                break;
        }

        if (uiData == DONE)
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << m_auiEncounter[0];

            strInstData = saveStream.str();

            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
        }
    }

    const char* Save()
    {
        return strInstData.c_str();
    }

    void Load(const char* chrIn)
    {
        if (!chrIn)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(chrIn);

        std::istringstream loadStream(chrIn);
        loadStream >> m_auiEncounter[0];

        for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
        {
            if (m_auiEncounter[i] == IN_PROGRESS)
                m_auiEncounter[i] = NOT_STARTED;
        }

        OUT_LOAD_INST_DATA_COMPLETE;
    }

    uint32 GetData(uint32 uiType)
    {
        switch(uiType)
        {
            case TYPE_MALYGOS:
                return m_auiEncounter[0];   
        }
        return 0;
    }

    uint64 GetData64(uint32 uiData)
    {
        switch(uiData)
        {
            default:
                return 0;
        }
        return 0;
    }
};

InstanceData* GetInstanceData_instance_eye_of_eternity(Map* pMap)
{
    return new instance_eye_of_eternity(pMap);
}

void AddSC_instance_eye_of_eternity()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "instance_eye_of_eternity";
    pNewScript->GetInstanceData = &GetInstanceData_instance_eye_of_eternity;
    pNewScript->RegisterSelf();
}
