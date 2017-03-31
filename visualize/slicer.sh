# usage slicer attribute
javac Slicer.java

for f in ../data/*.in 
do
    java Slicer < $f > "sliceresults/$(basename $f)_$1.slice"
done