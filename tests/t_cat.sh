#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_DIR=$1
CAT_DIR=$2
TEST_FILE="$TEST_DIR/bytes.txt $TEST_DIR/test_1.txt $TEST_DIR/test_2.txt $TEST_DIR/test_3.txt"
CAT="$CAT_DIR/my_cat"
echo "" >>log.txt

for var in -b -e -n -s -t -v; do
  TEST1="$var $TEST_FILE"
  echo "$TEST1"
  $CAT $TEST1 >my_cat.txt
  cat $TEST1 >cat.txt
  DIFF_RES="$(diff -s my_cat.txt cat.txt)"
  if [ "$DIFF_RES" == "Files my_cat.txt and cat.txt are identical" ]; then
    ((COUNTER_SUCCESS++))
  else
    echo "$TEST1" >>log.txt
    ((COUNTER_FAIL++))
  fi
  rm my_cat.txt cat.txt
done

for var in -b -e -n -s -t -v; do
  for var2 in -b -e -n -s -t -v; do
    if [ $var != $var2 ]; then
      TEST1="$var $var2 $TEST_FILE"
      echo "$TEST1"
      $CAT $TEST1 >my_cat.txt
      cat $TEST1 >cat.txt
      DIFF_RES="$(diff -s my_cat.txt cat.txt)"
      if [ "$DIFF_RES" == "Files my_cat.txt and cat.txt are identical" ]; then
        ((COUNTER_SUCCESS++))
      else
        echo "$TEST1" >>log.txt
        ((COUNTER_FAIL++))
      fi
      rm my_cat.txt cat.txt
    fi
  done
done

for var in -b -e -n -s -t -v; do
  for var2 in -b -e -n -s -t -v; do
    for var3 in -b -e -n -s -t -v; do
      if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]; then
        TEST1="$var $var2 $var3 $TEST_FILE"
        echo "$TEST1"
        $CAT $TEST1 >my_cat.txt
        cat $TEST1 >cat.txt
        DIFF_RES="$(diff -s my_cat.txt cat.txt)"
        if [ "$DIFF_RES" == "Files my_cat.txt and cat.txt are identical" ]; then
          ((COUNTER_SUCCESS++))
        else
          echo "$TEST1" >>log.txt
          ((COUNTER_FAIL++))
        fi
        rm my_cat.txt cat.txt

      fi
    done
  done
done

for var in -b -e -n -s -t -v; do
  for var2 in -b -e -n -s -t -v; do
    for var3 in -b -e -n -s -t -v; do
      for var4 in -b -e -n -s -t -v; do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]; then
          TEST1="$var $var2 $var3 $var4 $TEST_FILE"
          echo "$TEST1"
          $CAT $TEST1 >my_cat.txt
          cat $TEST1 >cat.txt
          DIFF_RES="$(diff -s my_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files my_cat.txt and cat.txt are identical" ]; then
            ((COUNTER_SUCCESS++))
          else
            echo "$TEST1" >>log.txt
            ((COUNTER_FAIL++))
          fi
          rm my_cat.txt cat.txt

        fi
      done
    done
  done
done

echo "CAT_SUCCESS: $COUNTER_SUCCESS" >>log.txt
echo "CAT_FAIL: $COUNTER_FAIL" >>log.txt