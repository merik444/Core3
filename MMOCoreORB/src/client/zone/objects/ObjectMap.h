#ifndef OBJECTMAP_H_
#define OBJECTMAP_H_

#include "client/zone/objects/scene/SceneObject.h"

class ObjectMap : public HashTable<uint64, Reference<SceneObject*> > {
	int maxConnections;

	int hash(const uint64& key) const {
		return Long::hashCode(key);
	}

public:
	ObjectMap() : HashTable<uint64, Reference<SceneObject*> >(1000), maxConnections(3000) {
		setNullValue(NULL);
	}

};

#endif /*OBJECTMAP_H_*/
