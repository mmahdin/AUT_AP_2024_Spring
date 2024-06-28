import asyncio
import aiohttp
import json


API_KEY = '91c21d11575a405ab2c20411242706'

async def fetch_weather(city, session):
    url = f'http://api.weatherapi.com/v1/current.json?key={API_KEY}&q={city}&aqi=no'
    async with session.get(url) as response:
        if response.status == 200:
            data = await response.json()
            temperature = round(data['current']['temp_c'], 2)
            condition = data['current']['condition']['text']
            return {city: f'{temperature}°C, {condition}'}
        else:
            raise Exception(f'Failed to fetch weather for {city}')


async def aggregate_weather(cities):
    async with aiohttp.ClientSession() as session:
        tasks = [fetch_weather(city, session) for city in cities]
        results = await asyncio.gather(*tasks)
        return results
    


    
def main():
    cities = ['New York', 'London', 'Tokyo']
    weather_data = asyncio.run(aggregate_weather(cities))
    print('Weather Report:')
    for data in weather_data:
        city = list(data.keys())[0]
        print(f'{city}: {data[city]}')

main()