#pragma once

#include <string>
#include <assert.h>
#include <string_view>

/////////////////////////////////////////////////////////////////////////
//Utility to process a line with ease. I have designed and written this//
//"properly" because I intend to improve and build on this and use it  //
//in my other (personal) projects after finishing with this assignment //
/////////////////////////////////////////////////////////////////////////

namespace base {

	enum class it_strategy
	{
		DELIMITER,
		REGEX
	};

	template<it_strategy strategy, class _string_type> struct forward_line_parser;

	template<class _string_type> class forward_line_parser<it_strategy::DELIMITER, _string_type>
	{
	public:
		using string_type = _string_type;

		forward_line_parser(std::basic_string_view<typename string_type::value_type> string,
			std::basic_string_view<typename string_type::value_type> delimiter, std::size_t index) noexcept :
			m_String{ string }, m_Delimiter{ delimiter }, m_Index{ index }
		{
		}

	public:
		void reset() noexcept { m_Index = 0; }
		bool has_next() const noexcept { return hasNext; }

		std::basic_string_view<typename string_type::value_type> substr
		(const std::pair<std::size_t, std::size_t>& p) const
		{
			return m_String.substr(p.first, p.second);
		}

		//returns the next word in the line. Words are seperated depending on the
		//type of the delimiter provided.
		//for no value in between delimiters, it will return an empty string.
		//This is by design to let the users know that to that there  is a 
		//"field" there, but it just happens to be empty.
		std::pair<std::size_t, std::size_t> next() noexcept
		{
			//for end(), dont do any calculations.
			if (m_Index == m_String.length())
				return { m_Index, m_String.length() - 1 };

			//get next word and return it
			std::size_t previousIndex;
			if (next_word(previousIndex))
				return { previousIndex, m_String.length() - 1 };
			return { previousIndex, m_Index - previousIndex - m_Delimiter.length() };
		}

	private:
		//increments m_Index such that it lands at the beginning of the next word.
		//previous_index is the value of m_Index before the increment
		//returns whether it has reached the end of sentence after the increment
		//end reached = returns true. not reached = returns false
		bool next_word(std::size_t& previousIndex) noexcept
		{
			std::size_t newIndex = m_String.find(m_Delimiter, m_Index);
			previousIndex = m_Index;
			if (newIndex == m_String.npos)
			{
				m_Index += m_String.length() - previousIndex;
				hasNext = true;
				return true;
			}
			m_Index = newIndex + m_Delimiter.length();
			hasNext = false;
			return false;
		}

	private:
		std::size_t m_Index{};
		bool hasNext = true;
		std::basic_string_view<typename string_type::value_type> m_String;
		std::basic_string_view<typename string_type::value_type> m_Delimiter;
	};

	//Not sure how I want to implement this yet
	template<class _string_type> class forward_line_parser<it_strategy::REGEX, _string_type>
	{
	};

	//Class to convenitently parse, read and modify a line
	template<it_strategy delimiter, std::size_t preallocation_size, class _string_type>
	class basic_plain_line
	{
	public:
		using string_type = _string_type;

		basic_plain_line()
		{
			m_WriteBuffer.reserve(preallocation_size);
		}

		basic_plain_line(std::string& line, const std::string& delimiter) :
			m_Line{ line }, m_Delimiter{ delimiter }
		{
			m_WriteBuffer.reserve(preallocation_size);
		}

		basic_plain_line(const basic_plain_line&) = delete;
		basic_plain_line& operator=(const basic_plain_line&) = delete;

	public:
		//Iterators
		// On dereference - 
		//Retrun a pair with the first value being index to the first character in the word.
		//second value is the length of the word
		class forward_iterator
		{
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = std::pair<std::size_t, std::size_t>;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;

		public:
			forward_iterator(std::basic_string_view<typename string_type::value_type> string,
				std::basic_string_view<typename string_type::value_type> delimiter, std::size_t index) noexcept :
				m_Parser{ string, delimiter, index }
			{
				m_Index = m_Parser.next();
			}

		public:
			const reference operator*() noexcept { return m_Index; }
			forward_iterator& operator++() noexcept { m_Index = m_Parser.next(); return *this; }
			forward_iterator operator++(int) noexcept { forward_iterator val = *this; ++(*this); return val; }
			bool operator==(forward_iterator other) const noexcept { return m_Index.first == other.m_Index.first; }
			bool operator!=(forward_iterator other) const noexcept { return !(*this == other); }
			std::basic_string_view<typename string_type::value_type> str() const noexcept { return m_Parser.str(); }

		private:
			forward_line_parser<delimiter, string_type> m_Parser;
			std::pair<std::size_t, std::size_t> m_Index;
		};

		// On dereference - 
		//Retrun a string view of the word
		class const_forward_iterator
		{
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = std::basic_string_view<typename string_type::value_type>;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;

		public:
			const_forward_iterator(std::basic_string_view<typename string_type::value_type> string,
				std::basic_string_view<typename string_type::value_type> delimiter, std::size_t index) noexcept :
				m_Parser{ string, delimiter, index }
			{
				m_Index = m_Parser.next();
			}

		public:
			const value_type operator*() const noexcept { return m_Parser.substr(m_Index); }
			const_forward_iterator& operator++() noexcept { m_Index = m_Parser.next(); return *this; }
			const_forward_iterator operator++(int) noexcept { const_forward_iterator val = *this; ++(*this); return val; }
			bool operator==(const_forward_iterator other) const noexcept { return m_Index.first == other.m_Index.first; }
			bool operator!=(const_forward_iterator other) const noexcept { return !(*this == other); }

		private:
			forward_line_parser<delimiter, string_type> m_Parser;
			std::pair<std::size_t, std::size_t> m_Index;
		};

		const_forward_iterator cbegin() const noexcept { return const_forward_iterator{ m_Line, m_Delimiter, 0 }; }
		const_forward_iterator cend() const noexcept { return const_forward_iterator{ m_Line, m_Delimiter, m_Line.length() }; }
		forward_iterator begin() noexcept { return forward_iterator{ m_Line, m_Delimiter, 0 }; }
		forward_iterator end() noexcept { return forward_iterator{ m_Line, m_Delimiter, m_Line.length() }; }

	public:
		void set_delimeter(const string_type& d) noexcept { m_Delimiter = d; }
		//has to be a reference since we store its std::string_view
		void set_string(string_type& s) noexcept { m_Line = s; }

		void writebuffer_append_it(const const_forward_iterator& it)
		{
			if (!m_WriteBuffer.empty())
				m_WriteBuffer += m_Delimiter;
			m_WriteBuffer += *it;
		}

		void writebuffer_append_it(const forward_iterator& it)
		{
			if (!m_WriteBuffer.empty())
				m_WriteBuffer += m_Delimiter;
			std::basic_string_view<typename string_type::value_type> str = it.str();
			m_WriteBuffer += str.substr((*it).first, (*it).second);
		}

		void writebuffer_append(std::basic_string_view<typename string_type::value_type> word)
		{
			if (!m_WriteBuffer.empty())
				m_WriteBuffer += m_Delimiter;
			m_WriteBuffer.append(word);
		}

		void writebuffer_append_raw(std::basic_string_view<typename string_type::value_type> word)
		{
			m_WriteBuffer.append(word);
		}

		const string_type& get_write_buffer() const noexcept { return m_WriteBuffer; }

		void clear_write_buffer() noexcept { m_WriteBuffer.clear(); }

		std::basic_string_view<typename string_type::value_type> ltrim
		(std::basic_string_view<typename string_type::value_type> s)
		{
			std::basic_string_view<typename string_type::value_type> out = s;
			auto it = std::find_if(out.begin(), out.end(),
				[](char ch)
				{
					return !std::isspace(ch);
				});
			return out.substr(it - out.begin(), out.length() - (it - out.begin()));
		}

		std::basic_string_view<typename string_type::value_type> rtrim
		(std::basic_string_view<typename string_type::value_type> s)
		{
			std::basic_string_view<typename string_type::value_type> out = s;
			auto it = std::find_if(out.rbegin(), out.rend(),
				[](char ch)
				{
					return !std::isspace(ch);
				});
			return out.substr(0, out.length() - (it - out.rbegin()));
		}

		std::basic_string_view<typename string_type::value_type> trim
		(std::basic_string_view<typename string_type::value_type> s)
		{
			return rtrim(ltrim(s));
		}

		void set_token(const std::string& token) { m_Token = token; }

	private:
		string_type m_WriteBuffer;
		string_type m_Token;
		std::basic_string_view<typename string_type::value_type> m_Line{};
		string_type m_Delimiter;
	};

	template<it_strategy strategy, std::size_t size = 0>
	using plain_line = basic_plain_line<strategy, size, std::string>;
}