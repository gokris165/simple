from fastapi import FastAPI, Request
from dotenv import load_dotenv
import os

load_dotenv()

my_value = os.environ["MY_VALUE"]
print(my_value)

app = FastAPI(title="sso-email backend")


@app.post("/send_email")
async def send_email(request: Request):
    data = await request.json()
    print(f"{data['user_name']} | {data['user_email']}")
    print("--Function end--")
