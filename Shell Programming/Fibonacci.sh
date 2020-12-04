echo "enter number of digits in the series"
read n
a=0
b=1
echo "------"
for((i=1;i<=n;i++))
do
	echo "$a"
	next=$((a+b))
	a=$b
	b=$next
done
