/* Utilitaires de lecture pour les fichiers PBM, PGM, PPM
 * E.B.  12/98
 */

#ifndef _Util_h
#define _Util_h

#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include "Pixel.hpp"

typedef unsigned char bit;
typedef unsigned char gray;

// Returns the next bit (0 or 1) of "file". Takes into account the following separation char: ' ', '\t', '\n', '\r'
bit pm_getbit(std::istream& in);

// Returns the next char of "file". Takes into account the following separation char: '\n', '\r' and the lines starting by #
char pm_getc(std::istream& in);

// Returns the next integer of "file". Takes into account the following separation char: ' ', '\t', '\n' and '\r'
int pm_getint(std::istream& in);

// Returns the next Byte (octet) of "file" - do not ignore separation char
unsigned char pm_getrawbyte(std::istream& in);

// Throws an exception whose error message is "texte"
void pm_erreur(const std::string& texte);

float clampf(float v, float mini, float maxi);
int clampi(int v, int mini, int maxi);

uint64_t gcd(uint64_t a, uint64_t b);

#endif

