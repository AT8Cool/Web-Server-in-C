import requests

url = "http://127.0.0.1:8080"
data = {
    "message": "HelloServer"
}

try:
    response = requests.post(url, data=data)
    print("✅ Response from server:")
    print(response.text)
except requests.exceptions.RequestException as e:
    print("❌ Request failed:", e)
