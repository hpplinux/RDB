namespace RDB::Buffer
{
	class DatabaseBuffer
	{
	protected:
		std::filebuf	_fb;
		char*			_buffer;
		std::size_t		_pos;

	public:
		DatabaseBuffer(std::string filename)
		{
			_pos = 0;

			// open file buffer
			_fb.open(filename, (std::ios::out | std::ios::binary));

			// alloc buffer
			_buffer = new char[0x8000];
		}
		~DatabaseBuffer()
		{
			delete[] _buffer;
		}

		// Write functions
		template <typename T> void Write(T val)
		{
			*(T*)(_buffer + _pos) = val;
			_pos += sizeof(T);
		}
		void WriteStr(std::string str)
		{
			strcpy((char*)(_buffer + _pos), str.c_str());
			_pos += str.size();
		}

		void Flush()
		{
			// flush data to disk
			std::ostream _os(&_fb);
			_os.write(_buffer, _pos);
		}
		void Close()
		{
			_fb.close();
		}
	};
}