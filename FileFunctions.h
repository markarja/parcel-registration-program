// FileFunctions header
//
// Version: 1.2
// Written by: Markus Karjalainen/SGS
// Last changed: 2.1.2003
//

#include "ParcelRecord.h"
#ifndef FileFunctionsH
#define FileFunctionsH
void DisplayRecsWrittenToFile(const int * argRecs, const int * argHRecs);
void WriteDeviationsToFile(const char argFilename[], ParcelRecord * argRec);
bool ThereAreDeviations(ParcelRecord * argRec);
String GenerateFilename(bool CreateNew);
#endif
 