#ifdef RDB_COMPILING
#define RDB_LIB __declspec(dllexport)
#else
#define RDB_LIB extern 
#endif

#include "Database/DataEntry.h"
#include "Database/Database.h"