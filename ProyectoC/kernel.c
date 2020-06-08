void clearScreen();

void printString(char* string);
void readSector(char* buffer, int sector);
int div(int a, int b);
int mod(int a, int b);

void readFile(char* fileName,char* buffer);
void executeProgram(char* name, int segment);
void terminate();

main() {
  clearScreen();
  executeProgram("tprog1", 0x2000);
  for(;;){}
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
