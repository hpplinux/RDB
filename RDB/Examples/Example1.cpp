/*
 *	RDB - A NoSQL local database written in C++
 *	Author: https://github.com/MilkywayPwns
 *	Date:	13 - 10 - 2016
 */

#include "..\stdafx.h"

void Example1()
{
	// Allocate database
	RDB::Database::Database db;

	// Inserts a row into table users
	db["users"].Insert(
		{
			{ "uid", 0 },
			{ "username", RDB::Database::DataEntry("test") },
		}
	);

	// Sets column username in table users to username_test where username is test
	db["users"].Select(
		{
			{ "username", RDB::Database::DataEntry("test") }
		}
	)["username"] = "username_test";

	// Show values
	RDB::Database::DataRow row = db["users"].Select(
		{
			{ "username", RDB::Database::DataEntry("username_test") }
		}
	);

	// Store database to disk
	db.Save("test.db");
}
