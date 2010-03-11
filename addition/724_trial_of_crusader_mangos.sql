
-- instance
UPDATE `instance_template` SET `script`='instance_trial_of_the_crusader' WHERE `map`=649;
DELETE FROM `creature` WHERE `map` = 649 AND `id` IN 
(34797,34796,34799,35144,34780,34460,34463,34461,34471,34475,34472,34453,34455,34458,34454,34451,34456,34497,34496,34564,34467,35465,34468,35610,34473,34474,34441,34449,34448,34450);

-- announcers
UPDATE `creature_template` SET `npcflag`=1, `scriptname`='npc_toc_announcer' WHERE `entry`=34816;
UPDATE `creature_template` SET `scriptname`='boss_lich_king_toc' WHERE `entry`=35877;
UPDATE `creature_template` SET `minhealth`= 20000, `maxhealth` = 20000, `faction_A`= 1770, `faction_H` = 1770,  `scriptname`='npc_fizzlebang_toc' WHERE `entry`=35458;
UPDATE `creature_template` SET `scriptname`='npc_tirion_toc' WHERE `entry`=34996;
UPDATE `creature_template` SET `scriptname`='npc_garrosh_toc' WHERE `entry`=34995;
UPDATE `creature_template` SET `scriptname`='npc_rinn_toc' WHERE `entry`=34990;

-- grand crusaders
-- UPDATE `creature_template` SET `scriptname`='mob_toc_warrior' WHERE entry IN ();
-- UPDATE `creature_template` SET `scriptname`='mob_toc_mage' WHERE entry IN ();
-- UPDATE `creature_template` SET `scriptname`='mob_toc_shaman' WHERE entry IN ();
-- UPDATE `creature_template` SET `scriptname`='mob_toc_hunter' WHERE entry IN ();
-- UPDATE `creature_template` SET `scriptname`='mob_toc_rogue' WHERE entry IN ();
-- UPDATE `creature_template` SET `scriptname`='mob_toc_priest' WHERE entry IN ();
-- UPDATE `creature_template` SET `scriptname`='mob_toc_dk' WHERE entry IN ();
-- UPDATE `creature_template` SET `scriptname`='mob_toc_paladin' WHERE entry IN ();
-- UPDATE `creature_template` SET `scriptname`='mob_toc_druid' WHERE entry IN ();
-- UPDATE `creature_template` SET `scriptname`='mob_toc_warlock' WHERE entry IN ();

-- UPDATE `creature_template` SET `scriptname`='mob_toc_pet_cat' WHERE `entry` = 35465;
-- UPDATE `creature_template` SET `scriptname`='mob_toc_pet_dog' WHERE `entry` = 35610;

UPDATE `creature_template` SET `lootid`= 0 WHERE  `entry` IN
(34460,34463,34461,34471,34475,34472,34453,34455,34458,34454,34451,34456,34467,35465,34468,35610,34473,34474,34441,34449,34448,34450);
UPDATE `creature_template` SET `lootid`= 0 WHERE  `entry` IN
(12266,12209,12212,12281,12190,12284,12269,12272,12229,12187,12091,12088,12169,12103,12106,12112,12166,12163,12175,12183,12303,12300);
UPDATE `creature_template` SET `lootid`= 0 WHERE  `entry` IN
(12267,12210,12213,12282,12191,12285,12270,12273,12230,12188,12092,12089,12170,12104,12107,12113,12167,12164,12181,12184,12304,12301);
UPDATE `creature_template` SET `lootid`= 0 WHERE  `entry` IN
(12268,12211,12214,12283,12192,12286,12271,12274,12231,12189,12093,12090,12171,12105,12108,12114,12168,12165,12182,12185,12305,12302);

-- N10
DELETE FROM `creature_loot_template` WHERE `entry` IN 
(34460,34463,34461,34471,34475,34472,34453,34455,34458,34454,34451,34456,34467,35465,34468,35610,34473,34474,34441,34449,34448,34450);
-- H10
DELETE FROM `creature_loot_template` WHERE `entry` IN 
(12266,12209,12212,12281,12190,12284,12269,12272,12229,12187,12091,12088,12169,12103,12106,12112,12166,12163,12175,12183,12303,12300);
-- N25
DELETE FROM `creature_loot_template` WHERE `entry` IN 
(12267,12210,12213,12282,12191,12285,12270,12273,12230,12188,12092,12089,12170,12104,12107,12113,12167,12164,12181,12184,12304,12301);
-- H25
DELETE FROM `creature_loot_template` WHERE `entry` IN 
(12268,12211,12214,12283,12192,12286,12271,12274,12231,12189,12093,12090,12171,12105,12108,12114,12168,12165,12182,12185,12305,12302);

-- Nortrend beasts
-- UPDATE `creature_template` SET `scriptname`='boss_gormok' WHERE entry=34796;
-- UPDATE `creature_template` SET `scriptname`='boss_dreadscale' WHERE entry=34799;
-- UPDATE `creature_template` SET `scriptname`='boss_acidmaw' WHERE entry=35144;
-- UPDATE `creature_template` SET `scriptname`='boss_icehowl' WHERE entry=34797;
UPDATE `creature_template` SET `lootid`= 0 WHERE  `entry` IN
(34796,34799,35144);
DELETE FROM `creature_loot_template`  WHERE  `entry` IN
(34796,34799,35144);

-- Jaraxxus
UPDATE `creature_template` SET `scriptname`='boss_jaraxxus', `AIName` ='' WHERE entry= 34780;
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (34780, 34784, 34813, 34815, 34825, 34826);
UPDATE `creature_template` SET `scriptname`='mob_legion_flame', `AIName` ='', `faction_A`= 14, `faction_H` = 14 WHERE entry = 34784;
UPDATE `creature_template` SET `scriptname`='mob_infernal_volcano', `AIName` ='' WHERE entry = 34813;
UPDATE `creature_template` SET `scriptname`='mob_fel_infernal', `AIName` ='' WHERE entry = 34815;
UPDATE `creature_template` SET `scriptname`='mob_nether_portal', `AIName` ='' WHERE entry = 34825;
UPDATE `creature_template` SET `scriptname`='mob_mistress_of_pain', `AIName` ='' WHERE entry = 34826;

-- Froja's
-- UPDATE `creature_template` SET `scriptname`='boss_fjola', `AIName` ='' WHERE entry=34497;
-- UPDATE `creature_template` SET `scriptname`='boss_eydis', `AIName` ='' WHERE entry=34496;
-- UPDATE `creature_template` SET `scriptname`='mob_light_essence', `AIName` ='' WHERE entry = 34568;
-- UPDATE `creature_template` SET `scriptname`='mob_dark_essence', `AIName` ='' WHERE entry = 34567;

-- Anub'arak
-- UPDATE `creature_template` SET `scriptname`='boss_anubarak' WHERE entry=34564;

