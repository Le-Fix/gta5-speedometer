#pragma once
#include <Windows.h>

#include <inc\enums.h>
#include "speedoEnums.h"

#include <vector>
#include <string>

class Settings {
public:
	static void SetFile(const std::string &filepath);
	static void SaveGlobal();
	static void LoadGlobal();
	static void SaveLocal(int x);
	static void LoadLocal(int x);

	////CONSTANT////
	static const float hudSizeConst;
	static const float ledSizeConst;
	static const float needleRealisticDPS;

	////MENU GENERAL////

	//General
	static bool isActive;
	static int currentSetting;
	static bool iktCompatible;
	static bool isDebugMode;

	//Speedfactor
	static float speedFactor[numVEHDOMAIN];

	//Units
	static int unit[numVEHDOMAIN];

	////MENU MODE////

	//Toggle
	static bool isEnabledInVehDomain[numVEHDOMAIN];

	//Features
	static int featRpm;
	static bool featGear, featDmg, featVertical, featBrand, featHBrake, featFuel;
	static bool isShownInFpv, isShownAsPassenger;
	static bool useHighSpeedoByDefault;

	//Visual
	static float alphaFrontMax, alphaBackMax;
	static bool usePrimaryColor;
	static float needleStandardCol[numRGB];
	static float alphaBrand;

	static float dmgIntensityFactor, dmgFrequency;

	//Placement
	static bool isExtraGaugeLeft;
	static int ledsOffsetXInt, ledsOffsetYInt;
	static float hudSizeExp, mainOffsetX, mainOffsetY;

private:
	static std::string _filepath;
};
