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
		}
		// Load database from memory
		Database(const void *memory, std::size_t size)
		{
			_name = "";
		}

		// Functions
		bool Save(std::string filename)
		{
			// Check if filename has been set
			if (!filename.size())
				return false;

			// Flush data
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