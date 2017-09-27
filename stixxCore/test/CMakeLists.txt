file(GLOB_RECURSE tests *.cpp *.hpp mocks/*)
add_executable(StixxMicroTests ${tests})

target_include_directories(StixxMicroTests
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(StixxMicroTests StixxCore gtest gmock)
install(TARGETS StixxMicroTests DESTINATION bin)
