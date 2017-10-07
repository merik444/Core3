enhanced_kwi = Creature:new {
	objectName = "@mob/creature_names:geonosian_enhanced_kwi",
	socialGroup = "geonosian_creature",
	pvpFaction = "",
	faction = "",
	level = 355,
	chanceHit = 47.5,
	damageMin = 490,
	damageMax = 890,
	baseXp = 10081,
	baseHAM = 40000,
	baseHAMmax = 51000,
	armor = 2,
	resists = {40,40,5,40,35,25,35,45,15},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 16,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/kwi.iff"},
	scale = 1.4,
	lootGroups = {
		{
	        groups = 
			{
				{group = "armor_attachments", chance = 10000000},
			},
			lootChance = 1500000,
		},
		{
	        groups = 
			{
				{group = "clothing_attachments", chance = 10000000},
			},
			lootChance = 1000000,
		},
	 	{
	        groups = 
			{
				
				{group = "geonosian_relic", chance = 3500000},
				{group = "geonosian_common", chance = 5000000},
				{group = "mastery_geocave_jewelry", chance = 1500000},
			},
			lootChance = 1000000,
		},
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enhanced_kwi, "enhanced_kwi")
