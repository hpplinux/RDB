# RDB
RDB is an easy-to-use NoSQL database, fully written in C++. kinda like SQLite but without SQL. Even though its NoSQL, it uses a SQL like structure. RDB is lightweight and fast, and makes use of the C++11/C++14 libraries. RDB Database Tables are not static, meaning that every row can have a different amount of columns.

## Opening a database
To open a database, you need to call the ``RDB::Database::Database`` class. If you don't specify any parameter, it will create an empty database automatically.
Example:
```cpp
// Empty database
RDB::Database::Database Database1;

// From file
RDB::Database::Database Database2("database.rdb");

// From memory
void *DatabasePtr;
size_t DatabaseLen;
RDB::Database::Database Database3(DatabasePtr, DatabaseLen);
```

## Saving a database
To save the database, you simply call the .Save() function on the Database class. If you're using an empty database, you need to specify a filename to save to, otherwise it wont save.
Example:
```cpp
// Empty database
RDB::Database::Database Database1;
Database1.Save("test.rdb");

// Database from file
RDB::Database::Database Database2("test.rdb");
Database2.Save();
```

## Adding a new table to the database
Adding a new table to the database is quite easy, if it can't find the table in the database, it will go ahead and create it for you.
Example:
```cpp
// Allocate database
RDB::Database::Database Database;

// Create the table users inside our database.
Database["users"];
```

## Inserting a row into a table
To insert a row into a table, you need to select the table first, after that you can simply use the .Insert function, and supply the data for the columns.
Example:
```cpp
// Allocate database
RDB::Database::Database Database;

// Insert a row into table users with uid 0 and username test
Database["users"].Insert(
  {
    { "uid", 0 },
    { "username", "test" }
  }
);
```

## Selecting a row from a table
Selecting a row from the database is not very hard either, its kinda like SQL, but without the WHERE query.
Example:
```cpp
// Allocate database
RDB::Database::Database Database;

// Select the row from table users where username is test
Database["users"].Select(
  {
    { "username", "test" }
  }
);
```

Ofcourse it supports multiple WHERE statements inside the select function, another example:
```cpp
// Allocate database
RDB::Database::Database Database;

// Select the row from table users where uid is 0 and username is test
Database["users"].Select(
  {
    { "uid", 0 },
    { "username", "test" }
  }
);
```

## Updating data from an already existing row
To update the data from a row, you need to select it first. After that, its pretty easy to update the data into our row.
Example:
```cpp
// Allocate database
RDB::Database::Database Database;

// Select the row from table users where uid is 0 and username is test
RDB::Database::DataRow &row = Database["users"].Select(
  {
    { "uid", 0 },
    { "username", "test" }
  }
);
// Update the fields for the selected row
row["email"] = "test@gmail.com";
row["age"] = 21;
```

## Clearing data from a database/table/row/entry
To clear all the data in a database, table, row, or entry, you simply use the .Clear() function, Example:
```cpp
// Allocate database
RDB::Database::Database Database;

// Select the row from table users where uid is 0 and username is test
RDB::Database::DataRow &row = Database["users"].Select(
  {
    { "uid", 0 },
    { "username", "test" }
  }
);

row["username"].Clear();        // Clears the field username from the selected row
row.Clear();                    // Clears the selected row
Database["users"].Clear();      // Clears all data in table users
Database.Clear();               // Clears the entire database
```
