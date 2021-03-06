
#include "moho.h"

extern "C" 
{
	void Logf(const char* fmt, ...);

	int stricmp(const char* a, const char* b);

	void lua_pushbool(lua_state *L, int b);

	extern CWldSession* g_CWldSession;
	extern Sim* 		g_Sim;
};

extern "C" void print_hello_world()
{	
	Logf("Hello world!");
}

extern "C" bool ext_ValidateFocusArmyRequest(int army)
{
	//UserArmy* userArmy = ((UserArmy**)g_CWldSession->armies.objects_start)[army];

	return true;
}

extern "C" int cxx_AddCommandSourceId(lua_state* lua, const char* playerName, int sourceId)
{
	Sim* sim = g_Sim;
	for(int i=0; i < sim->armies.size(); i++)
	{
		SimArmy* army = (SimArmy*)sim->armies[i];
		if(stricmp(army->nickname.data(), playerName) == 0)
		{
			army->mValidCommandSources.add(sourceId);
			lua_pushbool(lua, true);
			return 1;
		}
	}
	lua_pushbool(lua, false);
	return 1;
}
extern "C" int cxx_SetCommandSourceId(lua_state* lua, int armyId, int sourceId, bool set_or_unset)
{
	Sim* sim = g_Sim;
	SimArmy* army = (SimArmy*)sim->armies[armyId];

	if(set_or_unset)
		army->mValidCommandSources.add(sourceId);
	else
		army->mValidCommandSources.remove(sourceId);
	lua_pushbool(lua, true);
	return 1;
}