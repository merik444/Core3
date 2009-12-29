/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "GroupManager.h"

#include "../../ZoneServer.h"
#include "../../Zone.h"

#include "../../../chat/room/ChatRoom.h"

#include "../../objects/creature/CreatureObject.h"
#include "../../objects/player/PlayerCreature.h"

#include "../../objects/group/GroupObject.h"
#include "../../objects/scene/variables/ParameterizedStringId.h"
#include "../../managers/object/ObjectManager.h"


GroupManager::GroupManager() {
}

void GroupManager::inviteToGroup(CreatureObject* leader, CreatureObject* player) {
	// Pre: leader locked
	// Post: player invited to leader's group, leader locked
	try {
		player->wlock(leader);

		if (leader->isGroupped()) {
			ManagedReference<GroupObject*> group = leader->getGroup();

			if (group->getLeader() != leader) {
				leader->sendSystemMessage("group", "must_be_leader");
				player->unlock();
				return;
			}
		}

		if (player->isGroupped()) {
			ParameterizedStringId stringId;
			stringId.setTT("group", "already_grouped");
			stringId.setTU(player);
			leader->sendSystemMessage(stringId);
			//leader->sendSystemMessage("group", "already_grouped", player->getObjectID());

			player->unlock();
			return;
		}

		if (player->getGroupInviterID() == leader->getObjectID()) {
			ParameterizedStringId stringId;
			stringId.setTT("group", "considering_your_group");
			stringId.setTU(player);
			leader->sendSystemMessage(stringId);
			//leader->sendSystemMessage("group", "considering_your_group", player->getObjectID());

			player->unlock();
			return;
		} else if (player->getGroupInviterID() != 0) {
			StringBuffer msg;
			msg << player->getCreatureName().toString() << " is considering joining another group.";
			leader->sendSystemMessage(msg.toString());

			player->unlock();
			return;
		}

		player->updateGroupInviterID(leader->getObjectID());

		ParameterizedStringId stringId;
		stringId.setTT("group", "considering_your_group");
		stringId.setTU(leader);
		player->sendSystemMessage(stringId);

		stringId.setTU(player);
		leader->sendSystemMessage(stringId);

		player->unlock();
	} catch (...) {
		System::out << "Exception in GroupManager::inviteToGroup(GroupObject* group, CreatureObject* player)\n";
		player->unlock();
	}
}

void GroupManager::joinGroup(CreatureObject* player) {
	//Pre: player locked
	//Post: player locked
	uint64 inviterID = player->getGroupInviterID();

	ZoneServer* server = player->getZone()->getZoneServer();
	SceneObject* object = server->getObject(inviterID);

	if (object == NULL || !object->isPlayerCreature() || object == player)
		return;

	CreatureObject* inviter = (CreatureObject*)object;
	GroupObject* group = NULL;

	try {
		inviter->wlock(player);

		group = inviter->getGroup();

		if (group == NULL)
			group = createGroup(inviter);

		inviter->unlock();
	} catch (Exception& e) {
		e.printStackTrace();
		inviter->unlock();

		return;
	} catch (...) {
		System::out << "Exception in GroupManager::joinGroup(CreatureObject* player)\n";
		inviter->unlock();

		return;
	}

	try {
		group->wlock(player);

		if (group->getGroupSize() == 20) {
			group->unlock();

			player->updateGroupInviterID(0);

			player->sendSystemMessage("group", "full");
			return;
		}

		player->info("joining group");

		group->addMember(player);
		player->updateGroup(group);
		player->sendSystemMessage("group", "joined_self");

		ChatRoom* groupChannel = group->getGroupChannel();

		/*groupChannel->sendTo(player);
		groupChannel->addPlayer(player, false);*/

		player->updateGroupInviterID(0);

		group->unlock();
	} catch (...) {
		group->unlock();
		System::out << "Exception in GroupManager::joinGroup(CreatureObject* player)\n";
	}
}

GroupObject* GroupManager::createGroup(CreatureObject* leader) {
	// Pre: leader locked
	// Post: GroupObject is a new group with leader, leader locked.

	ZoneServer* server = leader->getZone()->getZoneServer();

	ManagedReference<GroupObject*> group = (GroupObject*) ObjectManager::instance()->createObject(2022504856, 0, "");

	group->setZone(leader->getZone());

	group->sendTo(leader);

	leader->updateGroup(group);
	leader->sendSystemMessage("group", "formed_self");

	if (leader->getGroupInviterID() != 0)
		leader->updateGroupInviterID(0);

	return group;
}

void GroupManager::leaveGroup(ManagedReference<GroupObject*> group, CreatureObject* player) {
	// Pre: player locked
	// Post: player locked
	if (group == NULL)
		return;

	try {
		group->wlock(player);

		ChatRoom* groupChannel = group->getGroupChannel();
		if (groupChannel != NULL) {
			/*groupChannel->removePlayer(player, false);
			groupChannel->sendDestroyTo(player);

			ChatRoom* room = groupChannel->getParent();
			room->sendDestroyTo(player);*/
		}

		player->updateGroup(NULL);

		//if (player != NULL && player->isOnline() && !player->isLoggingOut())
		player->sendSystemMessage("group", "removed");

		player->unlock();

		group->removeMember(player);

		group->sendDestroyTo(player);

		player->info("leaving group");

		if (group->getGroupSize() < 2) {
			group->disband();
		}

		group->unlock();
	} catch (Exception& e) {
		System::out << e.getMessage();
		e.printStackTrace();
		group->unlock();
	} catch (...) {
		group->unlock();
		System::out << "Exception in GroupManager::leaveGroup(GroupObject* group, CreatureObject* player)\n";
	}

	player->wlock();
}

void GroupManager::disbandGroup(ManagedReference<GroupObject*> group, CreatureObject* player) {
	//Pre: player locked
	//Post: player locked
	player->unlock();

	try {
		group->wlock();
		//The following should never happen, as a check is made in
		//ObjectControlMessage.cpp and removes the player from the group
		//if he's not the leader. Remove?
		//After Fix 13 feb 2009 - Bankler
		if (group->getLeader() != player) {
			player->sendSystemMessage("group", "must_be_leader");
			group->unlock();
			player->wlock();
			return;
		}

		for (int i = 0; i < group->getGroupSize(); i++) {
			CreatureObject* play = (CreatureObject*) group->getGroupMember(i);

			play->sendSystemMessage("group", "disbanded");
		}

		group->disband();

		group->unlock();
	} catch (...) {
		group->unlock();
		System::out << "Exception in GroupManager::disbandGroup(GroupObject* group, CreatureObject* player)\n";
	}

	player->wlock();
}

void GroupManager::kickFromGroup(ManagedReference<GroupObject*> group, CreatureObject* player, CreatureObject* playerToKick) {
	// Pre: player is locked, group != NULL
	// Post: playerToKick kicked from group

	player->unlock();

	bool disbanded = false;

	try {
		group->wlock();

		if (!group->hasMember(playerToKick)) {
			group->unlock();
			player->wlock();
			return;
		}

		CreatureObject* leader = (CreatureObject*) group->getLeader();

		if (player != leader) {
			player->sendSystemMessage("group", "must_be_leader");

			group->unlock();

			player->wlock();
			return;
		}

		if (group->getGroupSize() - 1 < 2) {
			for (int i = 0; i < group->getGroupSize(); i++) {
				CreatureObject* play = (CreatureObject*) group->getGroupMember(i);

				play->sendSystemMessage("group", "disbanded");
			}
			group->disband();
			disbanded = true;
		} else {
			group->removeMember(playerToKick);

			playerToKick->sendSystemMessage("group", "removed");

			playerToKick->info("kicking from group");
		}

		group->unlock();

	} catch (...) {
		System::out << "Exception in GroupManager::kickFromGroup(GroupObject* group, CreatureObject* player, CreatureObject* playerToKick)\n";
		group->unlock();
	}

	if (!disbanded) {
		try {
			playerToKick->wlock();

			/*ChatRoom* groupChannel = group->getGroupChannel();
			groupChannel->removePlayer(playerToKick, false);
			groupChannel->sendDestroyTo(playerToKick);

			ChatRoom* room = groupChannel->getParent();
			room->sendDestroyTo(playerToKick);*/

			playerToKick->updateGroup(NULL);

			group->sendDestroyTo(playerToKick);

			playerToKick->unlock();
		} catch (...) {
			System::out << "Exception in GroupManager::kickFromGroup(GroupObject* group, CreatureObject* player, CreatureObject* playerToKick)\n";
			playerToKick->unlock();

		}
	}

	player->wlock();
}

void GroupManager::makeLeader(GroupObject* group, CreatureObject* player, CreatureObject* newLeader) {
	// Pre: player locked
	// Post: player locked
	player->unlock();

	try {
		group->wlock();

		if (group->getLeader() != player) {
			player->sendSystemMessage("group", "must_be_leader");
			group->unlock();
			player->wlock();
			return;
		}

		if (!group->hasMember(newLeader)) {
			group->unlock();
			player->wlock();
			return;
		}

		group->makeLeader(newLeader);

		String firstNameLeader;
		firstNameLeader = "[Offline player]";

		if (newLeader->isPlayerCreature()) {
			PlayerCreature* playerLeader = (PlayerCreature*) newLeader;
			if (playerLeader->isOnline() && !playerLeader->isLoggingOut())
				firstNameLeader= playerLeader->getFirstName();
		}

		StringBuffer message;
		message << firstNameLeader << " is now the group leader.\n";

		for (int i = 0; i < group->getGroupSize(); i++) {
			CreatureObject* play = (CreatureObject*) group->getGroupMember(i);

			play->sendSystemMessage(message.toString());
		}

		group->unlock();
	} catch (...) {
		group->unlock();
		System::out << "Exception in GroupManager::makeLeader(GroupObject* group, CreatureObject* player, CreatureObject* newLeader)\n";
	}
	player->wlock();
}
