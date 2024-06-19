import asyncio
import aiohttp
from typing import List, Dict

async def fetch_data(url: str) -> Dict:
    """Fetch JSON data from the given URL and return it as a dictionary."""
    async with aiohttp.ClientSession() as session:
        try:
            async with session.get(url) as response:
                response.raise_for_status()
                return await response.json()
        except aiohttp.ClientError as e:
            print(f"Error fetching data from {url}: {e}")
            await asyncio.sleep(1)  # Wait before retrying
        return {}  # Return an empty dictionary if all retries fail

async def main(urls: List[str]) -> List[Dict]:
    """Fetch data from all the URLs concurrently and return a list of JSON responses."""
    tasks = [fetch_data(url) for url in urls]
    return await asyncio.gather(*tasks)

# Example Test
if __name__ == "__main__":
    urls = [
        'https://jsonplaceholder.typicode.com/posts/1',
        'https://jsonplaceholder.typicode.com/posts/2',
        'https://jsonplaceholder.typicode.com/posts/3'
    ]
    results = asyncio.run(main(urls))
    for result in results:
        print(result)
