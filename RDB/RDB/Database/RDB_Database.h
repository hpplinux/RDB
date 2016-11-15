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
		std::mutex										_datamutex;
		std::unordered_map < std::string, DataTable >	_data;
		std::string										_name;

	public:
		// No arguments for a clean database
		Database()
		{
			_name = "";
		}
		// Load database from file
		Database(std::string filename)
		{
			this->Load(filename);
		}
		// Load database from memory
		Database(const void *memory, std::size_t size)
		{
			_datamutex.lock();

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

			_datamutex.unlock();
		}

		size_t BufferSize()
		{
			_datamutex.lock();

			size_t ret = sizeof(size_t);

			for (auto table : _data)
			{
				ret += table.first.size() + 1;
				ret += table.second.BufferSize() + 1;
			}

			return ret;

			_datamutex.unlock();
		}

		// Functions
		bool Save(std::string filename)
		{
			_datamutex.lock();

			// Check if filename has been set
			if (!filename.size())
			{
				_datamutex.unlock();
				return false;
			}

			// Update filename
			_name = filename;

			// Open DatabaseBuffer
			Buffer::DatabaseBuffer buffer(_name, (std::ios::out | std::ios::binary), 0);

			// Write amount of tables to disk
			buffer.Write(_data.size());

			// Loop through datatables
			for (auto table : _data)
			{
				buffer.WriteStr(table.first);		// Write table name
				table.second.Save(&buffer);			// Write table data
			}

			// Close buffer
			buffer.Flush();
			buffer.Close();

			_datamutex.unlock();

			// Return true when succeeded
			return true;
		}
		bool Save()
		{
			return Save(_name);
		}
		void Load(std::string filename)
		{
			_datamutex.lock();

			_name = filename;

			// Attempt to open file, to check if it exists
			std::filebuf fb;
			fb.open(filename, std::ios::in);

			if (fb.is_open())
			{
				// Close file
				fb.close();

				// Alloc buffer
				Buffer::DatabaseBuffer buffer(filename, (std::ios::in | std::ios::binary), 0);
				buffer.Init();				// Load file into memory

				// Read DataTable count
				size_t num_tables = buffer.Read<size_t>();

				// Loop through tables
				for (size_t i = 0; i < num_tables; i++)
				{
					// Read table name
					std::string name = buffer.ReadStr();

					// Load table data
					DataTable table;
					table.Load(&buffer);

					// Store table
					_data[name] = table;
				}

				// Close the file, delete the buffer
				buffer.Close();
			}

			_datamutex.unlock();
		}

		size_t Size()
		{
			return _data.size();
		}

		// Deletes the entire database.
		void Clear()
		{
			_datamutex.lock();
			_data.clear();
			_datamutex.unlock();
		}

		// Operators
		DataTable &operator[](std::string name)
		{
			_datamutex.lock();

			// Check if table exists
			if (_data.find(name) != _data.end())
			{
				DataTable &table = _data[name];
				_datamutex.unlock();
				return table;
			}

			// Create a new empty entry in our data store
			_data[name] = DataTable();
			DataTable &table = _data[name];
			_datamutex.unlock();

			return table;
		}
	};
}
