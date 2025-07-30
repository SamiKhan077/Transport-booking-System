# Transport Booking System

A comprehensive C program for managing transport bookings, including user signup, signin, and login functionalities. Users can register, log in, and book seats on available buses by selecting their preferred time.

## Features

- User signup and signin for secure access
- Login system to authenticate users
- Add new bookings with user and transport details
- Choose bus and select travel time during booking
- View all existing bookings
- Search bookings by user name or transport ID
- Basic input validation for reliability
- After every booking the system will log out after some inactivity. 

## Getting Started

### Prerequisites

- GCC or any standard C compiler

### Compilation

Compile the program using the following command:

```sh
gcc transport-booking-system.c -o transport-booking-system
```

### Usage

Run the compiled executable:

```sh
./transport-booking-system
```

1. **Signup:** New users can create an account by providing a username and password. The password have to be strong enough if it isn't the system will reject your password.
2. **Signin/Login:** Existing users log in with their credentials. Like username and password. 
3. **Book a Seat:** After login, users can view available buses, select a bus, choose a preferred time slot, and book a seat.
4. **Manage Bookings:** Users can view and search their bookings. 

## File Structure

- `transport-booking-system.c` — Main source code containing all logic for user management and booking system

## Example

```sh
Welcome to the Transport Booking System
1. Signup
2. Login
3. Exit
Enter your choice:

# After login
1. Book a Seat
2. View Bookings
3. Search Booking
Enter your choice:

# Booking flow
Available Buses:
1. Bus A - 9:00 AM
2. Bus B - 11:00 AM
3. Bus C - 2:00 PM and so on....
Select bus and time to book your seat.
```

## License

This project is licensed under the Diu license.
