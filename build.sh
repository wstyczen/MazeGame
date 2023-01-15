git submodule update --init
git submodule update --recursive

if [[ ! -d "build" ]]; then mkdir build; fi
cd build

debug=false

while getopts d name
do
  case ${name} in
    d) debug=true
    ;;
  esac
done


if [ $debug == true ];
then
  if [[ ! -d "debug" ]]; then mkdir debug; fi
  cd debug
  cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja ../..
  cmake --build .
else
  if [[ ! -d "release" ]]; then mkdir release; fi
  cd release
  cmake -DCMAKE_BUILD_TYPE=Release -G Ninja ../..
  cmake --build .
fi

