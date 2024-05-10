include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
    

add_executable(MathsTest "tests/MathsTest.cpp")
target_link_libraries(MathsTest GTest::gtest_main ctkMaths)

add_executable(DataTest "tests/DataTest.cpp")
target_link_libraries(DataTest GTest::gtest_main ctkDataObjs)

add_executable(FileIOTest "tests/FileIOTest.cpp")
target_link_libraries(FileIOTest GTest::gtest_main ctkDataObjs ctkFileIO)

add_executable(UFFTest "tests/UFFtest.cpp")
target_link_libraries(UFFTest GTest::gtest_main ctkDataObjs ctkFileIO ctkForceField)

include(GoogleTest)
gtest_discover_tests(MathsTest)
gtest_discover_tests(DataTest)
gtest_discover_tests(FileIOTest)
gtest_discover_tests(UFFTest)