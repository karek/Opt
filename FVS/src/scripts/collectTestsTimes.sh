test_file="fast_tests"
PROGRAM="./build/FeedbackVertexSet"
VERIFIER="./build/Verifier"
MAX_TIME=300

>&2 make 

if [ $# -eq 0 ]; then
  >&2 echo "No arguments supplied, assuming test file = $test_file"
  >&2 echo "Possible usage ./collectTestsTimes [test_file]\n"
else
  test_file=$1
  >&2 echo "Reading tests from file $test_file"
fi

timetmp=`mktemp`


while read p; do
  >&2 echo "Running $p"
  echo "=============================="
  echo "Test $p"
  /usr/bin/time -q --output=$timetmp -f "%E" timeout ${MAX_TIME}s $PROGRAM <../$p > ../${p%.graph}.out 2> a.err
  printf "Time spent = "
  cat $timetmp
  $VERIFIER ../$p ../${p%.graph}.out ../${p%.graph}.opt
  echo "\n"
done <$test_file
