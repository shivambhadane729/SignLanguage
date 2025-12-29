import requests

API_KEY = ""

url = (
    "https://generativelanguage.googleapis.com/v1beta/"
    "models/gemini-2.5-flash:generateContent"
    f"?key={API_KEY}"
)

payload = {
    "contents": [
        {
            "parts": [
                {
                    "text": (
                        "You are an assistive AI for sign language users.\n"
                        "Convert the following detected gesture words into a natural spoken sentence.\n\n"
                        "Words: HELLO THANK YOU"
                    )
                }
            ]
        }
    ]
}

response = requests.post(url, json=payload)
data = response.json()

# ✅ Extract only the generated sentence
sentence = data["candidates"][0]["content"]["parts"][0]["text"]

print("Final Sentence:")
print(sentence)
