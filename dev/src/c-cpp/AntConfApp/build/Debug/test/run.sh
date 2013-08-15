#!/bin/bash
#
# This script performs the experiments. These were defined in experiments.doc.
#

##################################################################################
# [Start] [Stop] [Variant] [Trials] [Evaluations] [DropBad] [Mu] [Lambda] [StartGroupSize] [{IncrementGroupSize]
function action {

GROUPSIZE=$9

for (( i=$1 ; i < $2 ; i++ )) 
do

    NAME="E"$i
    echo "#########################################################################"
    echo "Starting with parameter:"
    echo "  Variant       "$3
    echo "  Trials        "$4
    echo "  Name          '"$NAME"'"
    echo "  Groupsize     "$GROUPSIZE
    echo "  Evaluations   "$5
    echo ""

    ./AntConfApp $3 $4 $7 $NAME $7 $8 $GROUPSIZE $5
   
    if (( ${10} == "yes" ))
    then
        GROUPSIZE=$(($GROUPSIZE+1))
    fi

    echo "# DONE ##################################################################"
    echo ""

done
}

##################################################################################
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
    -s      Specifies the experiment set that will be performed
EOF
}
##################################################################################

SET=
while getopts "hs:" OPTION
do
    case $OPTION in
        h)
            usage
            exit 1
            ;;
        s)
            SET=$OPTARG
            ;;
        ?)
            usage
            ;;
        esac
done

#echo $FILE" "$START" "$STOP" "$TRIALS" "$PLOTSINGLE" "$CREATEARCH

#Presetup
VARIANT=4
TRIALS=50
START=16
STOP=24
ExperimentNo=16
DROPBAD=0

MU=0
LAMBDA=0

GROUPSIZE=2
INCGROUPSIZE=yes

EVALUATIONS=6000

if [ -z $SET ] 
then
#-- EXPERIMENTS 16-23 ------------------------------------------------------------

#Setup

    action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE

#-- EXPERIMENTS 24-31 ------------------------------------------------------------

#Setup
    TRIALS=200
    START=$STOP
    STOP=32

    action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE

#-- EXPERIMENTS 32-39 ------------------------------------------------------------

#Setup
    START=$STOP
    STOP=40

    action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE


else
    if (( $SET == 1 ))
    then
        TRIALS=200
        START=40
        STOP=48
        GROUPSIZE=2
        INCGROUPSIZE="yes"
        action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE

    fi
    
    if (( $SET == 2 ))
    then
        VARIANT=5
        TRIALS=20
        START=48
        STOP=56
        GROUPSIZE=2
        INCGROUPSIZE="yes"
        action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE

    fi

    if (( $SET == 3 ))
    then
        VARIANT=5
        TRIALS=20
        START=48
        STOP=56
        GROUPSIZE=2
        MU=10
        LAMBDA=20
        INCGROUPSIZE="yes"
        action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE

    fi

    if (( $SET == 4 ))
    then
        TRIALS=200
        START=57
        STOP=67
        GROUPSIZE=1
        INCGROUPSIZE="yes"
        EVALUATIONS=8000
        action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE

    fi

    if (( $SET == 10 ))
    then
        TRIALS=20
        VARIANT=10
        START=100
        STOP=101
        GROUPSIZE=1
        INCGROUPSIZE="no"
        EVALUATIONS=3000
        action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE

    fi

fi
