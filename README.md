<h1 align="center">
<strong>AUT_AP_2024_Spring Homework 5</strong>
</h1>

<p align="center">
<strong> Deadline: 1th of Tir - 23:59 o'clock</strong>
</p>

Welcome to your fifth homework assignment for the Advanced Programming Course! This homework is divided into three sections: `Object-Oriented Programming (OOP)`, `Python Decorators`, and `Asynchronous Programming`. Please read the instructions carefully and make sure to complete all the tasks.

## Section 1: Object-Oriented Programming (OOP)

In this section, you will implement several classes to practice your OOP skills in Python. Follow the detailed instructions for each class and method.

### 1. Person Class

This class represents each person. The constructor takes four arguments: `first_name`, `last_name`, `birthday`, and `gender`.

- The `birthday` is a private variable.
- This class cannot be instantiated directly.

### 2. Student Class

The constructor of this class takes the following arguments: `first_name`, `last_name`, `birthday`, `gender`, `faculty`, `academic_degree`, `university`, and `gpa`.

- The default value of `gpa` is 15.
- The `academic_degree` must be one of the following: Bachelor, Master, Doctoral. Otherwise, raise a `ValueError`.
- `faculty` and `university` are instances of the `Faculty` and `University` classes, respectively.
- Each student has a unique, immutable 6-digit student number. Attempting to modify it should raise a `ConstError`.
- Implement the `ConstError` exception in `exceptions.py`.
- The `get_age()` method should return the age of the student. if today is 2/2/2024 and birthday is 1/2/2000 you should return 24 and if birhday is 3/2/2000 you should return 21.
- This class should be printable and output the format: `I am (first name) (last name) and studying at (university)`.

### 3. Professor Class

The constructor takes the following arguments: `first_name`, `last_name`, `birthday`, `gender`, `faculty`, `academic_rank`, `university`, and `salary`.

- The `salary` is a private variable.
- This class should be printable and output the format: `I am (academic rank) (first name) (last name) and studying at (university)`.
- The `academic_rank` must be one of the following: Professor, Associate Professor, Assistant Professor, Lecturer. Otherwise, raise a `ValueError`.
- The `get_age()` method should return the age of the professor.

**Person, Student and Professor classes must be implemented in person.py file.**

### 4. University Class

This class has member variables: `name`, `established`, `chancellor`, and `faculties`.

- The constructor can either take a filename (with `name`, `established`, and `chancellor` stored in it) or these attributes directly.
- This class should be printable and output the format: `Here is (name)`.
- The `which_university_is_this` method returns the university of a student given their student number.
- The `add_faculties` method adds faculties to the `faculties` list.
- You can only create three instances of the `University` class. Creating more should raise a `RuntimeError`.

### 5. Faculty Class

The constructor takes the following arguments: `name` and `university`, with optional `students` (tuple) and `professors` (list).

- The `add_students()` and `add_professors()` methods add objects to the respective lists.
- The `get_top_remain()` method returns the student with the highest GPA for a specified academic degree.
- Summing two faculties together should merge their professors into the first faculty.
- Using the `%` operator should filter and return a list of students with a GPA greater than or equal to a specified value.
- Ensure that membership checks (`in` operator) work for both professors and students in a faculty.

**Faculty and University classes must be implemented in university.py file.**

## Section 2: Python Decorators

In this section, you will practice writing Python decorators to modify the behavior of functions.

### A. Reverse String Decorator

Modify the `reverse_string` decorator to reverse the output string of a function. If the output is not a string, return `None`.

```python
# MODIFY THIS DECORATOR
def reverse_string(func):
    """If output is a string, reverse it. Otherwise, return None."""
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

# TARGET FUNCTIONS
@reverse_string
def get_university_name() -> str:
    return "Western Institute of Technology and Higher Education"

@reverse_string
def get_university_founding_year() -> int:
    return 1957

# TEST OUPUT
print(
    get_university_name(),
    get_university_founding_year(),
    sep="\n"
)
```

### B. Prime Filter Decorator

Modify the `prime_filter` decorator to filter and return only prime integers from a list of integers returned by a function.

```python
# MODIFY THIS DECORATOR
def prime_filter(func):
    """Given a list of integers, return only the prime integers."""
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

# TARGET FUNCTIONS
@prime_filter
def numbers(from_num: int, to_num: int) -> List[int]:
    return [num for num in range(from_num, to_num)]

# TEST OUPUT
print(numbers(from_num=2, to_num=20))
```

### C. Choose One Decorator

Modify the `choose_one` decorator to select and return a random element from a list of elements returned by a function.

```python
# MODIFY THIS DECORATOR
def choose_one(func):
    """Given a list of elements, select a random one."""
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

# TARGET FUNCTIONS
@choose_one
def available_options() -> List[str]:
    return ["A", "B", "C"]

# TEST OUPUT
print(available_options())
```

### D. Power Meta-Decorator

Modify the `power` meta-decorator to return a tuple where the first element is the original number and the second is the nth power of the number.

```python
# MODIFY THIS META DECORATOR
def power(n: int):
    """Given a number, return a tuple where the first element is the
    original number and the second is the nth power."""
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        return wrapper
    return decorator

# TARGET FUNCTIONS
@power(n=5)
def get_random_number(from_num: int, to_num: int):
    return random.randint(a=from_num, b=to_num)

# TEST OUPUT
print(get_random_number(50, 100))
```

### E. Mask Data Decorator

Modify the `mask_data` decorator to replace the value of a specified dictionary key with a masked version.

```python
# MODIFY THIS DECORATOR
def mask_data(target_key: str, replace_with: str = "*"):
    """Replace the value of a dictionary with a 'masked' version."""
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        return wrapper
    return decorator

# TARGET FUNCTIONS
@mask_data(target_key="name")
def get_user(name: str, age: int):
    return {
        "name": name,
        "age": age
    }

# TEST OUPUT
print(
    get_user(name="Alice", age=30),
    get_user(name="Bob", age=25),
    sep="\n"
)
```

Please ensure you test your decorators with the provided target functions and verify the outputs.

Sure, here are two tasks designed to help students understand and practice asynchronous programming in Python:

## Section 3: Asynchronous Programming in Python

In this section, you will work on tasks that involve asynchronous programming using `asyncio`. These tasks are designed to help you understand how to write and manage asynchronous code in Python.

### Task 1: Fetch Data from Multiple APIs Concurrently

In this task, you will write a program that fetches data from multiple APIs concurrently. This will help you understand how to use `asyncio` to run multiple I/O-bound tasks in parallel.

1. Create a file named `async_fetch.py`.
2. Write an asynchronous function `fetch_data(url: str) -> dict` that takes a URL and returns the JSON response as a dictionary.
3. Write another asynchronous function `main(urls: List[str]) -> List[dict]` that takes a list of URLs, fetches data from all the URLs concurrently, and returns a list of the JSON responses.
4. Use the `aiohttp` library to perform the HTTP requests. Make sure to handle exceptions and retries in case of network errors.
5. Test your program with at least three different APIs that return JSON data.

Example Test:

```python
urls = [
    'https://jsonplaceholder.typicode.com/posts/1',
    'https://jsonplaceholder.typicode.com/posts/2',
    'https://jsonplaceholder.typicode.com/posts/3'
]

asyncio.run(main(urls))
```

### Task 2: Implement a Simple Asynchronous Web Crawler

In this task, you will implement a simple asynchronous web crawler that visits a list of URLs, extracts links from the pages, and continues to visit the new links up to a certain depth. This task will help you understand how to manage concurrency and synchronization in an asynchronous context.

1. Create a file named `async_crawler.py`.
2. Write an asynchronous function `fetch_page(url: str) -> str` that fetches the HTML content of a given URL.
3. Write a function `extract_links(html: str) -> List[str]` that extracts and returns all the hyperlinks from the HTML content. You can use the `BeautifulSoup` library for this purpose.
4. Write an asynchronous function `crawl(start_url: str, max_depth: int) -> None` that performs the following:
   - Fetch the HTML content of the `start_url`.
   - Extract links from the fetched HTML.
   - Recursively visit the extracted links up to `max_depth`.
   - Ensure that each URL is visited only once.
5. Use `asyncio` and `aiohttp` for asynchronous network operations, and handle exceptions appropriately.

Example Test:

```python
start_url = 'https://ganjoor.net/'
max_depth = 2

asyncio.run(crawl(start_url, max_depth))
```

<p align="center">
  <img src="./Resource/One-Way-Or-Another.jpeg" alt="It Takes Time, One Way or Another" style="width: 60%;">
</p>

**Best Regards, [Hamidi](https://github.com/smhamidi)**
