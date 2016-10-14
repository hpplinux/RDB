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

		// Clears all data in this row
		void Clear()
		{
			_data.clear();
		}
	};
}
