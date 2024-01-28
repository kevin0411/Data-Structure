#include <catch2/catch_test_macros.hpp>
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.

TEST_CASE("My Test Case", "") {
    bool student_wrote_test_case = false;

    List<int> list;
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    list.insertBack(4);
    list.insertBack(5);
    list.insertBack(6);
    for(List<int>::ListIterator debug = list.begin(); debug!=list.end();++debug){
        std::cout << *debug << " ";
    }
    std::cout << " " << std::endl;
    list.reverse();
    for(List<int>::ListIterator debug = list.begin(); debug!=list.end();++debug){
        std::cout << *debug << " ";
    }
    std::cout << " " << std::endl;
    list.reverse();
    list.reverseNth(3);
    for(List<int>::ListIterator debug = list.begin(); debug!=list.end();++debug){
        std::cout << *debug << " ";
    }
    REQUIRE( student_wrote_test_case );
}
