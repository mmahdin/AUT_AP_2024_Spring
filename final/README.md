## STL Question 1: Merge and Modify

### Overview

In this task, you are required to merge two pre-sorted vectors of integers and then modify the merged vector by adding a constant value to every element. The main goal is to familiarize yourself with combining and transforming data using C++ STL functions without using loops.

### Function to Implement

#### **Merge and Modify**

- **Function Signature**:
  ```cpp
  void merge_and_modify(std::vector<int>& v1, const std::vector<int>& v2, int addend);
  ```

- **Expected Behavior**: The function merges the second vector (`v2`) into the first vector (`v1`) and then increases each element of the merged vector by a given value (`addend`).

### Hints

1. **Merging Vectors**: Use the `std::merge` function. This function requires that both input ranges are already sorted and outputs to a destination that has enough space to hold the results.
2. **Modifying Elements**: After merging, apply a transformation to all elements in the resulting vector to add a specified value (`addend`). Consider using the `std::transform` function.
3. **Function Prototypes**:
   - `std::merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first);`
   - `std::transform(InputIt first, InputIt last, OutputIt d_first, UnaryOperation unary_op);`

---

## STL Question 2: Remove and Collect

### Overview

This task requires you to remove elements from a vector that exist in a given set and return these removed elements in a new vector. This will help you practice using STL functions to manipulate and filter data without explicit loops.

### Function to Implement

#### **Remove and Collect**

- **Function Signature**:
  ```cpp
  std::vector<int> remove_and_collect(std::vector<int>& v, const std::set<int>& to_remove);
  ```

- **Expected Behavior**: Modify the vector `v` by removing all elements that are present in the `to_remove` set. Return these removed elements in a new vector.

### Hints

1. **Identifying Elements to Remove**: Use `std::copy_if` to copy elements that need to be removed into a new vector.
2. **Erasing Elements**: Apply the erase-remove idiom using `std::remove_if` to remove elements from the original vector.
3. **Lambda Functions**: Both the `std::copy_if` and `std::remove_if` functions will need a lambda that checks if an element is in the `to_remove` set.
4. **Function Prototypes**:
   - `std::copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate pred);`
   - `std::remove_if(ForwardIt first, ForwardIt last, UnaryPredicate pred);`

## STL Testing

Test your program with the following code, add your functions definition and run the following code:
```cpp
#include <iostream>
#include <vector>
#include <set>
#include <algorithms>

// Function declarations for the tasks
void merge_and_modify(std::vector<int>& v1, const std::vector<int>& v2, int addend);
std::vector<int> remove_and_collect(std::vector<int>& v, const std::set<int>& to_remove);

// Main function to run the tests
int main() {
    // Test for merge_and_modify
    std::vector<int> vector1 {1, 3, 5};
    std::vector<int> vector2 {2, 4, 6};
    merge_and_modify(vector1, vector2, 10);
    std::cout << "After merging and modifying: ";
    for (int num : vector1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Test for remove_and_collect
    std::vector<int> vector3 {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::set<int> to_remove {1, 3, 5, 7};
    std::vector<int> removed = remove_and_collect(vector3, to_remove);
    std::cout << "Remaining elements: ";
    for (int num : vector3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "Removed elements: ";
    for (int num : removed) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

---

## Python Decorator Question 1: Context Logging Decorator

### Overview

This task involves creating a `context_logging` decorator that enriches a function by logging detailed information about its execution. This includes when the function is called, what arguments it was called with, its return value, and when it finished executing. This decorator is invaluable for debugging and monitoring the performance of functions in a production environment.

### Function to Implement

#### **Context Logging Decorator**

- **Expected Behavior**: Decorate a function to log:
  1. The timestamp and the function name at the start of execution.
  2. The arguments with which the function is called.
  3. The result of the function.
  4. The timestamp and the function name upon completion of execution.

### Hints

1. **Logging Setup**: Consider using the `datetime` module to capture the current time at the beginning and end of the function's execution.
2. **Decorating Functions**: Apply the decorator to functions to automatically log the required information.
3. **Result Handling**: Ensure that the decorator correctly captures and logs the return value of the function.
4. **Print Statements**: Use print statements for logging within the decorator.

### Testing

Test this decorator by applying it to a function that performs simple arithmetic operations or string manipulations. Verify that all logs are printed correctly reflecting the function's execution process.

---

## Python Decorator Question 2: Retry Mechanism Decorator

### Overview

Develop a `retry` decorator that enhances the reliability of functions by allowing them to attempt re-execution upon encountering errors. This decorator should attempt to execute a function up to a specified number of retries if exceptions are thrown, making it particularly useful for handling transient errors in network requests or file operations.

### Function to Implement

#### **Retry Decorator**

- **Expected Behavior**: Automatically retry a function’s execution if it raises an exception, up to a specified number of times. The number of retries should be configurable.

### Hints

1. **Exception Handling**: Implement exception handling within the decorator to catch failures in the function execution.
2. **Retry Logic**: Incorporate a loop to manage the number of retry attempts.
3. **Configurability**: Allow the decorator to accept a parameter specifying the maximum number of retries.
4. **Delay Between Retries**: Optionally implement a delay (e.g., using `time.sleep`) between retries to handle use cases like rate limiting or temporary resource unavailability.

### Testing

Test the decorator with a function that can fail intermittently (e.g., by raising an exception randomly). Ensure that the function either succeeds within the allowed number of retries or raises an exception after all retries are exhausted.

---

## Python ASYNC Question: Asynchronous Weather API Integration

### Overview

This task involves developing an asynchronous Python program to fetch and display weather conditions for multiple cities using an external API. Your implementation must asynchronously gather weather data from multiple cities concurrently using the `aiohttp` library and then print a formatted weather report.

### Function to Implement

#### **API Key and URL Configuration**

- **API Key**: `91c21d11575a405ab2c20411242706`
- **URL Template**: Use the following endpoint to fetch weather data:
  ```
  http://api.weatherapi.com/v1/current.json?key={API_KEY}&q={CITY}&aqi=no
  ```

#### **`fetch_weather` Function**

- **Purpose**: Fetch weather data for a single city.
- **Inputs**: `city` (string), `session` (aiohttp.ClientSession object)
- **Outputs**: A dictionary with the city as the key and a string combining the temperature in Celsius and weather condition as the value.
- **Details**: Construct the request URL using the city and API key, send the HTTP request, and parse the JSON response to extract and return temperature and weather condition.

#### **`aggregate_weather` Function**

- **Purpose**: Aggregate weather data for multiple cities.
- **Inputs**: `cities` (list of strings)
- **Outputs**: A list of dictionaries returned by `fetch_weather`.
- **Details**: Manage an HTTP session and use asyncio to concurrently fetch weather data for each city.

#### **Main Function and Execution**

- **Implementation**: Initialize a list of cities, call `aggregate_weather`, and print a formatted weather report.
- **Example Output**: For each city, format should be: `City: Temperature°C, Weather Condition`

### Hints

1. **Concurrency**: Use `asyncio.gather` to handle concurrent HTTP requests efficiently.
2. **HTTP Session Management**: Utilize `aiohttp.ClientSession` to manage HTTP sessions.
3. **Exception Handling**: Implement error handling for HTTP requests to manage potential failures.
4. **Formatting and Output**: Ensure the output is clearly formatted for easy reading.

### Testing

Test your program with a predefined list of cities such as "New York", "London", and "Tokyo". Ensure that the program correctly fetches and displays the weather information concurrently and handles any exceptions gracefully.

### Example Output
```
Weather Report:
New York: 22.2°C, Light rain
London: 19.3°C, Clear
Tokyo: 29.0°C, Partly cloudy
```
