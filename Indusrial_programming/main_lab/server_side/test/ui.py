import tkinter as tk
from tkinter import simpledialog, messagebox
from main import ObjectList, Vehicle
from datetime import datetime
import json
import xml.etree.ElementTree as ET
from xml.dom import minidom
import zipfile
from cryptography.fernet import Fernet
import os

# ToDo: add sorting by field
# ToDo: fix encryption
# ToDo: make archive and encrypt as decorator

class VehicleApp:
    def __init__(self, master):
        self.master = master
        self.master.title("Vehicle Management App")

        self.obj_list = ObjectList()

        # UI elements
        self.label = tk.Label(master, text="Vehicle Management App", font=("Helvetica", 16))
        self.label.grid(row=0, column=1, pady=10)

        self.add_button = tk.Button(master, text="Add Vehicle (Console)", command=self.add_vehicle_console)
        self.add_button.grid(row=1, column=0, padx=10, pady=10)

        self.json_button = tk.Button(master, text="Add Vehicle (JSON)", command=self.add_vehicle_json)
        self.json_button.grid(row=1, column=1, padx=10, pady=10)

        self.xml_button = tk.Button(master, text="Add Vehicle (XML)", command=self.add_vehicle_xml)
        self.xml_button.grid(row=1, column=2, padx=10, pady=10)

        self.show_button = tk.Button(master, text="Show Vehicles", command=self.show_vehicles)
        self.show_button.grid(row=2, column=1, padx=10, pady=10)

    def add_vehicle_console(self):
        vehicle = self.input_vehicle_data()
        self.obj_list.add_vehicle(vehicle)
        messagebox.showinfo("Success", "Vehicle added successfully!")

    def add_vehicle_json(self):
        filename = self.input_dialog("Enter JSON file name")
        try:
            self.obj_list.read_from_file(filename)
            messagebox.showinfo("Success", "Data read from JSON file!")
        except Exception as e:
            messagebox.showerror("Error", f"Error reading from JSON file: {e}")

    def add_vehicle_xml(self):
        filename = self.input_dialog("Enter XML file name")
        try:
            self.obj_list.read_from_xml(filename)
            messagebox.showinfo("Success", "Data read from XML file!")
        except Exception as e:
            messagebox.showerror("Error", f"Error reading from XML file: {e}")

    def show_vehicles(self):
        encrypt = messagebox.askyesno("Encryption", "Encrypt vehicle data?")
        archive = messagebox.askyesno("Archive", "Archive vehicle data?")
        formats = ["JSON", "XML", "Text File", "Window"]

        selected_formats = []
        for format in formats:
            if messagebox.askyesno("Output Format", f"Output vehicles to {format}?"):
                selected_formats.append(format)

        result = self.generate_output(selected_formats, encrypt, archive)
        messagebox.showinfo("Vehicles", result)

    def input_vehicle_data(self):
        id = int(self.input_dialog("Enter vehicle id"))
        type = self.input_dialog("Enter vehicle type")
        model = self.input_dialog("Enter vehicle model")
        engine_power = int(self.input_dialog("Enter engine power"))
        max_speed = int(self.input_dialog("Enter max speed"))
        manufacture_date_str = self.input_dialog("Enter manufacture date (YYYY-MM-DD)")
        manufacture_date = datetime.strptime(manufacture_date_str, "%Y-%m-%d")
        price = float(self.input_dialog("Enter price"))
        return Vehicle(id, type, model, engine_power, max_speed, manufacture_date, price)

    def input_dialog(self, prompt):
        return simpledialog.askstring("Input", prompt)

    def generate_output(self, formats, encrypt, archive):
        output_str = ""
        for format in formats:
            if format == "JSON":
                output_str += self.generate_json_output(encrypt, archive)
            elif format == "XML":
                output_str += self.generate_xml_output(encrypt, archive)
            elif format == "Text File":
                output_str += self.generate_text_file_output(encrypt, archive)
            elif format == "Window":
                output_str += self.generate_window_output(encrypt, archive)

        # Convert encrypted_data list to string for display
        output_str += "\n".join(map(str, encrypted_data))
        return output_str

    def generate_json_output(self, encrypt, archive):
        if encrypt:
            key = Fernet.generate_key()
            self.obj_list.encrypt_data(key)

        if archive:
            self.obj_list.zip_data('vehicles.json.zip')
            return f"Data encrypted, archived, and saved to vehicles.json.zip\n"
        else:
            self.obj_list.save_to_file('vehicles.json')
            return f"Data {'encrypted ' if encrypt else ''}saved to vehicles.json\n"

    def generate_xml_output(self, encrypt, archive):
        if encrypt:
            key = Fernet.generate_key()
            self.obj_list.encrypt_data(key)

        if archive:
            self.obj_list.zip_data('vehicles.xml.zip')
            return f"Data encrypted, archived, and saved to vehicles.xml.zip\n"
        else:
            self.obj_list.save_to_xml('vehicles.xml')
            return f"Data {'encrypted ' if encrypt else ''}saved to vehicles.xml\n"

    def generate_text_file_output(self, encrypt, archive):
        if encrypt:
            key = Fernet.generate_key()
            self.obj_list.encrypt_data(key)

        if archive:
            self.obj_list.zip_data('vehicles.txt.zip')
            return f"Data encrypted, archived, and saved to vehicles.txt.zip\n"
        else:
            with open('vehicles.txt', 'w') as file:
                for vehicle in self.obj_list.vehicles:
                    file.write(str(vehicle) + '\n')
            return f"Data {'encrypted ' if encrypt else ''}saved to vehicles.txt\n"

    def generate_window_output(self, encrypt, archive):
        vehicles_str = "\n".join(str(vehicle) for vehicle in self.obj_list.vehicles)
        if encrypt:
            key = Fernet.generate_key()
            self.obj_list.encrypt_data(key)
            vehicles_str = f"Data encrypted:\n{vehicles_str}"

        if archive:
            self.obj_list.zip_data('vehicles_window.txt.zip')
            return f"{vehicles_str}\n\nData archived and saved to vehicles_window.txt.zip\n"
        else:
            return f"{vehicles_str}\n\nData not archived\n"

def main():
    root = tk.Tk()
    app = VehicleApp(root)
    root.mainloop()

if __name__ == "__main__":
    main()
