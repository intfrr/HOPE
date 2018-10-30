#include "gtest/gtest.h"

#include <assert.h>

#include <bitset>
#include <fstream>
#include <iostream>

#include "hu_tucker_cg.hpp"
#include "symbol_selector_factory.hpp"

namespace ope {

namespace hutuckertest {

static const std::string kFilePath = "../../test/words.txt";
static const int kWordTestSize = 234369;
static std::vector<std::string> words;
static const std::string kEmailFilePath = "../../test/emails.txt";
static const int kEmailTestSize = 25000000;
static std::vector<std::string> emails;
static const std::string kWikiFilePath = "../../test/wikis.txt";
static const int kWikiTestSize = 14000000;
static std::vector<std::string> wikis;
static const std::string kUrlFilePath = "../../test/urls.txt";
static const int kUrlTestSize = 25000000;
static std::vector<std::string> urls;
//static const int kLongestCodeLen = 4096;

class HuTuckerCGTest : public ::testing::Test {
public:
    virtual void SetUp () {}
    virtual void TearDown () {}
};

void print(const std::vector<SymbolCode> &symbol_code_list,
	   const HuTuckerCG* code_generator) {
    for (int i = 0; i < (int)symbol_code_list.size(); i++) {
	int64_t code = symbol_code_list[i].second.code;
	unsigned len = symbol_code_list[i].second.len;
	std::cout << i << ", " << "\t" << len << "\t";
	code <<= (32 - len);
	std::cout << std::bitset<32>(code) << std::endl;
    }
    std::cout << "Compression Rate = "
	      << code_generator->getCompressionRate() << std::endl;
}

TEST_F (HuTuckerCGTest, printSingleCharWordTest) {
    std::vector<SymbolFreq> symbol_freq_list;
    SymbolSelector* symbol_selector = SymbolSelectorFactory::createSymbolSelector(0);
    symbol_selector->selectSymbols(words, 1000, &symbol_freq_list);

    std::vector<SymbolCode> symbol_code_list;
    HuTuckerCG* code_generator = new HuTuckerCG();
    code_generator->genCodes(symbol_freq_list, &symbol_code_list);

    print(symbol_code_list, code_generator);
}

TEST_F (HuTuckerCGTest, printSingleCharEmailTest) {
    std::vector<SymbolFreq> symbol_freq_list;
    SymbolSelector* symbol_selector = SymbolSelectorFactory::createSymbolSelector(0);
    symbol_selector->selectSymbols(emails, 1000, &symbol_freq_list);

    std::vector<SymbolCode> symbol_code_list;
    HuTuckerCG* code_generator = new HuTuckerCG();
    code_generator->genCodes(symbol_freq_list, &symbol_code_list);

    print(symbol_code_list, code_generator);
}

TEST_F (HuTuckerCGTest, printSingleCharWikiTest) {
    std::vector<SymbolFreq> symbol_freq_list;
    SymbolSelector* symbol_selector = SymbolSelectorFactory::createSymbolSelector(0);
    symbol_selector->selectSymbols(wikis, 1000, &symbol_freq_list);

    std::vector<SymbolCode> symbol_code_list;
    HuTuckerCG* code_generator = new HuTuckerCG();
    code_generator->genCodes(symbol_freq_list, &symbol_code_list);

    print(symbol_code_list, code_generator);
}

TEST_F (HuTuckerCGTest, printSingleCharUrlTest) {
    std::vector<SymbolFreq> symbol_freq_list;
    SymbolSelector* symbol_selector = SymbolSelectorFactory::createSymbolSelector(0);
    symbol_selector->selectSymbols(urls, 1000, &symbol_freq_list);

    std::vector<SymbolCode> symbol_code_list;
    HuTuckerCG* code_generator = new HuTuckerCG();
    code_generator->genCodes(symbol_freq_list, &symbol_code_list);

    print(symbol_code_list, code_generator);
}

void loadWords() {
    std::ifstream infile(kFilePath);
    std::string key;
    int count = 0;
    while (infile.good() && count < kWordTestSize) {
	infile >> key;
	words.push_back(key);
	count++;
    }
}
    
void loadEmails() {
    std::ifstream infile(kEmailFilePath);
    std::string key;
    int count = 0;
    while (infile.good() && count < kEmailTestSize) {
	infile >> key;
	emails.push_back(key);
	count++;
    }
}

void loadWikis() {
    std::ifstream infile(kWikiFilePath);
    std::string key;
    int count = 0;
    while (infile.good() && count < kWikiTestSize) {
	infile >> key;
	wikis.push_back(key);
	count++;
    }
}

void loadUrls() {
    std::ifstream infile(kUrlFilePath);
    std::string key;
    int count = 0;
    while (infile.good() && count < kUrlTestSize) {
	infile >> key;
	urls.push_back(key);
	count++;
    }
}

} // namespace hutuckertest

} // namespace ope

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ope::hutuckertest::loadWords();
    ope::hutuckertest::loadEmails();
    ope::hutuckertest::loadWikis();
    ope::hutuckertest::loadUrls();
    return RUN_ALL_TESTS();
}
