echo "Enter three numbers"
read var_1
read var_2
read var_3
greatest=$var_1
if [ $greatest -lt $var_2 ] 
then
greatest=$var_2
fi
if [ $greatest -lt $var_3 ] 
then
greatest=$var_3
fi
echo "Greatest of three is $greatest"
