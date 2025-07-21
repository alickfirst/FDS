#include "ioexception.h"

Ioexception::Ioexception(const string& msg): runtime_error(msg){}
