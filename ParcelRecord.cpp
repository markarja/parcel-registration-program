// ParcelRecord class implementation
//
// Version: 1.2
// Written by: Markus Karjalainen/SGS
// Last changed: 3.2.2003
//
#pragma hdrstop
#include <time.h>
#include <fstream.h>
#include "ParcelRecord.h"

#pragma package(smart_init)

void ParcelRecord::SetTimeAndDate(void)
{
        time_t timeStructure;
        tm * thisday;
        time(&timeStructure);
        thisday = localtime(&timeStructure);
        this->regDay = thisday->tm_mday;
        if((thisday->tm_year - 100) < 10)
        {
                this->regYear = "200";
                this->regYear = this->regYear + (thisday->tm_year - 100);
        }
        else
        {
                this->regYear = "20";
                this->regYear = this->regYear + (thisday->tm_year - 100);
        }
        this->regMonth = (thisday->tm_mon + 1);
        this->regWeek = ((thisday->tm_yday/7) + 1);
        if(thisday->tm_hour < 10)
        {
                this->regTime = "0";
                this->regTime = this->regTime + thisday->tm_hour;
        }
        else
                this->regTime = thisday->tm_hour;
        if(thisday->tm_min < 10)
                this->regTime = this->regTime + "0" + thisday->tm_min;
        else
                this->regTime = this->regTime + "" + thisday->tm_min;
        if(thisday->tm_sec < 10)
                this->regTime = this->regTime + "0" + thisday->tm_sec;
        else
                this->regTime = this->regTime + "" + thisday->tm_sec;
        /* Setting the year, hours and minutes for the hanging file */
        if((thisday->tm_year - 100) < 10)
        {
                this->regYear2 = "0";
                this->regYear2 = this->regYear2 + (thisday->tm_year - 100);
        }
        else
                this->regYear2 = (thisday->tm_year - 100);
        if(thisday->tm_hour < 10)
        {
                this->regHour = "0";
                this->regHour = this->regHour + thisday->tm_hour;
        }
        else
                this->regHour = thisday->tm_hour;
        if(thisday->tm_min < 10)
                this->regMin = this->regMin + "0" + thisday->tm_min;
        else
                this->regMin = this->regMin + "" + thisday->tm_min;

}
ParcelRecord::ParcelRecord(String argPackersInitials, String argPackSign)
{
        this->packersInitials = argPackersInitials;
        this->pickSign = argPackSign;
        for(int i = 0;i < 11; i++)
        {
                this->premiumSizes[i] = "000";
        }
        for(int i = 0;i < 11; i++)
        {
                this->secondarySizes[i] = "000";
        }
        this->weight = "";
        this->m3 = "";
        this->lWeight = "";
        this->lm3 =  "";
        this->recsWrittenToFile = 0;
        this->recsWrittenToHFile = 0;
}
ParcelRecord::~ParcelRecord()
{
}
void ParcelRecord::WriteToFile(const char argFilename[])
{
        fstream fileHandle(argFilename);
        fileHandle.seekg(0, ios_base::end);
        fileHandle.write(this->orderNo.c_str(), 5);
        fileHandle.write(this->lineNo.c_str(), 2);
        if(this->parcelNo.Length() < 4)
        {
                if(this->parcelNo.Length() == 0)
                        this->parcelNo = "0000";
                else if(this->parcelNo.Length() == 1)
                        this->parcelNo = "000" + this->parcelNo;
                else if(this->parcelNo.Length() == 2)
                        this->parcelNo = "00" + this->parcelNo;
                else if(this->parcelNo.Length() == 3)
                        this->parcelNo = "0" + this->parcelNo;
        }
        fileHandle.write(this->parcelNo.c_str(), 4);
        if(this->regWeek.Length() < 2)
        {
                if(this->regWeek.Length() == 0)
                        this->regWeek = "00";
                else if(this->regWeek.Length() == 1)
                        this->regWeek = "0" + this->regWeek;
        }
        fileHandle.write(this->regWeek.c_str(), 2);
        fileHandle.write(this->regYear.c_str(), 4);
        if(this->regMonth.Length() < 2)
        {
                if(this->regMonth.Length() == 0)
                        this->regMonth = "00";
                else if(this->regMonth.Length() == 1)
                        this->regMonth = "0" + this->regMonth;
        }
        fileHandle.write(this->regMonth.c_str(), 2);
        if(this->regDay.Length() < 2)
        {
                if(this->regDay.Length() == 0)
                        this->regDay = "00";
                else if(this->regDay.Length() == 1)
                        this->regDay = "0" + this->regDay;
        }
        fileHandle.write(this->regDay.c_str(), 2);
        fileHandle.write(this->regTime.c_str(), 6);
        if(this->weight.Length() == 0)
        {
                this->weight = "00000" + this->weight;
                fileHandle.write(this->weight.c_str(), 5);
                this->weight.Delete(1, 5);
        }
        else if(this->weight.Length() == 1)
        {
                this->weight = "0000" + this->weight;
                fileHandle.write(this->weight.c_str(), 5);
                this->weight.Delete(1, 4);
        }
        else if(this->weight.Length() == 2)
        {
                this->weight = "000" + this->weight;
                fileHandle.write(this->weight.c_str(), 5);
                this->weight.Delete(1, 3);
        }
        else if(this->weight.Length() == 3)
        {
                this->weight = "00" + this->weight;
                fileHandle.write(this->weight.c_str(), 5);
                this->weight.Delete(1, 2);
        }
        else if(this->weight.Length() == 4)
        {
                this->weight = "0" + this->weight;
                fileHandle.write(this->weight.c_str(), 5);
                this->weight.Delete(1, 1);
        }
        else
                fileHandle.write(this->weight.c_str(), 5);
        if(this->m3.Length() == 0)
        {
                this->m3 = "00000" + this->m3;
                fileHandle.write(this->m3.c_str(), 5);
                this->m3.Delete(1, 5);
        }
        else if(this->m3.Length() == 1)
        {
                this->m3 = "0000" + this->m3;
                fileHandle.write(this->m3.c_str(), 5);
                this->m3.Delete(1, 4);
        }
        else if(this->m3.Length() == 2)
        {
                this->m3 = "000" + this->m3;
                fileHandle.write(this->m3.c_str(), 5);
                this->m3.Delete(1, 3);
        }
        else if(this->m3.Length() == 3)
        {
                this->m3 = "00" + this->m3;
                fileHandle.write(this->m3.c_str(), 5);
                this->m3.Delete(1, 2);
        }
        else if(this->m3.Length() == 4)
        {
                this->m3 = "0" + this->m3;
                fileHandle.write(this->m3.c_str(), 5);
                this->m3.Delete(1, 1);
        }
        else
                fileHandle.write(this->m3.c_str(), 5);
        for(int i = 0;i < 11; i++)
        {
                if(this->premiumSizes[i].Length() == 1)
                {
                        this->premiumSizes[i] = "00" + this->premiumSizes[i];
                }
                else if (this->premiumSizes[i].Length() == 2)
                {
                        this->premiumSizes[i] = "0" + this->premiumSizes[i];
                }
                fileHandle.write(this->premiumSizes[i].c_str(), 3);
        }
        for(int i = 0;i < 11; i++)
        {
                if(this->secondarySizes[i].Length() == 1)
                {
                        this->secondarySizes[i] = "00" + this->secondarySizes[i];
                }
                else if (this->secondarySizes[i].Length() == 2)
                {
                        this->secondarySizes[i] = "0" + this->secondarySizes[i];
                }
                fileHandle.write(this->secondarySizes[i].c_str(), 3);
        }
        fileHandle.write(this->pickSign.c_str(), 1);
        fileHandle.write(this->packersInitials.c_str(), 3);
        fileHandle.write("\n", 1);
        fileHandle.close();
        this->recsWrittenToFile = this->recsWrittenToFile + 1;
}

void ParcelRecord::Reset(void)
{
        for(int i = 0;i < 11; i++)
        {
                this->premiumSizes[i] = "000";
        }
        for(int i = 0;i < 11; i++)
        {
                this->secondarySizes[i] = "000";
        }
        if(this->weight != "")
        {
                this->lWeight = this->weight;
                this->weight = "";
        }
        if(this->m3 != "")
        {
                this->lm3 = this->m3;
                this->m3 = "";
        }
}
