#include "VehicleData.h"

#include "Settings.h"
#include "Util\INIutils.hpp"
#include "Util\UIutils.hpp"
#include <inc/natives.h>

VehicleData::VehicleData()
{
	vDomain = (eVEHDOMAIN)0;
	vClass = (eVEHCLASS)0;

	velocity = 0.0f;
	velocityVertical = 0.0f;
	rpm = 0.0f;
	rpmMax = 5.0f;
	fuel = 0.0f;
	hasFuel = false;
	engineTemp = 0.0f;
	ext3 = 1.0f;
	gear = 0;
	gearMax = 0;
	gearAcc = 0.0f;
	handbrake = false;
}

VehicleData::~VehicleData()
{
}

void VehicleData::update(Vehicle currentVehicle)
{
	if (veh != currentVehicle && currentVehicle != 0)
	{
		veh = currentVehicle; // New existing vehicle

		//Vehicle domain and class
		updateVehicleDomainAndClass();

		//Get livery name
		char* c = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(veh));
		std::string liveryHelp(c, std::find(c, c + 16, '\0'));
		livery = liveryHelp;

		//Get brand name
		brand = get_brand_name_from_ini(livery);

		//Get max rpm
		if (vDomain == VD_ROAD)
		{
			rpmMax = get_max_rpm_from_ini(livery);
		}
		else
		{
			rpmMax = 0.0f;
		}

		//Top Gear
		updateGearMax();

		//TankVolume
		updateTankVolume();
	}
	if (veh != 0 && ENTITY::DOES_ENTITY_EXIST(veh))
	{
		updateDashboard();
		updateVelocity();
		updateVelocityVertical();
		updateRpm();
		updateFuel();
		updateEngineTemp();
		updateDamage();
		updateGear();
		updateHandbrake();
	}
}

std::string VehicleData::get_brand_name_from_ini(std::string liveryName)
{
	std::string path = GetCurrentModulePath(); // includes trailing slash
	path = path + "LeFixSpeedo\\settingsBrands.ini";
	std::string brandName = readString(path, "LIVERY", liveryName, "UnkownLivery");
	if (brandName == "UnkownLivery")
	{
		if(Settings::isDebugMode) showSubtitle("Livery name: " + liveryName + "isn't registered in settingsBrand.ini (No Brand: 'Empty')", 5000);
		brandName = "Empty";
	}
	return brandName;
}
float VehicleData::get_max_rpm_from_ini(std::string liveryName)
{
	std::string path = GetCurrentModulePath(); // includes trailing slash
	path = path + "LeFixSpeedo\\settingsMaxRpm.ini";
	float maxRpm = readInt(path, "MAXRPM", liveryName, -1, 10, 150)  * 0.1f;
	if (maxRpm < 0.0f)
	{
		if (Settings::isDebugMode) showSubtitle("Livery name: " + liveryName + "isn't registered in settingsMaxRpm.ini (Default: '50x100rpm')", 5000);
		maxRpm = 5.0f;
	}
	return maxRpm;
}

void VehicleData::updateDashboard()
{
	isDashboardOn = TRUE == VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(veh);
}
void VehicleData::updateVehicleDomainAndClass()
{
	vClass = (eVEHCLASS)VEHICLE::GET_VEHICLE_CLASS(veh);

	switch (vClass)
	{
	case VC_BICYCLE:	vDomain = VD_VELO; break;
	case VC_BOAT:		vDomain = VD_WATER; break;
	case VC_HELICOPTER:
	case VC_AIRPLANE:	vDomain = VD_AIR; break;
	case VC_TRAIN:		vDomain = VD_RAIL; break;
	default:			vDomain = VD_ROAD; break;
	}
}
void VehicleData::updateVelocity()
{
	if (vDomain == VD_WATER)
	{
		//Horizontal velocity
		Vector3 speedVect = ENTITY::GET_ENTITY_SPEED_VECTOR(veh, false);
		velocity = sqrtf(speedVect.x*speedVect.x + speedVect.y*speedVect.y);
	}
	else
	{
		//Total velocity
		velocity = ENTITY::GET_ENTITY_SPEED(veh);
	}
}
void VehicleData::updateVelocityVertical()
{
	velocityVertical = ENTITY::GET_ENTITY_SPEED_VECTOR(veh, false).z;
}
void VehicleData::updateRpm()
{
	if (vDomain == VD_ROAD)
	{
		rpm = ext.GetCurrentRPM(veh);
	}
	else
	{
		rpm = 0.0f;
	}
}
void VehicleData::updateFuel()
{
	if (hasFuel) fuel = ext.GetFuelLevel(veh) / tankVolume;
}
void VehicleData::updateEngineTemp()
{
	//TODO
}
void VehicleData::updateTankVolume()
{
	if (vDomain == VD_ROAD)
	{
		tankVolume = ext.GetPetrolTankVolume(veh);
		hasFuel = tankVolume > 0.0f;
	}
	else
	{
		tankVolume = 1.0f;
		hasFuel = false;
	}
}
void VehicleData::updateDamage()
{
	//Some arbitrary damage value (currently only engine health part of calculation)
	float engineHealth = VEHICLE::GET_VEHICLE_ENGINE_HEALTH(veh);
	damage = engineHealth*(-0.001f) + 1.0f;
	if (damage > 1.0f) damage = 1.0f;
}
void VehicleData::updateGear()
{
	if (vDomain == VD_ROAD)
	{
		gear = ext.GetGearCurr(veh);
		gearAcc = ext.GetThrottle(veh);

		// Avoid picture bugs
		if (gear > 8) gear = 8;

		// Reverse returns 0, N doesn't exist
		if (gear == 0) gear = -1;

		// Handbremse
		if (Settings::featHBrake && handbrake) gear = 0;

		// Manual Transmissions mod compatibility (@ikt)
		if (Settings::iktCompatible)
		{
			// Shift up down indicator
			if (DECORATOR::DECOR_EXIST_ON(veh, "hunt_score"))
			{
				int x = DECORATOR::DECOR_GET_INT(veh, "hunt_score");
				shiftDown = (x == 2);
				shiftUp = (x == 1);
			}
			// Non-native neutral gear postion
			if (DECORATOR::DECOR_EXIST_ON(veh, "hunt_weapon"))
			{
				int x = DECORATOR::DECOR_GET_INT(veh, "hunt_weapon");
				if (x == 1)
				{
					gear = 0;
				}
			}
		}
		else
		{
			shiftDown = false;
			shiftUp = false;
		}
	}
	else
	{
		gear = 0;
		gearAcc = 0.0f;
		shiftDown = false;
		shiftUp = false;
	}
}
void VehicleData::updateGearMax()
{
	if (vDomain == VD_ROAD)
	{
		gearMax = ext.GetTopGear(veh);
	}
	else
	{
		gearMax = 0;
	}
}
void VehicleData::updateHandbrake()
{
	if (vDomain == VD_ROAD)
	{
		handbrake = ext.GetHandbrake(veh);
	}
	else
	{
		handbrake = false;
	}
}