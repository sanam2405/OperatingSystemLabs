
clear                           # clears the screen
row=6              # This indicates after how many lines the chess board should be displayed
col=15     # This indicates after how many cols the chess board should be displayed     

for i in `seq 9`
do

   for j in 1 2            # prints same line twice to increase height of the block
   do
      tput cup $row $col        # moves cursor to partcular ROW(here row) & COLUMN(here col)

     for k in `seq 9`
     do

        c=`expr $((i+k)) %  2`          # to determine whether it is odd or even block

        if [ $c -eq 0 ]
        then
             echo -e -n "\033[47m    "   # White background, no. of spaces indicates the width of the block
        else
             echo -e -n "\033[40m    "   # Black background, no. of spaces indicates the width of the block
        fi

      done
      row=`expr $row + 1`

    done

done

echo -e "\033[0m"                         # Restores color settings
read key                                  # Waits for enter

