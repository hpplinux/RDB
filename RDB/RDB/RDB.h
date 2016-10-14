/*
 *	RDB - A NoSQL local database written in C++
 *	Author: https://github.com/MilkywayPwns
 *	Date:	13 - 10 - 2016
 */

// Headers needed for RDB
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef _IOSTREAM_
#include <iostream>
#endif
#ifndef _SSTREAM_
#include <sstream>
#endif
#ifndef _STDINT
#include <stdint.h>
#endif
#ifndef _UNORDERED_MAP_
#include <unordered_map>
#endif
#ifndef _VECTOR_
#include <vector>
#endif
#ifndef _FSTREAM_
#include <fstream>
#endif
#ifndef _MUTEX_
#include <mutex>
#endif

// Include files
#include "Buffer/RDB_DatabaseBuffer.h"
#include "Database/RDB_DataEntry.h"
#include "Database/RDB_DataRow.h"
#include "Database/RDB_DataTable.h"
#include "Database/RDB_Database.h"
