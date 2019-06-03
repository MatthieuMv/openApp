mkdir -p Build
cd Build
cmake ../Library/Tests
make
./run_tests
cd ..
gcovr --exclude Library/Tests