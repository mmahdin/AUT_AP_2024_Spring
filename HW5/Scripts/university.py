import json
from person import Professor, Student

class University:
    _instance_count = 0
    _max_instances = 3

    def __init__(self, name=None, established=None, chancellor=None, filename=None):
        if University._instance_count >= University._max_instances:
            raise RuntimeError("Cannot create more than three instances of University")
        University._instance_count += 1
        
        if filename:
            with open(filename, 'r') as file:
                data = json.load(file)
                self.name = data["name"]
                self.established = data["established"]
                self.chancellor = data["chancellor"]
        else:
            self.name = name
            self.established = established
            self.chancellor = chancellor
        
        self.faculties = []

    def __str__(self):
        return f"Here is {self.name}"

    def which_university_is_this(self, student_number):
        for faculty in self.faculties:
            for student in faculty.students:
                if student.student_number == student_number:
                    return self.name
        return None

    def add_faculties(self, *faculties):
        self.faculties.extend(faculties)

class Faculty:
    def __init__(self, name, university, students=(), professors=[]):
        self.name = name
        self.university = university
        self.students = list(students)
        self.professors = list(professors)

    def add_students(self, *students):
        self.students.extend(students)

    def add_professors(self, *professors):
        self.professors.extend(professors)

    def get_top_remain(self, academic_degree):
        top_student = None
        for student in self.students:
            if student.academic_degree == academic_degree:
                if top_student is None or student.gpa > top_student.gpa:
                    top_student = student
        return top_student

    def __add__(self, other):
        self.professors.extend(other.professors)
        return self

    def __mod__(self, gpa):
        return [student for student in self.students if student.gpa >= gpa]

    def __contains__(self, person):
        if isinstance(person, Professor):
            return person in self.professors
        elif isinstance(person, Student):
            return person in self.students
        return False
