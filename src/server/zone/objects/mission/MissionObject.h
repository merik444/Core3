/*
 *	server/zone/objects/mission/MissionObject.h generated by engine3 IDL compiler 0.60
 */

#ifndef MISSIONOBJECT_H_
#define MISSIONOBJECT_H_

#include "engine/orb/DistributedObjectBroker.h"

#include "engine/core/ManagedReference.h"

#include "engine/core/ManagedWeakReference.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {

class SceneObject;

} // namespace scene
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::scene;

namespace server {
namespace zone {
namespace objects {
namespace waypoint {

class WaypointObject;

} // namespace waypoint
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::waypoint;

namespace server {
namespace zone {

class Zone;

} // namespace zone
} // namespace server

using namespace server::zone;

namespace server {
namespace zone {
namespace templates {

class SharedObjectTemplate;

} // namespace templates
} // namespace zone
} // namespace server

using namespace server::zone::templates;

namespace server {
namespace zone {
namespace objects {
namespace mission {

class MissionObserver;

} // namespace mission
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::mission;

namespace server {
namespace zone {
namespace objects {
namespace player {

class PlayerCreature;

} // namespace player
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::player;

namespace server {
namespace zone {
namespace objects {
namespace mission {

class MissionObjective;

} // namespace mission
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::mission;

#include "server/zone/objects/scene/variables/StringId.h"

#include "server/zone/templates/TemplateReference.h"

#include "engine/lua/LuaObject.h"

#include "server/zone/objects/intangible/IntangibleObject.h"

#include "system/util/SortedVector.h"

namespace server {
namespace zone {
namespace objects {
namespace mission {

class MissionObject : public IntangibleObject {
public:
	static const int DESTROY = 0x74EF9BE3;

	static const int BOUNTY = 0x2904F372;

	static const int DELIVER = 0xE5C27EC6;

	static const int CRAFTING = 0xE5F6DC59;

	static const int ESCORT = 0x682B871E;

	static const int ESCORT2ME = 0x58F59884;

	static const int ESCORTTOCREATOR = 0x5E4C7163;

	static const int HUNTING = 0x906999A2;

	static const int MUSICIAN = 0x4AD93196;

	static const int DANCER = 0xF067B37;

	static const int RECON = 0x34F4C2E4;

	static const int SURVEY = 0x19C9FAC1;

	MissionObject();

	WaypointObject* createWaypoint();

	void destroyObjectFromDatabase(bool destroyContainedObjects = false);

	void updateToDatabaseAllObjects(bool startTask);

	void setRefreshCounter(int ctr, bool notifyClient = true);

	void setTypeCRC(unsigned int crc, bool notifyClient = true);

	void initializeTransientMembers();

	void sendBaselinesTo(SceneObject* player);

	void setMissionDescription(const String& file, const String& id, bool notifyClient = true);

	void setMissionTitle(const String& file, const String& id, bool notifyClient = true);

	void setMissionTargetName(const String& target, bool notifyClient = true);

	void setMissionDifficulty(int difficulty, bool notifyClient = true);

	void setRewardCredits(int creds, bool notifyClient = true);

	void setTargetTemplate(SharedObjectTemplate* templ, bool notifyClient = true);

	void setStartPosition(float posX, float posY, unsigned int planetCRC, bool notifyClient = true);

	void setEndPosition(float posX, float posY, unsigned int planetCRC, bool notifyClient = true);

	void setCreatorName(const String& name, bool notifyClient = true);

	void updateMissionLocation();

	void abort();

	void setMissionObjective(MissionObjective* obj);

	void setStartPlanetCRC(unsigned int crc);

	void setEndPlanetCRC(unsigned int crc);

	void setMissionTarget(SceneObject* target);

	void setMissionTargetDest(SceneObject* target);

	void setMissionNumber(int num);

	void setTemplateStrings(const String& temp1, const String& temp2);

	float getStartPositionX();

	float getStartPositionY();

	unsigned int getStartPlanetCRC();

	float getEndPositionX();

	float getEndPositionY();

	unsigned int getEndPlanetCRC();

	WaypointObject* getWaypointToMission();

	SceneObject* getMissionTarget();

	SceneObject* getMissionTargetDest();

	unsigned int getTypeCRC();

	int getRewardCredits();

	UnicodeString getCreatorName();

	int getDifficultyLevel();

	StringId* getMissionDescription();

	StringId* getMissionTitle();

	String getTargetName();

	int getRefreshCounter();

	int getMissionNumber();

	SharedObjectTemplate* getTargetTemplate();

	bool isSurveyMission();

	bool isMissionObject();

	String getTemplateString1();

	String getTemplateString2();

protected:
	MissionObject(DummyConstructorParameter* param);

	virtual ~MissionObject();

	String _return_getTargetName;
	String _return_getTemplateString1;
	String _return_getTemplateString2;

	UnicodeString _return_getCreatorName;

	friend class MissionObjectHelper;
};

} // namespace mission
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::mission;

namespace server {
namespace zone {
namespace objects {
namespace mission {

class MissionObjectImplementation : public IntangibleObjectImplementation {
protected:
	ManagedReference<WaypointObject* > waypointToMission;

	ManagedReference<MissionObjective* > missionObjective;

	unsigned int typeCRC;

	int difficultyLevel;

	UnicodeString creatorName;

	int rewardCredits;

	int missionNumber;

	float startPositionX;

	float startPositionY;

	unsigned int startPlanetCRC;

	float endPositionX;

	float endPositionY;

	unsigned int endPlanetCRC;

	StringId missionDescription;

	StringId missionTitle;

	unsigned int refreshCounter;

	String targetName;

	ManagedReference<SceneObject* > missionTarget;

	ManagedReference<SceneObject* > missionTargetDest;

	String templateString1;

	String templateString2;

	TemplateReference<SharedObjectTemplate*> targetTemplate;

public:
	static const int DESTROY = 0x74EF9BE3;

	static const int BOUNTY = 0x2904F372;

	static const int DELIVER = 0xE5C27EC6;

	static const int CRAFTING = 0xE5F6DC59;

	static const int ESCORT = 0x682B871E;

	static const int ESCORT2ME = 0x58F59884;

	static const int ESCORTTOCREATOR = 0x5E4C7163;

	static const int HUNTING = 0x906999A2;

	static const int MUSICIAN = 0x4AD93196;

	static const int DANCER = 0xF067B37;

	static const int RECON = 0x34F4C2E4;

	static const int SURVEY = 0x19C9FAC1;

	MissionObjectImplementation();

	MissionObjectImplementation(DummyConstructorParameter* param);

	WaypointObject* createWaypoint();

	void destroyObjectFromDatabase(bool destroyContainedObjects = false);

	void updateToDatabaseAllObjects(bool startTask);

	void setRefreshCounter(int ctr, bool notifyClient = true);

	void setTypeCRC(unsigned int crc, bool notifyClient = true);

	void initializeTransientMembers();

	void sendBaselinesTo(SceneObject* player);

	void setMissionDescription(const String& file, const String& id, bool notifyClient = true);

	void setMissionTitle(const String& file, const String& id, bool notifyClient = true);

	void setMissionTargetName(const String& target, bool notifyClient = true);

	void setMissionDifficulty(int difficulty, bool notifyClient = true);

	void setRewardCredits(int creds, bool notifyClient = true);

	void setTargetTemplate(SharedObjectTemplate* templ, bool notifyClient = true);

	void setStartPosition(float posX, float posY, unsigned int planetCRC, bool notifyClient = true);

	void setEndPosition(float posX, float posY, unsigned int planetCRC, bool notifyClient = true);

	void setCreatorName(const String& name, bool notifyClient = true);

	void updateMissionLocation();

	void abort();

	void setMissionObjective(MissionObjective* obj);

	void setStartPlanetCRC(unsigned int crc);

	void setEndPlanetCRC(unsigned int crc);

	void setMissionTarget(SceneObject* target);

	void setMissionTargetDest(SceneObject* target);

	void setMissionNumber(int num);

	void setTemplateStrings(const String& temp1, const String& temp2);

	float getStartPositionX();

	float getStartPositionY();

	unsigned int getStartPlanetCRC();

	float getEndPositionX();

	float getEndPositionY();

	unsigned int getEndPlanetCRC();

	WaypointObject* getWaypointToMission();

	SceneObject* getMissionTarget();

	SceneObject* getMissionTargetDest();

	unsigned int getTypeCRC();

	int getRewardCredits();

	UnicodeString getCreatorName();

	int getDifficultyLevel();

	StringId* getMissionDescription();

	StringId* getMissionTitle();

	String getTargetName();

	int getRefreshCounter();

	int getMissionNumber();

	SharedObjectTemplate* getTargetTemplate();

	bool isSurveyMission();

	bool isMissionObject();

	String getTemplateString1();

	String getTemplateString2();

	MissionObject* _this;

	operator const MissionObject*();

	DistributedObjectStub* _getStub();
protected:
	virtual ~MissionObjectImplementation();

	void finalize();

	void _initializeImplementation();

	void _setStub(DistributedObjectStub* stub);

	void lock(bool doLock = true);

	void lock(ManagedObject* obj);

	void rlock(bool doLock = true);

	void wlock(bool doLock = true);

	void wlock(ManagedObject* obj);

	void unlock(bool doLock = true);

	void runlock(bool doLock = true);

	void _serializationHelperMethod();

	friend class MissionObject;
};

class MissionObjectAdapter : public IntangibleObjectAdapter {
public:
	MissionObjectAdapter(MissionObjectImplementation* impl);

	Packet* invokeMethod(sys::uint32 methid, DistributedMethod* method);

	WaypointObject* createWaypoint();

	void destroyObjectFromDatabase(bool destroyContainedObjects);

	void updateToDatabaseAllObjects(bool startTask);

	void setRefreshCounter(int ctr, bool notifyClient);

	void setTypeCRC(unsigned int crc, bool notifyClient);

	void initializeTransientMembers();

	void sendBaselinesTo(SceneObject* player);

	void setMissionDescription(const String& file, const String& id, bool notifyClient);

	void setMissionTitle(const String& file, const String& id, bool notifyClient);

	void setMissionTargetName(const String& target, bool notifyClient);

	void setMissionDifficulty(int difficulty, bool notifyClient);

	void setRewardCredits(int creds, bool notifyClient);

	void setStartPosition(float posX, float posY, unsigned int planetCRC, bool notifyClient);

	void setEndPosition(float posX, float posY, unsigned int planetCRC, bool notifyClient);

	void setCreatorName(const String& name, bool notifyClient);

	void updateMissionLocation();

	void abort();

	void setMissionObjective(MissionObjective* obj);

	void setStartPlanetCRC(unsigned int crc);

	void setEndPlanetCRC(unsigned int crc);

	void setMissionTarget(SceneObject* target);

	void setMissionTargetDest(SceneObject* target);

	void setMissionNumber(int num);

	void setTemplateStrings(const String& temp1, const String& temp2);

	float getStartPositionX();

	float getStartPositionY();

	unsigned int getStartPlanetCRC();

	float getEndPositionX();

	float getEndPositionY();

	unsigned int getEndPlanetCRC();

	WaypointObject* getWaypointToMission();

	SceneObject* getMissionTarget();

	SceneObject* getMissionTargetDest();

	unsigned int getTypeCRC();

	int getRewardCredits();

	UnicodeString getCreatorName();

	int getDifficultyLevel();

	String getTargetName();

	int getRefreshCounter();

	int getMissionNumber();

	bool isSurveyMission();

	bool isMissionObject();

	String getTemplateString1();

	String getTemplateString2();

protected:
	String _param0_setMissionDescription__String_String_bool_;
	String _param1_setMissionDescription__String_String_bool_;
	String _param0_setMissionTitle__String_String_bool_;
	String _param1_setMissionTitle__String_String_bool_;
	String _param0_setMissionTargetName__String_bool_;
	String _param0_setCreatorName__String_bool_;
	String _param0_setTemplateStrings__String_String_;
	String _param1_setTemplateStrings__String_String_;
};

class MissionObjectHelper : public DistributedObjectClassHelper, public Singleton<MissionObjectHelper> {
	static MissionObjectHelper* staticInitializer;

public:
	MissionObjectHelper();

	void finalizeHelper();

	DistributedObject* instantiateObject();

	DistributedObjectServant* instantiateServant();

	DistributedObjectAdapter* createAdapter(DistributedObjectStub* obj);

	friend class Singleton<MissionObjectHelper>;
};

} // namespace mission
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::mission;

#endif /*MISSIONOBJECT_H_*/
