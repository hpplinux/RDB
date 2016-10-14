#ifdef RDB_COMPILING
#define RDB_LIB __declspec(dllexport)
#else
#define RDB_LIB extern 
#endif

// Include files
#include "Database/DataEntry.h"
#include "Database/DataRow.h"
#include "Database/DataTable.h"
#include "Database/Database.h"