echo "enter a string"
read s
v="$(echo "$s" | grep -oi [aeiouAEIOU] | wc -l)"
echo "vowel count: $v"
