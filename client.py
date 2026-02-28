
"""
Interactive CLI client for C Web Server API
Demonstrates all endpoints: status, time, store, retrieve, stats, BST structure
"""

import requests
import json
import time
from datetime import datetime

BASE_URL = "http://localhost:8080"

class APIClient:
    def __init__(self, base_url):
        self.base_url = base_url
        self.session = requests.Session()
    
    def get_status(self):
        """Fetch server status"""
        try:
            resp = self.session.get(f"{self.base_url}/api/status")
            return resp.json()
        except Exception as e:
            return {"error": str(e)}
    
    def get_time(self):
        """Fetch server time"""
        try:
            resp = self.session.get(f"{self.base_url}/api/time")
            return resp.json()
        except Exception as e:
            return {"error": str(e)}
    
    def get_stats(self):
        """Get detailed stats"""
        try:
            resp = self.session.get(f"{self.base_url}/api/stats")
            return resp.json()
        except Exception as e:
            return {"error": str(e)}
    
    def get_bst_structure(self):
        """Get BST structure info"""
        try:
            resp = self.session.get(f"{self.base_url}/api/bst-structure")
            return resp.json()
        except Exception as e:
            return {"error": str(e)}
    
    def store_data(self, key, value):
        """Store key-value pair"""
        try:
            resp = self.session.post(
                f"{self.base_url}/api/store?key={key}&value={value}"
            )
            return resp.json()
        except Exception as e:
            return {"error": str(e)}
    
    def retrieve_data(self, key):
        """Retrieve value by key"""
        try:
            resp = self.session.get(f"{self.base_url}/api/retrieve?key={key}")
            return resp.json()
        except Exception as e:
            return {"error": str(e)}

def print_header(title):
    print(f"\n{'='*60}")
    print(f"  {title}")
    print(f"{'='*60}")

def print_json(data):
    print(json.dumps(data, indent=2))

def demo_interactive():
    """Run interactive demo"""
    client = APIClient(BASE_URL)
    
    print("\n" + "█"*60)
    print("█" + " "*58 + "█")
    print("█  C WEB SERVER - INTERACTIVE API CLIENT DEMO" + " "*11 + "█")
    print("█" + " "*58 + "█")
    print("█"*60)
    
    print("\nTesting HTTP routing, JSON parsing, and data structures...\n")
    
    # Test 1: Server Status
    print_header("1. TEST: Server Status")
    print("Endpoint: GET /api/status")
    status = client.get_status()
    print_json(status)
    
    time.sleep(1)
    
    # Test 2: Server Time
    print_header("2. TEST: Server Time")
    print("Endpoint: GET /api/time")
    server_time = client.get_time()
    print_json(server_time)
    
    time.sleep(1)
    
    # Test 3: Store Data
    print_header("3. TEST: Store Data (Dictionary)")
    print("Endpoint: POST /api/store?key=username&value=john_doe")
    store_result = client.store_data("username", "john_doe")
    print_json(store_result)
    
    time.sleep(1)
    
    # Test 4: Retrieve Data
    print_header("4. TEST: Retrieve Data (BST Lookup)")
    print("Endpoint: GET /api/retrieve?key=username")
    retrieve_result = client.retrieve_data("username")
    print_json(retrieve_result)
    
    time.sleep(1)
    
    # Test 5: Stats
    print_header("5. TEST: Server Statistics")
    print("Endpoint: GET /api/stats")
    stats = client.get_stats()
    print_json(stats)
    
    time.sleep(1)
    
    # Test 6: BST Structure
    print_header("6. TEST: BST Data Structure Info")
    print("Endpoint: GET /api/bst-structure")
    bst_info = client.get_bst_structure()
    print_json(bst_info)
    
    # Summary
    print_header("DEMO SUMMARY")
    print("""
Key Components Demonstrated:
  ✓ HTTP Request Parsing (method, path, query strings)
  ✓ URL Routing (API endpoints dispatcher)
  ✓ JSON Response Building
  ✓ Binary Search Tree (data structure)
  ✓ Dictionary (key-value storage)
  ✓ Server Statistics Tracking
  ✓ Socket Communication (Windows Winsock)

Architecture Highlights:
  • HTTPHandler.c: Endpoint routing & JSON builders
  • test.c: Request parser & dispatcher
  • DataStructures: BST & Dictionary for O(log n) searches
  • Server.c: Low-level socket management

For Interview Demo:
  1. Open http://localhost:8080 in browser (interactive dashboard)
  2. Click buttons to test endpoints live
  3. Show console logs displaying request routing
  4. Explain data structure choices (BST for efficient lookups)
  5. Discuss error handling & socket lifecycle
    """)

def interactive_mode():
    """Interactive menu"""
    client = APIClient(BASE_URL)
    
    print("\n" + "█"*60)
    print("█  C WEB SERVER - INTERACTIVE CLIENT" + " "*23 + "█")
    print("█"*60)
    
    while True:
        print("\n▶ Menu:")
        print("  1. Check server status")
        print("  2. Get server time")
        print("  3. Store data")
        print("  4. Retrieve data")
        print("  5. View stats")
        print("  6. View BST info")
        print("  7. Run full demo")
        print("  0. Exit")
        
        choice = input("\n➤ Enter choice: ").strip()
        
        if choice == "1":
            print_header("Server Status")
            print_json(client.get_status())
        elif choice == "2":
            print_header("Server Time")
            print_json(client.get_time())
        elif choice == "3":
            key = input("Enter key: ").strip()
            value = input("Enter value: ").strip()
            print_header(f"Storing {key}={value}")
            print_json(client.store_data(key, value))
        elif choice == "4":
            key = input("Enter key to retrieve: ").strip()
            print_header(f"Retrieving {key}")
            print_json(client.retrieve_data(key))
        elif choice == "5":
            print_header("Server Statistics")
            print_json(client.get_stats())
        elif choice == "6":
            print_header("Binary Search Tree Structure")
            print_json(client.get_bst_structure())
        elif choice == "7":
            demo_interactive()
        elif choice == "0":
            print("\n✓ Goodbye!")
            break
        else:
            print("Invalid choice, try again")

if __name__ == "__main__":
    import sys
    
    print("\n⏳ Checking if server is running on localhost:8080...")
    try:
        requests.get(BASE_URL, timeout=1)
        print("✓ Server is running!\n")
    except:
        print("✗ Server not found. Start the server first: .\\testserver.exe\n")
        sys.exit(1)
    
    if len(sys.argv) > 1 and sys.argv[1] == "demo":
        demo_interactive()
    else:
        interactive_mode()
