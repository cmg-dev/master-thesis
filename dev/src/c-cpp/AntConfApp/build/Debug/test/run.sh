#!/bin/bash
#
# This script performs the experiments. These were defined in experiments.doc.
#

##################################################################################
# [Start] [Stop] [Variant] [Trials] [Evaluations] [DropBad] [Mu] [Lambda] [StartGroupSize] [IncrementGroupSize]
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
    echo "  Mu            "$7
    echo "  Lambda        "$8
    echo ""

    ./AntConfApp $3 $4 $7 $NAME $7 $8 $GROUPSIZE $5
   
    if [ ${10} == "yes" ]
    then
        GROUPSIZE=$(($GROUPSIZE+1))
        echo " New Group size "$GROUPSIZE
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
 #=================================================================================================#  
    if (( $SET == 1 ))
    then
        TRIALS=200
        START=40
        STOP=48
        GROUPSIZE=2
        INCGROUPSIZE="yes"
        action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE

    fi
 #=================================================================================================#      
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
#=================================================================================================#   
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
        START=56
        STOP=66
        GROUPSIZE=1
        INCGROUPSIZE="yes"
        EVALUATIONS=8000
        action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE

    fi
#=================================================================================================#   
    if (( $SET == 5 ))
    then
        TRIALS=50
        VARIANT=4
        START=66
        STOP=67
        GROUPSIZE=1
        INCGROUPSIZE="no"
        EVALUATIONS=50000
        MU=10
        LAMBDA=20
       
        a=0
        b=10
       
        for (( j=i$a ; j < $b ; j++ )) 
        do 

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
            MU=$((MU+10))
            LAMBDA=$((LAMBDA+10))
        
            START=$((START+1))
            STOP=$((STOP+1))

        done

    fi
#=================================================================================================#   
    if (( $SET == 6 ))
    then
        TRIALS=50
        VARIANT=4
        START=76
        STOP=77
        GROUPSIZE=1
        INCGROUPSIZE="no"
        EVALUATIONS=50000
        MU=10
        LAMBDA=20
       
        a=0
        b=10
       
        for (( j=i$a ; j < $b ; j++ )) 
        do 

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
            #MU=$((MU+10))
            LAMBDA=$((LAMBDA+10))
        
            START=$((START+1))
            STOP=$((STOP+1))

        done

    fi
#=================================================================================================#   
    if (( $SET == 7 ))
    then
        TRIALS=100
        VARIANT=4
        START=100
        STOP=110
        GROUPSIZE=1
        INCGROUPSIZE="yes"
        EVALUATIONS=50000
        MU=0
        LAMBDA=0
       
        #a=0
        #b=10
       
        #for (( j=i$a ; j < $b ; j++ )) 
        #do 

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
            #MU=$((MU+10))
            #LAMBDA=$((LAMBDA+10))
        
            #START=$((START+1))
            #STOP=$((STOP+1))

        #done

    fi
#=================================================================================================#   
    if (( $SET == 8 ))
    then
        TRIALS=10
        VARIANT=4
        START=140
        STOP=141
        GROUPSIZE=20
        INCGROUPSIZE="no"
        EVALUATIONS=50000
        MU=50
        LAMBDA=60
       
        a=0
        b=15
       
        for (( j=i$a ; j < $b ; j++ )) 
        do 

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
            #MU=$((MU+5))
            LAMBDA=$((LAMBDA+10))
        
            #GROUPSIZE=$((GROUPSIZE+1))
            START=$((START+1))
            STOP=$((STOP+1))

        done

    fi
#=================================================================================================#
    if (( $SET == 9 ))
    then
        TRIALS=10
        VARIANT=4
        START=154
        STOP=155
        GROUPSIZE=1
        INCGROUPSIZE="no"
        EVALUATIONS=50000
        MU=10
        LAMBDA=150
       
        a=0
        b=15
       
        for (( j=i$a ; j < $b ; j++ )) 
        do 

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
            #MU=$((MU+5))
            #LAMBDA=$((LAMBDA+10))
        
            GROUPSIZE=$((GROUPSIZE+1))
            START=$((START+1))
            STOP=$((STOP+1))

        done

    fi
#=================================================================================================#
    if (( $SET == 10 ))
    then
        TRIALS=30
        VARIANT=4
        START=170
        STOP=180
        GROUPSIZE=1
        INCGROUPSIZE="yes"
        EVALUATIONS=50000
        MU=0
        LAMBDA=0
       
        a=0
        b=30
       
        for (( j=i$a ; j < $b ; j++ )) 
        do 
        GROUPSIZE=1

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
            MU=$((MU+5))
            LAMBDA=$((LAMBDA+10))
        
            #GROUPSIZE=$((GROUPSIZE+1))
            START=$((START+10))
            STOP=$((STOP+10))

        done

    fi
#=================================================================================================#
    #test the algorithm against the calibration
    if (( $SET == 100 ))
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
