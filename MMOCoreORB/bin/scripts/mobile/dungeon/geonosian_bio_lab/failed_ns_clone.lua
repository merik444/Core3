failed_ns_clone = Creature:new {
	objectName = "@mob/creature_names:failed_ns_clone",
	customName = "A Failed Nightsister Clone",
	socialGroup = "geonosian_creature",
	pvpFaction = "",
	faction = "",
	level = 400,
	chanceHit = 35.5,
	damageMin = 1820,
	damageMax = 2950,
	baseXp = 28654,
	baseHAM = 101000,
	baseHAMmax = 122000,
	armor = 2,
	resists = {65,65,65,65,65,65,65,65,45},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dathomir_nightsister_elder.iff"},
	lootGroups = {
		{
	        groups = 
			{
				{group = "geonosian_epic", chance = 10000000},
			},
			lootChance = 2500000,
		},
		{
	        	groups = 
			{
				{group = "armor_attachments", chance = 10000000},
			},
			lootChance = 4500000,
		},
		{
	        	groups = 
			{
				{group = "clothing_attachments", chance = 10000000},
			},
			lootChance = 4500000,
		},
		{
			groups = {
				{group = "power_crystals", chance = 5000000},
				{group = "nightsister_common", chance = 5000000},
				
			},
			lootChance = 7500000,
		},
		{
			groups = 
			{
				{group = "pistols", chance = 2500000},
				{group = "rifles", chance = 2500000},
				{group = "carbines", chance = 2500000},
				{group = "melee_weapons", chance = 2500000},
			},
			lootChance = 5000000,
		},
		{
			groups = 
			{
				{group = "geonosian_cubes", chance = 10000000},
			},
			lootChance = 2500000,
		},
	},
	weapons = {"dark_trooper_weapons"},
	conversationTemplate = "",
	attacks = merge(tkamaster,brawlermaster,forcewielder)
}

CreatureTemplates:addCreatureTemplate(failed_ns_clone, "failed_ns_clone")
