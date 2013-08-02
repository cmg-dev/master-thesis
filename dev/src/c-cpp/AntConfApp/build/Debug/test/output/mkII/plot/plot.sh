#
# This script will perform all steps to plot the data.
# Author:   C. Gnip
# Date:     02|Aug|2013
# Usage:    <Name> <Start Idx> <Stop Idx> <Trials>
#

if [ $# -eq 4 ]
then
    echo "****"
    echo "1st copy process "
    echo "****"
    ./cp_data_to_printable.sh $1 $2 $3 $4

    echo "****"
    echo "2nd copy process "
    echo "****"
    ./cp_many_to_single.sh $1 $4

    echo "****"
    echo "Generating plots "
    echo "****"
    gnuplot gen_plots.gp

    echo "****"
    echo "Creating Archiv"
    echo "****"
    ./create_arch.sh $1

    echo "****"
    echo "Init new image repository"
    echo "****"
    ./init_new.sh

    echo "done"
else
    echo "Parameter unsatisfied"
    echo "Usage: <Name> <Start Idx> <Stop Idx> <Trials>"
fi
