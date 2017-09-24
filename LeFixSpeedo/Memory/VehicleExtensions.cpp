#include "VehicleExtensions.hpp"
#include <vector>
#include "NativeMemory.hpp"
#include "Versions.h"
#include "Offsets.hpp"
#include "../Util/Logger.hpp"

VehicleExtensions::VehicleExtensions() {
	logger.SetFile("./LeFixSpeedo.log");
	logger.Clear();
	mem::init();
	getOffsets();
}

BYTE *VehicleExtensions::GetAddress(Vehicle handle) {
	return reinterpret_cast<BYTE *>(mem::GetAddressOfEntity(handle));
}

void VehicleExtensions::getOffsets() {
	auto addr = mem::FindPattern("\x3C\x03\x0F\x85\x00\x00\x00\x00\x48\x8B\x41\x20\x48\x8B\x88",
		"xxxx????xxxxxxx");
	handlingOffset = *(int*)(addr + 0x16);
	logger.Write("Handling Offset: " + std::to_string(handlingOffset));

	addr = mem::FindPattern("\xF3\x44\x0F\x10\x93\x00\x00\x00\x00\xF3\x0F\x10\x0D",
		"xxxxx????xxxx");
	rpmOffset = *(int*)(addr + 5);
	logger.Write("RPM Offset: " + std::to_string(rpmOffset));
}

float VehicleExtensions::GetCurrentRPM(Vehicle handle) {
	auto address = GetAddress(handle);

	return address == nullptr ? 0.0f : *reinterpret_cast<const float *>(address + rpmOffset);
}

float VehicleExtensions::GetFuelLevel(Vehicle handle) {
	auto address = GetAddress(handle);

	auto offset = gameVersion >= G_VER_1_0_372_2_STEAM ? 0x768 : 0x758;
	offset = gameVersion >= G_VER_1_0_877_1_STEAM ? 0x788 : offset;
	offset = gameVersion >= G_VER_1_0_944_2_STEAM ? 0x7A8 : offset;
	offset = gameVersion >= G_VER_1_0_1103_2_STEAM ? 0x7B8 : offset;
	offset = gameVersion >= G_VER_1_0_1180_2_STEAM ? 0x7C8 : offset;

	return *reinterpret_cast<float *>(address + offset);
}

uint64_t VehicleExtensions::GetHandlingPtr(Vehicle handle) {
	auto address = GetAddress(handle);

	return *reinterpret_cast<uint64_t *>(address + handlingOffset);
}

float VehicleExtensions::GetPetrolTankVolume(Vehicle handle) {
	auto address = GetHandlingPtr(handle);
	if (address == 0) return 0.0f;
	return *reinterpret_cast<float *>(address + hOffsets.fPetrolTankVolume);
}

uint16_t VehicleExtensions::GetGearCurr(Vehicle handle) {
	auto address = GetAddress(handle);

	auto offset = gameVersion >= G_VER_1_0_372_2_STEAM ? 0x7A2 : 0x792;
	offset = gameVersion >= G_VER_1_0_877_1_STEAM ? 0x7C2 : offset;
	offset = gameVersion >= G_VER_1_0_944_2_STEAM ? 0x7E2 : offset;
	offset = gameVersion >= G_VER_1_0_1103_2_STEAM ? 0x7F2 : offset;
	offset = gameVersion >= G_VER_1_0_1180_2_STEAM ? 0x812 : offset;

	return address == nullptr ? 0 : *reinterpret_cast<const uint16_t *>(address + offset);
}

float VehicleExtensions::GetThrottle(Vehicle handle) {
	auto address = GetAddress(handle);

	auto offset = gameVersion >= G_VER_1_0_372_2_STEAM ? 0x7E4 : 0x7D4;
	offset = gameVersion >= G_VER_1_0_877_1_STEAM ? 0x804 : offset;
	offset = gameVersion >= G_VER_1_0_944_2_STEAM ? 0x824 : offset;
	offset = gameVersion >= G_VER_1_0_1103_2_STEAM ? 0x834 : offset;
	offset = gameVersion >= G_VER_1_0_1180_2_STEAM ? 0x854 : offset;

	return *reinterpret_cast<float *>(address + offset);
}

unsigned char VehicleExtensions::GetTopGear(Vehicle handle) {
	auto address = GetAddress(handle);

	auto offset = gameVersion >= G_VER_1_0_372_2_STEAM ? 0x7A6 : 0x796;
	offset = gameVersion >= G_VER_1_0_877_1_STEAM ? 0x7C6 : offset;
	offset = gameVersion >= G_VER_1_0_944_2_STEAM ? 0x7E6 : offset;
	offset = gameVersion >= G_VER_1_0_1103_2_STEAM ? 0x7F6 : offset;
	offset = gameVersion >= G_VER_1_0_1180_2_STEAM ? 0x816 : offset;

	return address == nullptr ? 0 : *reinterpret_cast<const unsigned char *>(address + offset);
}

bool VehicleExtensions::GetHandbrake(Vehicle handle) {
	auto address = GetAddress(handle);

	auto offset = gameVersion >= G_VER_1_0_372_2_STEAM ? 0x8BC : 0x8AC;
	offset = gameVersion >= G_VER_1_0_877_1_STEAM ? 0x8DC : offset;
	offset = gameVersion >= G_VER_1_0_944_2_STEAM ? 0x904 : offset;
	offset = gameVersion >= G_VER_1_0_1103_2_STEAM ? 0x914 : offset;
	offset = gameVersion >= G_VER_1_0_1180_2_STEAM ? 0x934 : offset;

	return *reinterpret_cast<bool *>(address + offset);
}
