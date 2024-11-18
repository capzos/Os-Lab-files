#  Write a program to implement an address book with options given below: a) Create
#  address book. b) View address book. c) Insert a record. d) Delete a record. e) Modify a
#  record. f) Exit


#!/bin/bash

ADDRESS_BOOK_FILE="address_book.txt"

# Function to create a new address book
create_address_book() {
    > "$ADDRESS_BOOK_FILE"
    echo "Address book created."
}

# Function to view the address book
view_address_book() {
    if [ -s "$ADDRESS_BOOK_FILE" ]; then
        cat "$ADDRESS_BOOK_FILE"
    else
        echo "Address book is empty."
    fi
}

# Function to insert a new record
insert_record() {
    echo "Enter Name:"
    read name
    echo "Enter Phone Number:"
    read phone
    echo "Enter Email:"
    read email
    echo "$name, $phone, $email" >> "$ADDRESS_BOOK_FILE"
    echo "Record added."
}

# Function to delete a record
delete_record() {
    echo "Enter the name to delete:"
    read name
    if grep -q "^$name," "$ADDRESS_BOOK_FILE"; then
        grep -v "^$name," "$ADDRESS_BOOK_FILE" > temp_file && mv temp_file "$ADDRESS_BOOK_FILE"
        echo "Record deleted."
    else
        echo "Record not found."
    fi
}

# Function to modify a record
modify_record() {
    echo "Enter the name to modify:"
    read name
    if grep -q "^$name," "$ADDRESS_BOOK_FILE"; then
        grep -v "^$name," "$ADDRESS_BOOK_FILE" > temp_file && mv temp_file "$ADDRESS_BOOK_FILE"
        echo "Enter new Name:"
        read new_name
        echo "Enter new Phone Number:"
        read new_phone
        echo "Enter new Email:"
        read new_email
        echo "$new_name, $new_phone, $new_email" >> "$ADDRESS_BOOK_FILE"
        echo "Record modified."
    else
        echo "Record not found."
    fi
}

# Main menu loop
while true; do
    echo "
    Address Book Menu:
    a) Create address book
    b) View address book
    c) Insert a record
    d) Delete a record
    e) Modify a record
    f) Exit
    "
    echo "Enter your choice:"
    read choice
    case $choice in
        a) create_address_book ;;
        b) view_address_book ;;
        c) insert_record ;;
        d) delete_record ;;
        e) modify_record ;;
        f) echo "Exiting..."; break ;;
        *) echo "Invalid choice. Try again." ;;
    esac
done




# open terminal in same folder
# chmod +x address_book.sh
# ./address_book.sh

