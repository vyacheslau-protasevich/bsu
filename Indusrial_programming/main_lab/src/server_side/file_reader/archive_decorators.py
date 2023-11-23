import zipfile
import rarfile


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


def rar_decorator(func):
    def wrapper(self, file_path, *args, **kwargs):
        if file_path.endswith('.rar'):
            with rarfile.RarFile(file_path, 'r') as rar_ref:
                file_list = rar_ref.namelist()
                if len(file_list) == 1:  # Assume the first file is the one to read
                    with rar_ref.open(file_list[0]) as file_in_rar:
                        return func(self, file_in_rar, *args, **kwargs)
                else:
                    raise ValueError("Archive must contain exactly one file.")
        else:
            return func(self, file_path, *args, **kwargs)
    return wrapper
