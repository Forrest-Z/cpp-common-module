#!/bin/sh


set -e

PROJECT_NAME=common
install_path=${PWD}/Prebuilt
build_dir=${PWD}/Build

if [ $# != 0 ]; then
  for arg in "$@"
  do
    if [ "$arg" = "no_install" ]; then
      run_install="no"
    fi
  done
fi



echo "########################################################"
echo ${build_dir}
echo ${install_path}
echo "########################################################"

cmake -B${build_dir} \
      -D PROJECT_NAME="${PROJECT_NAME}" \
      -D install_path="${install_path}" \
      -D build_dir="${build_dir}"

cd ${build_dir}
make -j

if [ "$run_install" = "yes" ]; then
  mkdir -p ${output_dir}
  make install/strip
fi
