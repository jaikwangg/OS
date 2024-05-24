for file in $(find . -type f -name "*.c")
	do
		trimmedNameWithEX=`echo $file | cut -d'/' -f2`
		trimmedName=`echo $file | cut -d'/' -f2 | cut -d'.' -f1`
		gcc -o $trimmedName $trimmedNameWithEX 2>/dev/null
		if [ -f $trimmedName ]
			then
			if [ 10 = $(./$trimmedName) ]
				then 
				printf "%s\t10\n" $trimmedNameWithEX 
			else
				printf "%s\t7\n" $trimmedNameWithEX  
			fi
		else
			printf "%s\t%d\n" $trimmedNameWithEX 5 
		fi
		#echo 10
	done