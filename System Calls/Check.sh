echo "Enter a number"
read num
temp=$((num%2))
if [ $temp -eq 0 ]
then
	echo "$num, is an even number"
else
	echo "$num, is an odd number"
fi
