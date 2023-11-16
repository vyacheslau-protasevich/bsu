from Indusrial_programming.main_lab.src.server_side.file_reader import FileOperations

# ToDo: add normal import


def main():
    file_ops = FileOperations()

    # Чтение текстового файла
    text_content = file_ops.read_text_file('file.txt')

    # Запись в текстовый файл
    file_ops.write_text_file(file_path='out/output.txt', content=text_content)

    # Чтение XML файла
    xml_root = file_ops.read_xml_file('file.xml')

    # Запись в XML файл
    file_ops.write_xml_file('out/output.xml', xml_root)

    # Чтение JSON файла
    json_data = file_ops.read_json_file('file.json')

    # Запись в JSON файл
    file_ops.write_json_file('out/output.json', json_data)

    # Архивация файла
    file_ops.zip_file('file.txt', 'out/archive.zip')

    # Деархивация файла
    file_ops.read_text_file('out/archive.zip', 'out/extracted_folder')


if __name__ == '__main__':
    main()
