mkdir -p BuildTests
cd BuildTests
cmake ../Library/Tests
make
./run_tests
cd ..
echo "Starting GCOVR"
gcovr --exclude Library/Tests