#ifndef _CITYONPLANET_H
#define _CITYONPLANET_H

#include "libs.h"
#include "mtrand.h"
#include "Object.h"
#include "LmrModel.h"

class Planet;
class SpaceStation;
class Frame;
class Geom;

#define CITY_ON_PLANET_RADIUS 5000.0

class CityOnPlanet: public Object {
public:
	OBJDEF(CityOnPlanet, Object, CITYONPLANET);
	CityOnPlanet(const Planet *planet, const SpaceStation *station, Uint32 seed);
	virtual ~CityOnPlanet();
	void Render(const SpaceStation *station, const vector3d &viewCoords, const matrix4x4d &viewTransform);
private:
	void PutCityBit(MTRand &rand, const matrix4x4d &rot, vector3d p1, vector3d p2, vector3d p3, vector3d p4);
	void AddStaticGeomsToCollisionSpace();
	void RemoveStaticGeomsFromCollisionSpace();
	void MakeBuildingBaseGeometry();

	struct BuildingDef {
		LmrModel *model;
		float clipRadius;
		int rotation; // 0-3
		vector3d pos;
		Geom *geom;
		// may not be at lower detail level
		bool isEnabled;
		vector3d rect[4];
		double height; // from centre of planet
	};

	const Planet *m_planet;
	Frame *m_frame;
	std::vector<BuildingDef> m_buildings;
	// building bases (square foundations)
	GLuint m_buildingBaseGeometryVBO;
	int m_detailLevel;
};

#endif /* _CITYONPLANET_H */
