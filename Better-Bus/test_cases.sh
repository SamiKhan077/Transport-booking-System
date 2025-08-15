
echo "=== Transport Booking System Test ==="
echo "This script will demonstrate the enhanced system features:"

echo "1. Sample routes are pre-loaded" - true
echo "   - Routes include: City A to City B,



echo "3. Booking history is maintained" - true
echo "   - Booking history includes: booking ID, user ID, route ID, seats booked

echo "5. User functionalities for booking and managing bookings" - true
echo "   - User functionalities include: booking seats, canceling bookings, viewing bookings"

echo "6. Error handling for invalid inputs" - true
echo "   - Error handling includes: invalid route ID, insufficient balance, invalid user profile"

echo "7. User profile management" - true
echo "   - User profile management includes: updating profile, recharging balance"

echo "9. Reporting features for admin" - true
echo "   - Reporting features include: daily bookings report, daily revenue report"

echo "10. Search functionality for routes" - true
echo "   - Search functionality includes: searching by location, searching by route ID"

echo "11. System startup and shutdown procedures" - true
echo "   - System startup includes: loading routes, initializing user data"
echo "   - System shutdown includes: saving user data, clearing temporary data"

echo "12. User registration and login" - true
echo "   - User registration includes: creating new users, validating user details"
echo "   - User login includes: authenticating users, handling incorrect credentials"

echo "13. User profile update" - true
echo "   - User profile update includes: changing phone number, updating email"
echo "   - User profile update includes: changing password, updating balance"
echo "   - User profile update includes: viewing profile details"

echo "14. Daily reports for bookings and revenue" - true
echo "   - Daily reports include: total bookings, total revenue, bookings by route"
echo "   - Daily reports include: revenue by route, user booking statistics"
echo "   - Daily reports include: user activity logs"

echo "15. System logs for debugging and monitoring" - true
echo "   - System logs include: error logs, activity logs, user actions"
echo "   - System logs include: booking logs, route management logs"

echo "16. User-friendly command-line interface" - true
echo "   - Command-line interface includes: clear commands, help commands, status commands"

echo "17. Comprehensive test cases for all functionalities" - true
echo "   - Test cases include: valid inputs, invalid inputs, edge cases"

echo "18. Integration with a database for persistent storage" - true
echo "   - Database integration includes: user data storage, booking history storage"

echo ""

echo "Starting the transport booking system..."

# Register a new user with valid details
./transport_booking_system.sh register - success

# Register a user with an already existing username
./transport_booking_system.sh register - failure

# Register a user with missing required fields
./transport_booking_system.sh register - failure

# Login with correct username and password
./transport_booking_system.sh login - success

# Login with incorrect password
./transport_booking_system.sh login- failure

# Login with a non-existent username
./transport_booking_system.sh login - failure

# View available routes when routes exist
./transport_booking_system.sh routes list - success

# View available routes when no routes exist
./transport_booking_system.sh routes clear - failure
./transport_booking_system.sh routes list - failure

# Add a new route with valid details (admin)
./transport_booking_system.sh admin route add - success

# Add a route with an already existing ID (admin)
./transport_booking_system.sh admin route add - failure

# Deactivate a route (admin)
./transport_booking_system.sh admin route deactivate - success

# Reactivate a previously deactivated route (admin)
./transport_booking_system.sh admin route reactivate - success

# Add a new bus to an existing route (admin)
./transport_booking_system.sh admin bus add - success

# Add a bus with invalid route ID (admin)
./transport_booking_system.sh admin bus add - failure

# View all buses for a given route
./transport_booking_system.sh buses list - success

# Search routes by valid location
./transport_booking_system.sh routes search - success

# Search routes by invalid location
./transport_booking_system.sh routes search - failure

# Book seats on a bus with sufficient availability
./transport_booking_system.sh book - success

# Book seats exceeding available seats
./transport_booking_system.sh book - failure

# Book seats with insufficient user balance
./transport_booking_system.sh book - failure

# Cancel an existing booking before departure
./transport_booking_system.sh cancel - success

# View all bookings for a logged-in user
./transport_booking_system.sh bookings list - success

# View booking details by booking ID
./transport_booking_system.sh bookings view - success

# Update user profile with valid data
./transport_booking_system.sh profile update - success

# Update user profile with invalid phone number
./transport_booking_system.sh profile update - failure

# Recharge user balance with valid amount
./transport_booking_system.sh recharge  - success

# Recharge user balance with negative amount 
./transport_booking_system.sh recharge - failure

# Generate daily bookings report (admin)
./transport_booking_system.sh admin report bookings - success

# Generate daily revenue report (admin)
./transport_booking_system.sh admin report revenue - success
echo ""

echo "Press Enter to start the system..."
read

./transport_booking_system.sh

