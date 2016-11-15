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
		std::filebuf				_fb;
		std::unique_ptr <char[]>	_buffer;
		std::size_t					_pos;
		std::size_t					_len;

	public:
		DatabaseBuffer(std::string filename, int mode, size_t size)
		{
			_pos = 0;
			_len = size;
			
			// open file buffer
			_fb.open(filename, mode);

			// alloc buffer
			if (size) _buffer = std::make_unique<char[]>(size);
		}
		DatabaseBuffer(const void *memory, size_t size)
		{
			_pos = 0;
			_len = size;

			// Copy memory
			_buffer = std::make_unique<char[]>(size);
			memcpy(_buffer.get(), memory, size);
		}

		void Realloc()
		{
			// Alloc a temp buffer to copy over existing data
			auto _tmpbuf = std::make_unique<char[]>(this->_len);

			// Copy old data
			memcpy(_tmpbuf.get(), _buffer.get(), this->_len);

			// Allocate new buffer
			_buffer = std::make_unique<char[]>(this->_len + 0x10000);

			// Copy data
			memcpy(_buffer.get(), _tmpbuf.get(), this->_len);

			// Increase length
			this->_len += 0x10000;
		}

		// Write functions
		template <typename T> void Write(T val)
		{
			// Reallocate buffer before attempting to write
			if (_pos + sizeof(T) >= this->_len)
				this->Realloc();

			// Write variable into buffer
			*(T*)(_buffer.get() + _pos) = val;
			_pos += sizeof(T);
		}
		void WriteStr(std::string str)
		{
			// Reallocate buffer before attempting to write
			if (_pos + str.size() + 1 >= this->_len)
				this->Realloc();

			// Write string into buffer
			strcpy((char*)(_buffer.get() + _pos), str.c_str());
			_pos += str.size() + 1;
		}
		template <typename T> T Read()
		{
			// Read variable from buffer
			T val = *(T*)(_buffer.get() + _pos);
			_pos += sizeof(T);

			return val;
		}
		std::string ReadStr()
		{
			// Read string from buffer
			std::string val((char*)(_buffer.get() + _pos));
			_pos += val.size() + 1;

			return val;
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

			// Alloc buffer
			_buffer = std::make_unique<char[]>(fsize);

			// Read to buffer
			_is.read(_buffer.get(), fsize);
		}

		// This function is only used when we're writing files.
		void Flush()
		{
			// flush data to disk
			std::ostream _os(&_fb);
			_os.write(_buffer.get(), _pos);
			_os.clear();
		}

		// This function is only used when we're reading/writing files to disk.
		void Close()
		{
			_fb.close();
		}
	};
}
