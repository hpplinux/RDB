#include "..\stdafx.h"

void Example1()
{
	// Allocate database
	RDB::Database::Database db;

	// sets column username in table users to username_test
	db["users"]["username"] = "username_test";
}