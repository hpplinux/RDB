/*
 *	RDB - A NoSQL local database written in C++
 *	Author: https://github.com/MilkywayPwns
 *	Date:	13 - 10 - 2016
 */

namespace RDB::Database
{
	class DataEntry
	{
	protected:
		std::string _raw;

	public:
		DataEntry()
		{
			_raw = "";
		}
		DataEntry(std::string str)
		{
			_raw = str;
		}
		DataEntry(const char *str)
		{
			_raw = std::string(str);
		}

#define DATAENTRY_TYPE(__in_type, __convert_name, __convert_func) \
		DataEntry(__in_type __in_arg) \
		{ \
			_raw = std::to_string(__in_type(__in_arg)); \
		} \
		DataEntry &operator=(__in_type __in_arg) \
		{ \
			_raw = std::to_string(__in_type(__in_arg)); \
			return *this; \
		} \
		__in_type __convert_name() \
		{ \
			return __convert_func(_raw); \
		} \
		bool operator==(__in_type __in_arg) \
		{ \
			return (__convert_func(_raw) == __in_arg); \
		} \
		bool operator!=(__in_type __in_arg) \
		{ \
			return (__convert_func(_raw) == __in_arg); \
		}

		// Manual operators
		bool operator==(DataEntry in)
		{
			return (in._raw == _raw);
		}
		bool operator!=(DataEntry in)
		{
			return (in._raw != _raw);
		}
		bool operator==(std::string in)
		{
			return (in == _raw);
		}
		bool operator!=(std::string in)
		{
			return (in != _raw);
		}
		DataEntry &operator=(std::string str)
		{
			_raw = str;
			return *this;
		}
		DataEntry &operator=(const char *str)
		{
			_raw = std::string(str);
			return *this;
		}
		DataEntry &operator=(DataEntry in)
		{
			_raw = in._raw;
			return *this;
		}
		std::string ToString()
		{
			return _raw;
		}

		// Save/Load
		void Save(Buffer::DatabaseBuffer *buffer)
		{
			// Write value of this Entry
			buffer->WriteStr(_raw);
		}
		void Load(Buffer::DatabaseBuffer *buffer)
		{
			// Read value for this entry
			_raw = buffer->ReadStr();
		}

		// Clears data in this entry
		void Clear()
		{
			_raw.clear();
		}

		size_t Size()
		{
			return _raw.size();
		}

		// Generate operators and To* functions
		DATAENTRY_TYPE(int32_t, ToInt32, std::stoi)
		DATAENTRY_TYPE(uint32_t, ToUint32, std::stoul)
		DATAENTRY_TYPE(int64_t, ToInt64, std::stoll)
		DATAENTRY_TYPE(uint64_t, ToUint64, std::stoull)
		DATAENTRY_TYPE(float, ToFloat, std::stof)
		DATAENTRY_TYPE(double, ToDouble, std::stod)
		DATAENTRY_TYPE(long double, ToLongDouble, std::stold)
	};
}
