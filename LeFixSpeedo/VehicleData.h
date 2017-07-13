#pragma once

#include "speedoEnums.h"
#include "Memory\VehicleExtensions.hpp"
#include <inc/types.h>
#include <string>

class VehicleData
{
public:
	VehicleData();
	~VehicleData();

	void update(Vehicle currentVeh);

	//Members
	Vehicle veh;

	eVEHDOMAIN vDomain;
	eVEHCLASS vClass;
	std::string livery, brand;

	bool isDashboardOn;
	bool hasFuel;
	float velocity, velocityVertical, fuel, damage;
	float rpm, rpmMax;
	int gear, gearMax;
	float gearAcc;
	float ext2, ext3;
	bool handbrake;
	bool shiftUp, shiftDown;

private:

	VehicleExtensions ext;
	float tankVolume;

	std::string get_brand_name_from_ini(std::string liveryName);
	float get_max_rpm_from_ini(std::string liveryName);

	void updateDashboard();
	void updateVehicleDomainAndClass();
	void updateVelocity();
	void updateVelocityVertical();
	void updateRpm();
	void updateFuel();
	void updateTankVolume();
	void updateDamage();
	void updateGear();
	void updateGearMax();
	void updateHandbrake();
};

