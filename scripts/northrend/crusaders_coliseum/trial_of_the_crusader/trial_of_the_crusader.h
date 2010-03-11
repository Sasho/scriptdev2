
#ifndef DEF_CRUSADER_H
#define DEF_CRUSADER_H

enum
{
    TYPE_STAGE                  = 0,
    TYPE_BEASTS                 = 1,
    TYPE_JARAXXUS               = 2,
    TYPE_CRUSADERS              = 3,
    TYPE_FROJA                  = 4,
    TYPE_LICH_KING              = 5,
    TYPE_ANUBARAK               = 6,
    TYPE_COUNTER                = 7,
    TYPE_EVENT                  = 8,
    MAX_ENCOUNTERS              = 9,

    NPC_BARRENT                 = 34816,
    NPC_TIRION                  = 34996,
    NPC_FIZZLEBANG              = 35458,
    NPC_GARROSH                 = 34995,
    NPC_RINN                    = 34990,
    NPC_LICH_KING_0             = 16980,
    NPC_LICH_KING_1             = 35877,

    NPC_ICEHOWL                 = 34797,
    NPC_GORMOK                  = 34796,
    NPC_DREADSCALE              = 34799,
    NPC_ACIDMAW                 = 35144,

    NPC_JARAXXUS                = 34780,

    NPC_CRUSADER_1_1            = 34460,
    NPC_CRUSADER_1_2            = 34463,
    NPC_CRUSADER_1_3            = 34461,
    NPC_CRUSADER_1_4            = 34471,
    NPC_CRUSADER_1_5            = 34475,
    NPC_CRUSADER_1_6            = 34472,
    NPC_CRUSADER_1_7            = 34467,
    NPC_CRUSADER_1_8            = 34468,
    NPC_CRUSADER_1_9            = 34473,
    NPC_CRUSADER_1_10           = 34474,

    NPC_CRUSADER_2_1            = 34453,
    NPC_CRUSADER_2_2            = 34455,
    NPC_CRUSADER_2_3            = 34458,
    NPC_CRUSADER_2_4            = 34454,
    NPC_CRUSADER_2_5            = 34451,
    NPC_CRUSADER_2_6            = 34456,
    NPC_CRUSADER_2_7            = 34441,
    NPC_CRUSADER_2_8            = 34449,
    NPC_CRUSADER_2_9            = 34448,
    NPC_CRUSADER_2_10           = 34450,

    NPC_CRUSADER_0_1            = 35465,
    NPC_CRUSADER_0_2            = 35610,

    NPC_LIGHTBANE               = 34497,
    NPC_DARKBANE                = 34496,

    NPC_ANUBARAK                = 34564,

    GO_CRUSADERS_CACHE_10       = 195631,
    GO_CRUSADERS_CACHE_25       = 195632,
    GO_CRUSADERS_CACHE_10_H     = 195633,
    GO_CRUSADERS_CACHE_25_H     = 195635,

    GO_TRIBUTE_CHEST_10H_25     = 195665,
    GO_TRIBUTE_CHEST_10H_45     = 195666,
    GO_TRIBUTE_CHEST_10H_50     = 195667,
    GO_TRIBUTE_CHEST_10H_99     = 195668,

    GO_TRIBUTE_CHEST_25H_25     = 195669,
    GO_TRIBUTE_CHEST_25H_45     = 195670,
    GO_TRIBUTE_CHEST_25H_50     = 195671,
    GO_TRIBUTE_CHEST_25H_99     = 195672,

    GO_ARGENT_COLISEUM_FLOOR    = 195527, //20943

    TYPE_DIFFICULTY             = 101,
    TYPE_EVENT_TIMER            = 102,
    TYPE_EVENT_NPC              = 103,
    TYPE_NORTHREND_BEASTS       = 110,

    DESPAWN_TIME                = 300000

};

struct Locations
{
    float x, y, z;
    uint32 id;
};

static Locations SpawnLoc[]=
{
    {559.257996, 90.266197, 395.122986},  // 0 Barrent
    {563.672974, 139.571, 393.837006},    // 1 Center
    {563.833008, 187.244995, 394.5},      // 2 Backdoor
    {583.336182, 181.737717, 395.135956}, // 3 
    {545.914185, 180.859543, 395.137909}, // 4 
    {599.042358, 179.260727, 395.137146}, // 5
    {532.248901, 180.331955, 395.132658}, // 6
    {586.342285, 181.515823, 395.135956}, // 7 
    {539.239929, 181.825577, 395.137909}, // 8 
    {599.042358, 179.260727, 395.137146}, // 9
    {588.720581, 183.015472, 395.132658}, // 10
    {551.534119, 184.214478, 395.139526}, // 11
    {576.231201, 183.941071, 395.139526}, // 12
    {552.811610, 171.985779, 394.671661}, // 13
    {575.641724, 170.351501, 394.659943}, // 14
    {516.633972, 159.391708, 395.137543}, // 15
    {612.816956, 161.477921, 395.136810}, // 16
    {563.549, 152.474, 394.393},          // 17 - Lich king start
    {563.547, 141.613, 393.908},          // 18 - Lich king end
    {787.932556, 133.28978, 142.612152},  // 19 - Anub'arak start location
    {618.157898, 132.640869, 139.559769}, // 20 - Anub'arak move point location
    {508.104767, 138.247345, 395.128052}, // 21 - Fizzlebang start location
};

struct WayPoints
{
    WayPoints(uint32 _id, float _x, float _y, float _z)
    {
        id = _id;
        x = _x;
        y = _y;
        z = _z;
    }
    uint32 id;
    float x, y, z;
};

enum SpellTableParameters
{
  DIFFICULTY_LEVELS = 4,
  CAST_ON_SELF      = 1000,
  CAST_ON_SUMMONS,
  CAST_ON_VICTIM,
  CAST_ON_RANDOM,
  CAST_ON_BOTTOMAGGRO,
};

struct SpellTable
{
    uint32 id;
    uint32 m_uiSpellEntry[DIFFICULTY_LEVELS];          // Stores spell entry for difficulty levels
    uint32 m_uiSpellTimerMin[DIFFICULTY_LEVELS];       // The timer (min) before the next spell casting, in milliseconds
    uint32 m_uiSpellTimerMax[DIFFICULTY_LEVELS];       // The timer (max) before the next spell casting
    uint32 m_uiStageMask;                              // The mask of stages where spell is casted
    uint32 m_CastTarget;                              // Target on casting spell
    bool   m_IsVisualEffect;                           // Spellcasting is visual effect or real effect
    bool   m_IsBugged;                                 // Need override for this spell
};

enum uiWorldStates
{
    UPDATE_STATE_UI_SHOW            = 4390,
    UPDATE_STATE_UI_COUNT           = 4389,
};

#endif
