from data_fetcher import get_crypto_price, get_multiple_prices

def display_menu():
    print("\n" + "="*50)
    print("CRYPTOCURRENCY PRICE TRACKER")
    print("="*50)
    print("1. View Bitcoin Price")
    print("2. View Ethereum Price") 
    print("3. View Top Cryptocurrencies")
    print("4. Custom Coin Search")
    print("5. Exit")
    print("="*50)

def view_top_cryptos():
    print("\nTOP CRYPTOCURRENCIES")
    coins = ["bitcoin", "ethereum", "binancecoin", "ripple", "cardano", "solana", "dogecoin"]
    prices = get_multiple_prices(coins)
    
    for coin, price in prices.items():
        print(f"   {coin.capitalize():<12} ${price:>12,.2f}")

def custom_search():
    coin_id = input("\nEnter cryptocurrency ID (e.g., bitcoin, ethereum): ").strip().lower()
    price = get_crypto_price(coin_id)
    if price:
        print(f"{coin_id.capitalize()}: ${price:,.2f}")
    else:
        print("Coin not found. Check the ID and try again.")

def main():
    print("Cryptocurrency Price Tracker Started!")
    
    while True:
        display_menu()
        choice = input("\nSelect an option (1-5): ")
        
        if choice == '1':
            price = get_crypto_price("bitcoin")
            if price:
                print(f"Bitcoin: ${price:,.2f}")
        elif choice == '2':
            price = get_crypto_price("ethereum")
            if price:
                print(f"Ethereum: ${price:,.2f}")
        elif choice == '3':
            view_top_cryptos()
        elif choice == '4':
            custom_search()
        elif choice == '5':
            print("Thank you for using Crypto Tracker!")
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
