.PHONY: clean fclean re all libjson makedir comp

###################################################################################
#                               Compiler & Flags                                  #
###################################################################################

CXX       =   clang++
CPPFLAGS  =   -Wall -Wextra -Werror -std=c++98
DEBUG     =

ifeq ($(DEBUG), 1)
	CPPFLAGS += -g
endif

###################################################################################
#                                    Tests                                        #
###################################################################################

CYCLES	   = 1000
OUTPUT_STD = output_std
OUTPUT_FT  = output_ft
TESTER_STD = tester_std
TESTER_FT  = tester_ft

OK = "OK, all tests passed"
KO = "KO, some tests failed\n \
	Try to compare ${OUTPUT_FT} and ${OUTPUT_STD}"

###################################################################################
#                              Directories & Files                                #
###################################################################################

SRCS_DIR     = tests
OBJS_DIR     = .obj
DEPS_DIR     = .deps
INCLUDE_DIR  = include
SRCS    	 = main.cpp        \
			   map_test.cpp    \
			   set_test.cpp    \
			   stack_test.cpp  \
			   vector_test.cpp \

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
DEPS = $(addprefix $(DEPS_DIR)/, $(SRCS:.cpp=.d))

###################################################################################
#                                   Commands                                      #
###################################################################################

comp: makedir $(NAME)

all: 
	
makedir:
	@if ! [ -d ${OBJS_DIR} ] ; then mkdir ${OBJS_DIR} ; fi
	@if ! [ -d ${DEPS_DIR} ] ; then mkdir ${DEPS_DIR} ; fi

$(NAME): $(TESTER_STD) $(TESTER_FT)
	./${TESTER_STD} ${CYCLES} > ${OUTPUT_STD}
	./${TESTER_FT}  ${CYCLES} > ${OUTPUT_FT}
	if [ ! "$(diff ${OUTPUT_FT} ${OUTPUT_STD})" ] ; then echo ${OK}; clean; else echo ${KO} ; fi

$(TESTER_STD): $(OBJS)
	$(CXX) $(CPPFLAGS) -D STD -c $< -o $@ -I $(INCLUDE_DIR)

$(TESTER_FT): $(OBJS)
	$(CXX) $(CPPFLAGS) -c $< -o $@ -I $(INCLUDE_DIR)

-include $(DEPS)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ -I $(INCLUDE_DIR)

clean:
	rm -f ${OUTPUT_FT} ${OUTPUT_STD} 
    rm -f ${TESTER_FT} ${TESTER_STD}

fclean: clean
	rm -rf $(NAME)

re: fclean all

