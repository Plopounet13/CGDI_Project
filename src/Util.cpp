/* Utilitaires de lecture pour les fichiers PBM, PGM, PPM
**
** E.B. 12/98
*/

#include <cstdio>
#include <cstdlib>
#include "Util.hpp"

using namespace std;

char pm_getc(istream& in) {
	int ich;
	char ch;

	ich = in.get();
	if (in.eof())
		pm_erreur("EOF / read error" );
	ch = (char) ich;

	if (ch == '#')
	{
		do
		{
			ich = in.get();
			if (in.eof())
				pm_erreur("EOF / read error" );
			ch = (char) ich;
		}
		while (ch != '\n' && ch != '\r');
	}

	return ch;
}


bit pm_getbit(istream& in) {
	char ch;

	do
	{
		ch = pm_getc(in);
	}
	while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');

	if (ch != '0' && ch != '1')
		pm_erreur("junk in file where bits should be" );

	return ( ch == '1' ) ? 1 : 0;
}


unsigned char pm_getrawbyte(istream& in) {
	int iby;

	iby = in.get();
	if (in.eof())
		pm_erreur("EOF / read error" );
	return (unsigned char) iby;
}

int pm_getint(istream& in) {
	char ch;
	int i;

	do
	{
		ch = pm_getc(in);
	}
	while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');

	if (ch < '0' || ch > '9')
		pm_erreur( "junk in file where an integer should be" );

	i = 0;
	do
	{
		i = i*10+ch-'0';
		ch = pm_getc(in);
	}
	while (ch >= '0' && ch <= '9');

	return i;
}

void pm_erreur(const string& texte) {
	cerr << endl << texte << endl << endl;
	exit(1);
}

int clampi(int v, int mini, int maxi){
	return min(maxi, max(mini, v));
}

float clampf(float v, float mini, float maxi){
	return min(maxi, max(mini, v));
}












