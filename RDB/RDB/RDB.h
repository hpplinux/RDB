/*
 *	RDB - A NoSQL local database written in C++
 *	Author: https://github.com/MilkywayPwns
 *	Date:	13 - 10 - 2016
 */

#ifdef RDB_COMPILING
#define RDB_LIB __declspec(dllexport)
#else
#define RDB_LIB extern 
#endif

// Include files
#include "Buffer/DatabaseBuffer.h"
#include "Database/DataEntry.h"
#include "Database/DataRow.h"
#include "Database/DataTable.h"
#include "Database/Database.h"
