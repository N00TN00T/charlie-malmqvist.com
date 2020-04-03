#include <iostream>
#include <string>
#include <array>
#include <string>
#include <sstream>
#include <set>

typedef std::string string;

// Custom assert macro, as the one from assert.h header doesn't have an error message argument
#define ASSERT(x, msg) if (!(x)) { std::cout << "\nAssertion failed! " << msg << "\n"; abort(); }

// Simple struct to group the text and denominator
struct Word
{
    Word(const string& text, int printDenominator) : text(text), printDenominator(printDenominator) {}

    string text;
    int printDenominator;
};

// A simple class that plays the fizzbuzz game, but has an option to create a modified verison of it
template <int WORD_COUNT>
class FizzBuzzer
{
public:

    // Default constructor overload - initializes with the classic fizzbuzz rules
    FizzBuzzer()
    {
        m_words = { Word("Fizz", 3), Word("Buzz", 5) };
        m_printAllDenominator = 15;
        m_fullWord = "FizzBuzz";
    }

    // Overload constructor to create a custom version off the fizzbuzz game
    FizzBuzzer(const std::array<Word, WORD_COUNT>& words, int printAllDenominator)
        : m_words(words), m_printAllDenominator(printAllDenominator)
    {
        m_fullWord = "";

        // Put all denominators in a set to detect duplicates
        std::set<int> denominators;
        denominators.emplace(printAllDenominator);

        // Add the summ of all words into m_fullWord
        for (int i = 0; i < WORD_COUNT; i++)
        {
            // Assert that there are no duplicates
            bool first = denominators.emplace(words[i].printDenominator).second;
            ASSERT(first, "Denominator dupicate!");

            m_fullWord += words[i].text;
        }
    }

    // Play the fizzbuzz game for given iterations
    string DoFizzBuzz(int iterations)
    {
        std::stringstream ss;
        for (int i = 1; i < iterations; i++)
        {
            if (i % m_printAllDenominator == 0)
            {
                ss << m_fullWord << "\n";
            }
            else
            {
                PrintWordForIndex(ss, i);
            }
        }

        return ss.str();
    }

private:
    // print the word that should be at given index
    void PrintWordForIndex(std::stringstream& ss, int index)
    {
        bool match = false;
        for (int i = 0; i < WORD_COUNT; i++)
        {
            if (index % m_words[i].printDenominator == 0)
            {
                ss << m_words[i].text;
                match = true;
                break;
            }
        }
        if (!match) ss << index;
        ss << "\n";
    }

private:
    std::array<Word, WORD_COUNT> m_words; // Rhe words to be used in the game
    string m_fullWord; // The summary of all words
    int m_printAllDenominator; // The denominator of which the full word should be printed
};

int main()
{
    FizzBuzzer<2> classicFizzBuzzer({ Word("Fizz", 3), Word("Buzz", 5) }, 15);

    string classicResult = classicFizzBuzzer.DoFizzBuzz(100);

    FizzBuzzer<3> newFizzBuzzer({ Word("Harf", 3), Word("Buzz", 5), Word("Fizz", 10) }, 23);

    string newResult = newFizzBuzzer.DoFizzBuzz(100);

    std::cout << "====================CLASSIC====================\n";
    std::cout << classicResult << "\n";
    std::cout << "====================NEW====================\n";
    std::cout << newResult << "\n";

    return 0;
}
