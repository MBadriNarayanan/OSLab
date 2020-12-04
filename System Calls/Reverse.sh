echo "Enter the string"
read s
len=${#s}
for((i=$((len-1));i>=0;i--))
do
	reverse="$reverse${s:$i:1}"
done
echo "$reverse"
