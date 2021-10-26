#ifdef _WIN32
#define _HAS_STD_BYTE 0
#endif
#include <clickup/clickup.h>
#include <catch2/catch.hpp>
#include <iostream>
#include <map>
#include <future>

using namespace std;

static inline std::string GetEnvVal(const std::string &var, std::string def)
{
    auto val = std::getenv(var.c_str());
    //        cout << val << endl;
    if (val == nullptr) {
        return def;
    } else {
        return std::string(val);
    }
}

class ClickUpFixture
{
private:
public:
    clickup clickup;

    static std::string connect() { return GetEnvVal("ACCESS_TOKEN", "null"); }
    ClickUpFixture() : clickup(connect()) {}
};

TEST_CASE_METHOD(ClickUpFixture, "test getting a folderless list", "[clickup.cpp]")
{
    auto o = clickup.GetFolderlessList("54005663");
    REQUIRE(o["respUrl"] == "https://api.clickup.com/api/v2/space/54005663/list");
}

TEST_CASE_METHOD(ClickUpFixture, "async test getting a folderless list", "[clickup.cpp]")
{
  auto o = std::async( [&]() {
    return clickup.GetFolderlessList("54005663");
  });
  REQUIRE(o.get()["respUrl"] == "https://api.clickup.com/api/v2/space/54005663/list");
}

TEST_CASE_METHOD(ClickUpFixture, "test getting folders", "[clickup.cpp]")
{
    auto o = clickup.GetFolders("54005663");
    REQUIRE(o["respUrl"] == "https://api.clickup.com/api/v2/space/54005663/folder");
}


TEST_CASE_METHOD(ClickUpFixture, "test getting tasks with options", "[clickup.cpp]")
{
  SECTION("test no options", "[clickup.cpp]" )
  {
    auto o = clickup.GetTasksByListId("156038738", GetTasksByListIdOptions());
    REQUIRE(o["respUrl"] == "https://api.clickup.com/api/v2/list/156038738/task");
  }
  SECTION("test archive boolean", "[clickup.cpp]" )
  {
    auto o = clickup.GetTasksByListId("156038738", GetTasksByListIdOptions(true));
    REQUIRE(o["respUrl"] == "https://api.clickup.com/api/v2/list/156038738/task?archived=true");
  }

  SECTION("test page number", "[clickup.cpp]" )
  {
    auto o = clickup.GetTasksByListId("156038738", GetTasksByListIdOptions(false, 2));
    REQUIRE(o["respUrl"] == "https://api.clickup.com/api/v2/list/156038738/task?page=2");
  }
  SECTION("test closed boolean", "[clickup.cpp]" )
  {
    auto o = clickup.GetTasksByListId("156038738", GetTasksByListIdOptions(false, -1, true));
    cout << o << endl;
    REQUIRE(o["respUrl"] == "https://api.clickup.com/api/v2/list/156038738/task?include_closed=true");
  }
  SECTION("test all options", "[clickup.cpp]" )
  {
    auto o = clickup.GetTasksByListId("156038738", GetTasksByListIdOptions(true, 2, true));
    cout << o << endl;
    REQUIRE(o["respUrl"] == "https://api.clickup.com/api/v2/list/156038738/task?archived=true&page=2&include_closed=true");
  }
}

TEST_CASE_METHOD(ClickUpFixture, "test creating a task in list", "[clickup.cpp]")
{
    auto t = R"({
    "name": "ljlklk"
  })";
    auto j = nlohmann::json::parse(t);

    auto o = clickup.CreateTaskInList("156038738", j);
    cout << o << endl;
    REQUIRE(o["respUrl"] == "https://api.clickup.com/api/v2/list/156038738/task");
}

TEST_CASE_METHOD(ClickUpFixture, "test adding a task to a list", "[clickup.cpp]")

{
    auto o = clickup.AddTaskToList("156038738", "1p051y3");
    cout << o << endl;

    REQUIRE(o["respUrl"] == "https://api.clickup.com/api/v2/list/156038738/task/1p051y3");
}

TEST_CASE_METHOD(ClickUpFixture, "test getting a list of custom fields", "[clickup.cpp]")

{
    auto o = clickup.GetListCustomFields("156038738");
    cout << o << endl;
    REQUIRE(o["respUrl"] == "https://api.clickup.com/api/v2/list/156038738/field");
}

TEST_CASE_METHOD(ClickUpFixture, "test getting a task by id", "[clickup.cpp]")
{
    auto o = clickup.GetTaskById("1p051y3");
  REQUIRE(o["respUrl"] == "https://api.clickup.com/api/v2/task/1p051y3");
}
