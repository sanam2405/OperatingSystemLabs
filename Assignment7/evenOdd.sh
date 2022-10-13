# HOW TO FIND A NUMBER IS EVEN OR ODD IN SHELL SCRIPT
# WRITTEN BY SURAJ MAITY
# TUTORIALSINHAND.COM
clear 
echo "---- EVEN OR ODD IN SHELL SCRIPT -----"
echo -n "Enter a number:"
read n
echo -n "RESULT: "
if [ `expr $n % 2` == 0 ]
then
	echo "$n is even"
else
	echo "$n is Odd"
fi
