#ifndef __AGSI_H__
#define __AGSI_H__


#include <windows.h>


#define AGSIEXPORT __declspec( dllexport )
#define AGSIAPI    WINAPIV


#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
//
// AGSI: Advanced Generic Simulator Interface (Simulation Interface Part)
//

typedef DWORD AGSIVTR;
typedef DWORD AGSIADDR;
typedef DWORD AGSITIMER;
typedef void (* AGSICALLBACK)(void);

typedef struct {
  HINSTANCE     m_hInstance;
  const char*   m_pszProjectPath;
  const char*   m_pszDevice;
  const char*   m_pszConfiguration;
  const char*   m_pszAppFile;
} AGSICONFIG;

typedef enum {
  AGSIBYTE = 1,
  AGSIWORD = 2,
  AGSILONG = 4,
  AGSIBIT  = 5,
  AGSIVTRCHAR = 10,
  AGSIVTRWORD = 11,
  AGSIVTRLONG = 12,
  AGSIVTRFLOAT = 13
} AGSITYPE;

typedef enum {
  AGSIREAD,
  AGSIWRITE,
  AGSIREADWRITE,
} AGSIACCESS;

// function code numbers for AgsiEntry function
typedef enum {
  AGSI_CHECK     = 0,
  AGSI_INIT      = 1,
  AGSI_TERMINATE = 2,
  AGSI_RESET     = 3,
  AGSI_PREPLL    = 4,
  AGSI_POSTPLL   = 5
} AGSIFUNC;


/*
 * 80x51 memory spaces
 */

#define   amXDATA  0x0001           // XDATA
#define   amBANK0  0x0080           // BANK0
#define   amBANK31 0x009F           // BANK31
#define   amDATA   0x00F0           // DATA
#define   amBIT    0x00F1           // BIT
#define   amEDATA  0x00F2           // EDATA (i251)
#define   amIDATA  0x00F3           // IDATA
#define   amECODE  0x00F4           // 251 ecode
#define   amHDATA  0x00F5           // 251 hdata
#define   amHCONS  0x00F6           // 251 hconst
#define   amCONST  0x00F7           // 251 const
#define   amPDATA  0x00FE           // PDATA (c51 macht das bei generic)
#define   amCODE   0x00FF           // CODE 


typedef struct {
#ifdef __C166__
   AGSIADDR        vec;
   char          *mess;     // interrupt name
   AGSIADDR        sfr;     // interrupt control sfr 
#else
   AGSIADDR        vec;
   char          *mess;     // interrupt name
   AGSIADDR       msfr;     // interrupt mode sfr 
   WORD          mmask;     // interrupt mode bit mask
   const char   *mname;     // name of interrupt mode bit
   AGSIADDR       rsfr;     // interrupt request sfr 
   WORD          rmask;     // interrupt request bit mask
   const char   *rname;     // name of interrupt request bit
   AGSIADDR       esfr;     // interrupt enable sfr
   WORD          emask;     // interrupt enable bit mask
   const char   *ename;     // name of interrupt enable bit
   AGSIADDR      p0sfr;     // interrupt priority 0 sfr
   WORD         p0mask;     // interrupt priority 0 bit mask
   const char   *pname;     // name of interrupt priority bit
   AGSIADDR      p1sfr;     // interrupt priority 1 sfr
   WORD         p1mask;     // interrupt priority 1 bit mask
   WORD            pwl;     // priority within level
   WORD     auto_reset;     // reset interrupt request flag on interrupt entry
#endif
} AGSIINTERRUPT;


/*
 * Symbol search masks (may be combined using |) :
 */

typedef enum {
  AGSI_SYM_VAR = 0x0001,         // search for non-bit Variables
  AGSI_SYM_CON = 0x0002,         // search for named Constants
  AGSI_SYM_BIT = 0x0004,         // search for Bit in Memory
  AGSI_SYM_LOC = 0x0008,         // search for Function/Label
  AGSI_SYM_SFR = 0x0200          // search for SFR name
} AGSISYMMASK;

/*
 * Type of found symbol:
 */

typedef enum {
  AGSI_TP_VOID   = 0,
  AGSI_TP_BIT    = 1,
  AGSI_TP_CHAR   = 2,
  AGSI_TP_UCHAR  = 3,
  AGSI_TP_INT    = 4,
  AGSI_TP_UINT   = 5,
  AGSI_TP_SHORT  = 6,
  AGSI_TP_USHORT = 7,
  AGSI_TP_LONG   = 8,
  AGSI_TP_ULONG  = 9,
  AGSI_TP_FLOAT  = 10,
  AGSI_TP_DOUBLE = 11,
  AGSI_TP_PTR    = 12,
  AGSI_TP_UNION  = 13,
  AGSI_TP_STRUCT = 14,
  AGSI_TP_FUNC   = 15,
  AGSI_TP_STRING = 16,
  AGSI_TP_ENUM   = 17,
  AGSI_TP_FIELD  = 18
} AGSISYMTYPE;


typedef struct  {                  // Search for Sym by Name or Value.
  AGSISYMMASK nMask;               // search mask (AG_SYM_LOC | ...)
  char szName [256];               // search/found name (zero-terminated
  UINT64        val;               // search/found Adr/Value
  AGSISYMTYPE  type;               // type of found symbol (AGSI_TP_???)
  DWORD          Ok;               // 1:=Ok, else find failed.
} AGSISYMDSC;



/*
 * Dynamic Menu construction and maintanance
 */

//#pragma pack(1)

#define AGSIDLGD struct AgsiDlgDat
struct AgsiDlgDat {                      // every dialog has it's own structure
  DWORD             iOpen;               // auto reopen dialog (pos := 'rc')
  HWND                 hw;               // Hwnd of Dialog
  BOOL (CALLBACK *wp) (HWND hw, UINT msg, WPARAM wp, LPARAM lp);
  RECT                 rc;               // Position rectangle
  void   (*Update) (void);               // Update dialog content
  void (*Kill) (AGSIDLGD *pM);           // Kill dialog
  void                *vp;               // reserved for C++ Dialogs (Dlg *this)
};

#define AGSIMENU struct AgsiDynaM
struct AgsiDynaM  {                      // Menu item data structure
  int              nDelim;               // Menu template delimiter
  char            *szText;               // Menu item text
  void    (*fp) (AGSIMENU *pM);          // create/bringDlgtoTop function
  DWORD               nID;               // uv3 assigned ID_xxxx
  DWORD            nDlgId;               // Dialog ID
  AGSIDLGD          *pDlg;               // link to dialog attributes
};
//#pragma pack()

/*
 * nDelim:  1 := normal Menu entry
 *          2 := Popup-Entry (nested submenu)
 *         -2 := end of Popup-Group-List
 *         -1 := total end of Menu-List
 *  text:   the name for the menu/popup-menu entry
 *    fp:   Function to be activated on menu-selection
 */


// Function that must be exported by the loaded DLL
AGSIEXPORT DWORD        AGSIAPI AgsiEntry (DWORD nCode, void *vp);

// Callback functions that are ONLY allowed to call during the initialisation process
AGSIEXPORT BOOL         AGSIAPI AgsiDefineSFR(const char* pszSfrName, AGSIADDR dwAddress, AGSITYPE eType, BYTE bBitPos);
AGSIEXPORT AGSIVTR      AGSIAPI AgsiDefineVTR(const char* pszVtrName, AGSITYPE eType, DWORD dwValue);
AGSIEXPORT BOOL         AGSIAPI AgsiDeclareInterrupt(AGSIINTERRUPT *pInterrupt);
AGSIEXPORT BOOL         AGSIAPI AgsiSetWatchOnSFR(AGSIADDR SFRAddress, AGSICALLBACK pfnReadWrite, AGSIACCESS eAccess);
AGSIEXPORT BOOL         AGSIAPI AgsiSetWatchOnVTR(AGSIVTR hVTR, AGSICALLBACK pfnReadWrite, AGSIACCESS eAccess);
AGSIEXPORT BOOL         AGSIAPI AgsiSetWatchOnMemory(AGSIADDR StartAddress, AGSIADDR EndAddress, AGSICALLBACK pfnReadWrite, AGSIACCESS eAccess);
AGSIEXPORT AGSITIMER    AGSIAPI AgsiCreateTimer(AGSICALLBACK pfnTimer);
AGSIEXPORT BOOL         AGSIAPI AgsiDefineMenuItem(AGSIMENU *pDym);

// Callback functions that are NOT allowed to call during the initialisation process
AGSIEXPORT BOOL         AGSIAPI AgsiWriteSFR(AGSIADDR SFRAddress, DWORD dwValue, DWORD dwMask);
AGSIEXPORT BOOL         AGSIAPI AgsiReadSFR (AGSIADDR SFRAddress, DWORD* pdwCurrentValue, DWORD* pdwPreviousValue, DWORD dwMask);
AGSIEXPORT BOOL         AGSIAPI AgsiWriteVTR(AGSIVTR hVTR, DWORD dwValue);
AGSIEXPORT BOOL         AGSIAPI AgsiReadVTR (AGSIVTR hVTR, DWORD* pdwCurrentValue);
AGSIEXPORT BOOL         AGSIAPI AgsiSetSFRReadValue(DWORD dwValue);
AGSIEXPORT BOOL         AGSIAPI AgsiReadMemory (AGSIADDR Address, DWORD dwCount, BYTE* pbValue);
AGSIEXPORT BOOL         AGSIAPI AgsiWriteMemory(AGSIADDR Address, DWORD dwCount, BYTE* pbValue);
AGSIEXPORT AGSIADDR     AGSIAPI AgsiGetLastMemoryAddress(void);
AGSIEXPORT BOOL         AGSIAPI AgsiIsSimulatorAccess(void);
AGSIEXPORT BOOL         AGSIAPI AgsiSetTimer(AGSITIMER hTimer, DWORD dwClock);
AGSIEXPORT UINT64       AGSIAPI AgsiGetStates(void);
AGSIEXPORT AGSIADDR     AGSIAPI AgsiGetProgramCounter(void);
AGSIEXPORT DWORD        AGSIAPI AgsiIsInInterrupt(void);
AGSIEXPORT BOOL         AGSIAPI AgsiIsSleeping(void);
AGSIEXPORT void         AGSIAPI AgsiStopSimulator(void);
AGSIEXPORT void         AGSIAPI AgsiTriggerReset(void);
AGSIEXPORT void         AGSIAPI AgsiUpdateWindows(void);
AGSIEXPORT void         AGSIAPI AgsiHandleFocus (HWND hwndDialog);
AGSIEXPORT DWORD        AGSIAPI AgsiGetExternalClockRate(void);
AGSIEXPORT DWORD        AGSIAPI AgsiGetInternalClockRate(void);
AGSIEXPORT double       AGSIAPI AgsiGetClockFactor(void);
AGSIEXPORT void         AGSIAPI AgsiMessage(const char* pszFormat, ...);
AGSIEXPORT const char * AGSIAPI AgsiGetTargetKey(const char* pszKey);
AGSIEXPORT BOOL         AGSIAPI AgsiSetTargetKey(const char* pszKey, const char *pszString);
AGSIEXPORT DWORD        AGSIAPI AgsiGetSymbolByName (AGSISYMDSC *vp);
AGSIEXPORT DWORD        AGSIAPI AgsiGetSymbolByValue(AGSISYMDSC *vp);

#ifdef __cplusplus
}
#endif


#endif // __AGSI_H__


