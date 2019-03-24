#include <stdio.h>
#include "ciphers.h"



// The code below is shown only to get you started
int main(void) {
  
	// String with initialization
	char alphabet[] = " ZYXWVUTSRQPONMLKJIHGFEDCBA";

	// Array declaration to hold a string 
	// (of up to 255 characters, plus '\0' character)
	char input[256];
	char output[256];

	// Print the alphabet
	// We demarcate the string with | | so spaces at the
	// start or end can be distinguished more clearly
	printf("\n This is the alphabet: \"%s\"\n", alphabet);

	// Get input for the user
	// The scanf formatting reads a string, including 
	// the blank spaces, until a newline is encountered
	// Also, leave the blank space before the '%' to  clear the buffer first
	printf("\n Enter a string: ");
	scanf(" %[^\n]s",input);	
	printf(" The string you entered was: \"%s\"\n\n",input);		
 

	// Examples. They are commented out since the functions
	// are not implemented yet. They are included here to
	// illustrate the function  arguments and their use.
	//
	// Substition cipher: Encrypt the string 'input' and 
	//                    put the result in 'output'. Use 
	//                    'alphabet' as the key.
	//    cipher_substitution(input,output,alphabet,ENCRYPT);
	//
	// Caesar cipher:     Encrypt the string 'input' and 
	//                    put the result in 'output'. The
	//                    key is 3.
	//    cipher_caesar(input,output,3,ENCRYPT);
	//
	// Enigma cipher:     Encrypt the string 'input' and 
	//                    put the result in 'output'. The
	//                    key is 1304.
	//    cipher_enigma(input,output,1304,ENCRYPT);
	

}
