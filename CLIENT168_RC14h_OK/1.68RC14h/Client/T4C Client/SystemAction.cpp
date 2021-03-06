#include "pch.h"
#include <windows.h>
#include "System.h"
#include "TfcPacket.h"
#include "TFCSocket.h"
#include "PowerDebug.h"
#include "SystemAction.h"
#include "VisualObjectList.h"
#include "Global.h"
#include "NewInterface/RTHelp.h"


//**************************************************************************************//
UINT AttackMode
//**************************************************************************************//
// Callback Function for using a Skill.
// 
(
 LPVOID pParam // Paramteter
)
//**************************************************************************************//
{
   Objects.Lock(109);
   Objects.AttackMode();
   Objects.Unlock(109);
	return 0;
}

//**************************************************************************************//
UINT ShowActualMap
//**************************************************************************************//
// Callback Function for using a Skill.
// 
(
 LPVOID pParam // Paramteter
)
//**************************************************************************************//
{
   /*
	Objects.Lock(0);
	F1Help.ShowMap(false);
	Objects.Unlock(0);
   */

	return 0;
}

//**************************************************************************************//
// Callback Function for using a Skill.
// 
//**************************************************************************************//
UINT ShowWorldMap(LPVOID pParam)
{
   RTHelp   *pRTHelp  = RTHelp::GetInstance();
   if(!pRTHelp->IsShown())
      pRTHelp->Show(true,2,0);
   else
      pRTHelp->Hide();

	return 0;
}




