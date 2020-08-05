# Clean old stuff
rm -rf ./_build/*

# Generate build files
cmake -B"./_build" -S"./"

cd ./_build && cmake --build .
cd ../
