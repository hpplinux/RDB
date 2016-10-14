namespace RDB::Database
{
	class Database
	{
	protected:
		std::map < std::string, DataTable > _data;

	public:
		// No arguments for a clean database
		Database()
		{

		}
		// Load database from file
		Database(std::string filename)
		{

		}
		// Load database from memory
		Database(const void *memory, std::size_t size)
		{

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