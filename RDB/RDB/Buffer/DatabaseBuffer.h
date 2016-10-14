/*
 *	RDB - A NoSQL local database written in C++
 *	Author: https://github.com/MilkywayPwns
 *	Date:	13 - 10 - 2016
 */

namespace RDB::Buffer
{
	class DatabaseBuffer
	{
	protected:
		std::filebuf	_fb;
		char*			_buffer;
		std::size_t		_pos;

	public:
		DatabaseBuffer(std::string filename, int mode)
		{
			_pos = 0;

			// open file buffer
			_fb.open(filename, mode);

			// alloc buffer
			_buffer = new char[0x8000];
		}
		DatabaseBuffer(const void *memory, size_t size)
		{
			_pos = 0;
			_buffer = (char*)memory;
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
			_pos += str.size() + 1;
		}
		template <typename T> T Read()
		{
			T val = *(T*)(_buffer + _pos);
			_pos += sizeof(T);

			return val;
		}
		std::string ReadStr()
		{
			std::string val((char*)(_buffer + _pos));
			_pos += val.size() + 1;

			return val;
		}

		void Init()
		{
			// Copies raw data into buffer
			std::istream _is(&_fb);
			
			// Calculate buffer size
			std::streampos fsize = _is.tellg();
			_is.seekg(0, std::ios::end);
			fsize = _is.tellg() - fsize;
			_is.seekg(0, std::ios::beg);

			// Read to buffer
			_is.read(_buffer, fsize);
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
