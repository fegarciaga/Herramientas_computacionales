echo "Strating scaling with system size: 6000000"
for NTH in 1 2 4  8; do
    echo -n "$NTH   ";
    mpirun -np $NTH --oversubscribe ./a.out 6000000  0 100; 
done > scaling-6000000.txt

echo "Computing parallel metrics"
awk 'BEGIN{TS=1.0;} {if (NR==1) TS=$2; print $1, $2, TS/$2, TS/$2/$1}' scaling-6000000.txt > metrics-6000000.txt
echo "Parameters saved in metrics-1000000.txt"
