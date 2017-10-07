/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCELIGHTNINGCONE2NPCCOMMAND_H_
#define FORCELIGHTNINGCONE2NPCCOMMAND_H_

#include "ForcePowersQueueCommand.h"

class ForceLightningCone2NPCCommand : public ForcePowersQueueCommand {
public:

	ForceLightningCone2NPCCommand(const String& name, ZoneProcessServer* server)
		: ForcePowersQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		return doCombatAction(creature, target);
	}

};

#endif //FORCELIGHTNINGCONE2NPCCOMMAND_H_
