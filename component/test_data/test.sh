mkdir -p /opt/gomros/run/compA/lib
mkdir -p /opt/gomros/data/gomros_test

TEST_SO_FILE=libdynamic_load_test.so

cp ../../Build/component/${TEST_SO_FILE} .

cp ${TEST_SO_FILE} /opt/gomros/run/compA/lib
cp component.xml product.xml /opt/gomros/run/compA
cp config.xml /opt/gomros/data/gomros_test
