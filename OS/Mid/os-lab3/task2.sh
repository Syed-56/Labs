#/bin/bash
name="Syed Sultan"
section="BCS-4H"
num=6
echo $name $section $num
echo "Modify"
name="Syed Sultan Ahmed"
num=9
echo $name $section $num
array=("Sultan" "Hammad" "Mufti" "Ali" "Agha")
echo "${array[*]}"
array+=(5)
i=0
for item in "${array[@]}"
 do
	((i++))
	echo $i $item
done
