/* ScannerFunctions implementation

   Version              Date            New features
   1.3                  23.1.2004       Added the char CalculateCheckDigit(char cBarcode[], int iLenghtOfBarcode, int iModuloFactor)
                                        function to enable the possibility to type in only the order and line number.

                                        Fixed the input of the barcode, so that the user is able to do corrections to the input with
                                        the backspace key.

   Written by: Markus Karjalainen/DHL Solutions
   Last changed: 1.3 23.1.2004

*/

#pragma hdrstop
#include <conio.h>
#include "ScannerFunctions.h"
#include "ParcelRecord.h"

#pragma package(smart_init)
void ReadAndDisplayBarCode(ParcelRecord * argRec)
{
  int x = 10;
  int y = 12;
  int i = 0;
  char cBarcode[9] = {0,0,0,0,0,0,0,0,0};
  char cInput = 0;
  gotoxy(x, y);
  x = x + 19;
  cprintf("Kortin viivakoodi: ");
  while (i < 8) {
    gotoxy(x, y);
    cInput = getch();
    if((int)cInput == BACKSPACE && i > 0) {
      cBarcode[i - 1] = 0;
      i--;
      gotoxy(x - 1, y);
      cprintf(" ");
      x--;
    } else if((int)cInput == ENTER) {
      if(i == 7) {
        cBarcode[i] = CalculateCheckDigit(cBarcode, 7, 3);
        cprintf("%c", cBarcode[i]);
        break;
      }
    } else if ((int)cInput != BACKSPACE) {
      cBarcode[i] = cInput;
      cprintf("%c", cBarcode[i]);
      x++;
      i++;
    }
  }
  i = 0;
  argRec->orderNo = "";
  argRec->lineNo = "";
  argRec->checkDigit = "";
  while(i < 8) {
    if(i < 5) {
      argRec->orderNo = argRec->orderNo + cBarcode[i];
    } else if(i >= 5 && i < 7) {
      argRec->lineNo = argRec->lineNo + cBarcode[i];
    } else {
      argRec->checkDigit = cBarcode[i];
    }
    i++;
  }
}

char CalculateCheckDigit(char cBarcode[], int iLenghtOfBarcode, int iModuloFactor) {
  int iCurrentDigit = 0;
  int iSumEven = 0;
  int iSumOdd = 0;
  int iSumTotal = 0;
  int iSumTotalSubDigit = 0;
  int iNextMultipleOfTen = 0;
  int iCheckDigit = 0;
  int iDigitToSum;
  int iReturnDigit = 0;

  String sSumTotal = NULL;
  String sSumTotalSubString = NULL;
  String sNextMultipleOfTen = NULL;
  String sReturnDigit = NULL;
  String sDigitToSum = NULL;

  char * cReturnDigit = NULL;

  while(iCurrentDigit < iLenghtOfBarcode) {
    sDigitToSum = cBarcode[iCurrentDigit];
    iDigitToSum = sDigitToSum.ToInt();
    if(iCurrentDigit % 2 == 0) {
      iSumEven = iSumEven + iDigitToSum;
    } else {
      iSumOdd = iSumOdd + iDigitToSum;
    }
    iCurrentDigit++;
  }

  iSumTotal = iSumOdd + (iSumEven * iModuloFactor);
  sSumTotal = iSumTotal;

  if(sSumTotal.Length() > 2) {
    sSumTotalSubString = sSumTotal.SubString(2, 1);
    iSumTotalSubDigit = sSumTotalSubString.ToInt() + 1;
    sNextMultipleOfTen = "1" + (String)iSumTotalSubDigit + "0";
  } else {
    sSumTotalSubString = sSumTotal.SubString(1, 1);
    iSumTotalSubDigit = sSumTotalSubString.ToInt() + 1;
    sNextMultipleOfTen = "" + (String)iSumTotalSubDigit + "0";
  }
  iReturnDigit = sNextMultipleOfTen.ToInt() - iSumTotal;

  if(iReturnDigit == 10) {
    sReturnDigit = (String)iReturnDigit;
    sReturnDigit = sReturnDigit.SubString(2, 1);
    cReturnDigit = (char *)sReturnDigit.c_str();
  } else {
    sReturnDigit = (String)iReturnDigit;
    cReturnDigit = (char *)sReturnDigit.c_str();
  }

  return cReturnDigit[0];
}
