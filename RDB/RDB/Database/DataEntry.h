namespace Database
{
	class DataEntry
	{
	protected:
		std::string _raw;

	public:
#define DATAENTRY_TYPE(__in_type, __convert_func) \
		DataEntry(__in_type __in) \
		{ \
			_raw = std::to_string(__in_type(__in)); \
		} \
		DataEntry operator=(__in_type __in) \
		{ \
			_raw = std::to_string(__in_type(__in)); \
			return *this; \
		} \
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

		DATAENTRY_TYPE(uint32_t, std::stoul)
		DATAENTRY_TYPE(int32_t, std::stoi)
	};
}