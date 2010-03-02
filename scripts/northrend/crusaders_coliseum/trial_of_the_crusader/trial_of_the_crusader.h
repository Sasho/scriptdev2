
#ifndef DEF_CRUSADER_H
#define DEF_CRUSADER_H

enum
{
    MAX_ENCOUNTERS              = 6,
    NPC_BARRENT                 = 34816,

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

    TYPE_STAGE                  = 0,
    TYPE_BEASTS                 = 1,
    TYPE_JARAXXUS               = 2,
    TYPE_CRUSADERS              = 3,
    TYPE_FROJA                  = 4,
    TYPE_ANUBARAK               = 5,

    TYPE_DIFFICULTY             = 101,

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
};

#endif
