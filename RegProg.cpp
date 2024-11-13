// Keräilykorttien rekisteröintiohjelma main program
//
// Version: 1.2.1
// Written by: Markus Karjalainen/SGS
// Last changed: 2.1.2003
//
//

#pragma hdrstop
#include "ParcelRecord.h"
#include "MenuFunctions.h"
#include "FileFunctions.h"
#include <conio.h>

int main()
{
        unsigned int currentParcelNo = 0;
        unsigned short input = 0;
        ParcelRecord * myRec = new ParcelRecord("999","0");
        textbackground(LIGHTGRAY);
        textcolor(BLACK);
        clrscr();
        PrintApplicationName();
        PrintCopyrightNotice();
        DisplayRecsWrittenToFile(&myRec->recsWrittenToFile, &myRec->recsWrittenToHFile);
        currentParcelNo = GetFirstParcelNo();
        GenerateFilename(true);
        do
        {
                DisplayMenu();
                input = GetAndDisplayInput();
                if(input == 49)
                {
                        HangingGarments(myRec);
                        ClearMenuArea();
                }
                else if(input == 50)
                {
                        do
                        {
                                DisplayParcelMenu();
                                input = GetAndDisplayInput();
                                if(input == 49)
                                {
                                        ManyCardsOneParcel(myRec, &currentParcelNo);
                                        currentParcelNo++;
                                }
                                else if(input == 50)
                                {
                                        OneCardOneParcel(myRec, &currentParcelNo);
                                        currentParcelNo++;
                                }
                                else if(input == 51)
                                {
                                        OneCardManyParcels(myRec, &currentParcelNo);
                                        currentParcelNo++;
                                }
                        }
                        while(input != 52);
                        ClearMenuArea();
                }
        }
        while(input != 51);
        delete myRec;
        return 0;
}
//---------------------------------------------------------------------------
