namespace RDB::Database
{
	class DataEntry
	{
	protected:
		std::string _raw;

	public:
#define DATAENTRY_TYPE(__in_type, __convert_name, __convert_func) \
		DataEntry(__in_type __in) \
		{ \
			_raw = std::to_string(__in_type(__in)); \
		} \
		DataEntry operator=(__in_type __in) \
		{ \
			_raw = std::to_string(__in_type(__in)); \
		} \
		__in_type __convert_name() \
		{ \
			return __convert_func(_raw); \
		}

		/*
		bool operator==(__in_type __in) \
		{ \
			return (__convert_func(_raw) == __in); \
		} \
		bool operator!=(__in_type __in) \
		{ \
			return (__convert_func(_raw) != __in); \
		} \
		bool operator<=(__in_type __in) \
		{ \
			return (__convert_func(_raw) <= __in); \
		} \
		bool operator>=(__in_type __in) \
		{ \
			return (__convert_func(_raw) >= __in); \
		} \
		bool operator<(__in_type __in) \
		{ \
			return (__convert_func(_raw) < __in); \
		} \
		bool operator>(__in_type __in) \
		{ \
			return (__convert_func(_raw) > __in); \
		}
		*/

		DATAENTRY_TYPE(int32_t, ToInt32, std::stoi)
		DATAENTRY_TYPE(uint32_t, ToUint32, std::stoul)
		DATAENTRY_TYPE(int64_t, ToInt64, std::stoll)
		DATAENTRY_TYPE(uint64_t, ToUint64, std::stoull)
	};
}