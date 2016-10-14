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

	printf("Username: %s\nUID: %i\n", row["username"].ToString().c_str(), row["uid"].ToInt32());
}