#include "gtest/gtest.h"
#include "WordProcessor.h"
#include <string_view>

// arguments parser
namespace parser {
    static std::string getOption(const std::vector<std::string>& args, const std::string& option_name) {
        const auto findArg{ std::find_if(args.begin(), args.end(), [&option_name](const auto& _val) { return _val == option_name; }) };
        if (findArg != args.end() && findArg + 1 != args.end())
            return *(findArg + 1);
        return "";
    }
    static bool hasOption(const std::vector<std::string>& args, const std::string& option_name) {
        const auto findArg{ std::find_if(args.begin(), args.end(), [&option_name](const auto& _val) { return _val == option_name; }) };
        return findArg != args.end();
    }
}

// simple application
int main(int argc, char**argv)
{
    const std::vector<std::string> args(argv + 1, argv + argc);
    const auto fileName{ parser::getOption(args, "-f") };
    const auto sortingOption{ parser::getOption(args, "-s") };
    const auto removeDuplicates{ parser::hasOption(args, "-rd") };

    if( fileName.empty() || sortingOption.empty() ){
        std::cerr << "usage: -f <input_file> -s <sorting_option: asc or desc> -rd..." << std::endl;
        return -1;
    }

    jsa::WordProcessor words;
    words.load(fileName);
    words.process(sortingOption == "asc" ? jsa::WordProcessor::SortingOption::Ascending : jsa::WordProcessor::SortingOption::Descending, removeDuplicates);
    words.print();
}

// to run tests, comment main above and uncomment below
//int main(int argc, char** argv)
//{
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}
