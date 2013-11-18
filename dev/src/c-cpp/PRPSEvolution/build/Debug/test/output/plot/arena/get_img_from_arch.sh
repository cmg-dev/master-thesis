#!/bin/bash
#
usage()
{
cat << EOF
usage: $0 options

This script will plot all the data from an experiment.
Part of the PRPSEvolution Tool-Suite.

Author
    CG

OPTIONS:
    -h      Show this message
    -s      Start index of the archive
    -e      End index of the archive
    -r      Remove only
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
    exit 1
fi

for(( i=$START; i < $STOP;i++ )) {

    if [ -a $i ] 
    then 
        rm -R $i
    fi

    #if -r flag is set. remove only
    if [ -z $REMOVE ]
    then
        mkdir $i
    
        echo "****"
        echo "Extracting archives"
        echo "****"
        tar -C $i -xvzf ../store/E$i.tar.gz img/

    else
        echo "rm "$i
    fi

}
