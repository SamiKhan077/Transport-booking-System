# Transport Booking System

## Overview
This is an enhanced C-based transport booking system that addresses the issues in the original system:

1. **No routes available** - Fixed by adding sample routes
2. **No user data storage** - Fixed by implementing persistent user management

## Features

### 1. Sample Routes (Pre-loaded)
The system comes with 5 sample routes:
- New York ↔ Boston (350 km, $45)
- Los Angeles ↔ San Francisco (400 km, $55)
- Chicago ↔ Detroit (280 km, $35)

### 2. User Data Storage
- **Persistent user accounts** - User data is stored in `users.dat`
- **User registration and login** - Secure user authentication
- **User balance management** - Each user starts with $1000 balance
- **Booking history** - All bookings are stored in `bookings.dat`

### 3. Booking System
- **Route browsing** - View all available routes
- **Bus selection** - Choose from available buses for each route
- **Seat booking** - Book multiple seats
- **Payment system** - Automatic deduction from user balance
- **Booking confirmation** - Detailed booking receipts

### 4. Admin Features
- **User management** - View all registered users
- **Booking management** - View all bookings in the system
- **Route management** - Add new routes
- **Bus management** - Add new buses
- **System statistics** - View revenue and usage statistics

### 5. Data Persistence
All data is stored in separate files:
- `users.dat` - User accounts and balances
- `routes.dat` - Route information
- `bookings.dat` - Booking history
- `buses.dat` - Bus schedules and availability

## How to Use

### Compilation
```bash
gcc -o transport_enhanced transport_enhanced.c
```

### Running the System
```bash
./transport_enhanced
```

### Test Script
```bash
./test_system.sh
```

## System Flow

### For Users:
1. **Register** - Create a new account (option 1)
2. **Login** - Access your account (option 2)
3. **View Routes** - See available routes
4. **Book Ticket** - Select route, bus, and seats
5. **View Bookings** - Check your booking history
6. **Cancel Booking** - Cancel and get refund

### For Admins:
1. **Admin Login** - Login as admin (username: admin, password: admin123)
2. **Manage System** - Add routes, buses, view statistics
3. **Monitor Users** - View all user accounts and bookings

## Sample Data

### Default Admin Account:
- Username: `admin`
- Password: `admin123`
- Balance: $10,000

### Sample Routes:
1. New York → Boston (350 km, $45)
2. Boston → New York (350 km, $45)
3. Los Angeles → San Francisco (400 km, $55)
4. San Francisco → Los Angeles (400 km, $55)
5. Chicago → Detroit (280 km, $35)

### Sample Buses:
- 10 buses with different schedules
- 50 seats per bus
- Various departure times (8:00 AM to 4:00 PM)

## Data Files Created

When you run the system for the first time, it will create:
- `users.dat` - User accounts
- `routes.dat` - Route information
- `bookings.dat` - Booking history
- `buses.dat` - Bus schedules

## Key Improvements

1. **Persistent Data Storage** - All user data and bookings are saved
2. **Sample Routes** - Users can immediately see and book routes
3. **User Management** - Complete user registration and authentication
4. **Booking History** - Users can view their past bookings
5. **Admin Panel** - Comprehensive admin interface
6. **Error Handling** - Better input validation and error messages
7. **Balance Management** - Automatic payment processing

## Testing the System

1. Run the system: `./transport_enhanced`
2. Register a new user (option 1)
3. Login as the new user (option 2)
4. View routes and book a ticket
5. Check your booking history
6. Login as admin to see system statistics

The system now provides a complete transport booking experience with persistent data storage and user management! 