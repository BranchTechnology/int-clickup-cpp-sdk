#include <aws/s3/model/PutObjectRequest.h>
#include <clickupS3/clickupS3.h>
#include <config_clickup.h>

#include <catch2/catch.hpp>
#include <fstream>
#include <iostream>
#include <map>

class S3Fixture
{
private:
    inline std::string GetEnvVal(const std::string &var, std::string def)
    {
        auto val = std::getenv(var.c_str());
        if (val == nullptr) {
            return def;
        } else {
            return val;
        }
    }

public:
    clickupS3 clickup;
    std::string bucket = "cambia-project-test2";
    std::string objectName = "test/test3/input.stp";

    clickupS3 connect()
    {
        std::string host = GetEnvVal("S3HOST", "127.0.0.1:4566");
        return clickupS3("us-east-1", host);
    }
    S3Fixture() : clickup(connect()) {}
};

TEST_CASE_METHOD(S3Fixture, "Test_creating a bucket", "[clickup.cpp]")
{
    REQUIRE_NOTHROW(clickup.CreateBucket(bucket));

    // local stack improperly mocks the list bucket implementation of s3...
    // auto buckets = clickup.ListBuckets();
    // bool valid = false;
    // for (const auto& i: buckets){
    //     std::cout << "found bucket" << i.GetName() <<std::endl;
    //     if(i.GetName() == bucket.c_str()) {
    //         valid = true;

    //     }
    // }
    // REQUIRE(valid);
}

TEST_CASE_METHOD(S3Fixture, "Test creating a signed url for download", "[clickup.cpp]")
{
    auto t = clickup.CreatePresignedUrl(bucket, "test/test/input.stp");
    REQUIRE(t.length() > 0);
    std::cout << t << std::endl;
}

TEST_CASE_METHOD(S3Fixture, "Test_putting_a_file_in_s3", "[clickup.cpp]")
{
    const std::string dir = SOURCE_DIR;
    const std::string fileName = dir + "/test/test_data/aaa.stp";
    // push the object
    REQUIRE_NOTHROW(clickup.PutFile(bucket, objectName, fileName));
}

TEST_CASE_METHOD(S3Fixture, "Test putting a bunch of files in s3", "[clickup.cpp]")
{
    const std::string dir = SOURCE_DIR;
    const std::string fileName = dir + "/test/test_data/aaa.stp";

    std::map<std::string, std::string> files{
            {"test/test/0",fileName},
            {"test/test/1",fileName},
            {"test/test/2",fileName}
    };
    // push the object
    REQUIRE_NOTHROW(clickup.PutObjectsAsync(bucket, files));
}

TEST_CASE_METHOD(S3Fixture, "Test_getting_a_file_from_s3", "[clickup.cpp]")
{
    REQUIRE_NOTHROW(clickup.GetObject(bucket, objectName));
}

TEST_CASE_METHOD(S3Fixture, "Test_downloading_a_file_from_s3", "[clickup.cpp]")
{
    REQUIRE_NOTHROW(clickup.DownloadFile(bucket, objectName, "./test.scs"));
}

TEST_CASE_METHOD(S3Fixture, "Test_putting_a_buffer_in_s3", "[clickup.cpp]")
{
    std::string dir = SOURCE_DIR;
    std::string file = dir + "/test/test_data/aaa.stp";

    std::shared_ptr<Aws::IOStream> input_data =
        Aws::MakeShared<Aws::FStream>("SampleAllocationTag", file.c_str(), std::ios_base::in | std::ios_base::binary);

    REQUIRE_NOTHROW(clickup.PutObject(bucket, objectName, input_data));
    REQUIRE_NOTHROW(clickup.GetObject(bucket, objectName));
}

// TEST_CASE_METHOD(S3Fixture, "Test_listing_buckets_s3", "[clickup.cpp]")
// {
// local stack sucks
//     REQUIRE_NOTHROW(clickup.ListBuckets());
// }
