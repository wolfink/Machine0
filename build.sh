if [[ $1 = "rebuild" ]]; then
    cmake build
fi
cmake --build build
