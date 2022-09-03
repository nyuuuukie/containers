#!/bin/bash

CXX=clang++
CYCLES=1000
# DEBUG= -g
DEBUG=
FT_ROOT_FOLDER="./"
TESTER_STD="tester_std"
TESTER_FT="tester_ft"
OUTPUT_STD_NAME="output_std"
OUTPUT_FT_NAME="output_ft"
 
${CXX} *.cpp -I ${FT_ROOT_FOLDER} ${DEBUG} -std=c++98 -o ${TESTER_FT}
${CXX} *.cpp -I ${FT_ROOT_FOLDER} ${DEBUG} -std=c++98 -o ${TESTER_STD} -D _CONTAINER_TESTER_STD

./${TESTER_STD} ${CYCLES} > ${OUTPUT_STD_NAME}
./${TESTER_FT} ${CYCLES} > ${OUTPUT_FT_NAME}

DIFF=$(diff ${OUTPUT_FT_NAME} ${OUTPUT_STD_NAME}) 
if [ "$DIFF" == "" ]
then
    echo "OK, all tests passed"
    rm -f ${OUTPUT_FT_NAME} ${OUTPUT_STD_NAME} 
    rm -f ${TESTER_FT} ${TESTER_STD}
else   
    echo "KO, some tests failed"
    echo "Try to compare ${OUTPUT_FT_NAME} and ${OUTPUT_STD_NAME}"
fi
