#include "ciphers.h"
#include <stdio.h>

// Write your code here. You need to implement the following functions.
//    char_at_index
//    index_of_char
//    cipher_caesar
//    cipher_substitution
//    cipher_enigma - the rotor codes are given below
//		outer rotor:  "BDFHJLNPRTVXZACEGIKMOQSUWY "
//		middle rotor: "EJOTYCHMRWAFKPUZDINSXBGLQV ";
// 		inner rotor:  "GNUAHOVBIPWCJQXDKRYELSZFMT ";



// replaces a char in a string by a shifted amount
char char_at_index(char array[],  int shift, int index) {
  int stringLength = 0, i;

  for(i = 0; array[i] != '\0'; i++) {
    stringLength++;
  }

  if((shift + index <= stringLength) && (shift + index >= 0)) { /* normal shift that doesn't exceed the length of the array */
    array[index] = array[index + shift];
    return array[index];
  }
  else if(shift + index < 0) { /* when shifting from beginning back to end */
    array[index] = array[index + shift + stringLength];
    return array[index];
  }
  
  else  {  /* if shift needs to circle from end back to beginning */
    array[index] = array[index + shift - stringLength];
    return array[index];
  }
}






// finds index of a character in a string
int index_of_char(char array[], int shift, char findIt) { 
  int index = 0, size = 0, i;

  while(1) { // finds index of character
    if(array[index] == findIt) {
      break;
    }
    index++;
  }

  for(i = 0; array[i] != '\0'; i++) { // determines size of string
    size++;
  }

  /* when a shift is within the normal range */
  if((index - shift <= size) && (index - shift >= 0)) {
    index = index - shift;
    return index;
  }

  /* when the shift circles from beginning to end */
  else if(index - shift < 0) {
    index = index - shift + size;
    return index;
  }

  /* shift from end to beginning - case of lrage, negative number */
  else {
    index = index - shift - size;
    return index;
  }
}


void cipher_substitution(char input[], char output[], char key[], int command) {
  int i, sizeInput = 0, j, k;

  char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "; 

  for(i = 0; input[i] != '\0'; i++) {   /* takes size of input word for later for loops */
    sizeInput++;
  }

  // main loop is what encrypts or decrypts by each letter
  for(i = 0; i < sizeInput; i++) {
    if(command == ENCRYPT) {
      output[i] = key[index_of_char(alphabet, 0, input[i])];
    }
    if(command == DECRYPT) {
      output[i] = alphabet[index_of_char(key, 0, input[i])];
    }
  }

}


void cipher_caesar(char input[], char output[], int move, int command) {
  char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", code[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int i, j = 0, m = 26;

  // creates a key to decode the input
  for(i = 0; i < 27; i++) {
    if(i == 26) {
      code[i] = '\0';
      break;
    }
    if(i + move > 25) {
      code[i] = alphabet[j];
      j++;
      continue;
    }
    // in the case that the shift is negative
    if(i + move < 0) {
      code[i] = alphabet[m];
      m--;
    }
    code[i] = char_at_index(code, move, i);
  }


  // the encryption/decryption code
  for(i = 0; input[i] != '\0'; i++) {
    if(input[i] == ' ') {
      continue;
    }
    else {
      if(command == ENCRYPT) {
	output[i] = code[index_of_char(alphabet, 0, input[i])];
      }
      if(command == DECRYPT) {
	output[i] = alphabet[index_of_char(code, 0, input[i])];
      }
    }

  }

}
 

void cipher_enigma(char input[], char output[], int key, int command) {
  int key1 = key % 100, key2 = key / 100, i, j, m;

  // declares the 3 rotors that will be worked with
  char rotor1[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ", rotor2[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ", rotor3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ", rotor4[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

  // shifts the inner and middle rotors
  for(i = 0; i < 27; i++) {
    // inner rotor
    rotor1[i] = rotor4[index_of_char(rotor4, key1, rotor4[i])];
    // middle rotor
    rotor2[i] = rotor4[index_of_char(rotor4, key2, rotor4[i])];
  }

  // loop to read the input
  for(i = 0; input[i] != '\0'; i++) {
    output[i] = rotor3[index_of_char(rotor2, 0, rotor2[char_at_index(rotor3, 0, rotor3[index_of_char(rotor1, 0, input[i])])])];
  }

}
