void clearScreen();
void printString(char* string);
void readString(char* buffer);
void readSector(char* buffer, int sector);
int div(int a, int b);
int mod(int a, int b);

main() {
  char buffer[512];
  char line[80];

  clearScreen();

  printString("Enter a line: \0");
  readString(line);
  printString(line);

  readSector(buffer, 30);
  printString(buffer);

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

void readString(char* buffer) {
  int hexValueZero = 0x0;
  int hexValueEnter = 0xD;
  int hexValueBackspace = 0x8;
  int hexValueBackslashN = 0xA;
  int hexValueBackslashR = 0xD;
  int bufferCursor = 2;
  int currentHexValue;

  buffer[0] = hexValueBackslashR;
  buffer[1] = hexValueBackslashN;

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
