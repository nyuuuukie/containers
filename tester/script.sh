#!/bin/bash

CXX=clang++
CYCLES=1000
# DEBUG= -g
DEBUG=
INCLUDE_DIR="./"
TESTER_STD="tester_std"
TESTER_FT="tester_ft"
OUTPUT_STD="output_std"
OUTPUT_FT="output_ft"
CONT_SRCS=
 
${CXX} *.cpp ${CONT_SRCS} -I ${INCLUDE_DIR} ${DEBUG} -std=c++98 -o ${TESTER_FT}
${CXX} *.cpp  -D _CONTAINER_TESTER_STD      ${DEBUG} -std=c++98 -o ${TESTER_STD}

./${TESTER_STD} ${CYCLES} > ${OUTPUT_STD_NAME}
./${TESTER_FT} ${CYCLES} > ${OUTPUT_FT_NAME}

DIFF=$(diff ${OUTPUT_FT_NAME} ${OUTPUT_STD_NAME}) 
if [ "$DIFF" == "" ]
then
    echo "OK, all tests passed"
    rm -rf ${OUTPUT_FT} ${OUTPUT_STD} 
    rm -rf ${TESTER_FT}* ${TESTER_STD}*
else   
    echo "KO, some tests failed"
    echo "Try to compare ${OUTPUT_FT_NAME} and ${OUTPUT_STD_NAME}"
fi
