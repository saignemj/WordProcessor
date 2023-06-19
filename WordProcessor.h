#pragma once

#include <vector>
#include <string>
#include <filesystem>

namespace jsa
{
	using words = std::vector< std::string >;
	class WordProcessor
	{
	public:
		WordProcessor() = default;
		virtual ~WordProcessor() = default;

	public:
		// load words from a file containing a string per line
		bool load(const std::filesystem::path& _path);
		enum class SortingOption { Ascending, Descending };
		// sort and/or remove duplicate words
		void process(SortingOption _sort, bool _removeDuplicates);
		// for display purposes
		void print() const;
		// get words at any state (before or after processing)
		const words & get() const;

	private:
		words m_words;
	};
}
