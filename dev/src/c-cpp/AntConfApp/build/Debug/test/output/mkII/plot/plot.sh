#!/bin/bash
#
# This script will perform all steps to plot the data.
# Author:   C. Gnip
# Date:     02|Aug|2013
# Usage:    <Name> <Start Idx> <Stop Idx> <Trials>
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
    -f      Filename to process
    -s      Start of the index
    -e      End of the index
    -t      Amount of trials done
    -p      Will generate single plots for all data
    -a      Amount of variables in this Experiment
    -c      Creates an archive with the data and removes the old one
EOF
}

PLOTSINGLE=
CREATEARCH=
FILE=
TRIALS=
START=
STOP=
VARAMOUNT=
SED=
LIMIT=
COPY="yes"
while getopts "hf:s:e:t:p:c:a:x:l:o" OPTION
do
    case $OPTION in
        h)
            usage
            exit 1
            ;;
        f)
            FILE=$OPTARG
            ;;
        s)
            START=$OPTARG
            ;;
        e)
            STOP=$OPTARG
            ;;
        t)
            TRIALS=$OPTARG
            ;;
        p)
            PLOTSINGLE=$OPTARG
            ;;
        c)
            CREATEARCH=$OPTARG
            ;;
        a)
            VARAMOUNT=$OPTARG
            ;;
        x)
            SED=$OPTARG
            ;;
        l)
            LIMIT=$OPTARG
            ;;
        o)
            COPY="no"
            ;;
        ?)
            usage
            ;;
        esac
done

#echo $FILE" "$START" "$STOP" "$TRIALS" "$PLOTSINGLE" "$CREATEARCH

if [ -z $FILE ] || [ -z $START ] || [ -z $STOP ] || [ -z $TRIALS ] || [ -z $VARAMOUNT ] || [ -z $PLOTSINGLE ]
then
    echo "Arguments not satisfied:"
    usage
    exit 1
fi

if [ -z $LIMIT ]
then
    LIMIT=300000
    echo "LIMIT set to: "$LIMIT
fi

if [ $COPY == "yes" ]
 then
    echo "****"
    echo "1st copy process "
    echo "****"
    ./cp_data_to_printable.sh $FILE $START $STOP $TRIALS $PLOTSINGLE $SED

    echo "****"
    echo "2nd copy process "
    echo "****"
    ./cp_many_to_single.sh $FILE $TRIALS

fi

rm init.gp
echo "i="$START >> init.gp
echo "j="$START >> init.gp
echo "a="$VARAMOUNT >> init.gp
echo "n="$STOP >> init.gp
echo "m="$TRIALS >> init.gp
echo "h=707" >> init.gp
echo "w=1000" >> init.gp
echo "limit="$LIMIT >> init.gp
 
echo "****"
echo "Generating plots "
echo "****"
if [ $PLOTSINGLE == "yes" ]
then
    gnuplot gen_plots_all.gp
else
    gnuplot gen_plots.gp
fi

if [ $CREATEARCH == "yes" ]
then
    echo "****"
    echo "Creating Archiv"
    echo "****"
#    ./create_arch.sh $FILE
    ./create_arch.temp.sh $FILE
    
    echo "****"
    echo "Init new image repository"
    echo "****"
    ./init_new.sh
fi
echo "done"
