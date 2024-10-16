echo Updating git submodules
git submodule update --init --recursive

echo Updating vcpkg
external/vcpkg/bootstrap-vcpkg.sh -disableMetrics

echo Installing vcpkg libs
external/vcpkg/vcpkg install sockpp argparse
