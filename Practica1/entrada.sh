echo "alg	n		real			user			sys				porc" >tiempos.txt
for i in 6 5 4 3 2 1; do
	./main 100 nums.txt $i >>tiempos.txt
./main 100 nums.txt $i >>tiempos.txt
./main 1000 nums.txt $i >>tiempos.txt
./main 5000 nums.txt $i >>tiempos.txt
./main 10000 nums.txt $i >>tiempos.txt
./main 50000 nums.txt $i >>tiempos.txt
./main 100000 nums.txt $i >>tiempos.txt
./main 200000 nums.txt $i >>tiempos.txt
./main 400000 nums.txt $i >>tiempos.txt
./main 600000 nums.txt $i >>tiempos.txt
./main 800000 nums.txt $i >>tiempos.txt
./main 1000000 nums.txt $i >>tiempos.txt
done


