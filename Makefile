.PHONY: clean fclean re all makedir

NAME = tester

###################################################################################
#                               Compiler & Flags                                  #
###################################################################################

CXX       =   clang++
CPPFLAGS  =   -Wall -Wextra -Werror -std=c++98
# DEBUG     = 1

ifeq ($(DEBUG), 1)
	CPPFLAGS += -g
endif

###################################################################################
#                                   Tester                                        #
###################################################################################

CYCLES	   = 1000
OUTPUT_STD = output_std
OUTPUT_FT  = output_ft
TESTER_STD = tester_std
TESTER_FT  = tester_ft

###################################################################################
#                              Directories & Files                                #
###################################################################################

SRCS_DIR     = tester
OBJS_DIR     = .obj
INCLUDE_DIR  = include
SRCS_LIST    = main.cpp        \
               map_test.cpp    \
               set_test.cpp    \
               stack_test.cpp  \
               vector_test.cpp \

SRCS  = $(addprefix $(SRCS_DIR)/, ${SRCS_LIST})

###################################################################################
#                                   Commands                                      #
###################################################################################

all: makedir $(NAME)
	
makedir:
	@if ! [ -d ${OBJS_DIR} ] ; then mkdir ${OBJS_DIR} ; fi
	@if ! [ -d ${DEPS_DIR} ] ; then mkdir ${DEPS_DIR} ; fi

$(NAME): $(TESTER_STD) $(TESTER_FT)
	@./${TESTER_STD} ${CYCLES} > ${OUTPUT_STD}
	@./${TESTER_FT}  ${CYCLES} > ${OUTPUT_FT}
ifeq "$(diff ${OUTPUT_FT} ${OUTPUT_STD})" ""
	@echo "OK, all tests passed"
	@$(MAKE) clean
else
	@echo "KO, some tests failed"
	@echo "Try to compare ${OUTPUT_FT} and ${OUTPUT_STD}"
endif

$(TESTER_STD): $(SRCS)
	@$(CXX) $(CPPFLAGS) $^ -o $@ -D _CONTAINER_TESTER_STD

$(TESTER_FT): $(SRCS)
	@$(CXX) $(CPPFLAGS) $^ -o $@ -I ./$(INCLUDE_DIR)

clean:
	@rm -rf ${OUTPUT_FT} ${OUTPUT_STD} 
	@rm -rf ${TESTER_FT}* ${TESTER_STD}*

fclean: clean

re: fclean all

