#include "databox.h"

Data g_Data;

void Initdata(void)
{
	g_Data.bPause = false;
	g_Data.nFever = 100;
	g_Data.bFever = false;
	g_Data.nFeverTime = 0;
	g_Data.nTitleNum = 0;
	g_Data.bFeverMan = false;
}

void Resetdata(void)
{
	g_Data.bPause = false;
	g_Data.nFever = 100;
	g_Data.bFever = false;
	g_Data.nFeverTime = 0;
	g_Data.nTitleNum = 0;
	g_Data.bFeverMan = false;
	g_Data.bOK = false;
}

Data *GetData(void)
{
	return &g_Data;
}