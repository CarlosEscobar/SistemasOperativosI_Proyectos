void clearScreen();

void printString(char* string);
void readString(char* buffer);
void readSector(char* buffer, int sector);
int div(int a, int b);
int mod(int a, int b);

void readFile(char* fileName,char* buffer);
void executeProgram(char* name, int segment);
void terminate();

void writeSector(char* buffer, int sector);
void deleteFile(char* fileName);
void writeFile(char* fileName, char* buffer, int numberOfSectors);
void printDirectory();

main() {
  char shellInput[80];
  char inputFileName1[6];
  char inputFileName2[6];
  char fileInputTypeBuffer[13312];
  char aBuffer[512];
  char createFileInput[80];
  int i;

  clearScreen();

  for(;;){
    printString("CaiOs Shell> \0");
    readString(shellInput);

    if(shellInput[0] == 'c'
    && shellInput[1] == 'l'
    && shellInput[2] == 'e'
    && shellInput[3] == 'a'
    && shellInput[4] == 'r')
    {
     clearScreen();
    }
    else if(shellInput[0] == 't'
    && shellInput[1] == 'y'
    && shellInput[2] == 'p'
    && shellInput[3] == 'e')
    {
      for(i=0;i<6;i++){
       inputFileName1[i] = shellInput[i+5];
      }
      readFile(inputFileName1,fileInputTypeBuffer);
      printString(" -> \0");
      printString(fileInputTypeBuffer);
    }
    else if(shellInput[0] == 'e'
    && shellInput[1] == 'x'
    && shellInput[2] == 'e'
    && shellInput[3] == 'c'
    && shellInput[4] == 'u'
    && shellInput[5] == 't'
    && shellInput[6] == 'e')
    {
      for(i=0;i<6;i++){
        inputFileName1[i] = shellInput[i+8];
      }
      clearScreen();
      executeProgram(inputFileName1,0x2000);
    }
    else if(shellInput[0] == 'd'
    && shellInput[1] == 'e'
    && shellInput[2] == 'l'
    && shellInput[3] == 'e'
    && shellInput[4] == 't'
    && shellInput[5] == 'e')
    {
      for(i=0;i<6;i++){
        inputFileName1[i] = shellInput[i+7];
      }
      printString("\r\n\0");
      deleteFile(inputFileName1);
    }
    else if(shellInput[0] == 'c'
    && shellInput[1] == 'o'
    && shellInput[2] == 'p'
    && shellInput[3] == 'y')
    {
      for(i=0;i<6;i++){
        inputFileName1[i] = shellInput[i+5];
      }
      for(i=0;i<6;i++){
        inputFileName2[i] = shellInput[i+12];
      }
      printString("\r\n\0");
      readFile(inputFileName1,aBuffer);
      writeFile(inputFileName2,aBuffer,1);
    }
    else if(shellInput[0] == 'd'
    && shellInput[1] == 'i'
    && shellInput[2] == 'r')
    {
      printDirectory();
    }
    else if(shellInput[0] == 'c'
    && shellInput[1] == 'r'
    && shellInput[2] == 'e'
    && shellInput[3] == 'a'
    && shellInput[4] == 't'
    && shellInput[5] == 'e')
    {
      for(i=0;i<6;i++){
        inputFileName1[i] = shellInput[i+7];
      }
      printString("\r\n\0");
      readString(createFileInput);
      writeFile(inputFileName1,createFileInput,1);
      printString("\r\n\0");
    }
    else
    {
     printString("\r\nCaiOs Shell> Unknown command: \0");
     printString(shellInput);
    }
  }
}

void clearScreen()
{
  int i;
  for(i=0; i<2000; i++) {
    putInMemory(0xB000, 0x8000 + (2*i), ' ');
    putInMemory(0xB000, 0x8001 + (2*i), 0x7);
  }
}

void printString(char* string){
  int i = 0;
  while(string[i] != '\0'){
    int currentChar = string[i];
    interrupt(0x10, 0xe*256+currentChar, 0, 0, 0);
    i++;
  }
}

void readString(char* buffer) {
  int hexValueZero = 0x0;
  int hexValueEnter = 0xD;
  int hexValueBackspace = 0x8;
  int hexValueBackslashN = 0xA;
  int hexValueBackslashR = 0xD;
  int bufferCursor = 0;
  int currentHexValue;

  for(;;){
    currentHexValue = interrupt(0x16,0,0,0,0);
    if(currentHexValue == hexValueEnter){
      buffer[bufferCursor++] = hexValueBackslashR;
      buffer[bufferCursor++] = hexValueBackslashN;
      buffer[bufferCursor] = hexValueZero;
      return;
    } else if(currentHexValue == hexValueBackspace && bufferCursor > 0) {
      buffer[bufferCursor--] = hexValueZero;
      interrupt(0x10,0xe*256+hexValueBackspace,0,0,0);
      bufferCursor++;
      interrupt(0x10,0xe*256+hexValueZero,0,0,0);
      bufferCursor--;
      interrupt(0x10,0xe*256+hexValueBackspace,0,0,0);
    } else {
      buffer[bufferCursor++] = currentHexValue;
      interrupt(0x10, 0xe*256+currentHexValue, 0, 0, 0);
    }
  }
}

void readSector(char* buffer, int sector){
  int relativeSector = mod(sector,18) + 1;
  int head = mod(div(sector,18),2);
  int track = div(sector/36);
  interrupt(0x13,2*256+1,buffer,track*256+relativeSector,head*256+0);
}

int div(int a, int b){
  int res=0;
  while(a >= b){
    a = a-b;
    res++;
  }
  return res;
}

int mod(int a, int b){
  while(a >= b){
      a = a-b;
  }
  return a;
}

void readFile(char* fileName,char* buffer){
  int bytesInSector=512;
  int numberOfFiles=16;
  int bytesInFile=32;
  int bytesForName=6;
  int bytesForContent=26;

  int i,j;
  int fileIndex;
  int foundFile=0;
  int fileSectors[27];
  int fileCursor=0;

  readSector(buffer,2);

  for(i=0; i<numberOfFiles; i++){
    if (buffer[bytesInFile*i] != 0){
      for(j=0;j<bytesForName; j++){
        if(fileName[j] == 0){
          break;
        }else if(buffer[j+bytesInFile*i] == fileName[j]) {
          foundFile=1;
        } else {
          foundFile=0;
          break;
        }
      }
      if(foundFile==1) { fileIndex = i;}
    }
  }

  if(foundFile!=1) {
    printString("File Not Found\0");
		return;
  }

  fileIndex = (fileIndex*bytesInFile)+bytesForName;
  for (i=0;i<bytesForContent;i++){
      fileSectors[i] = buffer[fileIndex+i];
  }
  fileSectors[i] = 0;

  i=0;
  while(fileSectors[i] != 0){
    readSector(buffer+fileCursor,fileSectors[i]);
    fileCursor += bytesInSector;
    i++;
  }
}

void executeProgram(char* name, int segment){
	int i;
	char buffer[13312];

	readFile(name, buffer);
	for (i=0; i<13312;i++){
		putInMemory(segment,i,buffer[i]);
	}
	launchProgram(segment);
}

void terminate(){
  clearScreen();
  for(;;){}
}

void writeSector(char* buffer, int sector) {
  int relativeSector = mod(sector,18) + 1;
  int head = mod(div(sector,18),2);
  int track = div(sector/36);
  interrupt(0x13,3*256+1,buffer,track*256+relativeSector,head*256+0);
}

void deleteFile(char* fileName) {
  int bytesInSector=512;
  int numberOfFiles=16;
  int bytesInFile=32;
  int bytesForName=6;
  int bytesForContent=26;

  int i,j;
  int fileIndex;
  int foundFile=0;
  int fileSectors[27];
  int fileCursor=0;

  char mapBuffer[512];
	char directoryBuffer[512];

  readSector(mapBuffer,1);
	readSector(directoryBuffer,2);

  for(i=0; i<numberOfFiles; i++){
    if (directoryBuffer[bytesInFile*i] != 0){
      for(j=0;j<bytesForName; j++){
        if(fileName[j] == 0){
          break;
        }else if(directoryBuffer[j+bytesInFile*i] == fileName[j]) {
          foundFile=1;
        } else {
          foundFile=0;
          break;
        }
      }
      if(foundFile==1) { fileIndex = i;}
    }
  }

  if(foundFile!=1) {
    printString("File Not Found\0");
		return;
  }

  for(i=0; i<bytesForName; i++){
    directoryBuffer[fileIndex*bytesInFile+i] = 0x00;
  }

  fileIndex = (fileIndex*bytesInFile)+bytesForName;

  for (i=0;i<bytesForContent;i++) {
    fileSectors[i] = directoryBuffer[fileIndex+i];
    directoryBuffer[fileIndex+i] = 0x00;
  }
  fileSectors[26] = 0x0;

  for (i=0;i<bytesForContent;i++) {
    if(fileSectors[i] == 0){
      break;
    }
    mapBuffer[fileSectors[i]] = 0x00;
  }

  writeSector(mapBuffer,1);
	writeSector(directoryBuffer,2);
}

void writeFile(char* fileName, char* buffer, int numberOfSectors)
{
  int bytesInSector=512;
  int numberOfFiles=16;
  int bytesInFile=32;
  int bytesForName=6;

  char mapBuffer[512];
	char directoryBuffer[512];
  char anotherBuffer[512];

  int i,j;
  int directoryIndex=0;
  int directoryAvailable = 0;
  int fileNameLength=0;
  int currentSector;

  readSector(mapBuffer,1);
	readSector(directoryBuffer,2);

  for(directoryIndex=0; directoryIndex<numberOfFiles; directoryIndex++) {
    if(directoryBuffer[bytesInFile*directoryIndex] == 0x00){
      directoryAvailable = 1;
      break;
    }
  }

  if (directoryAvailable == 0){
		printString("No free directory. \0");
		return;
	}

  while(fileName[fileNameLength] != 0x0
    &&  fileName[fileNameLength] != '\0' ) {
      fileNameLength++;
    }

  for(i=0; i<fileNameLength; i++){
    directoryBuffer[bytesInFile*directoryIndex+i] = fileName[i];
  }

  if(fileNameLength < bytesForName) {
    for(i=0;i<(bytesForName-fileNameLength); i++){
      directoryBuffer[bytesInFile*directoryIndex+fileNameLength+i] = 0x0;
    }
  }

  for(i=0; i<numberOfSectors; i++){
    currentSector = 0;
    while(mapBuffer[currentSector] != 0x0){
      currentSector++;
    }

    if(currentSector == 26){
  		printString("No available sector. \0");
  		return;
  	}

    mapBuffer[currentSector] = 0xFF;
    directoryBuffer[bytesInFile*directoryIndex+bytesForName+i] = currentSector;

    for(j=0;j<bytesInSector;j++){
      anotherBuffer[j] = buffer[j*(i+1)];
    }
    writeSector(anotherBuffer,currentSector);
  }

  writeSector(mapBuffer,1);
	writeSector(directoryBuffer,2);
}

void printDirectory()
{
  int numberOfFiles=16;
  int bytesInFile=32;
  int bytesForName=6;

  char resultBuffer[512];
  char directoryBuffer[512];

  int i,j;
  int resultCursor = 0;

  readSector(directoryBuffer,2);

  resultBuffer[resultCursor++] = ' ';
  resultBuffer[resultCursor++] = 'F';
  resultBuffer[resultCursor++] = 'i';
  resultBuffer[resultCursor++] = 'l';
  resultBuffer[resultCursor++] = 'e';
  resultBuffer[resultCursor++] = 's';
  resultBuffer[resultCursor++] = ':';
  resultBuffer[resultCursor++] = ' ';

  for(i=0; i<numberOfFiles; i++)
  {
      if(directoryBuffer[bytesInFile*i] != 0x0){
        for(j=0; j<bytesForName; j++){
          resultBuffer[resultCursor++] = directoryBuffer[bytesInFile*i+j];
        }
        resultBuffer[resultCursor++] = ',';
      }
  }

  resultBuffer[--resultCursor] = '\r';
  resultBuffer[++resultCursor] = '\n';
  resultBuffer[++resultCursor] = '\0';
  printString(resultBuffer);
}
