#!/bin/bash
rm plot.dat

writedata() {

    for i in {1..20}; do
        echo -e $i"\t"$(adcRead) >> plot.dat
        sleep 0.1
    done

    for i in {21..100}; do
        echo "$(tail -n +2 plot.dat)" > plot.dat
        echo -e $i"\t"$(adcRead) >> plot.dat
        sleep 0.1
    done
}

writedata &
gnuplot liveplot.gnu
