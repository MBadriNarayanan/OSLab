echo "Enter the string"
read s
echo "Enter the chars to be replaced and to be replaced with"
read c1
read c2
echo "new string is: ${s//$c1/$c2}"
