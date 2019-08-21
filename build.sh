mkdir -p Build
cd Build
cmake ../Library
make
cd ..
cp Build/libopenApp.* Library