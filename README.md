# Cryptography

Here is a desciption of what each program does:

************
Phi and Psi

 phi.c - Calculates the phi of characters in the input file.
  
 psi.c - Calculates the psi of characters in the input file.

 phi_pair.c - Calculates the phi of pairs of characters in the inout file.
  
 psi_pair.c - Calculates the psi of pairs of characters in the inout file.

*************
Ceaser Cipher

ceaser_cipher1.c - Takes an input file and key. Outputs the encrypted file.

ceaser_cipher2.c - Takes a ceaser cipher as input. Finds the keys assuming that 'e' is the most common letter in english      alphabet and outputs the decrypted file.

ceaser_cipher3.c - Takes a ceaser cipher and key as input. Decrypts the ceaser cipher with the entered key addictively till the most frequent letter in the decrypted text is 'e'. Ouputs the decrypted text. This program proves the addictive property of ceaser cipher.

*************
ADFGVX cipher

adfgvx_3Q.c - Decrypts the entered adfgvx cipher using an entered adfgvx table.

adfgvx_4Q.c - Takes the input cipher and checks if the cipher is permuted or not. Finds the period of permutation. Outputs the number of rows and columns of the permutation matrix.

adfgvx_5Q.c - Takes two inputs - cipher text file and original file. Checks if the cipher is from the original file or not. The program calculates phi of characters, phi of pairs of characters and phi of three characters of both the cipher text and all possible substring of the original file to find this.
