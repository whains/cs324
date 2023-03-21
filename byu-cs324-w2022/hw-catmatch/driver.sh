#!/bin/bash
MAX_POINTS=20
TMUX_POINTS=4
COMPILE_POINTS=2
PID_POINTS=2
FUNCTIONALITY_POINTS=12
TEST_TEXT="lorem-ipsum.txt"
CATMATCH_TESTS=("al" "zzz" "culpa") # Best is if FUNCTIONALITY_POINTS is evenly divisable by 
									# number of tests + 1 (The one is for when there is no env
                                    # var set)

runit() {
	cat $1 | while read line; do
		if [ -z "$CATMATCH_PATTERN" ]; then val=0;
		elif echo "$line" | grep -q "$CATMATCH_PATTERN"; then val=1;
		else val=0;
		fi;
		printf "%d %s\n" $val "$line";
	done
	echo
}

run_test() {
	local saved=0
	echo "Testing '$1' on $TEST_TEXT"
	CATMATCH_PATTERN="$1" ./a.out "$TEST_TEXT" >temp.txt 2>std_err.txt &
	cat temp.txt
	local pid=$!
	CATMATCH_PATTERN="$1" runit "$TEST_TEXT" >temp2.txt 2>/dev/null
	grep $pid std_err.txt >/dev/null
	if [ $? -ne 0 ]; then
		echo "PID not correctly sent to std_err"
		pid_test_points=0
	fi

	diff -B temp.txt temp2.txt &>/dev/null
	saved=$?
	if [ $saved -ne 0 ]; then
		sed -i '1d' temp.txt
		diff -B temp.txt temp2.txt >/dev/null	# This is attempting to give points 
												# if they printed the PID to stdout
		saved=$?
		if [ $saved -ne 0 ]; then
			echo -e "FAILED - Expected output\n"
			cat temp2.txt
		else
			echo "Check to make sure your PID is going to stderr"
		fi							
	else
		echo "PASSED"
	fi
	return $saved
}

running_total=0
run_score=0
pid_test_points=$PID_POINTS
temp_points=0
points_per_test=$(($FUNCTIONALITY_POINTS / (${#CATMATCH_TESTS[@]} + 1)))

if [ -f points.txt ]; then
	rm points.txt
fi

echo -e "\nCOMPILER MESSAGES\n"
if [ -f a.out ]; then
	rm a.out
fi
gcc -Werror catmatch.c 2>&1
if [ $? -ne 0 ]; then
    temp_points=0
    gcc catmatch.c &>/dev/null
	if [ $? -ne 0 ]; then
		echo Failed to compile
		exit -1
	fi
else
    temp_points=$COMPILE_POINTS
fi
echo "Compiles without warnings: $temp_points/$COMPILE_POINTS" >> points.txt
running_total=$(($running_total + $temp_points))

echo "____________________________________________________"
echo -e "Testing with no environment variable on $TEST_TEXT"

timeout 5 ./a.out "$TEST_TEXT" >temp.txt 2>std_err.txt 
if [ $? -ne 0 ]; then
    echo -e "Test had a non-zero exit code. Common problems are\n1) segfault\n2) Took longer than 5 seconds\n3) int main's return value isn't 0"
else
   	runit "$TEST_TEXT" >temp2.txt 2>/dev/null
	diff -B temp.txt temp2.txt &>/dev/null
	if [ $? -ne 0 ]; then
		sed -i '1d' temp.txt
		diff -B temp.txt temp2.txt &>/dev/null	# This is attempting to give points 
												# if they printed the PID to stdout
		if [ $? -ne 0 ]; then
			echo -e "FAILED - Expected output\n"
			cat temp2.txt
		else
			echo "You have an extra line at the top, but passed"
			run_score=$points_per_test
		fi
								
	else
		echo "PASSED"
		run_score=$points_per_test
	fi
fi

for i in "${CATMATCH_TESTS[@]}"; do
    echo "____________________________________________________"
    run_test "$i"
    if [ $? -eq 0 ]; then
        run_score=$(($run_score + $points_per_test))
    fi
done
echo "____________________________________________________"

running_total=$(($running_total + $pid_test_points))
echo "Correct PID to stderr: $pid_test_points/$PID_POINTS" >> points.txt

running_total=$(($running_total + $run_score))
echo "Functionality: $run_score/$FUNCTIONALITY_POINTS" >> points.txt
echo "the next line is from your submission, should have TMUX"
cat catmatch.c | grep "TMUX"
if [ $? -ne 0 ]; then
    temp_points=0
else
    temp_points="$TMUX_POINTS"
fi
echo "Completed TMUX: $temp_points/$TMUX_POINTS" >> points.txt
running_total=$(($running_total + $temp_points))

echo "Total: $running_total/$MAX_POINTS" >> points.txt

echo "____________________________________"
cat points.txt
rm points.txt
rm temp.txt
rm temp2.txt
rm std_err.txt
