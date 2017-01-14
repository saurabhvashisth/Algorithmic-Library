flag=1
count=0
while [ $flag -eq 1 ]
do
	let count=count+1
	./gen > data
	./my < data > myout
	./test < data > testout
	diff myout testout
	if [ $? -ne 0 ]
	then
		flag=0
	else
		echo $count Test Successful
	fi

done
