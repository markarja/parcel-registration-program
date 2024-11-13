/* MenuFunctions header

   Version history:

   Version              Date            New features
   1.2                  31.1.2003
   1.3                  11.7.2003       Added the void DisplayDeviationsInSizes(String sizes[]) and
                                        the void ClearDeviationDisplayArea(void) functions
                                        which enable the possibility to see what deviations
                                        the user has entered. This was a request of user Sanna Joki.
                                        Change implemented by Markus Karjalainen.

   Written by: Markus Karjalainen/SGS
   Last changed: 11.7.2003

*/
#include "ParcelRecord.h"
#ifndef MenuFunctionsH
#define MenuFunctionsH
const char EMPTY_STR[80] = "                                                                               ";
const unsigned short ENTER = 13;
const unsigned short BACKSPACE = 8;
const unsigned short SMALL_S_CHAR = 83;
const unsigned short S_CHAR = 115;
const unsigned short SMALL_P_CHAR = 80;
const unsigned short P_CHAR = 112;
const unsigned short SMALL_O_CHAR = 79;
const unsigned short O_CHAR = 111;
const unsigned short K_CHAR = 75;
const unsigned short SMALL_K_CHAR = 107;
const char SCAN_AE = 65412;
const char SCAN_O = 65428;

unsigned int GetFirstParcelNo(void);
void DisplayParcelMenu(void);
void DisplayMenu(void);
int GetAndDisplayInput(void);
unsigned short GetActionIdFromUsr(void);
void GetPremiumSizesFromUsr(ParcelRecord * argRec);
void DisplayDeviationsInSizes(String sizes[]);
void ClearDeviationDisplayArea(void);
void GetSecondarySizesFromUsr(ParcelRecord * argRec);
void ManyCardsOneParcel(ParcelRecord * argRec, unsigned  int * argParcelNo);
void OneCardOneParcel(ParcelRecord * argRec, unsigned int * argParcelNo);
void OneCardManyParcels(ParcelRecord * argRec, unsigned int * argParcelNo);
void HangingGarments(ParcelRecord * argRec);
unsigned int GetParcelNoFromUsr(unsigned int argParcelNo);
void ClearSizesInputArea(void);
void ClearBarcodeInputArea(void);
void ClearSizeClassInputArea(void);
void ClearMenuArea(void);
bool IsDigitOrEnter(char argChar);
bool SizeClassIsLegal(char argSizeClass[]);
void GetParcelWeightAndCapacityFromUsr(ParcelRecord * argRec);
void PrintCopyrightNotice(void);
void PrintApplicationName(void);
void GetWhAddrFromUsr(ParcelRecord * argRec);
#endif
