mkdir -p BuildTests
cd BuildTests
cp -r ../Library/Tests/TestMedias TestMedias
cmake ../Library/Tests
make
./run_tests
cd ..
echo "Starting GCOVR"
gcovr --exclude Library/Tests