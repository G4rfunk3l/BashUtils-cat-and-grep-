#!/bin/bash

FILE="$1/Makefile.txt"
CAT="$2/my_cat"
GREP="$3/my_grep"

cat $FILE >txt1.txt && $CAT $FILE >txt2.txt && diff txt1.txt txt2.txt 
cat -b $FILE >txt1.txt && $CAT -b $FILE >txt2.txt && diff txt1.txt txt2.txt
cat -e $FILE >txt1.txt && $CAT -e $FILE >txt2.txt && diff txt1.txt txt2.txt
cat -n $FILE >txt1.txt && $CAT -n $FILE >txt2.txt && diff txt1.txt txt2.txt
cat -s $FILE >txt1.txt && $CAT -s $FILE >txt2.txt && diff txt1.txt txt2.txt
cat -t $FILE >txt1.txt && $CAT -t $FILE >txt2.txt && diff txt1.txt txt2.txt
cat -v $FILE >txt1.txt && $CAT -v $FILE >txt2.txt && diff txt1.txt txt2.txt
cat -b $FILE >txt1.txt && $CAT --number-nonblank $FILE >txt2.txt && diff txt1.txt txt2.txt
cat -n $FILE >txt1.txt && $CAT --number $FILE >txt2.txt && diff txt1.txt txt2.txt
cat -s $FILE >txt1.txt && $CAT --squeeze-blank $FILE >txt2.txt && diff txt1.txt txt2.txt
grep make $FILE >txt1.txt && $GREP make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep -e make $FILE >txt1.txt && $GREP -e make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep -i make $FILE >txt1.txt && $GREP -i make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep -c make $FILE >txt1.txt && $GREP -c make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep -l make $FILE >txt1.txt && $GREP -l make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep -n make $FILE >txt1.txt && $GREP -n make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep -h make $FILE >txt1.txt && $GREP -h make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep -s make $FILE >txt1.txt && $GREP -s make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep -o make $FILE >txt1.txt && $GREP -o make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep -ie make $FILE >txt1.txt && $GREP -ie make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep -cn make $FILE >txt1.txt && $GREP -cn make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep -so make $FILE >txt1.txt && $GREP -so make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep -sol make $FILE >txt1.txt && $GREP -sol make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep -svol make $FILE >txt1.txt && $GREP -svol make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep -svolhn make $FILE >txt1.txt && $GREP -svolhn make $FILE >txt2.txt && diff txt1.txt txt2.txt
grep make $FILE $FILE >txt1.txt && $GREP make $FILE $FILE >txt2.txt && diff txt1.txt txt2.txt
