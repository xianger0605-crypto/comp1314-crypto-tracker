import requests

def get_crypto_price(coin_id="bitcoin"):
    """Get real cryptocurrency price from CoinGecko API"""
    try:
        url = f"https://api.coingecko.com/api/v3/simple/price"
        params = {
            'ids': coin_id,
            'vs_currencies': 'usd'
        }
        
        response = requests.get(url, params=params)
        response.raise_for_status()
        
        data = response.json()
        return data[coin_id]['usd']
        
    except requests.exceptions.RequestException as e:
        print(f"Error fetching price for {coin_id}: {e}")
        return None
    except KeyError:
        print(f"Invalid coin ID: {coin_id}")
        return None

def get_multiple_prices(coin_ids):
    """Get prices for multiple cryptocurrencies"""
    prices = {}
    for coin_id in coin_ids:
        price = get_crypto_price(coin_id)
        if price is not None:
            prices[coin_id] = price
    return prices
