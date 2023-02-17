FT_CONTAINER = ft_container
STD_CONTAINER = std_container
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
FT_SRCS = ft_container.cpp
STD_SRCS = std_container.cpp
INCLUDES = -I./
LOGS = ./logs

FT_OBJS = $(FT_SRCS:.cpp=.o)
STD_OBJS = $(STD_SRCS:.cpp=.o)

OBJS = $(FT_OBJS) $(STD_OBJS)

all : $(FT_CONTAINER) $(STD_CONTAINER)

$(FT_CONTAINER) : $(FT_OBJS)
		c++ $(CXXFLAGS) $(FT_OBJS) -o $(FT_CONTAINER) $(INCLUDES)

$(STD_CONTAINER) : $(STD_OBJS)
		c++ $(CXXFLAGS) $(STD_OBJS) -o $(STD_CONTAINER) $(INCLUDES)

clean :
		rm -f $(OBJS)

fclean : clean
		rm -f $(FT_CONTAINER) $(STD_CONTAINER)
		rm -rf $(LOGS)

re :
		make fclean
		make all

.PHONY : all clean fclean re