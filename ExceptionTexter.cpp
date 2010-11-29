/*###############################
# FH Salzburg                   #
# WS2010 MMT-B2009              #
# Multimediale Netzwerke        #
# Uebungsprojekt                #
# Fritsch Andreas, Hanli Ismail #
# Sun, 28.11.2010 22:00         #
###############################*/

#include "ExceptionTexter.h"

const char* exceptionTexter(const char* exceptionText, const int errorCode)
{
	ostringstream finalException;

	finalException << exceptionText;
	finalException << errorCode;
	finalException << ")";

	return finalException.str().c_str();
}
