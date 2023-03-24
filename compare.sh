#!/bin/bash

make -s test_performance > ft_performance.txt
make -s test_performance STD=1 > std_performance.txt

myarray=( $(cat ft_performance.txt) )
stdarray=( $(cat std_performance.txt) )

for (( i = 0; i < ${#myarray[@]}; ++i ));
do
  current=${myarray[i]}
  if [[ $current == "Vector_tests" || $current == "Map_Test" ]]; then
    printf "\n\n%s\n" $current
  else
    if [[ $current == "Executing:" ]]; then
      test_name=${myarray[++i]}
      printf "\n%s\n" $test_name
    elif [[ $current == "Time_of_Execution_in_Miliseconds:" ]]; then
      ft_value=$( echo -n ${myarray[++i]} | sed 's/ms//' )
      std_value=$( echo -n ${stdarray[++i]} | sed 's/ms//')
      printf "ft_performance_result: %f\n" $ft_value
      printf "stl_performance_result: %f\n" $std_value
      awk -- 'BEGIN{printf "allowed max limit: %f\n", ARGV[1]*ARGV[2]}' "$std_value" "20"
      awk -- 'BEGIN{printf "Times Slower Than STL: %.3f\n", ARGV[1]/ARGV[2]}' "$ft_value" "$std_value"
    fi
  fi
done
