// FileFunctions implementation
//
// Version: 1.3
// Written by: Markus Karjalainen/SGS
// Last changed: 02.09.2003
//      - fixed a bug related to the filename, where the day didn't get included
//        in the filename if the day was smaller than ten. See comment.
//

#pragma hdrstop
#include <fstream.h>
#include <conio.h>
#include "FileFunctions.h"
#include <stdlib.h>
#include <time.h>

#pragma package(smart_init)
bool ThereAreDeviations(ParcelRecord * argRec)
{
        int i = 0;
        bool returnValue = false;
        for(i = 0;i < 11;i++)
        {
                if(argRec->premiumSizes[i] != "000")
                {
                        returnValue = true;
                        break;
                }
        }
        if(i == 11)
        {
                for(i = 0;i < 11;i++)
                {
                        if(argRec->secondarySizes[i] != "000")
                        {
                        returnValue = true;
                        break;
                        }
                }
        }
        return returnValue;
}

void WriteDeviationsToFile(const char argFilename[], ParcelRecord * argRec)
{
        argRec->SetTimeAndDate();
        if(argRec->regDay.Length() < 2)
        {
                argRec->regDay = "0" + argRec->regDay;
        }
        if(argRec->regMonth.Length() < 2)
        {
                argRec->regMonth = "0" + argRec->regMonth;
        }
        fstream fileHandle(argFilename);
        fileHandle.seekg(0, ios_base::end);
        if(ThereAreDeviations(argRec))
        {
                bool PAddedToWhAddr = false;
                int intSizeClass = 0;
                char strSizeClass[2] = {0,0};
                for(int i = 0;i < 11;i++)
                {
                        if(argRec->premiumSizes[i] != "000")
                        {
                                fileHandle.write(argRec->regDay.c_str(), 2);
                                fileHandle.write(".", 1);
                                fileHandle.write(argRec->regMonth.c_str(), 2);
                                fileHandle.write(".", 1);
                                fileHandle.write(argRec->regYear2.c_str(), 2);
                                fileHandle.write(";", 1);
                                fileHandle.write(argRec->regHour.c_str(), 2);
                                fileHandle.write(":", 1);
                                fileHandle.write(argRec->regMin.c_str(), 2);
                                fileHandle.write(";", 1);
                                fileHandle.write(argRec->packersInitials.c_str(), 3);
                                fileHandle.write(";", 1);
                                fileHandle.write("P", 1);
                                fileHandle.write(";", 1);
                                fileHandle.write(argRec->orderNo.c_str(), 5);
                                fileHandle.write(argRec->lineNo.c_str(), 2);
                                fileHandle.write(argRec->checkDigit.c_str(), 1);
                                fileHandle.write(";", 1);
                                intSizeClass = i + 1;
                                if(i < 10)
                                {
                                        itoa(intSizeClass, strSizeClass, 10);
                                        fileHandle.write(strSizeClass, 1);
                                }
                                else
                                {
                                        itoa(intSizeClass, strSizeClass, 10);
                                        fileHandle.write(strSizeClass, 2);
                                }
                                fileHandle.write(";", 1);
                                if(argRec->premiumSizes[i].Length() == 1)
                                        fileHandle.write(argRec->premiumSizes[i].c_str(), 1);
                                else if(argRec->premiumSizes[i].Length() == 2)
                                        fileHandle.write(argRec->premiumSizes[i].c_str(), 2);
                                else if(argRec->premiumSizes[i].Length() == 3)
                                        fileHandle.write(argRec->premiumSizes[i].c_str(), 3);
                                fileHandle.write(";", 1);
                                if(!PAddedToWhAddr)
                                {
                                       argRec->warehouseAddress = "P" + argRec->warehouseAddress;
                                       PAddedToWhAddr = true;
                                }
                                for(int j = 0;j < 7;j++)
                                {
                                        if(argRec->warehouseAddress.Length() == j + 1)
                                        {
                                                fileHandle.write(argRec->warehouseAddress.c_str(), j + 1);
                                        }
                                }
                                fileHandle.write(";", 1);
                                fileHandle.write(";", 1);
                                fileHandle.write("\n", 1);
                                argRec->premiumSizes[i] = "000";
                                argRec->recsWrittenToHFile = argRec->recsWrittenToHFile + 1;
                        }
                }
                for(int i = 0;i < 11;i++)
                {
                        if(argRec->secondarySizes[i] != "000")
                        {
                                fileHandle.write(argRec->regDay.c_str(), 2);
                                fileHandle.write(".", 1);
                                fileHandle.write(argRec->regMonth.c_str(), 2);
                                fileHandle.write(".", 1);
                                fileHandle.write(argRec->regYear2.c_str(), 2);
                                fileHandle.write(";", 1);
                                fileHandle.write(argRec->regHour.c_str(), 2);
                                fileHandle.write(":", 1);
                                fileHandle.write(argRec->regMin.c_str(), 2);
                                fileHandle.write(";", 1);
                                fileHandle.write(argRec->packersInitials.c_str(), 3);
                                fileHandle.write(";", 1);
                                fileHandle.write("S", 1);
                                fileHandle.write(";", 1);
                                fileHandle.write(argRec->orderNo.c_str(), 5);
                                fileHandle.write(argRec->lineNo.c_str(), 2);
                                fileHandle.write(argRec->checkDigit.c_str(), 1);
                                fileHandle.write(";", 1);
                                intSizeClass = i + 1;
                                if(i < 10)
                                {
                                        itoa(intSizeClass, strSizeClass, 10);
                                        fileHandle.write(strSizeClass, 1);
                                }
                                else
                                {
                                        itoa(intSizeClass, strSizeClass, 10);
                                        fileHandle.write(strSizeClass, 2);
                                }
                                fileHandle.write(";", 1);
                                if(argRec->secondarySizes[i].Length() == 1)
                                        fileHandle.write(argRec->secondarySizes[i].c_str(), 1);
                                else if(argRec->secondarySizes[i].Length() == 2)
                                        fileHandle.write(argRec->secondarySizes[i].c_str(), 2);
                                else if(argRec->secondarySizes[i].Length() == 3)
                                        fileHandle.write(argRec->secondarySizes[i].c_str(), 3);
                                fileHandle.write(";", 1);
                                if(!PAddedToWhAddr)
                                {
                                        argRec->warehouseAddress = "P" + argRec->warehouseAddress;
                                        PAddedToWhAddr = true;
                                }
                                for(int j = 0;j < 7;j++)
                                {
                                        if(argRec->warehouseAddress.Length() == j + 1)
                                        {
                                                fileHandle.write(argRec->warehouseAddress.c_str(), j + 1);
                                        }
                                }
                                fileHandle.write(";", 1);
                                fileHandle.write(";", 1);
                                fileHandle.write("\n", 1);
                                argRec->secondarySizes[i] = "000";
                                argRec->recsWrittenToHFile = argRec->recsWrittenToHFile + 1;
                        }
                }
        }
        else
        {
                fileHandle.write(argRec->regDay.c_str(), 2);
                fileHandle.write(".", 1);
                fileHandle.write(argRec->regMonth.c_str(), 2);
                fileHandle.write(".", 1);
                fileHandle.write(argRec->regYear2.c_str(), 2);
                fileHandle.write(";", 1);
                fileHandle.write(argRec->regHour.c_str(), 2);
                fileHandle.write(":", 1);
                fileHandle.write(argRec->regMin.c_str(), 2);
                fileHandle.write(";", 1);
                fileHandle.write(argRec->packersInitials.c_str(), 3);
                fileHandle.write(";", 1);
                fileHandle.write("O", 1);
                fileHandle.write(";", 1);
                fileHandle.write(argRec->orderNo.c_str(), 5);
                fileHandle.write(argRec->lineNo.c_str(), 2);
                fileHandle.write(argRec->checkDigit.c_str(), 1);
                fileHandle.write(";", 1);
                fileHandle.write(";", 1);
                fileHandle.write(";", 1);
                argRec->warehouseAddress = "P" + argRec->warehouseAddress;
                for(int i = 0;i < 7;i++)
                {
                        if(argRec->warehouseAddress.Length() == i + 1)
                        {
                                fileHandle.write(argRec->warehouseAddress.c_str(), i + 1);
                        }
                }
                fileHandle.write(";", 1);
                fileHandle.write(";", 1);
                fileHandle.write("\n", 1);
                argRec->recsWrittenToHFile = argRec->recsWrittenToHFile + 1;
        }
        argRec->warehouseAddress.Delete(1, 1); //deletes the P-prefix from the warehouseaddress
        fileHandle.close();
}

void DisplayRecsWrittenToFile(const int * argRecs, const int * argHRecs)
{
        gotoxy(1, 25);
        textcolor(WHITE);
        cprintf("PFileC: %i r", *argRecs);
        cprintf(" HFileC: %i r", *argHRecs);
        textcolor(BLACK);
}

String GenerateFilename(bool CreateNew)
{
        static String filename;
        if(CreateNew)
        {
                time_t timeStructure;
                tm * thisday;
                time(&timeStructure);
                thisday = localtime(&timeStructure);
                if(thisday->tm_mday < 10)
                        filename = filename + "0" + (thisday->tm_mday);  //added the null string filename in
                                                                         //front of the zero catenation to make
                                                                         //the catenation work
                else
                        filename = thisday->tm_mday;
                if(thisday->tm_mon < 10)
                        filename = filename + "0" + (thisday->tm_mon + 1);
                else
                        filename = filename + (thisday->tm_mon + 1);
                if(thisday->tm_hour < 10)
                        filename = filename + "0" + thisday->tm_hour;
                else
                        filename = filename + thisday->tm_hour;
                if(thisday->tm_min < 10)
                        filename = filename + "0" + thisday->tm_min;
                else
                        filename = filename + thisday->tm_min;
                filename = filename + ".txt";
        }
        return filename;
}
