import tkinter as tk
import subprocess
from tkinter import messagebox

class MetroApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Metro Route Finder")

        # Create a label for query number
        self.query_label = tk.Label(root, text="Enter query number (1-7):")
        self.query_label.pack(pady=5)

        # Create an entry for query number input
        self.query_entry = tk.Entry(root)
        self.query_entry.pack(pady=5)

        # Create a label for source station
        self.source_label = tk.Label(root, text="Enter Source station:")
        self.source_label.pack(pady=5)

        # Create an entry for source station input
        self.source_entry = tk.Entry(root)
        self.source_entry.pack(pady=5)

        # Create a label for destination station
        self.dest_label = tk.Label(root, text="Enter Destination station:")
        self.dest_label.pack(pady=5)

        # Create an entry for destination station input
        self.dest_entry = tk.Entry(root)
        self.dest_entry.pack(pady=5)

        # Create a button to run metro.cpp
        self.run_button = tk.Button(root, text="Run metro.cpp", command=self.run_metro_cpp)
        self.run_button.pack(pady=10)

    def run_metro_cpp(self):
        try:
            # Get inputs from entry widgets
            query_num = self.query_entry.get()
            source_station = self.source_entry.get()
            dest_station = self.dest_entry.get()

            # Validate query number
            if not query_num.isdigit() or int(query_num) < 1 or int(query_num) > 7:
                raise ValueError("Query number must be between 1 and 7.")

            # Validate station names
            if not source_station.strip() or not dest_station.strip():
                raise ValueError("Source and Destination stations cannot be empty.")

            # Run metro.cpp using subprocess based on query number
            if query_num == '1':
                self.show_all_stations()
            elif query_num == '2':
                self.show_time(source_station, dest_station)
            elif query_num == '3':
                self.show_fare(source_station, dest_station)
            elif query_num == '4':
                self.num_stations(source_station, dest_station)
            elif query_num == '5':
                self.show_route(source_station, dest_station)
            elif query_num == '6':
                self.check_station(source_station, dest_station)
            else:
                raise ValueError("Invalid query number.")

        except ValueError as ve:
            messagebox.showerror("Error", str(ve))

    def show_all_stations(self):
        try:
            process = subprocess.run(['./metro', '1'], capture_output=True, text=True, timeout=30)
            output = process.stdout
            if output:
                messagebox.showinfo("All Stations", output)
            else:
                messagebox.showinfo("All Stations", "No stations found.")
        except subprocess.TimeoutExpired:
            messagebox.showerror("Error", "Timeout expired while running metro.cpp.")
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Error", f"Error running metro.cpp: {e.stderr}")

    def show_time(self, source_station, dest_station):
        try:
            process = subprocess.run(['./metro', '2', source_station, dest_station], capture_output=True, text=True, timeout=30)
            output = process.stdout
            if output:
                messagebox.showinfo("Time", output)
            else:
                messagebox.showinfo("Time", "No output from metro.cpp")
        except subprocess.TimeoutExpired:
            messagebox.showerror("Error", "Timeout expired while running metro.cpp.")
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Error", f"Error running metro.cpp: {e.stderr}")

    def show_fare(self, source_station, dest_station):
        try:
            process = subprocess.run(['./metro', '3', source_station, dest_station], capture_output=True, text=True, timeout=30)
            output = process.stdout
            if output:
                messagebox.showinfo("Fare", output)
            else:
                messagebox.showinfo("Fare", "No output from metro.cpp")
        except subprocess.TimeoutExpired:
            messagebox.showerror("Error", "Timeout expired while running metro.cpp.")
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Error", f"Error running metro.cpp: {e.stderr}")

    def num_stations(self, source_station, dest_station):
        try:
            process = subprocess.run(['./metro', '4', source_station, dest_station], capture_output=True, text=True, timeout=30)
            output = process.stdout
            if output:
                messagebox.showinfo("Number of Stations", output)
            else:
                messagebox.showinfo("Number of Stations", "No output from metro.cpp")
        except subprocess.TimeoutExpired:
            messagebox.showerror("Error", "Timeout expired while running metro.cpp.")
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Error", f"Error running metro.cpp: {e.stderr}")

    def show_route(self, source_station, dest_station):
        try:
            process = subprocess.run(['./metro', '5', source_station, dest_station], capture_output=True, text=True, timeout=30)
            output = process.stdout
            if output:
                messagebox.showinfo("Route", output)
            else:
                messagebox.showinfo("Route", "No output from metro.cpp")
        except subprocess.TimeoutExpired:
            messagebox.showerror("Error", "Timeout expired while running metro.cpp.")
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Error", f"Error running metro.cpp: {e.stderr}")

    def check_station(self, source_station, dest_station):
        try:
            process = subprocess.run(['./metro', '6', source_station, dest_station], capture_output=True, text=True, timeout=30)
            output = process.stdout
            if output:
                messagebox.showinfo("Station Check", output)
            else:
                messagebox.showinfo("Station Check", "No output from metro.cpp")
        except subprocess.TimeoutExpired:
            messagebox.showerror("Error", "Timeout expired while running metro.cpp.")
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Error", f"Error running metro.cpp: {e.stderr}")

if __name__ == "__main__":
    root = tk.Tk()
    app = MetroApp(root)
    root.geometry("800x800")
    root.mainloop()
