/*
 *	RDB - A NoSQL local database written in C++
 *	Author: https://github.com/MilkywayPwns
 *	Date:	13 - 10 - 2016
 */

namespace RDB::Database
{
	class Database
	{
	protected:
		std::map < std::string, DataTable > _data;
		std::string							_name;
	public:
		// No arguments for a clean database
		Database()
		{
			_name = "";
		}
		// Load database from file
		Database(std::string filename)
		{
			_name = filename;

			// Alloc buffer
			auto buffer = new Buffer::DatabaseBuffer(filename, (std::ios::in | std::ios::binary));
			buffer->Init();				// Load file into memory

			// Read DataTable count
			size_t num_tables = buffer->Read<size_t>();

			// Loop through tables
			for (size_t i = 0; i < num_tables; i++)
			{
				// Read table name
				std::string name = buffer->ReadStr();

				// Load table data
				DataTable table;
				table.Load(buffer);

				// Store table
				_data[name] = table;
			}

			// Close the file, delete the buffer
			buffer->Close();
			buffer->~DatabaseBuffer();
		}
		// Load database from memory
		Database(const void *memory, std::size_t size)
		{
			// Alloc buffer
			auto buffer = new Buffer::DatabaseBuffer(memory, size);

			// Read DataTable count
			size_t num_tables = buffer->Read<size_t>();

			// Loop through tables
			for (size_t i = 0; i < num_tables; i++)
			{
				// Read table name
				std::string name = buffer->ReadStr();

				// Load table data
				DataTable table;
				table.Load(buffer);

				// Store table
				_data[name] = table;
			}

			// We don't want to close the file here, or delete the buffer, as we're reading from memory
		}

		// Functions
		bool Save(std::string filename)
		{
			// Check if filename has been set
			if (!filename.size())
				return false;

			// Update filename
			_name = filename;

			// Open DatabaseBuffer
			auto buffer = new Buffer::DatabaseBuffer(_name, (std::ios::out | std::ios::binary));

			// Write amount of tables to disk
			buffer->Write(_data.size());

			// Loop through datatables
			for (auto table : _data)
			{
				buffer->WriteStr(table.first);		// Write table name
				table.second.Save(buffer);			// Write table data
			}

			// Close buffer
			buffer->Flush();
			buffer->Close();
			buffer->~DatabaseBuffer();
		}
		bool Save()
		{
			Save(_name);
		}

		// Operators
		DataTable &operator[](std::string name)
		{
			// Check if table exists
			if (_data.find(name) != _data.end())
				return _data[name];

			// Create a new empty entry in our data store
			_data[name] = DataTable();
			return _data[name];
		}
	};
}
