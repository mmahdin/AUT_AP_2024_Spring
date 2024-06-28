from time import time
import datetime
import functools

def context_logging(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        # start time, function name, arguments
        print(f"Start: {datetime.datetime.now()} - {func.__name__}")

        # arguments
        print(f"Arguments: {args}, {kwargs}")

        # execute the function
        result = func(*args, **kwargs)

        print("Result: ", result)

        # end time, function name , result
        print(f"End: {datetime.datetime.now()} - {func.__name__}")
        return result
    return wrapper

@context_logging
def add(a, b):
    return a + b

add(2, 3)