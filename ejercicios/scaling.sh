echo "Strating scaling with system size: 1000000"
for NTH in 1 2 4 5 8; do
    echo -n "$NTH   ";
    ./a.out 1000000 $NTH 0 10; 
done > scaling-1000000.txt

echo "Computing parallel metrics"
awk 'BEGIN{TS=1.0;} {if (NR==1) TS=$2; print $1, $2, TS/$2, TS/$2/$1}' scaling-1000000.txt > metrics-1000000.txt
echo "Parameters saved in metrics-1000000.txt"
