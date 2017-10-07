graul_marauder = Creature:new {
	objectName = "@mob/creature_names:graul_marauder",
	socialGroup = "graul",
	faction = "",
	level = 140,
	chanceHit = 10.75,
	damageMin = 2595,
	damageMax = 2950,
	baseXp = 16411,
	baseHAM = 120000,
	baseHAMmax = 125000,
	armor = 2,
	resists = {95,95,95,95,95,95,95,95,50},
	meatType = "meat_carnivore",
	meatAmount = 5000,
	hideType = "hide_leathery",
	hideAmount = 5000,
	boneType = "bone_mammal",
	boneAmount = 5000,
	milk = 0,
	tamingChance = 0,
	ferocity = 15,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/graul_hue.iff"},
	scale = 1.35,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareableeding",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(graul_marauder, "graul_marauder")
