#!/bin/bash

# Function to check if a number is prime
is_prime() {
    local num=$1

    if (( num < 2 )); then
        echo "$num is not a prime number."
        return
    fi


    if (( num == 2 )); then
        echo "$num is a prime number."
        return
    fi

    if (( num % 2 == 0 )); then
        echo "$num is not a prime number."
        return
    fi

    for (( i=3; i*i<=num; i+=2 )); do
        if (( num % i == 0 )); then
            echo "$num is not a prime number."
            return
        fi
    done

    echo "$num is a prime number."
}

read -p "Enter a number: " number
is_prime "$number"

########################
#Armstrong

#!/bin/bash
read -p "Enter a number: " num
original_num=$num
sum=0
num_digits=${#num}
while (( num > 0 )); do
    digit=$(( num % 10 ))
    sum=$(( sum + digit ** num_digits ))
    num=$(( num / 10 ))
done
if (( sum == original_num )); then
    echo "$original_num is an Armstrong number."
else
    echo "$original_num is not an Armstrong number."
fi

#############################
#Factorial
#!/bin/bash

# Prompt the user to enter a number
read -p "Enter a number: " num
factorial=1

# Calculate the factorial
for (( i=1; i<=num; i++ )); do
    factorial=$(( factorial * i ))
done

# Output the result
echo "The factorial of $num is $factorial."

#######################
#Palindrome

#!/bin/bash

# Prompt the user to enter a number
read -p "Enter a number: " num
original_num=$num
reverse=0

# Calculate the reverse of the number
while (( num > 0 )); do
    digit=$(( num % 10 ))
    reverse=$(( reverse * 10 + digit ))
    num=$(( num / 10 ))
done

# Check if the original number is equal to its reverse
if (( original_num == reverse )); then
    echo "$original_num is a palindrome."
else
    echo "$original_num is not a palindrome."
fi

#######################################3
#Bubble sort
#!/bin/bash

# Prompt the user to enter numbers
read -p "Enter numbers separated by spaces: " -a arr
n=${#arr[@]}

# Perform Bubble Sort
for (( i = 0; i < n-1; i++ )); do
    for (( j = 0; j < n-i-1; j++ )); do
        if (( arr[j] > arr[j+1] )); then
            # Swap arr[j] and arr[j+1]
            temp=${arr[j]}
            arr[j]=${arr[j+1]}
            arr[j+1]=$temp
        fi
    done
done

# Output the sorted array
echo "Sorted array: ${arr[@]}"

######################
#Substrings
#!/bin/bash

# Prompt the user to enter the main string
read -p "Enter the main string: " str

# Prompt the user to enter the substring to search for
read -p "Enter the substring to count: " substr

# Count occurrences of the substring in the main string
count=$(grep -o "$substr" <<< "$str" | wc -l)

# Output the result
echo "The substring '$substr' occurs $count times in the main string."


