import json
import xml.etree.ElementTree as ET
from xml.dom import minidom
import zipfile
from cryptography.fernet import Fernet
import datetime


def zip_decorator(func):
    def wrapper(self, file_path, *args, **kwargs):
        if file_path.endswith('.zip'):
            with zipfile.ZipFile(file_path, 'r') as zip_ref:
                file_list = zip_ref.namelist()
                if len(file_list) == 1:  # Assume the first file is the one to read
                    with zip_ref.open(file_list[0]) as file_in_zip:
                        return func(self, file_in_zip, *args, **kwargs)
                else:
                    raise ValueError("Archive must contain exactly one file.")
        else:
            return func(self, file_path, *args, **kwargs)
    return wrapper


class Vehicle:
    def __init__(self, id, type, model, engine_power, max_speed, manufacture_date, price):
        self.id = id
        self.type = type
        self.model = model
        self.engine_power = engine_power
        self.max_speed = max_speed
        self.manufacture_date = manufacture_date
        self.price = price

    def __str__(self):
        return f"{self.id} - {self.type} {self.model}, Power: {self.engine_power}, Speed: {self.max_speed}, Manufactured: {self.manufacture_date}, Price: {self.price}"


class ObjectList:
    def __init__(self):
        self.vehicles = []

    def add_vehicle(self, vehicle):
        self.vehicles.append(vehicle)

    def save_to_file(self, filename):
        with open(filename, 'w') as file:
            for vehicle in self.vehicles:
                file.write(json.dumps(vehicle.__dict__) + '\n')

    def read_from_file(self, filename):
        try:
            with open(filename, 'r') as file:
                for line in file:
                    data = json.loads(line)
                    if isinstance(data, dict):  # Validate if loaded data is a dictionary
                        vehicle = Vehicle(**data)
                        # Additional validation if needed
                        self.add_vehicle(vehicle)
                    else:
                        print("Invalid data format in the file.")
                        break
        except FileNotFoundError:
            print(f"File '{filename}' not found.")
        except json.JSONDecodeError:
            print(f"Error decoding JSON from the file '{filename}'. Invalid JSON format.")

    def encrypt_data(self, key, data):
        cipher = Fernet(key)
        encrypted_data = cipher.encrypt(data)
        return encrypted_data

    def zip_data(self, output_filename):
        with zipfile.ZipFile(output_filename, 'w') as zip_file:
            for i, vehicle in enumerate(self.vehicles):
                zip_file.writestr(f'vehicle_{i}.json', vehicle)

    def save_to_xml(self, filename):
        root = ET.Element("vehicles")
        for vehicle in self.vehicles:
            vehicle_elem = ET.SubElement(root, "vehicle")
            for key, value in vehicle.__dict__.items():
                ET.SubElement(vehicle_elem, key).text = str(value)

        xml_str = ET.tostring(root, encoding='utf-8')
        xml_pretty_str = minidom.parseString(xml_str).toprettyxml(indent="  ")

        with open(filename, 'w') as xml_file:
            xml_file.write(xml_pretty_str)

    def read_from_xml(self, filename):
        tree = ET.parse(filename)
        root = tree.getroot()
        for vehicle_elem in root.findall("vehicle"):
            vehicle_data = {}
            for elem in vehicle_elem:
                vehicle_data[elem.tag] = elem.text
            vehicle = Vehicle(**vehicle_data)
            self.add_vehicle(vehicle)

    def input_vehicle_data(self):
        while True:
            try:
                id = int(input("Enter vehicle id: "))
                if id <= 0:
                    raise ValueError("ID must be an integer greater than 0.")

                type = input("Enter vehicle type: ")
                model = input("Enter vehicle model: ")

                engine_power = int(input("Enter engine power: "))
                if engine_power <= 0:
                    raise ValueError("Engine power must be an integer greater than 0.")

                max_speed = int(input("Enter max speed: "))
                if max_speed <= 0:
                    raise ValueError("Max speed must be an integer greater than 0.")

                # Validate manufacture_date
                while True:
                    try:
                        manufacture_date_str = input("Enter manufacture date (YYYY-MM-DD): ")
                        manufacture_date = datetime.datetime.strptime(manufacture_date_str, "%Y-%m-%d")

                        # Check if the date exists in the calendar
                        datetime.date(manufacture_date.year, manufacture_date.month, manufacture_date.day)

                        break  # Break out of the loop if the date is valid
                    except ValueError:
                        print("Invalid date. Please enter a valid date in the format YYYY-MM-DD.")

                price = int(input("Enter price: "))
                if price <= 0:
                    raise ValueError("Price must be a integer greater than 0.")

                return Vehicle(id, type, model, engine_power, max_speed, manufacture_date_str, price)
            except ValueError as e:
                print(f"Invalid input. {e}")
            except Exception as e:
                print(f"Error: {e}")

    def add_vehicle_from_console(self):
        new_vehicle = self.input_vehicle_data()
        self.add_vehicle(new_vehicle)

    def sort_data(self, field):
        try:
            self.vehicles = sorted(self.vehicles, key=lambda x: getattr(x, field))
        except AttributeError:
            print(f"Invalid field '{field}' for sorting. Check your data structure.")


# def main():
#     obj_list = ObjectList()
#
#     # Use Case 1: Add vehicles from the console
#     print("Use Case 1: Add vehicles from the console")
#     obj_list.add_vehicle_from_console()
#     obj_list.add_vehicle_from_console()
#
#     # Use Case 2: Save to JSON file
#     print("\nUse Case 2: Save to JSON file")
#     obj_list.save_to_file('vehicles_1.json')
#
#     # Use Case 3: Read from JSON file with data validation
#     print("\nUse Case 3: Read from JSON file with data validation")
#     obj_list.read_from_file('vehicles.json')
#
#     # Use Case 4: Sort data by a selected field
#     print("\nUse Case 4: Sort data by max_speed")
#     obj_list.sort_data('max_speed')
#
#     # Use Case 5: Print the vehicles after sorting
#     print("\nUse Case 5: Print the vehicles after sorting")
#     for vehicle in obj_list.vehicles:
#         print(vehicle)
#
#     # Use Case 6: Save to XML
#     print("\nUse Case 6: Save to XML")
#     obj_list.save_to_xml('vehicles.xml')
#
#     # Use Case 7: Read from XML with data validation
#     print("\nUse Case 7: Read from XML with data validation")
#     obj_list.read_from_xml('vehicles.xml')
#
#     # Use Case 8: Print the vehicles
#     print("\nUse Case 8: Print the vehicles")
#     for vehicle in obj_list.vehicles:
#         print(vehicle)
#
# if __name__ == "__main__":
#     main()