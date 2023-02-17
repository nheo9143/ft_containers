#!/bin/bash
GREEN="\033[0;32m"
RED="\033[0;31m"
BLACK="\033[0m"

echo "----vector diff----"
if diff logs/ft_vector.txt logs/std_vector.txt 1>/dev/null; then echo -e $GREEN "OK✅"; else echo -e $RED "KO❌"; diff logs/ft_vector.txt logs/std_vector.txt > logs/vector.diff; fi
echo -e $BLACK
echo "----map diff----"
if diff logs/ft_map.txt logs/std_map.txt 1>/dev/null; then echo -e $GREEN "OK✅"; else echo -e $RED "KO❌"; diff logs/ft_map.txt logs/std_map.txt > logs/map.diff; fi
echo -e $BLACK
echo "----stack diff----"
if diff logs/ft_stack.txt logs/std_stack.txt 1>/dev/null; then echo -e $GREEN "OK✅"; else echo -e $RED "KO❌"; diff logs/ft_stack.txt logs/std_stack.txt > logs/stack.diff; fi
echo -e $BLACK
echo "----set diff----"
if diff logs/ft_set.txt logs/std_set.txt  1>/dev/null; then echo -e $GREEN "OK✅"; else echo -e $RED "KO❌"; diff logs/ft_set.txt logs/std_set.txt > logs/set.diff; fi

