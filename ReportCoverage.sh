#!/bin/bash

cd Build
lcov -d ./ -c -o init.info 
lcov -a init.info -o total.info
lcov --remove total.info '*/usr/include/*' '*/usr/lib/*' '*/usr/lib64/*' '*/src/log/*' '*/tests/*' '*/usr/local/include/*' '*/usr/local/lib/*' '*/usr/local/lib64/*' '*/third/*' 'testa.cpp' -o final.info
genhtml -o cover_report --legend --title "lcov"  --prefix=./ final.info

### 用firefox 浏览器查看
firefox cover_report/index.html &
