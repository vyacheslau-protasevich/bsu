class CustomJsonDecoder:
    """ Custom JSON decoder to decode a JSON string into a Python dictionary. """

    def __init__(self):
        self.json_str = None
        self._idx = 0

    def __call__(self, json_str):
        self.json_str = json_str
        self._idx = 0
        return self._parse_object()

    def _parse_object(self):
        result = {}
        self._idx += 2  # Skip the opening curly brace
        while self.json_str[self._idx] != "}":
            key = self._parse_string()
            self._idx += 3  # Skip the colon
            value = self._parse_value()
            result[key] = value
            if self.json_str[self._idx] == ",":
                self._idx += 3  # Skip the comma
        self._idx += 1  # Skip the closing curly brace
        return result

    def _parse_string(self):
        start = self._idx
        while self.json_str[self._idx] not in ['"', "'"]:
            self._idx += 1
        value = self.json_str[start:self._idx]
        return value

    def _parse_value(self):
        if self.json_str[self._idx] == "{":
            return self._parse_object()
        elif self.json_str[self._idx] == "[":
            return self._parse_array()
        elif self.json_str[self._idx] in ['"', "'"]:
            self._idx += 1
            result = self._parse_string()
            self._idx += 1
            return result
        elif self.json_str[self._idx].isdigit() or self.json_str[self._idx] == "-":
            start = self._idx
            while self.json_str[self._idx].isdigit() or self.json_str[self._idx] in ['+', '-', '.', 'e', 'E']:
                self._idx += 1
            return float(self.json_str[start:self._idx])
        elif self.json_str[self._idx] == "t":
            self._idx += 4  # Skip "true"
            return True
        elif self.json_str[self._idx] == "f":
            self._idx += 5  # Skip "false"
            return False
        elif self.json_str[self._idx] == "n":
            self._idx += 4  # Skip "null"
            return None

    def _parse_array(self):
        result = []
        self._idx += 1  # Skip the opening square bracket
        while self.json_str[self._idx] != "]":
            value = self._parse_value()
            result.append(value)
            if self.json_str[self._idx] == ",":
                self._idx += 1  # Skip the comma
        self._idx += 1  # Skip the closing square bracket
        return result
