myvar="Hi there"  
#myvar = "error bacause of spacebar"
echo $myvar
echo 1 "$myvar"
echo 2 ' $myvar' 
echo 4 'myvar contains " '"$myvar"""
echo 5 "myvar contains \"$myvar\"" 
echo Enter some text
read myvar
echo '$myvar' value is $myvar
exit 0