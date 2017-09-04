/**
 * @file unit_tests.cpp
 * Unit tests for the AVL tree lab.
 *
 * @author Sean Massung
 * @date Summer 2012
 */

#include <vector>
#include <utility>
#include "avltree.h"
#include "proxy.h"

using namespace std;
using namespace util; // for readFile

#define GENERATE_SOLUTIONS 0

#if GENERATE_SOLUTIONS
#define ASSERT_TREE_EQUALS(output, filename)      \
	do {                                          \
		ofstream fout(string(filename).c_str());  \
		fout << output;                           \
		fout.close();                             \
	} while (0)
#else
#define ASSERT_TREE_EQUALS(output, filename)        \
	do {                                          \
		cout << output;                           \
		ASSERT(output == readFile(filename));     \
	} while (0)
#endif

template <class K, class V>
void runTest(const vector< pair<K, V> > & elems, const string & filename)
{
    AVLTree<K, V> tree;
	stringstream output;

    tree.setOutput(output);
    for(auto elem = elems.begin(); elem != elems.end(); ++elem)
        tree.insert(elem->first, elem->second);

    tree.print(output);
    ASSERT_TREE_EQUALS(output.str(), filename);
}

template <class K, class V>
void runTestRemoval(const vector< pair<K, V> > & elems, const vector< K > & removals, const string & filename)
{
    AVLTree<K, V> tree;
	stringstream output;

    tree.setOutput(output);
    for(auto elem = elems.begin(); elem != elems.end(); ++elem)
        tree.insert(elem->first, elem->second);

    for(auto elem = removals.begin(); elem != removals.end(); ++elem)
        tree.remove(*elem);

    tree.print(output);
    ASSERT_TREE_EQUALS(output.str(), filename);
}

UNIT_TEST(test_oneElement, 0, 8, 1000)
{
    vector< pair<string, string> > elems = { {"herp", "derp"} };
    runTest<string, string>(elems, "soln_oneElement.out");
}

UNIT_TEST(test_simpleRotateLeft, 0, 8, 1000)
{
    vector< pair<string, int> > elems = {
        {"0", 0}, {"1", 1}, {"2", 2}
    };
    runTest<string, int>(elems, "soln_simpleRotateLeft.out");
}

UNIT_TEST(test_simpleRotateRight, 0, 8, 1000)
{
    vector< pair<size_t, string> > elems = {
        {2, "two"}, {1, "one"}, {0, "zero"}
    };
    runTest<size_t, string>(elems, "soln_simpleRotateRight.out");
}

UNIT_TEST(test_threeLeftRotates, 0, 8, 1000)
{
    vector< pair<string, string> > elems = {
        {"10", "10"}, {"12", "12"}, {"21", "21"},
        {"36", "36"}, {"42", "42"}, {"55", "55"}
    };
    runTest<string, string>(elems, "soln_threeLeftRotates.out");
}

UNIT_TEST(test_threeRightRotates, 0, 8, 1000)
{
    vector< pair<int, string> > elems = {
        {5, "5"}, {4, "4"}, {3, "3"},
        {2, "2"}, {1, "1"}, {0, "0"}
    };
    runTest<int, string>(elems, "soln_threeRightRotates.out");
}

UNIT_TEST(test_manyRotations, 0, 17, 1000)
{
    vector< pair<int, string> > elems = {
        {0, "0"}, {5, "5"}, {1, "1"},
        {4, "4"}, {2, "2"}, {3, "3"}
    };
    runTest<int, string>(elems, "soln_manyRotations.out");
}

UNIT_TEST(test_manyInserts, 0, 17, 1000)
{
    vector< pair<size_t, string> > elems = {
        { 55, "" }, { 45, "" }, { 12, "" }, { 34, "" },
        { 56, "" }, { 46, "" }, { 13, "" }, { 35, "" },
        { 57, "" }, { 47, "" }, { 14, "" }, { 36, "" },
        { 58, "" }, { 48, "" }, { 15, "" }, { 37, "" }
    };
    runTest<size_t, string>(elems, "soln_manyInserts.out");
}

UNIT_TEST(test_manyRemovals, 0, 17, 1000)
{
    vector< pair<int, string> > elems = {
        {94, ""}, {87, ""}, {61, ""},
        {96, ""}, {76, ""}, {92, ""},
        {42, ""}, {78, ""}, {17, ""},
        {11, ""}, {41, ""}, {95, ""},
        {36, ""}, {26, ""}, {23, ""},
        {93, ""}, {31, ""}, {3, ""},
        {45, ""}, {18, ""}, {73, ""},
        {24, ""}, {74, ""}, {1, ""},
        {71, ""}, {82, ""}
    };
    vector< int > removals = { 95, 94, 61, 76, 73, 71 };
    runTestRemoval(elems, removals, "soln_manyRemovals.out");
}

VALGRIND_TEST(test_valgrind, 0, 9, 5000)
{
    vector< pair<size_t, string> > elems = {
        { 55, "1" }, { 45, "1" }, { 12, "1" }, { 34, "1" },
        { 56, "1" }, { 46, "1" }, { 13, "1" }, { 35, "1" },
        { 57, "1" }, { 47, "1" }, { 14, "1" }, { 36, "1" },
        { 58, "1" }, { 48, "1" }, { 15, "1" }, { 37, "1" }
    };

    AVLTree<size_t, string> tree;
     
    for(auto elem = elems.begin(); elem != elems.end(); ++elem)
        tree.insert(elem->first, elem->second);

    ASSERT(tree.find(55) == "1");
    ASSERT(tree.find(15) == "1");
    ASSERT(tree.find(37) == "1");
}
