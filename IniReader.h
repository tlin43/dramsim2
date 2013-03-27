/*********************************************************************************
*  Copyright (c) 2010-2011, Elliott Cooper-Balis
*                             Paul Rosenfeld
*                             Bruce Jacob
*                             University of Maryland 
*                             dramninjas [at] gmail [dot] com
*  All rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*  
*     * Redistributions of source code must retain the above copyright notice,
*        this list of conditions and the following disclaimer.
*  
*     * Redistributions in binary form must reproduce the above copyright notice,
*        this list of conditions and the following disclaimer in the documentation
*        and/or other materials provided with the distribution.
*  
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
*  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
*  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*********************************************************************************/

#ifndef INIREADER_H
#define INIREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map> 
#include "SystemConfiguration.h"

using namespace std;

#define DEFINE_UINT_PARAM(name, paramtype) {#name, &name, UINT, paramtype, false}
#define DEFINE_STRING_PARAM(name, paramtype) {#name, &name, STRING, paramtype, false}
#define DEFINE_FLOAT_PARAM(name,paramtype) {#name, &name, FLOAT, paramtype, false}
#define DEFINE_BOOL_PARAM(name, paramtype) {#name, &name, BOOL, paramtype, false}
#define DEFINE_UINT64_PARAM(name, paramtype) {#name, &name, UINT64, paramtype, false}

namespace DRAMSim
{

typedef enum _variableType {STRING, UINT, UINT64, FLOAT, BOOL} varType;
typedef enum _paramType {SYS_PARAM, DEV_PARAM} paramType;
typedef struct _configMap
{
	string iniKey; //for example "tRCD"

	void *variablePtr;
	varType variableType;
	paramType parameterType;
	bool wasSet;
} ConfigMap;



//---------MY CODE---------//

#define MY_DEFINE_UINT_PARAM(element, name, paramtype) {element.iniKey=#name;\
			element.variablePtr=&name;\
			element.variableType=UINT;\
			element.parameterType=paramtype;\
			element.wasSet=false;\
			i++;}
#define MY_DEFINE_STRING_PARAM(element, name, paramtype) {element.iniKey=#name;\
			element.variablePtr=&name;\
			element.variableType=STRING;\
			element.parameterType=paramtype;\
			element.wasSet=false;\
			i++;}
#define MY_DEFINE_FLOAT_PARAM(element, name, paramtype) {element.iniKey=#name;\
			element.variablePtr=&name;\
			element.variableType=FLOAT;\
			element.parameterType=paramtype;\
			element.wasSet=false;\
			i++;}
#define MY_DEFINE_BOOL_PARAM(element, name, paramtype) {element.iniKey=#name;\
			element.variablePtr=&name;\
			element.variableType=BOOL;\
			element.parameterType=paramtype;\
			element.wasSet=false;\
			i++;}
#define MY_DEFINE_UINT64_PARAM(element, name, paramtype) {element.iniKey=#name;\
			element.variablePtr=&name;\
			element.variableType=UINT64;\
			element.parameterType=paramtype;\
			element.wasSet=false;\
			i++;}

class ConfigSet
{
public:
   ConfigSet();

   unsigned NUM_DEVICES;
   unsigned NUM_RANKS;

   uint64_t TOTAL_STORAGE;
   unsigned NUM_BANKS;
   unsigned NUM_CHANS;
   unsigned NUM_ROWS;
   unsigned NUM_COLS;
   unsigned DEVICE_WIDTH;

   unsigned REFRESH_PERIOD;
   float tCK;
   float Vdd;
   unsigned CL;
   unsigned AL;
   unsigned BL;
   unsigned tRAS;
   unsigned tRCD;
   unsigned tRRD;
   unsigned tRC;
   unsigned tRP;
   unsigned tCCD;
   unsigned tRTP;
   unsigned tWTR;
   unsigned tWR;
   unsigned tRTRS;
   unsigned tRFC;
   unsigned tFAW;
   unsigned tCKE;
   unsigned tXP;
   unsigned tCMD;

   unsigned IDD0;
   unsigned IDD1;
   unsigned IDD2P;
   unsigned IDD2Q;
   unsigned IDD2N;
   unsigned IDD3Pf;
   unsigned IDD3Ps;
   unsigned IDD3N;
   unsigned IDD4W;
   unsigned IDD4R;
   unsigned IDD5;
   unsigned IDD6;
   unsigned IDD6L;
   unsigned IDD7;


   //in bytes
   unsigned JEDEC_DATA_BUS_BITS;

   //Memory Controller related parameters
   unsigned TRANS_QUEUE_DEPTH;
   unsigned CMD_QUEUE_DEPTH;

   //cycles within an epoch
   unsigned EPOCH_LENGTH;

   //row accesses allowed before closing (open page)
   unsigned TOTAL_ROW_ACCESSES;

   // strings and their associated enums
   string ROW_BUFFER_POLICY;
   string SCHEDULING_POLICY;
   string ADDRESS_MAPPING_SCHEME;
   string QUEUING_STRUCTURE;

   bool DEBUG_TRANS_Q;
   bool DEBUG_CMD_Q;
   bool DEBUG_ADDR_MAP;
   bool DEBUG_BANKSTATE;
   bool DEBUG_BUS;
   bool DEBUG_BANKS;
   bool DEBUG_POWER;
   bool USE_LOW_POWER;
   bool VIS_FILE_OUTPUT;

   bool VERIFICATION_OUTPUT;

   bool DEBUG_INI_READER;

   RowBufferPolicy rowBufferPolicy;
   SchedulingPolicy schedulingPolicy;
   AddressMappingScheme addressMappingScheme;
   QueuingStructure queuingStructure;

   ConfigMap local_configMap[128];
};
//---------END OF MY CODE----------//

class IniReader
{

public:
	typedef std::map<string, string> OverrideMap;
	typedef OverrideMap::const_iterator OverrideIterator; 

	static void SetKey(string key, string value, bool isSystemParam = false, size_t lineNumber = 0);
	static void OverrideKeys(const OverrideMap *map);
	static void ReadIniFile(string filename, bool isSystemParam);
	static void InitEnumsFromStrings();
	static bool CheckIfAllSet();
	static void WriteValuesOut(ConfigSet *local_config, std::ofstream &visDataOut);

	//------------MY CODE-----------//
	static void SetKey(ConfigSet *currentSet, string key, string value, bool isSystemParam = false, size_t lineNumber = 0);
	//static void OverrideKeys(const OverrideMap *map);
	static void ReadIniFile(ConfigSet *currentSet, string filename, bool isSystemParam);
	static void InitEnumsFromStrings(ConfigSet *currentSet);
	static bool CheckIfAllSet(ConfigSet *currentSet);
	//--------END OF MY CODE--------//

private:
	static void WriteParams(ConfigSet *local_config, std::ofstream &visDataOut, paramType t);
	static void Trim(string &str);
};

}


#endif
