// ParcelRecord class definition and prototypes
//
// Version: 1.2
// Written by: Markus Karjalainen/SGS
// Last changed: 31.1.2003
//

#include "system.hpp"                                                   //inluded to be able to use the String-object
#ifndef ParcelRecordH
#define ParcelRecordH

class ParcelRecord
{
public:
        String orderNo;                                                 //the ordernumber
        String lineNo;                                                  //the linenumber
        String checkDigit;                                              //the checkdigit of the barcode
        String parcelNo;                                                //the parcelnumber
        String regWeek;                                                 //registration week (ww)
        String regYear;                                                 //year in yyyy-format
        String regYear2;                                                //year in yy-format
        String regMonth;                                                //registration month (mm)
        String regDay;                                                  //registration day(dd)
        String regTime;                                                 //registration time
        String regHour;                                                 //hours to be used in the hanging file
        String regMin;                                                  //minutes to be used in the parcel file
        String weight;                                                  //weight of parcel (kg)
        String lWeight;                                                 //last weight
        String m3;                                                      //capacity of parcel (m3)
        String lm3;                                                     //last capacity
        String premiumSizes[11];                                        //deviations in premium size classes
        String secondarySizes[11];                                      //deviations in secondary size classes
        String pickSign;                                                //packers sign (0 for SGS)
        String packersInitials;                                         //packers initials (999 for SGS)
        String warehouseAddress;                                        //the physical warehouse address
        ParcelRecord(String argPackersInitials, String argPackSign);    //the constructor of the class
        ~ParcelRecord();                                                //the destructor
        int recsWrittenToFile;                                          //number of records written to parcel file
        int recsWrittenToHFile;                                         //number of records written to hanging file
        void SetTimeAndDate(void);                                      //sets the registration time and date
        void WriteToFile(const char argFilename[]);                     //writes the record to the file passed as an argument
        void Reset(void);                                               //resets the size classes, weight and m3
};
#endif
