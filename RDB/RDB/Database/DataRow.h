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
		std::map < std::string, DataEntry > _data;

	public:
		DataRow()
		{

		}
		DataRow(std::map < std::string, DataEntry > data)
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

		// Clears all data in this row
		void Clear()
		{
			_data.clear();
		}
	};
}
