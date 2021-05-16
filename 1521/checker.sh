x=1
val=1
rv=0
while [[ $rv != 1 ]]
do
  ((x=x+1))
  ./gen > test_input.txt
  ./my < test_input.txt > my_output.txt
  ./theirs < test_input.txt > theirs_output.txt
  diff my_output.txt theirs_output.txt
  if [[ $? -ne 0 ]]; then
    break
  fi
done
echo stop: $x
