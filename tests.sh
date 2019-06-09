mkdir -p BuildTests
cd BuildTests
cmake ../Library/Tests
make
./run_tests
cd ..
gcovr -r . --exclude Library/Tests