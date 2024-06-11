from datetime import date
from exceptions import ConstError
import random

class Person:
    def __init__(self, first_name, last_name, birthday, gender):
        self.first_name = first_name
        self.last_name = last_name
        self._birthday = birthday
        self.gender = gender
        if type(self) is Person:
            raise TypeError("Person class cannot be instantiated directly")

    def get_age(self):
        today = date.today()
        birth_date = date.fromisoformat(self._birthday)
        age = today.year - birth_date.year - ((today.month, today.day) < (birth_date.month, birth_date.day))
        return age


class Student(Person):
    _assigned_numbers = set()

    def __init__(self, first_name, last_name, birthday, gender, faculty, academic_degree, university, gpa=15):
        super().__init__(first_name, last_name, birthday, gender)
        if academic_degree not in ["Bachelor", "Master", "Doctoral"]:
            raise ValueError("Invalid academic degree")
        self.faculty = faculty
        self.academic_degree = academic_degree
        self.university = university
        self.gpa = gpa
        self._student_number = self._generate_unique_student_number()

    @property
    def student_number(self):
        return self._student_number

    @student_number.setter
    def student_number(self, value):
        raise ConstError("Student number is immutable")

    def _generate_unique_student_number(self):
        while True:
            number = random.randint(100000, 999999)
            if number not in self._assigned_numbers:
                self._assigned_numbers.add(number)
                return number

    def __str__(self):
        return f"I am {self.first_name} {self.last_name} and studying at {self.university}"
    
    def get_age(self):
        return super().get_age()


class Professor(Person):
    def __init__(self, first_name, last_name, birthday, gender, faculty, academic_rank, university, salary):
        super().__init__(first_name, last_name, birthday, gender)
        if academic_rank not in ["Professor", "Associate Professor", "Assistant Professor", "Lecturer"]:
            raise ValueError("Invalid academic rank")
        self.faculty = faculty
        self.academic_rank = academic_rank
        self.university = university
        self._salary = salary

    def __str__(self):
        return f"I am {self.academic_rank} {self.first_name} {self.last_name} and teaching at {self.university}"

    def get_age(self):
        return super().get_age()
