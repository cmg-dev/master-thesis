#!/bin/bash
#
usage()
{
cat << EOF
usage: $0 options

[Start] [End] [Repetitions] [Variables] [Trials] [Increment] [LIMIT]

This script will plot all the data from an experiment.
Part of the PRPSEvolution Tool-Suite.
 
Author
    CG
 
OPTIONS:
    -h      Show this message
    -s      Start index of the archive
    -e      End index of the archive
EOF
}
 
 #PLOTSINGLE=
 #CREATEARCH=
 #FILE=
 #TRIALS= 
 START=  
 STOP=       
REMOVE= 

while getopts "hs:e:r" OPTION
do
    case $OPTION in
        h)
            usage
            exit 1
            ;;
        #f)
            #FILE=$OPTARG
            #;;
        s)  
            START=$OPTARG
            ;;
        e)  
            STOP=$OPTARG
            ;;
        r)  
            REMOVE="yes"
            ;;
        #p) 
            #PLOTSINGLE=$OPTARG
            #;;
        #c) 
            #CREATEARCH=$OPTARG
            #;;
        #a)
            #VARAMOUNT=$OPTARG
            #;;
        ?)
            usage
            ;;
        esac
done
 
 if [ -z $START ] || [ -z $STOP ]
 then
     echo "Arguments not satisfied:"
     usage
     #exit 1
fi

#/plot.sh -f E154 -s 0 -e 10  -a 8 -t 8 -p no -c no -x no -l 60000 
#./plot.sh -f E100 -s 0 -e 50 -a 7 -t 8 -p no -c no -x no -l 60000 -o
#exit 0 

GROUPSIZE=$4
LIMIT=$7
for (( i=$1 ; i <$2 ; i+=$6 ))
do
    
    ./plot.sh -f E$i -s 0 -e $3 -a $GROUPSIZE -t $5 -p no -c yes -x no -l 100000
    GROUPSIZE=$((GROUPSIZE+1))
    if [ $GROUPSIZE -gt $LIMIT ]
    then
        GROUPSIZE=$LIMIT
        echo "Groupsize limited"
    fi
done

exit 0 
#./plot.sh -f E56 -s 0 -e 200 -a 7 -t 6 -p no -c no -x no 
./plot.sh -f E66 -s 0 -e 50 -a 7 -t 6 -p no -c yes -x no -l 50000
./plot.sh -f E67 -s 0 -e 50 -a 7 -t 6 -p no -c yes -x no -l 50000
./plot.sh -f E68 -s 0 -e 50 -a 7 -t 6 -p no -c yes -x no -l 50000
./plot.sh -f E69 -s 0 -e 50 -a 7 -t 6 -p no -c yes -x no -l 50000
./plot.sh -f E70 -s 0 -e 50 -a 7 -t 6 -p no -c yes -x no -l 50000
./plot.sh -f E71 -s 0 -e 50 -a 7 -t 6 -p no -c yes -x no -l 50000
./plot.sh -f E72 -s 0 -e 50 -a 7 -t 6 -p no -c yes -x no -l 50000
./plot.sh -f E73 -s 0 -e 50 -a 7 -t 6 -p no -c yes -x no -l 50000
./plot.sh -f E74 -s 0 -e 50 -a 7 -t 6 -p no -c yes -x no -l 50000
./plot.sh -f E75 -s 0 -e 50 -a 7 -t 6 -p no -c yes -x no -l 50000

exit 0 

./plot.sh -f E56 -s 0 -e 20 -a 7 -t 6 -p no -c yes -x no 
./plot.sh -f E57 -s 0 -e 20 -a 8 -t 6 -p no -c yes -x no 
./plot.sh -f E58 -s 0 -e 20 -a 9 -t 6 -p no -c yes -x no 
./plot.sh -f E59 -s 0 -e 20 -a 9 -t 6 -p no -c yes -x no 
./plot.sh -f E60 -s 0 -e 20 -a 9 -t 6 -p no -c yes -x no 
./plot.sh -f E61 -s 0 -e 20 -a 9 -t 6 -p no -c yes -x no 
./plot.sh -f E62 -s 0 -e 20 -a 9 -t 6 -p no -c yes -x no 
./plot.sh -f E63 -s 0 -e 20 -a 9 -t 6 -p no -c yes -x no 
./plot.sh -f E64 -s 0 -e 20 -a 9 -t 6 -p no -c yes -x no 
./plot.sh -f E65 -s 0 -e 20 -a 9 -t 6 -p no -c yes -x no 

exit 0 

./plot.sh -f E40 -s 0 -e 200 -a 8 -t 6 -p no -c yes 
./plot.sh -f E41 -s 0 -e 200 -a 9 -t 6 -p no -c yes 
./plot.sh -f E42 -s 0 -e 200 -a 9 -t 6 -p no -c yes 
./plot.sh -f E43 -s 0 -e 200 -a 9 -t 6 -p no -c yes 
./plot.sh -f E44 -s 0 -e 200 -a 9 -t 6 -p no -c yes 
./plot.sh -f E45 -s 0 -e 200 -a 9 -t 6 -p no -c yes 
./plot.sh -f E46 -s 0 -e 200 -a 9 -t 6 -p no -c yes 
./plot.sh -f E47 -s 0 -e 200 -a 9 -t 6 -p no -c yes

exit 0 

./plot.sh -f E48 -s 0 -e 20 -a 8 -t 6 -p no -c yes 
./plot.sh -f E49 -s 0 -e 20 -a 9 -t 6 -p no -c yes 
./plot.sh -f E50 -s 0 -e 20 -a 9 -t 6 -p no -c yes 
./plot.sh -f E51 -s 0 -e 20 -a 9 -t 6 -p no -c yes 
./plot.sh -f E52 -s 0 -e 20 -a 9 -t 6 -p no -c yes 
./plot.sh -f E53 -s 0 -e 20 -a 9 -t 6 -p no -c yes 
./plot.sh -f E54 -s 0 -e 20 -a 9 -t 6 -p no -c yes
./plot.sh -f E55 -s 0 -e 20 -a 9 -t 6 -p no -c yes
#./plot.sh -f E56 -s 0 -e 50 -a 9 -t 6 -p no -c yes

exit 0 

./plot.sh -f Test -s 0 -e 20 -a 3 -t 8 -p no -c no 

exit 0 

exit 0 

./plot.sh -f E16 -s 0 -e 50 -a 8 -t 1 -p no -c yes 
./plot.sh -f E17 -s 0 -e 50 -a 9 -t 1 -p no -c yes 
./plot.sh -f E18 -s 0 -e 50 -a 9 -t 1 -p no -c yes 
./plot.sh -f E19 -s 0 -e 50 -a 9 -t 1 -p no -c yes 
./plot.sh -f E20 -s 0 -e 50 -a 9 -t 1 -p no -c yes 
./plot.sh -f E21 -s 0 -e 50 -a 9 -t 1 -p no -c yes 
./plot.sh -f E22 -s 0 -e 50 -a 9 -t 1 -p no -c yes 
./plot.sh -f E23 -s 0 -e 50 -a 9 -t 1 -p no -c yes 
./plot.sh -f E24 -s 0 -e 200 -a 8 -t 1 -p no -c yes 
./plot.sh -f E25 -s 0 -e 200 -a 9 -t 1 -p no -c yes 
./plot.sh -f E26 -s 0 -e 200 -a 9 -t 1 -p no -c yes 
./plot.sh -f E27 -s 0 -e 200 -a 9 -t 1 -p no -c yes 
./plot.sh -f E28 -s 0 -e 200 -a 9 -t 1 -p no -c yes 
./plot.sh -f E29 -s 0 -e 200 -a 9 -t 1 -p no -c yes 
./plot.sh -f E30 -s 0 -e 200 -a 9 -t 1 -p no -c yes 
./plot.sh -f E31 -s 0 -e 200 -a 9 -t 1 -p no -c yes 
./plot.sh -f E32 -s 0 -e 200 -a 8 -t 1 -p no -c yes 
./plot.sh -f E33 -s 0 -e 200 -a 9 -t 1 -p no -c yes 
./plot.sh -f E34 -s 0 -e 200 -a 9 -t 1 -p no -c yes 
./plot.sh -f E35 -s 0 -e 200 -a 9 -t 1 -p no -c yes 
./plot.sh -f E36 -s 0 -e 200 -a 9 -t 1 -p no -c yes 
./plot.sh -f E37 -s 0 -e 200 -a 9 -t 1 -p no -c yes 
./plot.sh -f E38 -s 0 -e 200 -a 9 -t 1 -p no -c yes 
./plot.sh -f E39 -s 0 -e 200 -a 9 -t 1 -p no -c yes
