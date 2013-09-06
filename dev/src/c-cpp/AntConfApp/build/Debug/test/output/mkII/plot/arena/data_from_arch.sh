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
EOF
}

#PLOTSINGLE=
#CREATEARCH=
#FILE=
#TRIALS=
START=
STOP=
#VARAMOUNT=
#while getopts "hf:s:e:t:p:c:a:" OPTION
while getopts "hs:e:" OPTION
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
        #t)
            #TRIALS=$OPTARG
            #;;
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

    #if [ -a $i ] 
    #then 
        #rm -R $i
    #fi

    mkdir $i
    
    echo "****"
    echo "Extracting archives"
    echo "****"
    tar -C $i -xvzf ../store/E$i.tar.gz data/ SigmaStats.dat VectorStats.dat EvaluationStats.dat FitnessStats.dat ObjectivStats.dat  

}
