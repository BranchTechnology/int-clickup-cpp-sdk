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
    cout << o << endl;
}

TEST_CASE_METHOD(ClickUpFixture, "async test getting a folderless list", "[clickup.cpp]")
{
  auto o = std::async( [&]() {
    return clickup.GetFolderlessList("54005663");
  });
  cout << o.get() << endl;
}

TEST_CASE_METHOD(ClickUpFixture, "test getting folders", "[clickup.cpp]")
{
    auto o = clickup.GetFolders("54005663");
    cout << o << endl;
}

TEST_CASE_METHOD(ClickUpFixture, "test getting tasks", "[clickup.cpp]")

{
    auto o = clickup.GetTasksByListId("54005663", GetTasksByListIdOptions());
    cout << o << endl;
}

TEST_CASE_METHOD(ClickUpFixture, "test creating a task in list", "[clickup.cpp]")
{
    auto t = R"({
    "name": "sdf"
  })";
    auto j = nlohmann::json::parse(t);

    auto o = clickup.CreateTaskInList("54005663", j);
    cout << o << endl;
}

TEST_CASE_METHOD(ClickUpFixture, "test adding a task to a list", "[clickup.cpp]")

{
    auto o = clickup.AddTaskToList("156038738", "1p051y3");
    cout << o << endl;
}

TEST_CASE_METHOD(ClickUpFixture, "test getting a list of custom fields", "[clickup.cpp]")

{
    auto o = clickup.GetListCustomFields("156038738");
    cout << o << endl;
}

TEST_CASE_METHOD(ClickUpFixture, "test getting a task by id", "[clickup.cpp]")
{
    auto o = clickup.GetTaskById("1p051y3");
    cout << o << endl;
}
