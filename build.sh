git submodule update --init

if [[ ! -d "build" ]]; then mkdir build; fi
cd build

release=false

while getopts r name
do
  case ${name} in
    r) release=true
    ;;
  esac
done


if [ $release == true ]; then
  if [[ ! -d "release" ]]; then mkdir release; fi
  cd release
  cmake -DCMAKE_BUILD_TYPE=Release -G Ninja ../..
  cmake --build .
else
  if [[ ! -d "debug" ]]; then mkdir debug; fi
  cd debug
  cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja ../..
  cmake --build .
fi

