minor_gubbur = Creature:new {
	objectName = "@mob/creature_names:minor_gubbur",
	socialGroup = "gubbur",
	faction = "",
	level = 4,
	chanceHit = 0.24,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 135,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 123,
	hideType = "hide_leathery",
	hideAmount = 123,
	boneType = "bone_mammal",
	boneAmount = 123,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/minor_gubbur.iff"},
	scale = 0.85,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = { }
}

CreatureTemplates:addCreatureTemplate(minor_gubbur, "minor_gubbur")
