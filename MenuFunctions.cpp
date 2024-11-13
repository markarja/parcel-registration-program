/* MenuFunctions implementation

   Version              Date            New features
   1.2                  31.1.2003
   1.3                  11.7.2003       Added the void DisplayDeviationsInSizes(String sizes[]) and
                                        the void ClearDeviationDisplayArea(void) functions
                                        which enable the possibility to see what deviations
                                        the user has entered. This was a request of user Sanna Joki.
                                        Change implemented by Markus Karjalainen.
   1.4                  22.1.2004       Changed the void GetWhAddrFromUsr(ParcelRecord * argRec) function
                                        so that it capitalizes all letters in the warehouse address.
                                        Also fixed the owerflow of the chrAddress array by adding a seventh
                                        cell for null terminating.

   Written by: Markus Karjalainen/DHL Solutions
   Last changed: 1.4 22.1.2004

*/

#pragma hdrstop
#include "MenuFunctions.h"
#include "ScannerFunctions.h"
#include "FileFunctions.h"
#include <conio.h>
#include <fstream.h>

#pragma package(smart_init)

void ClearSizeClassInputArea(void)
{
        gotoxy(30, 18);
        textcolor(BLACK);
        cprintf("   ");
        textcolor(BLACK);
        gotoxy(12, 18);
        cprintf("Sy%ct%c kokoluokka: ", SCAN_O, SCAN_AE);
}

bool IsDigitOrEnter(char argChar)
{
        if((int)argChar !=  49 && (int)argChar !=  50 &&
           (int)argChar !=  51 && (int)argChar !=  52 &&
           (int)argChar !=  53 && (int)argChar !=  54 &&
           (int)argChar !=  55 && (int)argChar !=  56 &&
           (int)argChar != 57 && (int)argChar != ENTER &&
           (int)argChar != 48)
                return false;
        else
                return true;
}

bool SizeClassIsLegal(char argSizeClass[])
{
        unsigned short check = atoi(argSizeClass);
        if(check > 11 || check < 1)
                return false;
        else
                return true;
}

void DisplayParcelMenu(void)
{
        gotoxy(10, 8);
        cprintf("Valitse rekister%cintitapa:             ", SCAN_O);
        gotoxy(10, 10);
        cprintf("1. Monta korttia, yksi kolli            ");
        gotoxy(10, 12);
        cprintf("2. Yksi kortti, yksi kolli              ");
        gotoxy(10, 14);
        cprintf("3. Yksi kortti, monta kollia            ");
        gotoxy(10, 16);
        cprintf("4. Paluu                                ");
        gotoxy(10, 18);
        cprintf("Anna valinta[ ]                         ");
        gotoxy(23, 18);
}

void DisplayMenu(void)
{
        gotoxy(10, 8);
        cprintf("Valitse rekister%cintiyksikk%c          ", SCAN_O, SCAN_O );
        gotoxy(10, 10);
        cprintf("1. Riiput                               ");
        gotoxy(10, 12);
        cprintf("2. Kartongit                            ");
        gotoxy(10, 14);
        cprintf("3. Lopeta                               ");
        gotoxy(10, 16);
        cprintf("Anna valinta[ ]                         ");
        gotoxy(23, 16);
}

void ClearMenuArea(void)
{
        int x = 1, y = 8;
        textcolor(LIGHTGRAY);
        for(y;y < 19;y++)
        {
                gotoxy(x, y);
                cprintf("%s", EMPTY_STR);
        }
        textcolor(BLACK);
}
int GetAndDisplayInput(void)
{
        char input = 0;
        input = getch();
        cprintf("%c", input);
        return (int)input;
}

unsigned int GetFirstParcelNo(void)
{
        char returnNumber[4] = {0,0,0,0};
        char chrInput = 0;
        int i = 0;
        gotoxy(10, 8);
        cprintf("Sy%ct%c ensimm%cinen kollinumero: ", SCAN_O, SCAN_AE, SCAN_AE);
        do
        {
                chrInput = getch();
                if((int)chrInput == BACKSPACE)
                {
                        if(i > 0)
                        {
                                i--;
                                returnNumber[i] = 0;
                                gotoxy(wherex() - 1, wherey());
                                textcolor(LIGHTGRAY);
                                cprintf(" ");
                                textcolor(BLACK);
                                gotoxy(wherex() - 1, wherey());
                        }
                }
                else if(i < 4)
                {
                        returnNumber[i] = chrInput;
                        cprintf("%c", chrInput);
                        i++;
                }

        }
        while((int)chrInput != ENTER);
        return atoi(returnNumber);
}

unsigned int GetParcelNoFromUsr(unsigned int argParcelNo)
{
        char input = 0;
        char returnNumber[4] = {0,0,0,0};
        itoa(argParcelNo, returnNumber, 10);
        ClearMenuArea();
        gotoxy(10, 10);
        cprintf("Sy%ct%c kollinumero: ", SCAN_O, SCAN_AE);
        gotoxy(29, 10);
        cprintf("%s", returnNumber);
        do
        {
                input = getch();
                if((int)input == BACKSPACE && strlen(returnNumber)  > 0)
                {
                        gotoxy(strlen(returnNumber) + 28, 10);
                        textcolor(LIGHTGRAY);
                        cprintf(" ");
                        textcolor(BLACK);
                        gotoxy(strlen(returnNumber) + 28, 10);
                        returnNumber[strlen(returnNumber) - 1] = '\0';
                }
                else if((int)input != BACKSPACE && strlen(returnNumber) < 4)
                {
                        gotoxy(29, 10);
                        returnNumber[strlen(returnNumber)] = input;
                        cprintf("%s", returnNumber);
                }
        }
        while((int)input != ENTER);
        return atoi(returnNumber);
}

void GetParcelWeightAndCapacityFromUsr(ParcelRecord * argRec)
{
        char chrInput = 0, inputString[5] = {0,0,0,0,0};
        auto char * lastWeightOrCapacity = NULL;
        lastWeightOrCapacity = argRec->lWeight.c_str();
        int i = 0;
        int j = 1;
        while(j <= argRec->lWeight.Length())
        {
                inputString[i] = lastWeightOrCapacity[i];
                i++;
                j++;
        }
        lastWeightOrCapacity = NULL;
        gotoxy(12, 12);
        cprintf("Sy%ct%c kollin paino: ", SCAN_O, SCAN_AE);
        cprintf("%s", inputString);
        do
        {
                chrInput = getch();
                if((int)chrInput == BACKSPACE)
                {
                        if(i > 0)
                        {
                                i--;
                                inputString[i] = 0;
                                gotoxy(wherex() - 1, wherey());
                                textcolor(LIGHTGRAY);
                                cprintf(" ");
                                textcolor(BLACK);
                                gotoxy(wherex() - 1, wherey());
                        }
                }
                else if(i < 5 && chrInput != ENTER)
                {
                        inputString[i] = chrInput;
                        cprintf("%c", chrInput);
                        i++;
                }

        }
        while(chrInput != ENTER);
        argRec->weight = inputString;
        gotoxy(12, wherey() + 2);
        for(i = 0;i < 5;i++)
        {
                inputString[i] = 0;
        }
        i = 0;
        j = 1;
        lastWeightOrCapacity = argRec->lm3.c_str();
        while(j <= argRec->lm3.Length())
        {
                inputString[i] = lastWeightOrCapacity[i];
                i++;
                j++;
        }
        lastWeightOrCapacity = NULL;
        cprintf("Sy%ct%c kollin tilavuus: ", SCAN_O, SCAN_AE);
        cprintf("%s", inputString);
        do
        {
                chrInput = getch();
                if((int)chrInput == BACKSPACE)
                {
                        if(i > 0)
                        {
                                i--;
                                inputString[i] = 0;
                                gotoxy(wherex() - 1, wherey());
                                textcolor(LIGHTGRAY);
                                cprintf(" ");
                                textcolor(BLACK);
                                gotoxy(wherex() - 1, wherey());
                        }
                }
                else if(i < 5 && chrInput != ENTER)
                {
                        inputString[i] = chrInput;
                        cprintf("%c", chrInput);
                        i++;
                }

        }
        while(chrInput != ENTER);
        argRec->m3 = inputString;
}

unsigned short GetActionIdFromUsr(void)
{
        char input = 0;
        gotoxy(12,14);
        cprintf("Anna tapahtuma (O = OK, P = Puuttuvia, S = Sekundaa): ");
        while((int)input != SMALL_O_CHAR && (int)input != O_CHAR &&
              (int)input != SMALL_S_CHAR && (int)input != S_CHAR &&
              (int)input != SMALL_P_CHAR && (int)input != P_CHAR)
        {
                input = getch();
        }
        cprintf("%c", input);
        return input;
}

void GetPremiumSizesFromUsr(ParcelRecord * argRec)
{
        char chrInput = 0;
        char sizeClass[3] = {0,0,0};
        short input = 0;
        int i = 0;
        while(1)
        {
                gotoxy(12, 16);
                cprintf("Priimojen kappalem%c%crien muutokset", SCAN_AE, SCAN_AE);
                gotoxy(12, 17);
                cprintf("----------------------------------");
                gotoxy(12, 18);
                cprintf("Sy%ct%c kokoluokka: ", SCAN_O, SCAN_AE);
                do
                {
                        do
                                chrInput = getch();
                        while(!IsDigitOrEnter(chrInput));
                        cprintf("%c", chrInput);
                        sizeClass[i] = chrInput;
                        i++;
                        if(i == 2)
                        {
                                if(!SizeClassIsLegal(sizeClass))
                                {
                                        i = 0;
                                        chrInput = 0;
                                        sizeClass[0] = 0;
                                        sizeClass[1] = 0;
                                        ClearSizeClassInputArea();
                                }
                        }
                }
                while((int)chrInput != ENTER && i < 2);
                input = atoi(sizeClass);
                i = 0;
                gotoxy(12, 19);
                cprintf("Sy%ct%c kappalemaara: ", SCAN_O, SCAN_AE);
                do
                {
                        chrInput = getch();
                        if(i == 0 && (int)chrInput != ENTER)
                        {
                                argRec->premiumSizes[input - 1] = chrInput;
                        }
                        else if((int)chrInput != ENTER)
                        {
                                argRec->premiumSizes[input - 1] = argRec->premiumSizes[input - 1] + chrInput;
                        }
                        i++;
                        cprintf("%c", chrInput);
                }
                while((int)chrInput != ENTER && i < 3);
                DisplayDeviationsInSizes(argRec->premiumSizes);
                gotoxy(12, 20);
                cprintf("Lis%c%c kokoluokkia?: ", SCAN_AE, SCAN_AE);
                chrInput = getch();
                if((int)chrInput == SMALL_K_CHAR || (int)chrInput == K_CHAR)
                {
                        ClearSizesInputArea();
                        i = 0;
                }
                else
                {
                        ClearSizesInputArea();
                        ClearDeviationDisplayArea();
                        break;
                }
        }
}

void ClearDeviationDisplayArea(void) {
  int x = 0, y = 0;
  x = 10; y = 3;
  while(y < 12) {
    gotoxy(x, y);
    cprintf("%s", EMPTY_STR);
    y++;
  }
  return;
}

void DisplayDeviationsInSizes(String sizes[]) {
  int i = 0;
  int x = 0, y = 0;
  x = 10; y = 3;
  gotoxy(x, y);
  cprintf("Kokoluokka");
  x = x + 12;
  gotoxy(x, y);
  x = x - 12; y = y + 1;
  cprintf("Kappalem%c%cr%c", SCAN_AE, SCAN_AE, SCAN_AE);
  while(i < 11) {
    if(sizes[i] != "000") {
      gotoxy(x, y);
      cprintf("%i", i + 1);
      gotoxy(x + 12, y);
      cprintf("%s", sizes[i].c_str());
      y++;
    }
    i++;
  }
  return;
}

void GetSecondarySizesFromUsr(ParcelRecord * argRec)
{
        char chrInput = 0;
        char sizeClass[3] = {0,0,0};
        short input = 0;
        int i = 0;
        while(1)
        {
                gotoxy(12, 16);
                cprintf("Sekundojen kappalem%c%cr%ct", SCAN_AE, SCAN_AE, SCAN_AE);
                gotoxy(12, 17);
                cprintf("----------------------------------");
                gotoxy(12, 18);
                cprintf("Sy%ct%c kokoluokka: ", SCAN_O, SCAN_AE);
                do
                {
                        do
                                chrInput = getch();
                        while(!IsDigitOrEnter(chrInput));
                        cprintf("%c", chrInput);
                        sizeClass[i] = chrInput;
                        i++;
                        if(i == 2)
                        {
                                if(!SizeClassIsLegal(sizeClass))
                                {
                                        i = 0;
                                        chrInput = 0;
                                        sizeClass[0] = 0;
                                        sizeClass[1] = 0;
                                        ClearSizeClassInputArea();
                                }
                        }
                }
                while((int)chrInput != ENTER && i < 2);
                input = atoi(sizeClass);
                i = 0;
                gotoxy(12, 19);
                cprintf("Sy%ct%c kappalem%c%cr%c: ", SCAN_O, SCAN_AE, SCAN_AE, SCAN_AE, SCAN_AE);
                do
                {
                        chrInput = getch();
                        if(i == 0 && (int)chrInput != ENTER)
                        {
                                argRec->secondarySizes[input - 1] = chrInput;
                        }
                        else if((int)chrInput != ENTER)
                        {
                                argRec->secondarySizes[input - 1] = argRec->secondarySizes[input - 1] + chrInput;
                        }
                        i++;
                        cprintf("%c", chrInput);
                }
                while((int)chrInput != ENTER && i < 3);
                DisplayDeviationsInSizes(argRec->secondarySizes);
                gotoxy(12, 20);
                cprintf("Lis%c%c kokoluokkia?: " , SCAN_AE, SCAN_AE);
                chrInput = getch();
                if((int)chrInput == SMALL_K_CHAR || (int)chrInput == K_CHAR)
                {
                        ClearSizesInputArea();
                        i = 0;
                }
                else
                {
                        ClearSizesInputArea();
                        ClearDeviationDisplayArea();
                        break;
                }
        }
}

void ClearSizesInputArea(void)
{
        int x = 1, y = 16;
        textcolor(LIGHTGRAY);
        for(y;y < 21;y++)
        {
                gotoxy(x, y);
                cprintf("%s", EMPTY_STR);
        }
        textcolor(BLACK);
}

void ClearBarcodeInputArea(void)
{
        int x = 1, y = 12;
        textcolor(LIGHTGRAY);
        for(y;y< 25;y++)
        {
                gotoxy(x, y);
                cprintf("%s", EMPTY_STR);
        }
        textcolor(BLACK);
}

void ManyCardsOneParcel(ParcelRecord * argRec, unsigned  int * argParcelNo)
{
        String hFilename = GenerateFilename(false);
        String pFilename = GenerateFilename(false);
        hFilename = "K" + hFilename;
        pFilename = "SIS_K" + pFilename;
        char input = 0;
        *argParcelNo = GetParcelNoFromUsr(*argParcelNo);
        argRec->parcelNo = *argParcelNo;
        while(1)
        {
                ReadAndDisplayBarCode(argRec);
                GetWhAddrFromUsr(argRec);
                do
                {
                        input = GetActionIdFromUsr();
                        if((int)input == SMALL_P_CHAR || (int)input == P_CHAR)
                        {
                                GetPremiumSizesFromUsr(argRec);
                        }
                        else if((int)input == SMALL_S_CHAR || (int)input == S_CHAR)
                        {
                                GetSecondarySizesFromUsr(argRec);
                        }
                }
                while(input != SMALL_O_CHAR && input != O_CHAR);
                WriteDeviationsToFile(hFilename.c_str(), argRec);
                gotoxy(10, 16);
                cprintf("Lis%c%c kortteja kollinumerolle %i? ", SCAN_AE, SCAN_AE, *argParcelNo);
                input = getch();
                if(input == SMALL_K_CHAR || input == K_CHAR)
                {
                        ClearBarcodeInputArea();
                        argRec->SetTimeAndDate();
                        argRec->WriteToFile(pFilename.c_str());
                        argRec->Reset();
                        DisplayRecsWrittenToFile(&argRec->recsWrittenToFile, &argRec->recsWrittenToHFile);
                }
                else
                {
                        ClearBarcodeInputArea();
                        GetParcelWeightAndCapacityFromUsr(argRec);
                        ClearBarcodeInputArea();
                        argRec->SetTimeAndDate();
                        argRec->WriteToFile(pFilename.c_str());
                        argRec->Reset();
                        DisplayRecsWrittenToFile(&argRec->recsWrittenToFile, &argRec->recsWrittenToHFile);
                        break;
                }
        }
}

void OneCardOneParcel(ParcelRecord * argRec, unsigned int * argParcelNo)
{
        String hFilename = GenerateFilename(false);
        String pFilename = GenerateFilename(false);
        hFilename = "K" + hFilename;
        pFilename = "SIS_K" + pFilename;
        char input = 0;
        *argParcelNo = GetParcelNoFromUsr(*argParcelNo);
        argRec->parcelNo = *argParcelNo;
        while(1)
        {
                ReadAndDisplayBarCode(argRec);
                GetWhAddrFromUsr(argRec);
                do
                {
                        input = GetActionIdFromUsr();
                        if((int)input == SMALL_P_CHAR || (int)input == P_CHAR)
                        {
                                GetPremiumSizesFromUsr(argRec);
                        }
                        else if((int)input == SMALL_S_CHAR || (int)input == S_CHAR)
                        {
                                GetSecondarySizesFromUsr(argRec);
                        }
                }
                while(input != SMALL_O_CHAR && input != O_CHAR);
                WriteDeviationsToFile(hFilename.c_str(), argRec);
                ClearBarcodeInputArea();
                GetParcelWeightAndCapacityFromUsr(argRec);
                ClearBarcodeInputArea();
                argRec->SetTimeAndDate();
                argRec->WriteToFile(pFilename.c_str());
                argRec->Reset();
                DisplayRecsWrittenToFile(&argRec->recsWrittenToFile, &argRec->recsWrittenToHFile);
                break;
        }
}

void OneCardManyParcels(ParcelRecord * argRec, unsigned int * argParcelNo)
{
        String hFilename = GenerateFilename(false);
        String pFilename = GenerateFilename(false);
        hFilename = "K" + hFilename;
        pFilename = "SIS_K" + pFilename;
        char input = 0;
        *argParcelNo = GetParcelNoFromUsr(*argParcelNo);
        argRec->parcelNo = *argParcelNo;
        ReadAndDisplayBarCode(argRec);
        GetWhAddrFromUsr(argRec);
        do
        {
                input = GetActionIdFromUsr();
                if((int)input == SMALL_P_CHAR || (int)input == P_CHAR)
                {
                        GetPremiumSizesFromUsr(argRec);
                }
                else if((int)input == SMALL_S_CHAR || (int)input == S_CHAR)
                {
                        GetSecondarySizesFromUsr(argRec);
                }
        }
        while(input != SMALL_O_CHAR && input != O_CHAR);
        WriteDeviationsToFile(hFilename.c_str(), argRec);
        ClearBarcodeInputArea();
        GetParcelWeightAndCapacityFromUsr(argRec);
        ClearBarcodeInputArea();
        argRec->SetTimeAndDate();
        argRec->WriteToFile(pFilename.c_str());
        DisplayRecsWrittenToFile(&argRec->recsWrittenToFile, &argRec->recsWrittenToHFile);
        argRec->Reset();
        while(1)
        {
                gotoxy(10, 16);
                cprintf("Lis%c%c kolleja kortille %s%s? ", SCAN_AE, SCAN_AE, argRec->orderNo.c_str(), argRec->lineNo.c_str());
                input = getch();
                if((int)input == K_CHAR || (int)input == SMALL_K_CHAR)
                {
                        *argParcelNo = *argParcelNo + 1;
                        *argParcelNo = GetParcelNoFromUsr(*argParcelNo);
                        argRec->parcelNo = *argParcelNo;
                        ClearBarcodeInputArea();
                        GetParcelWeightAndCapacityFromUsr(argRec);
                        ClearBarcodeInputArea();
                        argRec->SetTimeAndDate();
                        argRec->WriteToFile(pFilename.c_str());
                        DisplayRecsWrittenToFile(&argRec->recsWrittenToFile, &argRec->recsWrittenToHFile);
                        argRec->Reset();
                }
                else
                {
                        break;
                }
        }
}

void PrintCopyrightNotice(void)
{
        gotoxy(58, 25);
        textcolor(DARKGRAY);
        cprintf("(C) DHL Solutions 2004");
        textcolor(BLACK);
}

void PrintApplicationName(void)
{
        gotoxy(1, 1);
        textcolor(WHITE);
        cprintf("Ker%cilykorttien rekister%cinti v1.3", SCAN_AE, SCAN_O);
        textcolor(BLACK);
}

void GetWhAddrFromUsr(ParcelRecord * argRec)
{
        bool ReaderSecured = false;
        char chrInput = 0;
        auto char * lastAddress = NULL;
        char chrAddress[7] = {0,0,0,0,0,0,0};
        lastAddress = argRec->warehouseAddress.c_str();
        int i = 0;
        int j = 1;
        while(j <= argRec->warehouseAddress.Length())
        {
                chrAddress[i] = lastAddress[i];
                i++;
                j++;
        }
        lastAddress = NULL;
        gotoxy(38, 12);
        cprintf("Sy%ct%c lokaatio: ", SCAN_O, SCAN_AE);
        cprintf("%s", chrAddress);
        do
        {
                chrInput = getch();
                if((int)chrInput == BACKSPACE)
                {
                        if(i > 0)
                        {
                                i--;
                                chrAddress[i] = 0;
                                gotoxy(wherex() - 1, wherey());
                                textcolor(LIGHTGRAY);
                                cprintf(" ");
                                textcolor(BLACK);
                                gotoxy(wherex() - 1, wherey());
                        }
                }
                else if(i < 6 && (int)chrInput != ENTER)
                {
                        chrAddress[i] = chrInput;
                        cprintf("%c", chrInput);
                        i++;
                }
                if(i == 0 && (int)chrInput == ENTER && !ReaderSecured)
                {
                        ReaderSecured = true;
                        chrInput = 0;
                }
        }
        while((int)chrInput != ENTER);
        //capitalizing letters of warehouse address
        i = 0;
        j = 6;
        while(i < j) {
          chrAddress[i] = UpCase(chrAddress[i]);
          i++;
        }
        argRec->warehouseAddress = chrAddress;
}

void HangingGarments(ParcelRecord * argRec)
{
        String hFilename = GenerateFilename(false);
        hFilename = "R" + hFilename;
        char input = 0;
        ClearMenuArea();
        do
        {
                ClearBarcodeInputArea();
                ReadAndDisplayBarCode(argRec);
                GetWhAddrFromUsr(argRec);
                do
                {
                        input = GetActionIdFromUsr();
                        if((int)input == SMALL_P_CHAR || (int)input == P_CHAR)
                        {
                                GetPremiumSizesFromUsr(argRec);
                        }
                        else if((int)input == SMALL_S_CHAR || (int)input == S_CHAR)
                        {
                                GetSecondarySizesFromUsr(argRec);
                        }
                }
                while(input != SMALL_O_CHAR && input != O_CHAR);
                WriteDeviationsToFile(hFilename.c_str(), argRec);
                gotoxy(10, 16);
                cprintf("Lis%c%c kortteja? ", SCAN_AE, SCAN_AE);
                input = getch();
                DisplayRecsWrittenToFile(&argRec->recsWrittenToFile, &argRec->recsWrittenToHFile);
        }
        while(input == K_CHAR || input == SMALL_K_CHAR);
        argRec->Reset();
}
