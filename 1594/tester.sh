#! /bin/sh

myfile=out_mine.txt
theirfile=out_their.txt

infile=input.txt

rm -f $myfile $theirfile $infile

result=1

while [ $result ]
do
  python test_gen.py > $infile
  ./mine < $infile > $myfile
  ./theirs < $infile > $theirfile
  if cmp -s -- "$myfile" "$theirfile"; then
    result=1
  else
    # cat $input
    diff "$myfile" "$theirfile"
    break
  fi
done

