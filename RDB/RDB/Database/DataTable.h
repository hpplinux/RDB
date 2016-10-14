namespace RDB::Database
{
	class DataTable
	{
	protected:
		std::vector < DataRow > _data;

	public:
		// Inserts a row into the table
		DataRow &Insert(std::map < std::string, DataEntry > args)
		{
			// Alloc row and add it to the array
			DataRow row(args);
			_data.push_back(row);

			// Return row reference
			return row;
		}

		// Selects the first row based on arguments specified
		DataRow &Select(std::map < std::string, DataEntry > args)
		{
			// Loop through stored rows
			for (auto row : _data)
			{
				bool bRowFound = true;

				// Loop through arguments
				for (auto column : args)
				{
					if (row[column.first] != column.second)
					{
						bRowFound = false;
						break;
					}
				}

				// Check if row has been found
				if (bRowFound)
					return row;
			}

			// Return empty row
			return DataRow();
		}

		// Clears all data in this table
		void Clear()
		{
			_data.clear();
		}
	};
}