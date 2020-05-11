int main()
{

  int i,j,k;
  char linea1[21];
  char linea2[48];
  char linea3[25];
  char linea4[27];
  char linea6[15];
  char linea7[16];
  char linea8[16];

  linea1[0] = 'S';
  linea1[1] = 'I';
  linea1[2] = 'S';
  linea1[3] = 'T';
  linea1[4] = 'E';
  linea1[5] = 'M';
  linea1[6] = 'A';
  linea1[7] = 'S';
  linea1[8] = ' ';
  linea1[9] = 'O';
  linea1[10] = 'P';
  linea1[11] = 'E';
  linea1[12] = 'R';
  linea1[13] = 'A';
  linea1[14] = 'T';
  linea1[15] = 'I';
  linea1[16] = 'V';
  linea1[17] = 'O';
  linea1[18] = 'S';
  linea1[19] = ' ';
  linea1[20] = 'I';

  linea2[0] = 'U';
  linea2[1] = 'N';
  linea2[2] = 'I';
  linea2[3] = 'V';
  linea2[4] = 'E';
  linea2[5] = 'R';
  linea2[6] = 'S';
  linea2[7] = 'I';
  linea2[8] = 'D';
  linea2[9] = 'A';
  linea2[10] = 'D';
  linea2[11] = ' ';
  linea2[12] = 'T';
  linea2[13] = 'E';
  linea2[14] = 'C';
  linea2[15] = 'N';
  linea2[16] = 'O';
  linea2[17] = 'L';
  linea2[18] = 'O';
  linea2[19] = 'G';
  linea2[20] = 'I';
  linea2[21] = 'C';
  linea2[22] = 'A';
  linea2[23] = ' ';
  linea2[24] = 'C';
  linea2[25] = 'E';
  linea2[26] = 'N';
  linea2[27] = 'T';
  linea2[28] = 'R';
  linea2[29] = 'O';
  linea2[30] = 'A';
  linea2[31] = 'M';
  linea2[32] = 'E';
  linea2[33] = 'R';
  linea2[34] = 'I';
  linea2[35] = 'C';
  linea2[36] = 'A';
  linea2[37] = 'N';
  linea2[38] = 'A';
  linea2[39] = ' ';
  linea2[40] = '(';
  linea2[41] = 'U';
  linea2[42] = 'N';
  linea2[43] = 'I';
  linea2[44] = 'T';
  linea2[45] = 'E';
  linea2[46] = 'C';
  linea2[47] = ')';

  linea3[0] = '2';
  linea3[1] = '1';
  linea3[2] = '2';
  linea3[3] = '5';
  linea3[4] = '1';
  linea3[5] = '0';
  linea3[6] = '6';
  linea3[7] = '7';
  linea3[8] = ' ';
  linea3[9] = '-';
  linea3[10] = ' ';
  linea3[11] = 'C';
  linea3[12] = 'A';
  linea3[13] = 'R';
  linea3[14] = 'L';
  linea3[15] = 'O';
  linea3[16] = 'S';
  linea3[17] = ' ';
  linea3[18] = 'E';
  linea3[19] = 'S';
  linea3[20] = 'C';
  linea3[21] = 'O';
  linea3[22] = 'B';
  linea3[23] = 'A';
  linea3[24] = 'R';

  linea4[0] = 'M';
  linea4[1] = 'I';
  linea4[2] = ' ';
  linea4[3] = 'P';
  linea4[4] = 'R';
  linea4[5] = 'I';
  linea4[6] = 'M';
  linea4[7] = 'E';
  linea4[8] = 'R';
  linea4[9] = ' ';
  linea4[10] = 'S';
  linea4[11] = 'I';
  linea4[12] = 'S';
  linea4[13] = 'T';
  linea4[14] = 'E';
  linea4[15] = 'M';
  linea4[16] = 'A';
  linea4[17] = ' ';
  linea4[18] = 'O';
  linea4[19] = 'P';
  linea4[20] = 'E';
  linea4[21] = 'R';
  linea4[22] = 'A';
  linea4[23] = 'T';
  linea4[24] = 'I';
  linea4[25] = 'V';
  linea4[26] = 'O';

  linea6[0] = ' ';
  linea6[1] = 'H';
  linea6[2] = 'o';
  linea6[3] = 'l';
  linea6[4] = 'a';
  linea6[5] = ' ';
  linea6[6] = 'M';
  linea6[7] = 'u';
  linea6[8] = 'n';
  linea6[9] = 'd';
  linea6[10] = 'o';
  linea6[11] = ' ';
  linea6[12] = '!';
  linea6[13] = '!';
  linea6[14] = ' ';

  linea7[0] = ' ';
  linea7[1] = 'H';
  linea7[2] = 'e';
  linea7[3] = 'l';
  linea7[4] = 'l';
  linea7[5] = 'o';
  linea7[6] = ' ';
  linea7[7] = 'W';
  linea7[8] = 'o';
  linea7[9] = 'r';
  linea7[10] = 'l';
  linea7[11] = 'd';
  linea7[12] = ' ';
  linea7[13] = '!';
  linea7[14] = '!';
  linea7[15] = ' ';

  linea8[0] = ' ';
  linea8[1] = 'O';
  linea8[2] = 't';
  linea8[3] = 'r';
  linea8[4] = 'o';
  linea8[5] = ' ';
  linea8[6] = 'I';
  linea8[7] = 'd';
  linea8[8] = 'i';
  linea8[9] = 'o';
  linea8[10] = 'm';
  linea8[11] = 'a';
  linea8[12] = ' ';
  linea8[13] = '!';
  linea8[14] = '!';
  linea8[15] = ' ';

  for(i=0; i<560; i++) {

    if(i<80){
      if(i<30) {
        putInMemory(0xB000, 0x8000 + (2*i), ' ');
      } else if(i<51) {
        putInMemory(0xB000, 0x8000 + (2*i), linea1[i-30]);
      } else {
        putInMemory(0xB000, 0x8000 + (2*i), ' ');
      }
    }else if(i<160){
      if(i<96) {
        putInMemory(0xB000, 0x8000 + (2*i), ' ');
      } else if(i<144) {
        putInMemory(0xB000, 0x8000 + (2*i), linea2[i-96]);
      } else {
        putInMemory(0xB000, 0x8000 + (2*i), ' ');
      }
    }else if(i<240){
      if(i<187) {
        putInMemory(0xB000, 0x8000 + (2*i), ' ');
      } else if(i<212) {
        putInMemory(0xB000, 0x8000 + (2*i), linea3[i-187]);
      } else {
        putInMemory(0xB000, 0x8000 + (2*i), ' ');
      }
    }else if(i<320){
      if(i<266) {
        putInMemory(0xB000, 0x8000 + (2*i), ' ');
      } else if(i<293) {
        putInMemory(0xB000, 0x8000 + (2*i), linea4[i-266]);
      } else {
        putInMemory(0xB000, 0x8000 + (2*i), ' ');
      }
    }else if(i<400){
      putInMemory(0xB000, 0x8000 + (2*i), '-');
    }else if(i<480){
      if(i<432) {
        putInMemory(0xB000, 0x8000 + (2*i), '*');
      } else if(i<447) {
        putInMemory(0xB000, 0x8000 + (2*i), linea6[i-432]);
      } else {
        putInMemory(0xB000, 0x8000 + (2*i), '*');
      }
    }else{
      if(i<512) {
        putInMemory(0xB000, 0x8000 + (2*i), '*');
      } else if(i<528) {
        putInMemory(0xB000, 0x8000 + (2*i), linea7[i-512]);
      } else {
        putInMemory(0xB000, 0x8000 + (2*i), '*');
      }
    }

    putInMemory(0xB000, 0x8001 + (2*i), 0x7);
  }

  k=560;
  for(i=0;i<18;i++) {
    for(j=0;j<80;j++) {
      if(j<32) {
        putInMemory(0xB000, 0x8000 + (2*k), '*');
      } else if(j<48) {
        putInMemory(0xB000, 0x8000 + (2*k), linea8[j-32]);
      } else {
        putInMemory(0xB000, 0x8000 + (2*k), '*');
      }
      putInMemory(0xB000, 0x8001 + (2*k), 0x7);
      k++;
    }
  }

  for(;;)
  return(0);
}