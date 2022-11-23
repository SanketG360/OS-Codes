add(){
	BOOK=$1

        echo -n "Enter Name of person: " 
        read name

        echo -n "Enter Phone number: "
        read phone

	echo -n "Enter PAN Number: "
        read PAN

        echo "Should I enter the values:"
        echo -e "$name ; $phone ; $PAN\n"

        echo -n "y/n: "
        read answer

        if [ "$answer" == "y" ] 
        then
            echo "$name ; $phone ; $PAN " >>$BOOK
        else
            echo "$name ; $phone  $PAN NOT written to $BOOK"
        fi
	cat $BOOK
}

list(){
	echo "---------------------------"
        echo "Name  ;   Phone Number ;  PAN"
	cat $BOOK
	echo "---------------------------"
}

findr(){
 	echo -n "What person are you seeking: "
        read find

        grep -i $find $BOOK
 	#search record Phone in address book
	if [ $? -ne 0 ]
	then 
		echo "No such record !"
	else
		echo "Record Found !!!"
	fi
}

del()	
{	echo -n "Which name should I delete: "
        read nm
	#search record name in address book
	grep -i ^$nm $BOOK
	if [ $? -ne 0 ]
	then 
		echo "No such record Found!"
	else
	#delete record from address book
		sed -i "/$nm/d" $BOOK
		echo "Record deleted successfully !!!"
	fi
}
modify()
{
	echo -n "Which name should I modify: "
	read nm
        echo -n "Enter new name : "
        read newnm
	#search record name in address book
	grep -i  ^$nm $BOOK
	if [ $? -ne 0 ]
	then 
		echo "No such record Found!"
	else
	#delete record from address book
		sed -i "s/$nm/$newnm/g" $BOOK
		echo "Record modified successfully !!!"
	fi
}
       

 	exit=0
	echo -n "Enter Book name to Create or Open:"
	read BOOK
	touch $BOOK
        while [ $exit -ne 1 ]
        do
            echo "Enter The Choice"
            echo -e "1. add\n2. list\n3. find\n4. delete\n5. modify\n6. exit\n"
            echo -n "Enter your choice:"
            read answer

            if [ $answer = 1 ]
            then
                add $BOOK
            elif [ $answer = 2 ]
            then
                list $BOOK
            elif [ "$answer" = "3" ]
            then
                findr $BOOK
            elif [ "$answer" = "4" ]
            then
                del $BOOK
            elif [ "$answer" = "5" ]
            then
                modify $BOOK

            elif [ "$answer" = "6" ]
            then
                exit=1
            else
                echo "Invalid Command."
            fi
        done

        exit 0




