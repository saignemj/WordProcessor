#include "WordProcessor.h"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace jsa
{
	bool WordProcessor::load(const std::filesystem::path& _path)
	{
		m_words.clear();
		if (!std::filesystem::exists(_path))
			return false;
		std::ifstream file{ _path.string() };
		if (!file.good())
			return false;
		std::string line;
		while (std::getline(file, line)){
			if (line.empty())
				continue;
			m_words.emplace_back(line);
		}
		return true;
	}

	void WordProcessor::process(SortingOption _sortingOpt, bool _removeDuplicates)
	{
		if(_sortingOpt == SortingOption::Ascending)
			std::sort(m_words.begin(), m_words.end(), [](const auto& _first, const auto& _second) { return _first < _second; });
		else if(_sortingOpt == SortingOption::Descending)
			std::sort(m_words.begin(), m_words.end(), [](const auto& _first, const auto& _second) { return _first > _second; });
		
		// list is sorted so we can remove duplicates using std::unique
		if (_removeDuplicates)
			m_words.erase(std::unique(m_words.begin(), m_words.end()), m_words.end());
	}

	void WordProcessor::print() const
	{
		for (const auto& word : m_words)
			std::cout << word << std::endl;
	}

	const words & WordProcessor::get() const
	{
		return m_words;
	}
}
