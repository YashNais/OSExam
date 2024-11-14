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


########################################################### New

#####odd_even
#!/bin/bash

# Prompt the user for input
read -p "Enter a number: " number

# Check if the number is even or odd using modulo operator
if (( number % 2 == 0 )); then
    echo "$number is even."
else
    echo "$number is odd."
fi

#####bubble_sort
#!/bin/bash

# Define an array of integers
arr=(5 3 8 4 2)

# Get the length of the array
n=${#arr[@]}

# Bubble Sort algorithm
for ((i = 0; i < n - 1; i++))
do
  for ((j = 0; j < n - i - 1; j++))
  do
    if (( arr[j] > arr[j + 1] ))
    then
      # Swap elements
      temp=${arr[j]}
      arr[j]=${arr[j + 1]}
      arr[j + 1]=$temp
    fi
  done
done

# Print sorted array
echo "Sorted Array: ${arr[@]}"

#######armstrong
#!/bin/bash

# Function to check if a number is an Armstrong number
is_armstrong() {
  num=$1
  sum=0
  temp=$num
  n=${#num}  # Number of digits

  # Calculate the sum of each digit raised to the power of the number of digits
  while [ $temp -gt 0 ]
  do
    digit=$((temp % 10))                 # Extract the last digit
    sum=$((sum + digit ** n))             # Add digit^n to sum
    temp=$((temp / 10))                   # Remove the last digit
  done

  # Check if the calculated sum matches the original number
  if [ $sum -eq $num ]; then
    echo "$num is an Armstrong number."
  else
    echo "$num is not an Armstrong number."
  fi
}

# Input number
read -p "Enter a number: " number
is_armstrong "$number"

########factorial
#!/bin/bash

# Function to calculate factorial
factorial() {
  num=$1
  fact=1

  for (( i=1; i<=num; i++ ))
  do
    fact=$((fact * i))
  done

  echo "Factorial of $num is $fact"
}

# Input number
read -p "Enter a number: " number

# Check if the number is non-negative
if [[ $number -lt 0 ]]; then
  echo "Factorial is not defined for negative numbers."
else
  factorial "$number"
fi
#######fact(with recursion)
#!/bin/bash

# Recursive function to calculate factorial
factorial_recursive() {
  if [ "$1" -le 1 ]; then
    echo 1
  else
    prev=$(factorial_recursive $(( $1 - 1 )))
    echo $(( $1 * prev ))
  fi
}

# Input number
read -p "Enter a number: " number

# Check if the number is non-negative
if [[ $number -lt 0 ]]; then
  echo "Factorial is not defined for negative numbers."
else
  result=$(factorial_recursive "$number")
  echo "Factorial of $number (recursive) is $result"
fi
#####fact(w/o recursion)
#!/bin/bash

# Function to calculate factorial iteratively
factorial_iterative() {
  num=$1
  fact=1

  for (( i=1; i<=num; i++ ))
  do
    fact=$((fact * i))
  done

  echo $fact
}

# Input number
read -p "Enter a number: " number

# Check if the number is non-negative
if [[ $number -lt 0 ]]; then
  echo "Factorial is not defined for negative numbers."
else
  result=$(factorial_iterative "$number")
  echo "Factorial of $number (iterative) is $result"
fi
#####palindrome
#!/bin/bash

# Function to check if a string is a palindrome
is_palindrome() {
  input=$1
  reversed=$(echo "$input" | rev)  # Reverse the string
  if [ "$input" == "$reversed" ]; then
    echo "$input is a palindrome."
  else
    echo "$input is not a palindrome."
  fi
}

# Input (string or number)
read -p "Enter a string or number: " input

# Remove spaces and convert to lowercase for case-insensitive comparison
input=$(echo "$input" | tr -d '[:space:]' | tr '[:upper:]' '[:lower:]')

# Check if the input is a palindrome
is_palindrome "$input"

######subsstr cnt
#!/bin/bash

# Function to count occurrences of a substring
count_occurrences() {
  string=abcedea
  substring=abc
  count=0

  # Loop to count occurrences
  while [[ $string =~ $substring ]]; do
    ((count++))
    string=${string#*$substring}  # Remove the first occurrence
  done

  echo "The substring '$substring' occurs $count times."
}

count_occurrences




#####sum of digits

# Function to calculate sum of digits
sum_of_digits() {
    local number=$1
    local sum=0

    while [ $number -gt 0 ]; do
        sum=$((sum + number % 10))
        number=$((number / 10))
    done

    echo $sum
}

# Example usage
number=12345
echo "Sum of digits of $number is $(sum_of_digits $number)"




