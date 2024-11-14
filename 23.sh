#!/bin/bash

DB_FILE="students.txt"

insert_record() {
    echo "Enter Student ID:"
    read id
    echo "Enter Name:"
    read name
    echo "Enter Age:"
    read age
    echo "Enter Course:"
    read course

    echo "$id,$name,$age,$course" >> "$DB_FILE"
    echo "Record inserted successfully."
}


delete_record() {
    echo "Enter Student ID to delete:"
    read id
    if grep -q "^$id," "$DB_FILE"; then
        grep -v "^$id," "$DB_FILE" > temp.txt && mv temp.txt "$DB_FILE"
        echo "Record deleted successfully."
    else
        echo "Record with ID $id not found."
    fi
}

update_record() {
    echo "Enter Student ID to update:"
    read id
    if grep -q "^$id," "$DB_FILE"; then
        echo "Enter new Name:"
        read name
        echo "Enter new Age:"
        read age
        echo "Enter new Course:"
        read course

        grep -v "^$id," "$DB_FILE" > temp.txt
        echo "$id,$name,$age,$course" >> temp.txt
        mv temp.txt "$DB_FILE"
        echo "Record updated successfully."
    else
        echo "Record with ID $id not found."
    fi
}


search_record() {
    echo "Enter Student ID to search:"
    read id
    if grep -q "^$id," "$DB_FILE"; then
        echo "Record found:"
        grep "^$id," "$DB_FILE"
    else
        echo "Record with ID $id not found."
    fi
}

while true; do
    echo "Choose an operation:"
    echo "a) Insert"
    echo "b) Delete"
    echo "c) Update"
    echo "d) Search"
    echo "e) Exit"
    read -p "Enter your choice: " choice

    case $choice in
        a) insert_record ;;
        b) delete_record ;;
        c) update_record ;;
        d) search_record ;;
        e) echo "Exiting..."; break ;;
        *) echo "Invalid choice. Please try again." ;;
    esac
done
