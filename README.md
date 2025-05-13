# Smart Attendance System using ESP32 & RFID

## Project Overview

The Smart Attendance System is an IoT-based solution designed to track and log attendance using RFID cards. Built around the ESP32 microcontroller, this system uses an RFID-RC522 reader to identify users, captures real-time timestamps via NTP (Network Time Protocol), and displays attendance records on a secure web dashboard. It also allows exporting logs in CSV format and filtering by date.

## Features

- RFID-based attendance tracking  
- Web-based dashboard with real-time updates  
- Admin login system  
- Real-time timestamping using NTP  
- CSV export of attendance logs  
- Date-based filtering (optional enhancement)  
- Background themes:
  - Tree background for Login Page  
  - Ice forest background for Dashboard

## Components Used

- ESP32 (with built-in Wi-Fi)  
- MFRC522 RFID Reader Module  
- RFID Tags/Cards  
- NTP (Network Time Protocol) for timestamps  
- HTML/CSS/JavaScript for web interface  
- MicroSD Card (optional, for storage)  
- Arduino IDE or PlatformIO  

## How It Works

1. **User Scans RFID Card**: The ESP32 reads the UID of the RFID card using the MFRC522 module.  
2. **UID Matching**: The UID is checked against predefined authorized users.  
3. **Timestamp Logging**: If valid, the user’s name and current time (from NTP) are logged.  
4. **Web Dashboard**: The log is displayed in a table format and updates every 2 seconds.  
5. **Admin Login**: Secured access to the dashboard is provided via a custom login page.  
6. **Export**: Attendance records can be downloaded as a CSV file.  

## User Interface

### Login Page  
- Background: Tree scenery  
- Fields: Username & Password  
- Action: Redirects to dashboard if credentials are correct  

### Dashboard  
- Background: Ice forest scene  
- Table Columns: Name | Time  
- Buttons: "Export CSV", "Filter by Date" (optional)  

## File Structure

