mkdir -p BuildTests
cd BuildTests
cmake ../Library/Tests
make
./run_tests
cd ..
gcovr BuildTests/CMakeFiles/run_tests.dir/ -r Library/openApp/