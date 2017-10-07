#pragma once

#include <vector>
#include <cstdint>
#include "../../../ScriptHookV_SDK/inc/types.h"
#include "../../../ScriptHookV_SDK/inc/nativeCaller.h"


class VehicleExtensions {
public:
	VehicleExtensions();
	BYTE *GetAddress(Vehicle handle);
	float GetCurrentRPM(Vehicle handle);
	float GetFuelLevel(Vehicle handle);
	uint64_t GetHandlingPtr(Vehicle handle);
	float GetPetrolTankVolume(Vehicle handle);
	uint16_t GetGearCurr(Vehicle handle);
	float GetThrottle(Vehicle handle);
	unsigned char GetTopGear(Vehicle handle);
	bool GetHandbrake(Vehicle handle);


private:
	// only run this once because patterns
	void getOffsets();
	eGameVersion gameVersion = getGameVersion();

	uint64_t handlingOffset;
	uint64_t rpmOffset;

};
