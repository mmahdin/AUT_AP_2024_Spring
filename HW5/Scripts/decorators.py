import functools
from typing import List
import random

#-------------------------------------------------------------------------------
# MODIFY THIS DECORATOR
def reverse_string(func):
    """If output is a string, reverse it. Otherwise, return None."""
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        result = func(*args, **kwargs)
        if isinstance(result, str):
            return result[::-1]
        return None
    return wrapper

# TARGET FUNCTIONS
@reverse_string
def get_university_name() -> str:
    return "Western Institute of Technology and Higher Education"

@reverse_string
def get_university_founding_year() -> int:
    return 1957


#-------------------------------------------------------------------------------
# Function to check if a number is prime
def is_prime(n: int) -> bool:
    for i in range(2, int(n/2)+1):
        if n%i == 0 : 
            return False
    return True

# MODIFY THIS DECORATOR
def prime_filter(func):
    """Given a list of integers, return only the prime integers."""
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        result = func(*args, **kwargs)
        if isinstance(result, list):
            return [num for num in result if is_prime(num)]
        return result
    return wrapper

# TARGET FUNCTIONS
@prime_filter
def numbers(from_num: int, to_num: int) -> List[int]:
    return [num for num in range(from_num, to_num)]


#-------------------------------------------------------------------------------
# MODIFY THIS DECORATOR
def choose_one(func):
    """Given a list of elements, select a random one."""
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        result = func(*args, **kwargs)
        if isinstance(result, list) and result:
            return random.choice(result)
        return None
    return wrapper

# TARGET FUNCTIONS
@choose_one
def available_options() -> List[str]:
    return ["A", "B", "C"]

#-------------------------------------------------------------------------------
# MODIFY THIS META DECORATOR
def power(n: int):
    """Given a number, return a tuple where the first element is the
    original number and the second is the nth power."""
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            original_number = func(*args, **kwargs)
            powered_number = original_number ** n
            return (original_number, powered_number)
        return wrapper
    return decorator

# TARGET FUNCTIONS
@power(n=5)
def get_random_number(from_num: int, to_num: int):
    return random.randint(a=from_num, b=to_num)

#-------------------------------------------------------------------------------
# MODIFY THIS DECORATOR
def mask_data(target_key: str, replace_with: str = "*"):
    """Replace the value of a dictionary key with a 'masked' version."""
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            result = func(*args, **kwargs)
            if isinstance(result, dict) and target_key in result:
                result[target_key] = replace_with * len(result[target_key])
            return result
        return wrapper
    return decorator

# TARGET FUNCTIONS
@mask_data(target_key="name")
def get_user(name: str, age: int):
    return {
        "name": name,
        "age": age
    }

#-------------------------------------------------------------------------------
# TEST OUTPUT
print(
    get_university_name(),
    get_university_founding_year(),
    sep="\n"
)

# TEST OUTPUT
print(numbers(from_num=2, to_num=20))

# TEST OUTPUT
print(available_options())

# TEST OUTPUT
print(get_random_number(50, 100))

# TEST OUTPUT
print(
    get_user(name="Alice", age=30),
    get_user(name="Bob", age=25),
    sep="\n"
)