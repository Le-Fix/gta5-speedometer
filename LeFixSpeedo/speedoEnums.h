#pragma once

enum eRGB {R, G, B, numRGB };
enum eRGBA {};
enum eUNIT { MPH, KMH, KNO, MPS, numUNIT};
static const float unitFactor[] = { 2.23693629f, 3.6f, 1.94384449f, 1.0f };

enum eRPM { RPM_NO, RPM_ANLG, RPM_LED, numRPM};

enum eVEHDOMAIN {VD_ROAD, VD_AIR, VD_VELO, VD_WATER, VD_RAIL, numVEHDOMAIN};

enum eVEHCLASS
{
	VC_COMPACT,		//0 : Compacts
	VC_SEDAN,		//1 : Sedans
	VC_SUV,			//2 : SUVs
	VC_COUPE,		//3 : Coupes
	VC_MUSCLE,		//4 : Muscle
	VC_SPORTCLASSIC,//5 : Sports Classics
	VC_SPORT,		//6 : Sports
	VC_SUPER,		//7 : Super
	VC_MOTORCYCLE,	//8 : Motorcycle
	VC_OFFROAD,		//9 : Off - road
	VC_INDUSTRIAL,	//10 : Industrial
	VC_UTILITY,		//11 : Utility
	VC_VANORPICKUP,	//12 : Vans / Pickups
	VC_BICYCLE,		//13 : Bicycle
	VC_BOAT,		//14 : Boats
	VC_HELICOPTER,	//15 : Helicopter
	VC_AIRPLANE,	//16 : Airplane
	VC_SERVICE,		//17 : Service
	VC_EMERGENCY,	//18 : Emergency
	VC_MILITARY,	//19 : Military
	VC_COMMERCIAL,	//20 : Commercial
	VC_TRAIN		//21 : Train
};