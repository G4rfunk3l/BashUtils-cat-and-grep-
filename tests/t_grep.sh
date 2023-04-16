#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_DIR=$1
CAT_DIR=$2
PATTERN="$TEST_DIR/pattern.txt"
FILE_1="$TEST_DIR/my_grep_c.txt"
FILE_2="$TEST_DIR/my_grep_h.txt"
FILE_3="$TEST_DIR/Makefile.txt"
GREP="$CAT_DIR/my_grep"
echo "" >>log.txt

for var in -v -c -l -n -h -o; do
  for var2 in -v -c -l -n -h -o; do
    for var3 in -v -c -l -n -h -o; do
      if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]; then
        TEST1="for( $FILE_1 $FILE_2 $FILE_3 $var $var2 $var3"
        echo "$TEST1"
        $GREP $TEST1 >my_grep.txt
        grep $TEST1 >grep.txt
        DIFF_RES="$(diff -s my_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files my_grep.txt and grep.txt are identical" ]; then
          ((COUNTER_SUCCESS++))
        else
          echo "$TEST1" >>log.txt
          ((COUNTER_FAIL++))
        fi
        rm my_grep.txt grep.txt

        TEST2="for $FILE_1 $var $var2 $var3"
        echo "$TEST2"
        $GREP $TEST2 >my_grep.txt
        grep $TEST2 >grep.txt
        DIFF_RES="$(diff -s my_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files my_grep.txt and grep.txt are identical" ]; then
          ((COUNTER_SUCCESS++))
        else
          echo "$TEST2" >>log.txt
          ((COUNTER_FAIL++))
        fi
        rm my_grep.txt grep.txt

        TEST3="-e for -e ^int $FILE_1 $FILE_2 $FILE_3 $var $var2 $var3"
        echo "$TEST3"
        $GREP $TEST3 >my_grep.txt
        grep $TEST3 >grep.txt
        DIFF_RES="$(diff -s my_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files my_grep.txt and grep.txt are identical" ]; then
          ((COUNTER_SUCCESS++))
        else
          echo "$TEST3" >>log.txt
          ((COUNTER_FAIL++))
        fi
        rm my_grep.txt grep.txt

        TEST4="-e for -e ^int $FILE_1 $var $var2 $var3"
        echo "$TEST4"
        $GREP $TEST4 >my_grep.txt
        grep $TEST4 >grep.txt
        DIFF_RES="$(diff -s my_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files my_grep.txt and grep.txt are identical" ]; then
          ((COUNTER_SUCCESS++))
        else
          echo "$TEST4" >>log.txt
          ((COUNTER_FAIL++))
        fi
        rm my_grep.txt grep.txt

        TEST5="-e regex -e ^print $FILE_1 $var $var2 $var3 -f $PATTERN"
        echo "$TEST5"
        $GREP $TEST5 >my_grep.txt
        grep $TEST5 >grep.txt
        DIFF_RES="$(diff -s my_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files my_grep.txt and grep.txt are identical" ]; then
          ((COUNTER_SUCCESS++))
        else
          echo "$TEST5" >>log.txt
          ((COUNTER_FAIL++))
        fi
        rm my_grep.txt grep.txt

        TEST6="-e while -e void $FILE_1 $FILE_3 $var $var2 $var3 -f $PATTERN"
        echo "$TEST6"
        $GREP $TEST6 >my_grep.txt
        grep $TEST6 >grep.txt
        DIFF_RES="$(diff -s my_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files my_grep.txt and grep.txt are identical" ]; then
          ((COUNTER_SUCCESS++))
        else
          echo "$TEST6" >>log.txt
          ((COUNTER_FAIL++))
        fi
        rm my_grep.txt grep.txt
      fi
    done
  done
done

echo "GREP_SUCCESS: $COUNTER_SUCCESS" >>log.txt
echo "GREP_FAIL: $COUNTER_FAIL" >>log.txt
