// ScannerFunctions header
//
// Version: 1.2
// Written by: Markus Karjalainen/SGS
// Last changed: 2.1.2002
//

#include "ParcelRecord.h"
#include "MenuFunctions.h"
#ifndef ScannerFunctionsH
#define ScannerFunctionsH

void ReadAndDisplayBarCode(ParcelRecord * argRec);
char CalculateCheckDigit(char cBarcode[], int iLenghtOfBarcode, int iModuloFactor);
#endif
 