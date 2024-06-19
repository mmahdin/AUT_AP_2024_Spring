import asyncio
import aiohttp
from aiohttp import ClientError
from bs4 import BeautifulSoup
from typing import List, Set, Tuple

async def fetch_page(url: str) -> Tuple[str, str]:
    """Fetch the HTML content of a given URL asynchronously."""
    try:
        async with aiohttp.ClientSession() as session:
            async with session.get(url) as response:
                response.raise_for_status()
                content_type = response.headers.get('Content-Type', '')
                if 'text/html' in content_type:
                    return await response.text(), url
                else:
                    print(f"Skipping non-HTML content at {url}")
                    return '', url
    except ClientError as e:
        print(f"Failed to fetch {url}: {e}")
        return "", url
    except asyncio.TimeoutError:
        print(f"Timeout while fetching {url}")
        return "", url
    except Exception as e:
        print(f"Unexpected error fetching {url}: {e}")
        return "", url

def extract_links(html: str) -> List[str]:
    """Extract and return all hyperlinks from the HTML content."""
    soup = BeautifulSoup(html, 'html.parser')
    links = [a.get('href') for a in soup.find_all('a', href=True)]
    return links

async def crawl(start_url: str, max_depth: int) -> None:
    """Recursively visit the extracted links up to max_depth."""
    visited_urls: Set[str] = set()

    async def _crawl(url: str, depth: int):
        if url in visited_urls or depth > max_depth:
            return
        visited_urls.add(url)
        html, fetched_url = await fetch_page(url)
        if html:
            links = extract_links(html)
            tasks = [_crawl(link, depth + 1) for link in links if link.startswith('http')]
            await asyncio.gather(*tasks)

    await _crawl(start_url, 0)

# Example Test
if __name__ == "__main__":
    start_url = 'https://ganjoor.net/'
    max_depth = 2
    asyncio.run(crawl(start_url, max_depth))
