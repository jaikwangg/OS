echo "Is it morning? yes or no"
read timeofday
if [ $timeofday = "yes" ]
	then 
		echo "Good morning"
elif [ $timeofday = "no" ]
	then 
		echo "Good arthernoon"
else
	echo "Sorry, do not understand $timeofday"
	exit 1
	fi
exit 0