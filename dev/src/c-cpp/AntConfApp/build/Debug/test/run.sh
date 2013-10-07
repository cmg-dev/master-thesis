#!/bin/bash
#
# This script performs the experiments. These were defined in experiments.doc.
#

##################################################################################
# [Start] [Stop] [Variant] [Trials] [Evaluations] [DropBad] [Mu] [Lambda] [StartGroupSize] [IncrementGroupSize] [Offset]
function action {

GS=$9

for (( i=$1 ; i < $2 ; i++ )) 
do

    NAME="E"$i
    echo "#########################################################################"
    echo "Starting with parameter:"
    echo "  Variant       "$3
    echo "  Trials        "$4
    echo "  Name          '"$NAME"'"
    echo "  Groupsize     "$GS
    echo "  Evaluations   "$5
    echo "  Mu            "$7
    echo "  Lambda        "$8
    echo "  Offset        "${11}
    echo ""

    ./AntConfApp $3 $4 $7 $NAME $7 $8 $GS $5 ${11}
   
    if [ ${10} == "yes" ]
    then
        GS=$(($GS+1))
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

Defined Experiments:
    200     Calculated the fitness plane of given input
    100     Performs Evo Calibration

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
        TRIALS=10
        VARIANT=4
        START=170
        STOP=175
        GROUPSIZE=3
        LOCALGS=3
        INCGROUPSIZE="yes"
        EVALUATIONS=50000
        MU=5
        LAMBDA=10
       
        a=0
        b=35
       
        for (( j=i$a ; j < $b ; j++ )) 
        do 
            GROUPSIZE=$LOCALGS

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
            echo "run done"
            MU=$((MU+5))
            LAMBDA=$((LAMBDA+10))
        
            #GROUPSIZE=$((GROUPSIZE+1))
            START=$((START+5))
            STOP=$((STOP+5))

        done

    fi
#=================================================================================================#
#fixed mu = 1
    if (( $SET == 11 ))
    then
        TRIALS=10
        VARIANT=4
        START=300
        STOP=310
        GROUPSIZE=1
        INCGROUPSIZE="yes"
        EVALUATIONS=500000
        MU=1
        LAMBDA=10
       
        a=0
        b=10
       
        for (( j=i$a ; j < $b ; j++ )) 
        do 
        GROUPSIZE=1

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
            #MU=$((MU+5))
            LAMBDA=$((LAMBDA+20))
        
            #GROUPSIZE=$((GROUPSIZE+1))
            START=$((START+10))
            STOP=$((STOP+10))

        done

    fi
#=================================================================================================#
#Test the (1+1) strategy
    if (( $SET == 12 ))
    then
        TRIALS=20
        VARIANT=4
        START=500
        STOP=510
        GROUPSIZE=1
        INCGROUPSIZE="yes"
        EVALUATIONS=50000
        MU=1
        LAMBDA=2
        
        action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
        

    fi
#=================================================================================================#
    if (( $SET == 13 ))
    then
        TRIALS=30
        VARIANT=4
        START=2050
        STOP=2060
        GROUPSIZE=20
        LOCALGS=1
        INCGROUPSIZE="yes"
        EVALUATIONS=100000
        MU=35
        LAMBDA=350
       
        a=0
        b=30
       
        for (( j=i$a ; j < $b ; j++ )) 
        do 
            GROUPSIZE=$LOCALGS

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
            echo "run done"
            MU=$((MU+10))
            LAMBDA=$((LAMBDA+50))
        
            #GROUPSIZE=$((GROUPSIZE+1))
            START=$((START+10))
            STOP=$((STOP+10))

        done

    fi
#=================================================================================================#
    if (( $SET == 14 ))
    then
        TRIALS=10
        VARIANT=4
        START=3000
        STOP=3001
        GROUPSIZE=5
        LOCALGS=5
        INCGROUPSIZE="yes"
        EVALUATIONS=100000
        MU=10
        LAMBDA=50
       
        a=0
        b=300
       
        for (( j=i$a ; j < $b ; j++ )) 
        do 
            GROUPSIZE=$LOCALGS

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
            echo "run done"
            MU=$((MU+20))
            LAMBDA=$((LAMBDA+100))
        
            #GROUPSIZE=$((GROUPSIZE+1))
            START=$((START+1))
            STOP=$((STOP+1))

        done

    fi
#=================================================================================================#
    if (( $SET == 15 ))
    then
        TRIALS=5
        VARIANT=6
        START=15000
        STOP=15010
        GROUPSIZE=1
        LOCALGS=1
        INCGROUPSIZE="yes"
        EVALUATIONS=100000
        MU=30
        LAMBDA=100
       
        a=0
        b=30
       
        for (( j=i$a ; j < $b ; j++ )) 
        do 
            GROUPSIZE=$LOCALGS

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
            echo "run done"
            MU=$((MU+10))
            LAMBDA=$((LAMBDA+50))
        
            #GROUPSIZE=$((GROUPSIZE+1))
            START=$((START+10))
            STOP=$((STOP+10))

        done

    fi
#=================================================================================================#
    if (( $SET == 16 ))
    then
        TRIALS=10
        VARIANT=6
        START=16000
        STOP=16001
        GROUPSIZE=5
        LOCALGS=5
        INCGROUPSIZE="yes"
        EVALUATIONS=100000
        MU=10
        LAMBDA=50
       
        a=0
        b=300
       
        for (( j=i$a ; j < $b ; j++ )) 
        do 
            GROUPSIZE=$LOCALGS

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
            echo "run done"
            MU=$((MU+20))
            LAMBDA=$((LAMBDA+100))
        
            #GROUPSIZE=$((GROUPSIZE+1))
            START=$((START+1))
            STOP=$((STOP+1))

        done

    fi
#=================================================================================================#
# Perform the new Variant with the reduced model. 
#=================================================================================================#
    if (( $SET == 17 ))
    then
        TRIALS=10
        VARIANT=7
        START=17000
        STOP=17010
        GROUPSIZE=1
        LOCALGS=1
        INCGROUPSIZE="yes"
        EVALUATIONS=100000
        MU=0
        LAMBDA=0
       
        a=0
        b=300
       
        for (( j=i$a ; j < $b ; j++ )) 
        do 
            GROUPSIZE=$LOCALGS

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
            echo "run done"
            MU=$((MU+20))
            LAMBDA=$((LAMBDA+100))
        
            #GROUPSIZE=$((GROUPSIZE+1))
            START=$((START+10))
            STOP=$((STOP+10))

        done

    fi
#=================================================================================================#
# Perform the new Variant with the reduced model. 
#=================================================================================================#
    if (( $SET == 18 ))
    then
        TRIALS=10
        VARIANT=7
        START=18000
        STOP=18001
        GROUPSIZE=1
        LOCALGS=1
        INCGROUPSIZE="yes"
        EVALUATIONS=100000
        MU=10
        LAMBDA=50
       
        a=0
        b=300
       
        for (( j=i$a ; j < $b ; j++ )) 
        do 
            GROUPSIZE=$LOCALGS

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE
            echo "run done"
            MU=$((MU+10))
            LAMBDA=$((LAMBDA+20))
        
            #GROUPSIZE=$((GROUPSIZE+1))
            START=$((START+1))
            STOP=$((STOP+1))

        done

    fi
#=================================================================================================#
# Perform the new Variant with the reduced model with all matrices availiable 
#=================================================================================================#
    if (( $SET == 19 ))
    then
        TRIALS=10
        VARIANT=7
        START=19000
        STOP=19001
        GROUPSIZE=1
        LOCALGS=1
        INCGROUPSIZE="no"
        EVALUATIONS=100000
        MU=100
        LAMBDA=500
       
        a=0
        b=35
       
        OFFSET=0

        for (( j=i$a ; j < $b ; j++ )) 
        do 
            GROUPSIZE=$LOCALGS

            action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE $OFFSET
            echo "run done"
            OFFSET=$((OFFSET+1))
            #MU=$((MU+10))
            #LAMBDA=$((LAMBDA+20))
        
            #GROUPSIZE=$((GROUPSIZE+1))
            START=$((START+1))
            STOP=$((STOP+1))

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
#=================================================================================================#
# calculated the fitnes plane of given model according to given input set
#=================================================================================================#
    if (( $SET == 200 ))
    then
        TRIALS=1
        VARIANT=100
        START=1000
        STOP=1001
        GROUPSIZE=1
        INCGROUPSIZE="no"
        EVALUATIONS=0
        action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE

    fi
#=================================================================================================#
# calculated the fitnes plane of the reduced model
#=================================================================================================#
    if (( $SET == 201 ))
    then
        TRIALS=1
        VARIANT=101
        START=2000
        STOP=2001
        GROUPSIZE=1
        INCGROUPSIZE="no"
        EVALUATIONS=0
        action $START $STOP $VARIANT $TRIALS $EVALUATIONS $DROPBAD $MU $LAMBDA $GROUPSIZE $INCGROUPSIZE

    fi

fi
