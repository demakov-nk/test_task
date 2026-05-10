#include <gtest/gtest.h>
#include "List.hpp"

#include <fstream>

// ==================== Конструкторы ====================

TEST(ListTest, DefaultConstructorCreatesEmptyList) {
    List list;
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, ConstructorWithSize) {
    List list(3, "hello");
    EXPECT_EQ(list.size(), 3);
}

TEST(ListTest, ConstructorWithZeroSize) {
    List list(0);
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, CopyConstructor) {
    List original(2, "copy");
    List copy(original);
    EXPECT_EQ(copy.size(), 2);
}

TEST(ListTest, MoveConstructor) {
    List original(2, "move");
    List moved(std::move(original));
    EXPECT_EQ(moved.size(), 2);
    EXPECT_EQ(original.size(), 0);
}

// ==================== push_back ====================

TEST(ListTest, PushBackIncreasesSize) {
    List list;
    list.push_back("one");
    EXPECT_EQ(list.size(), 1);
    list.push_back("two");
    EXPECT_EQ(list.size(), 2);
}

TEST(ListTest, PushBackLvalue) {
    List list;
    std::string s = "hello";
    list.push_back(s);
    EXPECT_EQ(list.size(), 1);
}

TEST(ListTest, PushBackRvalue) {
    List list;
    list.push_back(std::string("temp"));
    EXPECT_EQ(list.size(), 1);
}

// ==================== push_front ====================

TEST(ListTest, PushFrontIncreasesSize) {
    List list;
    list.push_front("one");
    EXPECT_EQ(list.size(), 1);
    list.push_front("two");
    EXPECT_EQ(list.size(), 2);
}

// ==================== pop_back ====================

TEST(ListTest, PopBackDecreasesSize) {
    List list(3, "elem");
    EXPECT_EQ(list.size(), 3);
    list.pop_back();
    EXPECT_EQ(list.size(), 2);
    list.pop_back();
    EXPECT_EQ(list.size(), 1);
}

TEST(ListTest, PopBackOnEmptyList) {
    List list;
    list.pop_back();
    EXPECT_EQ(list.size(), 0);
}

// ==================== pop_front ====================

TEST(ListTest, PopFrontDecreasesSize) {
    List list(3, "elem");
    list.pop_front();
    EXPECT_EQ(list.size(), 2);
}

TEST(ListTest, PopFrontOnEmptyList) {
    List list;
    list.pop_front();
    EXPECT_EQ(list.size(), 0);
}

// ==================== clear ====================

TEST(ListTest, ClearEmptiesList) {
    List list(5, "data");
    list.clear();
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, ClearOnEmptyList) {
    List list;
    list.clear();
    EXPECT_EQ(list.size(), 0);
}

// ==================== Iterator ====================

TEST(ListTest, BeginEndOnEmptyList) {
    List list;
    EXPECT_EQ(list.begin(), list.end());
}

TEST(ListTest, IterateForward) {
    List list;
    list.push_back("first");
    list.push_back("second");
    list.push_back("third");
    
    auto it = list.begin();
    EXPECT_EQ(*it, "first");
    ++it;
    EXPECT_EQ(*it, "second");
    ++it;
    EXPECT_EQ(*it, "third");
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(ListTest, IterateBackward) {
    List list;
    list.push_back("first");
    list.push_back("second");
    
    auto it = list.end();
    --it;
    EXPECT_EQ(*it, "second");
    --it;
    EXPECT_EQ(*it, "first");
}

TEST(ListTest, ModifyThroughIterator) {
    List list;
    list.push_back("original");
    
    *list.begin() = "modified";
    EXPECT_EQ(*list.begin(), "modified");
}

TEST(ListTest, PostfixIncrement) {
    List list;
    list.push_back("a");
    list.push_back("b");
    
    auto it = list.begin();
    auto old = it++;
    EXPECT_EQ(*old, "a");
    EXPECT_EQ(*it, "b");
}

TEST(ListTest, PostfixDecrement) {
    List list;
    list.push_back("a");
    list.push_back("b");
    
    auto it = list.end();
    auto old = it--;
    
    EXPECT_EQ(*it, "b");
    EXPECT_EQ(old, list.end());
}

// ==================== ConstIterator ====================

TEST(ListTest, ConstBeginEndOnEmptyList) {
    const List list;
    EXPECT_EQ(list.begin(), list.end());
}

TEST(ListTest, ConstIterateForward) {
    List non_const;
    non_const.push_back("one");
    non_const.push_back("two");
    
    const List& list = non_const;
    auto it = list.begin();
    EXPECT_EQ(*it, "one");
    ++it;
    EXPECT_EQ(*it, "two");
}

TEST(ListTest, ConstIteratorDoesNotAllowModification) {
    List non_const;
    non_const.push_back("value");
    
    const List& list = non_const;
    auto it = list.begin();
    // *it = "new";  // не должно скомпилироваться
    EXPECT_EQ(*it, "value");
}

// ==================== Присваивание ====================

TEST(ListTest, CopyAssignment) {
    List original(3, "orig");
    List copy;
    copy = original;
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(original.size(), 3);
}

TEST(ListTest, MoveAssignment) {
    List original(3, "orig");
    List moved;
    moved = std::move(original);
    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(original.size(), 0);
}

TEST(ListTest, SelfAssignment) {
    List list(2, "data");
    list = list;
    EXPECT_EQ(list.size(), 2);
}

// ==================== remove ====================

TEST(ListTest, RemoveExistingElement) {
    List list;
    list.push_back("a");
    list.push_back("b");
    list.push_back("a");
    list.remove("a");
    EXPECT_EQ(list.size(), 2);
}

TEST(ListTest, RemoveNonExistingElement) {
    List list;
    list.push_back("a");
    list.push_back("b");
    list.remove("c");
    EXPECT_EQ(list.size(), 2);
}

TEST(ListTest, RemoveFromEmptyList) {
    List list;
    list.remove("anything");
    EXPECT_EQ(list.size(), 0);
}

// ==================== Краевые случаи ====================

TEST(ListTest, LargeList) {
    List list;
    for (int i = 0; i < 1000; ++i) {
        list.push_back(std::to_string(i));
    }
    EXPECT_EQ(list.size(), 1000);
}

TEST(ListTest, MixedPushFrontBack) {
    List list;
    list.push_back("back1");
    list.push_front("front");
    list.push_back("back2");
    EXPECT_EQ(list.size(), 3);
}

TEST(ListTest, FullCycle) {
    List list;
    list.push_back("one");
    list.push_back("two");
    list.push_back("three");
    list.pop_front();
    list.pop_back();
    list.push_front("new_front");
    EXPECT_EQ(list.size(), 2);
}
