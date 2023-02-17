FT_CONTAINERS = ft_container
STD_CONTAINERS = std_container
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
FT_SRCS = ft_container.cpp
STD_SRCS = std_container.cpp
INCLUDES = -I./
LOGS = ./logs

FT_OBJS = $(FT_SRCS:.cpp=.o)
STD_OBJS = $(STD_SRCS:.cpp=.o)

OBJS = $(FT_OBJS) $(STD_OBJS)

all : $(FT_CONTAINERS) $(STD_CONTAINERS)

$(FT_CONTAINERS) : $(FT_OBJS)
		c++ $(CXXFLAGS) $(FT_OBJS) -o $(FT_CONTAINERS) $(INCLUDES)

$(STD_CONTAINERS) : $(STD_OBJS)
		c++ $(CXXFLAGS) $(STD_OBJS) -o $(STD_CONTAINERS) $(INCLUDES)

clean :
		rm -f $(OBJS)

fclean : clean
		rm -f $(NAME)
		rm -rf $(LOGS)

re :
		make fclean
		make all

.PHONY : all clean fclean re