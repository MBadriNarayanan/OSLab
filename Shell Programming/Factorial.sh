echo "Enter the number"
read n
if [ $n -lt 0 ]
then 
	echo "Negative Number"
	exit 0
fi
fact=1
for ((i=1;i<=n;i++))
do
	fact=$((fact*i))
done
echo "factorial is $fact"

