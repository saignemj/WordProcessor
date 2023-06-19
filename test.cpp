#include "gtest/gtest.h"
#include "WordProcessor.h"

class WordProcessorTest : public ::testing::Test
{
protected:
	WordProcessorTest() = default;
	virtual ~WordProcessorTest() = default;
	
	void SetUp() override {
		ASSERT_TRUE(words.load("test_data.txt"));
	}
	void TearDown() override {
	}
	
protected:
	jsa::WordProcessor words;
};

TEST_F(WordProcessorTest, load) {
	EXPECT_FALSE(words.load("fake_path"));
	EXPECT_TRUE(words.get().empty());
	ASSERT_TRUE(words.load("test_data.txt"));
	const std::vector< std::string > expectedWords = { "Pam", "Dwight", "Jim", "Jim" };
	EXPECT_EQ(expectedWords, words.get());
}

TEST_F(WordProcessorTest, ascending_with_duplicates) {
	const std::vector< std::string > expectedWords = { "Dwight", "Jim","Jim", "Pam" };
	words.process(jsa::WordProcessor::SortingOption::Ascending, false);
	EXPECT_EQ(expectedWords, words.get());
}

TEST_F(WordProcessorTest, descending_with_duplicates) {
	const std::vector< std::string > expectedWords = { "Pam", "Jim", "Jim", "Dwight" };
	words.process(jsa::WordProcessor::SortingOption::Descending, false);
	EXPECT_EQ(expectedWords, words.get());
}

TEST_F(WordProcessorTest, descending_without_duplicates) {
	const std::vector< std::string > expectedWords = { "Pam", "Jim", "Dwight" };
	words.process(jsa::WordProcessor::SortingOption::Descending, true);
	EXPECT_EQ(expectedWords, words.get());
}
