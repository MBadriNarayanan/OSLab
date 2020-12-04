echo "enter three digit number"
read n
temp=$n
sum=0
while [ $temp -gt 0 ]
do
	r=$((temp%10))
	cube=$((r*r*r))
	sum=$((sum+cube))
	temp=$((temp/10))
done
if [ $sum -eq $n ]
then
	echo "$n is an armstrong number"
else
	echo "$n is not an armstrong number"
fi
