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
		std::size_t		_len;

	public:
		DatabaseBuffer(std::string filename, int mode, size_t size)
		{
			_pos = 0;
			_len = size;
			
			// open file buffer
			_fb.open(filename, mode);

			// alloc buffer
			if (!size) _buffer = new char[0x8000];
			else _buffer = new char[size];
		}
		DatabaseBuffer(const void *memory, size_t size)
		{
			_pos = 0;
			_len = size;
			_buffer = (char*)memory;
		}
		// Do not call this if we're using an existing buffer.
		~DatabaseBuffer()
		{
			delete[] _buffer;
		}

		// Write functions
		template <typename T> void Write(T val)
		{
			// Reallocate buffer before attempting to write
			if (_pos + sizeof(T) >= _len)
				this->Realloc();

			// Write variable into buffer
			*(T*)(_buffer + _pos) = val;
			_pos += sizeof(T);
		}
		void WriteStr(std::string str)
		{
			// Reallocate buffer before attempting to write
			if (_pos + str.size() + 1 >= _len)
				this->Realloc();

			// Write string into buffer
			strcpy((char*)(_buffer + _pos), str.c_str());
			_pos += str.size() + 1;
		}
		template <typename T> T Read()
		{
			// Read variable from buffer
			T val = *(T*)(_buffer + _pos);
			_pos += sizeof(T);

			return val;
		}
		std::string ReadStr()
		{
			// Read string from buffer
			std::string val((char*)(_buffer + _pos));
			_pos += val.size() + 1;

			return val;
		}

		// Realloc: Reallocate the buffer
		void Realloc()
		{
			// Alloc a temp buffer to copy over existing data
			char *_tmpbuf = new char[_len];

			// Copy old data
			memcpy(_tmpbuf, _buffer, _len);

			// Allocate new buffer
			_buffer = new char[_len + 0x8000];

			// Copy data
			memcpy(_buffer, _tmpbuf, _len);

			// Increase length
			_len += 0x8000;

			// Free temponary buffer
			delete[] _tmpbuf;
		}

		// This function is only used when we're reading files.
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

		// This function is only used when we're writing files.
		void Flush()
		{
			// flush data to disk
			std::ostream _os(&_fb);
			_os.write(_buffer, _pos);
		}

		// This function is only used when we're reading/writing files to disk.
		void Close()
		{
			_fb.close();
		}
	};
}
