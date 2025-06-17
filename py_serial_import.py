import serial
import sys
import time

# Replace 'COM3' with your Arduino's port
arduino_port = "COM4"  
baud_rate = 9600  
output_file = "ArduinoData.txt"  

# Open serial port
try:
    ser = serial.Serial(arduino_port, baud_rate, timeout=1)
    print(f"Connected to {arduino_port} at {baud_rate} baud.")
except serial.SerialException as e:
    print(f"Error: {e}")
    sys.exit()

# Open the output file
with open(output_file, "w") as datafile:
    print("Saving data to:", output_file)

    metadata = "Base:FileState:Arduino:"  # Example metadata, adjust as needed
    datafile.write(metadata + "\n")
    datafile.flush()
    print(f"Metadata written: {metadata}")
    
    # Continuously read from Arduino
    while True:
        with open("stop.txt", "r") as signalfile:
            content = signalfile.read().strip()
        if content == "terminate":
            print("Termination signal received. Exiting loop.")
            ser.close()
            break
    
        if ser.in_waiting > 0:  # Check if there is data in the serial buffer
            data = ser.readline().decode("utf-8").strip()  # Read and decode data
            print(data)  # Print to console
            datafile.write(data + "\n")  # Save to file
            datafile.flush()
