mkdir -p Build
cd Build
cmake ../Library/openApp
make
cd ..
cp Build/libopenApp.* Library