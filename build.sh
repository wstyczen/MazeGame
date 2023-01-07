git submodule update --init

if [[ ! -d "build" ]]; then mkdir build; fi
cd build

if [[ ! -d "debug" ]]; then mkdir debug; fi
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja ../..
cmake --build .

cd ..

if [[ ! -d "release" ]]; then mkdir release; fi
cd release
cmake -DCMAKE_BUILD_TYPE=Release -G Ninja ../..
cmake --build .

