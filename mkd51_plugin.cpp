#include "mkd51_plugin.h"
#include "AGSI_Defs.h"
#include "Controller/headers/simulator.h"
#include <QWidget>


AGSICONFIG AgsiConfig;
AGSIFUNCS Agsi;

void showMessage(AGSIMENU* pm);
bool AgsiInit();
bool DefineAllMenuEntries();

extern "C" DWORD AGSIEXPORT AgsiEntry (DWORD nCode, void *vp) {

    switch (nCode) {

    case AGSI_CHECK:

      if (*((DWORD *)vp) == 8051) //check CPU Type
          return true;
      else
          return false;
      break;

    case AGSI_INIT:
      AgsiConfig = *((AGSICONFIG *)vp);
      if (!AgsiInit())
          return false;

      if (!DefineAllMenuEntries())
          return false;
      break;

    case AGSI_TERMINATE:
      break;

    case AGSI_RESET:
      break;
  }
  return true;
}

bool DefineAllMenuEntries() {
    AGSIMENU mkdMenu = { 1, "MKD Simulator" , showMessage, 0, 0, 0};

  if (!Agsi.DefineMenuItem(&mkdMenu)) return(false);

  return(true);
}

void showMessage(AgsiDynaM *pm) {
    if(!Controller::Simulator::simulator().guiStarted())
        Controller::Simulator::simulator().startGui();
    else
        Controller::Simulator::simulator().stopGui();
}

bool AgsiInit() {

    Agsi.DefineSFR            = (tAgsiDefineSFR)             GetProcAddress(AgsiConfig.m_hInstance, "AgsiDefineSFR");
    Agsi.DefineVTR            = (tAgsiDefineVTR)             GetProcAddress(AgsiConfig.m_hInstance, "AgsiDefineVTR");
    Agsi.DeclareInterrupt     = (tAgsiDeclareInterrupt)      GetProcAddress(AgsiConfig.m_hInstance, "AgsiDeclareInterrupt");
    Agsi.SetWatchOnSFR        = (tAgsiSetWatchOnSFR)         GetProcAddress(AgsiConfig.m_hInstance, "AgsiSetWatchOnSFR");
    Agsi.SetWatchOnVTR        = (tAgsiSetWatchOnVTR)         GetProcAddress(AgsiConfig.m_hInstance, "AgsiSetWatchOnVTR");
    Agsi.SetWatchOnMemory     = (tAgsiSetWatchOnMemory)      GetProcAddress(AgsiConfig.m_hInstance, "AgsiSetWatchOnMemory");
    Agsi.CreateTimer          = (tAgsiCreateTimer)           GetProcAddress(AgsiConfig.m_hInstance, "AgsiCreateTimer");
    Agsi.DefineMenuItem       = (tAgsiDefineMenuItem)        GetProcAddress(AgsiConfig.m_hInstance, "AgsiDefineMenuItem");

    Agsi.WriteSFR             = (tAgsiWriteSFR)              GetProcAddress(AgsiConfig.m_hInstance, "AgsiWriteSFR");
    Agsi.ReadSFR              = (tAgsiReadSFR)               GetProcAddress(AgsiConfig.m_hInstance, "AgsiReadSFR");
    Agsi.WriteVTR             = (tAgsiWriteVTR)              GetProcAddress(AgsiConfig.m_hInstance, "AgsiWriteVTR");
    Agsi.ReadVTR              = (tAgsiReadVTR)               GetProcAddress(AgsiConfig.m_hInstance, "AgsiReadVTR");
    Agsi.SetSFRReadValue      = (tAgsiSetSFRReadValue)       GetProcAddress(AgsiConfig.m_hInstance, "AgsiSetSFRReadValue");
    Agsi.ReadMemory           = (tAgsiReadMemory)            GetProcAddress(AgsiConfig.m_hInstance, "AgsiReadMemory");
    Agsi.WriteMemory          = (tAgsiWriteMemory)           GetProcAddress(AgsiConfig.m_hInstance, "AgsiWriteMemory");
    Agsi.GetLastMemoryAddress = (tAgsiGetLastMemoryAddress)  GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetLastMemoryAddress");
    Agsi.IsSimulatorAccess    = (tAgsiIsSimulatorAccess)     GetProcAddress(AgsiConfig.m_hInstance, "AgsiIsSimulatorAccess");
    Agsi.SetTimer             = (tAgsiSetTimer)              GetProcAddress(AgsiConfig.m_hInstance, "AgsiSetTimer");
    Agsi.GetStates            = (tAgsiGetStates)             GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetStates");
    Agsi.GetProgramCounter    = (tAgsiGetProgramCounter)     GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetProgramCounter");
    Agsi.IsInInterrupt        = (tAgsiIsInInterrupt)         GetProcAddress(AgsiConfig.m_hInstance, "AgsiIsInInterrupt");
    Agsi.IsSleeping           = (tAgsiIsSleeping)            GetProcAddress(AgsiConfig.m_hInstance, "AgsiIsSleeping");
    Agsi.StopSimulator        = (tAgsiStopSimulator)         GetProcAddress(AgsiConfig.m_hInstance, "AgsiStopSimulator");
    Agsi.TriggerReset         = (tAgsiTriggerReset)          GetProcAddress(AgsiConfig.m_hInstance, "AgsiTriggerReset");
    Agsi.UpdateWindows        = (tAgsiUpdateWindows)         GetProcAddress(AgsiConfig.m_hInstance, "AgsiUpdateWindows");
    Agsi.HandleFocus          = (tAgsiHandleFocus)           GetProcAddress(AgsiConfig.m_hInstance, "AgsiHandleFocus");
    Agsi.GetExternalClockRate = (tAgsiGetExternalClockRate)  GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetExternalClockRate");
    Agsi.GetInternalClockRate = (tAgsiGetInternalClockRate)  GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetInternalClockRate");
    Agsi.GetClockFactor       = (tAgsiGetClockFactor)        GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetClockFactor");
    Agsi.Message              = (tAgsiMessage)               GetProcAddress(AgsiConfig.m_hInstance, "AgsiMessage");
    Agsi.GetTargetKey         = (tAgsiGetTargetKey)          GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetTargetKey");
    Agsi.SetTargetKey         = (tAgsiSetTargetKey)          GetProcAddress(AgsiConfig.m_hInstance, "AgsiSetTargetKey");
    Agsi.GetSymbolByName      = (tAgsiGetSymbolByName)       GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetSymbolByName");
    Agsi.GetSymbolByValue     = (tAgsiGetSymbolByValue)      GetProcAddress(AgsiConfig.m_hInstance, "AgsiGetSymbolByValue");

    if ((Agsi.DefineSFR            == NULL) ||
        (Agsi.DefineVTR            == NULL) ||
        (Agsi.DeclareInterrupt     == NULL) ||
        (Agsi.SetWatchOnSFR        == NULL) ||
        (Agsi.SetWatchOnVTR        == NULL) ||
        (Agsi.SetWatchOnMemory     == NULL) ||
        (Agsi.CreateTimer          == NULL) ||
        (Agsi.DefineMenuItem       == NULL) ||

        (Agsi.WriteSFR             == NULL) ||
        (Agsi.ReadSFR              == NULL) ||
        (Agsi.WriteVTR             == NULL) ||
        (Agsi.ReadVTR              == NULL) ||
        (Agsi.SetSFRReadValue      == NULL) ||
        (Agsi.ReadMemory           == NULL) ||
        (Agsi.WriteMemory          == NULL) ||
        (Agsi.GetLastMemoryAddress == NULL) ||
        (Agsi.IsSimulatorAccess    == NULL) ||
        (Agsi.SetTimer             == NULL) ||
        (Agsi.GetStates            == NULL) ||
        (Agsi.GetProgramCounter    == NULL) ||
        (Agsi.IsInInterrupt        == NULL) ||
        (Agsi.IsSleeping           == NULL) ||
        (Agsi.StopSimulator        == NULL) ||
        (Agsi.TriggerReset         == NULL) ||
        (Agsi.UpdateWindows        == NULL) ||
        (Agsi.HandleFocus          == NULL) ||
        (Agsi.GetExternalClockRate == NULL) ||
        (Agsi.GetInternalClockRate == NULL) ||
        (Agsi.GetClockFactor       == NULL) ||
        (Agsi.Message              == NULL) ||
        (Agsi.GetTargetKey         == NULL) ||
        (Agsi.SetTargetKey         == NULL) ||
        (Agsi.GetSymbolByName      == NULL) ||
        (Agsi.GetSymbolByValue     == NULL)) {

      return false;
    }

    return true;
}
