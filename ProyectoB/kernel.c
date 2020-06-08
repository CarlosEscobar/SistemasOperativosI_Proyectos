void clearScreen();
void printString(char* string);
void readSector(char* buffer, int sector);
int div(int a, int b);
int mod(int a, int b);

main() {
  char buffer[512];

  clearScreen();

  printString("This is printString \0");

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
