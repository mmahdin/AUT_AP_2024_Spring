import functools
import time
from random import random

def exception_handling(max_retries=3, delay=1):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            retries = 0
            while True:
                try:
                    return func(*args, **kwargs)
                except Exception as e:
                    if retries >= max_retries:
                        raise
                    print(f"Error: {e}. Retrying in {delay} seconds...")
                    time.sleep(delay)
                    retries += 1

        return wrapper
    return decorator


@exception_handling(max_retries=5, delay=2)  
def func():
    if random() < 0.3: 
        raise Exception("Error occurred")
    return "Success"

print(func())