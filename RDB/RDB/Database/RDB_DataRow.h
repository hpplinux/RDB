/*
 *	RDB - A NoSQL local database written in C++
 *	Author: https://github.com/MilkywayPwns
 *	Date:	13 - 10 - 2016
 */

namespace RDB::Database
{
	class DataRow
	{
	protected:
		std::unordered_map < std::string, DataEntry > _data;

	public:
		DataRow()
		{

		}
		DataRow(std::unordered_map < std::string, DataEntry > data)
		{
			_data = data;
		}

		// Operators
		DataEntry &operator[](std::string name)
		{
			// Check if table exists
			if (_data.find(name) != _data.end())
				return _data[name];

			// Create a new empty entry in our data store
			_data[name] = DataEntry();
			return _data[name];
		}

		// Save/Load
		void Save(Buffer::DatabaseBuffer *buffer)
		{
			// Write entry count
			buffer->Write(_data.size());

			// Loop through entries
			for (auto entry : _data)
			{
				buffer->WriteStr(entry.first);		// Write entry name
				entry.second.Save(buffer);			// Write entry data
			}
		}
		void Load(Buffer::DatabaseBuffer *buffer)
		{
			// Read amount of DataRows
			size_t entries = buffer->Read<size_t>();

			// Read rows
			for (size_t i = 0; i < entries; i++)
			{
				// Read entry name
				std::string name = buffer->ReadStr();

				// Alloc entry and load data
				DataEntry entry;
				entry.Load(buffer);

				// Add entry to array
				_data[name] = entry;
			}
		}

		size_t BufferSize()
		{
			size_t ret = sizeof(size_t);

			for (auto entry : _data)
			{
				ret += entry.first.size() + 1;
				ret += entry.second.Size() + 1;
			}

			return ret;
		}

		size_t Size()
		{
			return _data.size();
		}

		// Clears all data in this row
		void Clear()
		{
			_data.clear();
		}
	};
}
