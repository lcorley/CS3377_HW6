/*Luke Corley lcc160130@utdallas.edu
 * CS 3377 Homework 6 4/23/2018*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdint.h>
#include <stdio.h>
#include <iomanip>
#include "cdk.h"


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader
{
public:
	
	uint32_t magicNumber; /*Should be feedface*/
	uint32_t versionNumber;
	uint64_t numRecords;
	
};

/*
* Records in the file have a fixed length buffer
* that will hold a C-Style string. This is the
* size of the fixed length buffer.
*/
const int maxRecordStringLength = 25;

class BinaryFileRecord
{
public:
	uint8_t strLength;
	char stringBuffer[maxRecordStringLength];
};

int main()
{

  
  //CDK window initialization
  
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix


  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};
  
  
  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  //read the binary file header record
	BinaryFileHeader *myHeader = new BinaryFileHeader();
	
	ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
	
	if (binInfile.is_open())
	{
		binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
	}
	else 
	{
		cout << "error reading binary file";
		return 0;
	}
	
	/* Display the Matrix */
	drawCDKMatrix(myMatrix, true);
	/*
   * rea and Display header information
   */
	stringstream numToString;
	string inputString;
	
	numToString << hex << myHeader->magicNumber;
	inputString = "Magic: " + numToString.str();
	numToString.str("");
	setCDKMatrixCell(myMatrix, 1, 1, inputString.c_str());
	
	numToString << myHeader->versionNumber;
	inputString = "Version: " + numToString.str();
	numToString.str("");
	setCDKMatrixCell(myMatrix, 1, 2, inputString.c_str());
	
	numToString << myHeader->numRecords;
	inputString = "NumRecords: " + numToString.str();
	numToString.str("");
	setCDKMatrixCell(myMatrix, 1, 3, inputString.c_str());
	
	//read the binary file records
	BinaryFileRecord *myRecord = new BinaryFileRecord();
	//read up to 4 records
	for (int row = 2; row < 6; row++)
	{
		if(binInfile.read((char *) myRecord, sizeof(BinaryFileRecord))); //if there are more records to read
		{
			//read string length and display
			stringstream ss;
			ss << strlen(myRecord->stringBuffer);
			inputString = "strlen: " + ss.str();
			ss.str(""); //clear ss
			//fill matrix cell
			setCDKMatrixCell(myMatrix, row, 1, inputString.c_str());
			
			//read string buffer and display
			string dataString = myRecord->stringBuffer;
			setCDKMatrixCell(myMatrix, row, 2, dataString.c_str());
		}
		
	}

	binInfile.close();
	
	drawCDKMatrix(myMatrix, true);    /* required  */
  
  /* So we can see results, pause until a key is pressed. */
	unsigned char x;
	cin >> x;

  // Cleanup screen
  endCDK();
}
