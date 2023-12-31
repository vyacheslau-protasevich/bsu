import json
import xml.etree.ElementTree as ET
import zipfile

import rarfile

from .archive_decorators import zip_decorator, rar_decorator


class FileOperations:
    @zip_decorator
    # @rar_decorator
    def read_text_file(self, file, *args, **kwargs):
        if isinstance(file, str):  # Если передан путь, а не файл
            with open(file, "r", encoding="utf-8") as file:
                return file.read()
        elif hasattr(file, 'read'):  # Если передан файл
            return file.read()
        else:
            raise ValueError("Invalid input. Please provide either a file path or a file object.")

    @zip_decorator
    @rar_decorator
    def write_text_file(self, file_path, content, *args, **kwargs):
        with open(file_path, 'w') as file:
            file.write(content)

    @zip_decorator
    @rar_decorator
    def read_xml_file(self, file, *args, **kwargs):
        tree = ET.parse(file)
        root = tree.getroot()
        return root

    @zip_decorator
    @rar_decorator
    def write_xml_file(self, file_path, root, *args, **kwargs):
        tree = ET.ElementTree(root)
        tree.write(file_path)

    @zip_decorator
    @rar_decorator
    def read_json_file(self, file_path, *args, **kwargs):
        with open(file_path, "r", encoding="utf-8") as file:
            return json.load(file)

    @zip_decorator
    @rar_decorator
    def write_json_file(self, file_path, data, *args, **kwargs):
        with open(file_path, 'w') as json_file:
            json.dump(data, json_file)

    def zip_file(self, file_path, zip_path):
        with zipfile.ZipFile(zip_path, 'w') as zip_ref:
            zip_ref.write(file_path)

    def unzip_file(self, zip_path, extract_folder):
        with zipfile.ZipFile(zip_path, 'r') as zip_ref:
            zip_ref.extractall(extract_folder)

    def rar_file(self, file_path, rar_path):
        with rarfile.RarFile(rar_path, 'w') as rar_ref:
            rar_ref.add(file_path)

    def unrar_file(self, rar_path, extract_folder):
        with rarfile.RarFile(rar_path, 'r') as rar_ref:
            rar_ref.extractall(extract_folder)

def a():
    pass


# Пример использования:
file_ops = FileOperations()

# Чтение текстового файла
text_content = file_ops.read_text_file('test/file.txt')

# Запись в текстовый файл
file_ops.write_text_file(file_path='../../../tests/filereader_tests/out/output.txt', content=text_content)

# Чтение XML файла
xml_root = file_ops.read_xml_file('test/file.xml')

# Запись в XML файл
file_ops.write_xml_file('test/out/output.xml', xml_root)

# Чтение JSON файла
json_data = file_ops.read_json_file('test/file.json')

# Запись в JSON файл
file_ops.write_json_file('test/out/output.json', json_data)

# Архивация файла
file_ops.zip_file('test/file.txt', 'test/out/archive.zip')

# Деархивация файла
file_ops.read_text_file('test/out/archive.zip', 'test/out/extracted_folder')

# # Архивация файла в формате RAR
# file_ops.rar_file('test/file.txt', 'test/out/archive.rar')
#
# # Деархивация файла из формата RAR
# file_ops.unrar_file('test/out/archive.rar', 'test/out/extracted_folder_rar')
