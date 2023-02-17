FT_CONTAINER = ft_container
STD_CONTAINER = std_container
TIME_TEST = time_test
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
FT_SRCS = ft_container.cpp
STD_SRCS = std_container.cpp
TIME_SRCS = time_test.cpp
INCLUDES = -I./
LOGS = ./logs

FT_OBJS = $(FT_SRCS:.cpp=.o)
STD_OBJS = $(STD_SRCS:.cpp=.o)
TIME_OBJS = $(TIME_SRCS:.cpp=.o)

OBJS = $(FT_OBJS) $(STD_OBJS) $(TIME_OBJS)

all : $(FT_CONTAINER) $(STD_CONTAINER) $(TIME_TEST)
		mkdir logs
$(FT_CONTAINER) : $(FT_OBJS)
		c++ $(CXXFLAGS) $(FT_OBJS) -o $(FT_CONTAINER) $(INCLUDES)

$(STD_CONTAINER) : $(STD_OBJS)
		c++ $(CXXFLAGS) $(STD_OBJS) -o $(STD_CONTAINER) $(INCLUDES)

$(TIME_TEST) : $(TIME_OBJS)
		c++ $(CXXFLAGS) $(TIME_OBJS) -o $(TIME_TEST) $(INCLUDES)

clean :
		rm -f $(OBJS)

fclean : clean
		rm -f $(FT_CONTAINER) $(STD_CONTAINER) $(TIME_TEST)
		rm -rf $(LOGS)

re :
		make fclean
		make all

.PHONY : all clean fclean re