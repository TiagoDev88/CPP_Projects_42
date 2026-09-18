#include "../inc/Span.hpp"
#include <climits>
#include <cstdlib>
#include <list>

static void title(const std::string& name)
{
    std::cout << "\n=== " << name << " ===" << std::endl;
}

static void printSpans(const Span& sp)
{
    try
    {
        std::cout << "shortest: " << sp.shortestSpan() << std::endl;
        std::cout << "longest:  " << sp.longestSpan() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main()
{
    title("Subject example");
    {
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        printSpans(sp);
    }

    title("Span full");
    {
        Span sp(2);
        try
        {
            sp.addNumber(1);
            sp.addNumber(2);
            sp.addNumber(3);
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    title("Not enough numbers (0 and 1)");
    {
        Span sp(5);
        printSpans(sp);
        sp.addNumber(42);
        printSpans(sp);
    }

    title("Extremes (INT_MIN, INT_MAX)");
    {
        Span sp(2);
        sp.addNumber(INT_MIN);
        sp.addNumber(INT_MAX);
        printSpans(sp);
    }

    title("Duplicates and negatives");
    {
        Span sp(4);
        sp.addNumber(5);
        sp.addNumber(5);
        sp.addNumber(-10);
        sp.addNumber(20);
        printSpans(sp);
    }

    title("addMultipleNumbers: 10000 sorted numbers (expects 3 and 29997)");
    {
        std::vector<int> in;
        for (unsigned int i = 0; i < 10000; i++)
            in.push_back(i * 3);

        Span sp(10000);
        sp.addMultipleNumbers(in.begin(), in.end());
        printSpans(sp);
    }

    title("addMultipleNumbers: 20000 random numbers");
    {
        std::vector<int> in;
        for (unsigned int i = 0; i < 20000; i++)
            in.push_back(std::rand());

        Span sp(20000);
        sp.addMultipleNumbers(in.begin(), in.end());
        printSpans(sp);
    }

    title("addMultipleNumbers: other container (list)");
    {
        std::list<int> l;
        l.push_back(1);
        l.push_back(100);
        l.push_back(50);

        Span sp(3);
        sp.addMultipleNumbers(l.begin(), l.end());
        printSpans(sp);
    }

    title("addMultipleNumbers: range bigger than capacity");
    {
        std::vector<int> in(10, 7); // 10 elements with value 7.
        Span sp(5);
        try
        {
            sp.addMultipleNumbers(in.begin(), in.end());
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "nothing was inserted:" << std::endl;
        printSpans(sp);
    }

    title("Copy is independent");
    {
        Span a(3);
        a.addNumber(1);
        a.addNumber(10);

        Span b(a);
        b.addNumber(100);

        std::cout << "a:" << std::endl;
        printSpans(a);
        std::cout << "b:" << std::endl;
        printSpans(b);
    }
    return 0;
}
